#include <windows.h>
#include "WaveSound.h"

dsSound::dsSound()
{
	m_Buffer = NULL ;
}

dsSound::~dsSound()
{
	Release();
}


//建立聲音檔
bool dsSound::Create(LPCTSTR file , DWORD flags, LPDIRECTSOUND8 ds_DS,bool isLooping)
{
	HMMIO mmIO = NULL ;
	MMCKINFO mmRiff ;
	MMCKINFO mmChunk ;
	bool ok ;
	LPDIRECTSOUNDBUFFER buffer1=NULL;
	//判定介面是否已建立
	if( !ds_DS ) 
		return false ;
	//移除舊介面
	Release();
	//開檔
	mmIO = mmioOpen((LPWSTR) file , NULL , MMIO_ALLOCBUF | MMIO_READ );
	if( mmIO == NULL )
		return false ;
	//取得聲音檔開頭
	mmRiff.fccType = mmioFOURCC( 'W' , 'A' , 'V' , 'E' );
	ok = mmioDescend( mmIO , &mmRiff , NULL , MMIO_FINDRIFF ) == MMSYSERR_NOERROR ;
	//取得音檔格式
	if( ok )
	{
		mmChunk.ckid = mmioFOURCC( 'f' , 'm' , 't' , ' ' );
		ok = mmioDescend( mmIO , &mmChunk , &mmRiff , MMIO_FINDCHUNK ) == MMSYSERR_NOERROR ;
	}
	if( ok )
		ok = mmioRead( mmIO , (char*)&m_Format , sizeof( WAVEFORMATEX )) != -1 ;
	if( ok )
		ok = mmioAscend( mmIO , &mmChunk , 0 ) == MMSYSERR_NOERROR ;
	//取得音檔資料開頭
	if( ok )
	{
		mmChunk.ckid = mmioFOURCC( 'd' , 'a' , 't' , 'a' );
		ok = mmioDescend( mmIO , &mmChunk , &mmRiff , MMIO_FINDCHUNK ) == MMSYSERR_NOERROR ;
		m_Size = mmChunk.cksize ;
	}
	//建立聲音緩衝區
	DSBUFFERDESC desc;
	if( ok )
	{
		memset( &desc , 0 , sizeof( desc ));
		desc.dwSize = sizeof( desc );
		desc.dwBufferBytes = m_Size ;
		desc.lpwfxFormat = &m_Format ;
		desc.dwFlags = flags ;
		ok = ds_DS->CreateSoundBuffer( &desc , &buffer1 , NULL ) == DS_OK;
	}
	//建立DX8聲音緩衝區
	if( ok )
		if( buffer1->QueryInterface( IID_IDirectSoundBuffer8 , (LPVOID*)&m_Buffer ) == DS_OK )
			buffer1->Release();
		else ok = false ;

		//取得聲音資料
		if( ok )
		{
			LPVOID pPtrl ;
			DWORD size ;
			if( m_Buffer->Lock( 0 , m_Size , &pPtrl , &size , 0 , 0 , 0 ) == DS_OK )
			{
				ok = mmioRead( mmIO , (char*)pPtrl , size ) != -1 ;
				m_Buffer->Unlock( pPtrl , size , 0 , 0 );
			}
		}
		//關掉音檔
		mmioClose( mmIO , 0 );

		m_isLooping = isLooping;

		return ok ;
}

//是否正在播放
bool dsSound::isPlaying()
{
	DWORD dwStatus;
	//如果取得播放狀態失敗的話就傳回false
	if (m_Buffer->GetStatus(&dwStatus) != DS_OK)
		return false;
	//如果播放中就傳回true
	if(dwStatus & DSBSTATUS_PLAYING)
		return true;
	return false;
}


// 播放
bool dsSound::Play()
{
	if( m_Buffer )
	{
		Restore(m_Buffer);
		//如果非播放中就播放,否則不做任何事
		if(!isPlaying())
			m_Buffer->Play(0 , 0 , m_isLooping);
		return true;
	}
	return false;
}

//停止播放
bool dsSound::Stop()
{
	if( m_Buffer ) 
	{
		//停止並把播放時間設為0
		m_Buffer->Stop(); 
		m_Buffer->SetCurrentPosition(0);
		return true;
	}
	return false;
}

//重播
bool dsSound::RePlay()
{
	if(m_Buffer) 
	{
		//停止並把播放時間設為0,然後在播放
		m_Buffer->Stop(); 
		m_Buffer->SetCurrentPosition(0);
		m_Buffer->Play(0 , 0 , m_isLooping);
		return true;
	}
	return false;
}

//暫停
bool dsSound::Pause()
{
	if( m_Buffer ) 
	{
		//停止播放
		m_Buffer->Stop(); 
		return true;
	}
	return false;
}

//恢復聲音緩衝區
void dsSound::Restore(LPDIRECTSOUNDBUFFER8 buffer)
{
	DWORD dwStatus;

	//取得緩衝區狀態
	if( buffer->GetStatus( &dwStatus ) != DS_OK )
		return ;
	//判定緩衝區是否遺失
	if( dwStatus & DSBSTATUS_BUFFERLOST )
	{
		//每隔10ms試著回複緩衝區
		do 
		{
			if( buffer->Restore() == DSERR_BUFFERLOST )
				Sleep( 10 );
			else 
				break ;
		}while( buffer->Restore() != DS_OK );
	}
}

void dsSound::MoveParameters( DWORD Frequency, LONG Pan, LONG Volume)
{
	DWORD oF ;
	LONG oP ;
	LONG oV	;
	if( !m_Buffer )
		return ;
	//頻率
	if(m_Buffer->GetFrequency(&oF) == DS_OK)
		if (Frequency + oF >= 100 && Frequency + oF <= 200000)
			m_Buffer->SetFrequency(Frequency + oF);
	//聲道
	if(m_Buffer->GetPan(&oP) == DS_OK)
		if (Pan + oP >= -10000 && Pan + oP <= 10000)
			m_Buffer->SetPan(Pan + oP);
	//音量
	if(m_Buffer->GetVolume(&oV) == DS_OK)
		if (Volume + oV >= -10000 && Volume + oV <= 0)
			m_Buffer->SetVolume(Volume + oV);
}

void dsSound::Release()
{
	if(m_Buffer) m_Buffer->Release();
	m_Buffer = NULL ;
}


///////////////////////////////////////////////////////////////////////////////////
//重複播放物件

dsDuplicate::dsDuplicate()
{
	Init();
}

void dsDuplicate::Init()
{
	m_Num = 0 ;
	m_Duplicate = NULL ;
}

dsDuplicate::~dsDuplicate()
{
	Release();
}

void dsDuplicate::Release()
{
	int i ;
	//移除複製緩衝區
	if(m_Duplicate)
		for(i = 0 ; i < m_Num ; i++)
			if(m_Duplicate[i])
				m_Duplicate[i]->Release();
	//移除複製緩衝的介面記憶體
	free(m_Duplicate);
	//移除實體緩衝區
	dsSound::Release();
	//歸零
	Init();
}

bool dsDuplicate::isPlaying(int index)
{
	if (!IsExist(index))
		return false;
	DWORD dwStatus;
	//如果取得播放狀態失敗的話就傳回false
	if (m_Duplicate[index]->GetStatus(&dwStatus))
		return false;
	//如果播放中就傳回true
	if(dwStatus & DSBSTATUS_PLAYING)
		return true;
	return false;
}

bool dsDuplicate::Play(int index)
{
	if (!IsExist(index))
		return false;
	if(m_Duplicate[index])
	{
		Restore(m_Duplicate[index]);
		//如果非播放中就播放,否則不做任何事
		if(!isPlaying(index))
		{
			m_Duplicate[index]->Play(0 , 0 , GetIsLooping());

		}
		return true;
	}
	return false;
}

//停止播放
bool dsDuplicate::Stop(int index)
{
	if (!IsExist(index))
		return false;
	if(m_Duplicate[index]) 
	{
		//停止並把播放時間設為0
		m_Duplicate[index]->Stop(); 
		m_Duplicate[index]->SetCurrentPosition(0);
		return true;
	}
	return false;
}

//重播
bool dsDuplicate::RePlay(int index)
{
	if (!IsExist(index))
		return false;
	if(m_Duplicate[index]) 
	{
		//停止並把播放時間設為0,然後在播放
		m_Duplicate[index]->Stop(); 
		m_Duplicate[index]->SetCurrentPosition(0);
		m_Duplicate[index]->Play(0, 0, GetIsLooping());
		return true;
	}
	return false;
}

//暫停
bool dsDuplicate::Pause(int index)
{
	if (!IsExist(index))
		return false;
	if(m_Duplicate[index]) 
	{
		//停止播放
		m_Duplicate[index]->Stop(); 
		return true;
	}
	return false;
}
// 建立

bool dsDuplicate::Duplicate(LPCTSTR file , DWORD flags, int num, LPDIRECTSOUND8 ds_DS, bool isLooping)
{
	int i ;
	Release();
	//建立資料緩衝區
	if( !Create(file , flags, ds_DS, isLooping))
		return false;
	//建立重複播放緩衝區介面記憶體
	m_Duplicate = (LPDIRECTSOUNDBUFFER8*)malloc(sizeof( LPDIRECTSOUNDBUFFER ) * num);
	memset(m_Duplicate, 0, sizeof(LPDIRECTSOUNDBUFFER) * num);
	//建立緩衝區
	for(i = 0 ; i < num ; i++)
	{
		if( ds_DS->DuplicateSoundBuffer(GetBuffer() , (LPDIRECTSOUNDBUFFER*)&m_Duplicate[i] )!= DS_OK)
		{
			//如果有一個建立失敗就把之前的release然後傳回false
			for (int i2 = 0; i2 < i; i2++)
				m_Duplicate[i2]->Release();
			return false ;
		}

	}
	m_Num = num ;
	return true ;
}



/*/////////////////////////////////////////////

控制

/*/////////////////////////////////////////////
void dsDuplicate::MoveDuplicateParameters( int index , DWORD Frequency, LONG Pan, LONG Volume)
{
	if (!IsExist(index))
		return;
	DWORD oF ;
	LONG oP ;
	LONG oV	;
	//頻率
	if(m_Duplicate[index]->GetFrequency(&oF) == DS_OK)
		if (Frequency + oF >= 100 && Frequency + oF <= 200000)
			m_Duplicate[index]->SetFrequency(Frequency + oF);
	//聲道
	if(m_Duplicate[index]->GetPan(&oP) == DS_OK)
		if (Pan + oP >= -10000 && Pan + oP <= 10000)
			m_Duplicate[index]->SetPan(Pan + oP);
	//音量
	if(m_Duplicate[index]->GetVolume(&oV) == DS_OK)
		if (Volume + oV >= -10000 && Volume + oV <= 0)
			m_Duplicate[index]->SetVolume(Volume + oV);

}

bool dsDuplicate::IsExist(int index)
{
	if (index >= m_Num)
		return false;
	return true;
}


WavSound::WavSound(HWND hWnd , DWORD Channels, DWORD Freq, DWORD BitRate)
{
	//Com物件初使化
	CoInitialize(0);
	if( DirectSoundCreate8( NULL, &ds_DS, NULL ) != DS_OK )
		return ;
	// 設定存取等級 
	if( ds_DS->SetCooperativeLevel( hWnd, DSSCL_PRIORITY ) != DS_OK )
		return ;
	//設定播放緩衝區格式
	LPDIRECTSOUNDBUFFER Primary ;

	//建立播放緩衝區 
	DSBUFFERDESC dsbd;
	ZeroMemory( &dsbd, sizeof(DSBUFFERDESC) );
	dsbd.dwSize        = sizeof(DSBUFFERDESC);
	dsbd.dwFlags       = DSBCAPS_PRIMARYBUFFER;
	dsbd.dwBufferBytes = 0;
	dsbd.lpwfxFormat   = NULL;

	if( ds_DS->CreateSoundBuffer( &dsbd, &Primary, NULL ) != DS_OK )
		return ;
	//設定播放格式 
	WAVEFORMATEX wfx;
	ZeroMemory( &wfx, sizeof(WAVEFORMATEX) ); 
	wfx.wFormatTag      = (WORD) WAVE_FORMAT_PCM; 
	wfx.nChannels       = (WORD) Channels; 
	wfx.nSamplesPerSec  = (DWORD) Freq; 
	wfx.wBitsPerSample  = (WORD) BitRate; 
	wfx.nBlockAlign     = (WORD) (wfx.wBitsPerSample / 8 * wfx.nChannels);
	wfx.nAvgBytesPerSec = (DWORD) (wfx.nSamplesPerSec * wfx.nBlockAlign);

	if( Primary->SetFormat(&wfx) != DS_OK )
	{
		Primary->Release();
		return  ;
	}
	//設定完成，移除介面
	Primary->Release();
	isStart = true;
}

bool WavSound::CreatSound(const char* filename, wchar_t* index)
{
	wchar_t *id = new wchar_t[wcslen(index) + 1];
	wcsncpy_s(id, wcslen(index) + 1, index, wcslen(index) + 1);
	if(m_SoundMap.find(id) != m_SoundMap.end())
	{
		delete[] id;
		return false;
	}

	dsSound *newsound = new dsSound();
	wchar_t *w_filename = new wchar_t[strlen(filename) + 2];
	AnsiToUnicode(w_filename, filename);
	if (!newsound->Create((LPCTSTR)w_filename, DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLVOLUME | 
		DSBCAPS_CTRLPAN  , ds_DS))
	{
		delete[] w_filename;
		delete[] id;
		return false;
	}
	delete[] w_filename;
	m_SoundMap.insert(std::make_pair(id, newsound));
	return true;
}

bool WavSound::CreatSound(const char* filename, wchar_t* index, int dupnum)
{
	wchar_t *id = new wchar_t[wcslen(index) + 1];
	wcsncpy_s(id, wcslen(index) + 1, index, wcslen(index) + 1);
	if(m_SoundMap.find(id) != m_SoundMap.end())
	{
		delete[] id;
		return false;
	}

	dsDuplicate *newdupsound = new dsDuplicate();
	wchar_t *w_filename = new wchar_t[strlen(filename) + 2];
	AnsiToUnicode(w_filename, filename);
	if(!newdupsound->Duplicate((LPCTSTR)w_filename, DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLVOLUME | 
		DSBCAPS_CTRLPAN , dupnum, ds_DS))
	{
		delete[] w_filename;
		return false;
	}
	delete[] w_filename;
	m_DupSoundMap.insert(std::make_pair(id, newdupsound));
	return true;
}

bool WavSound::CreatSound(wchar_t* filename, wchar_t* index)
{
	wchar_t *id = new wchar_t[wcslen(index) + 1];
	wcsncpy_s(id, wcslen(index) + 1, index, wcslen(index) + 1);
	if(m_SoundMap.find(id) != m_SoundMap.end())
	{
		delete[] id;
		return false;
	}

	dsSound *newsound = new dsSound();
	if (!newsound->Create((LPCTSTR)filename, DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLVOLUME | 
		DSBCAPS_CTRLPAN , ds_DS))
	{
		return false;
	}
	m_SoundMap.insert(std::make_pair(id, newsound));
	return true;
}

bool WavSound::CreatSound(wchar_t* filename, wchar_t* index, int dupnum)
{
	wchar_t *id = new wchar_t[wcslen(index) + 1];
	wcsncpy_s(id, wcslen(index) + 1, index, wcslen(index) + 1);
	if(m_SoundMap.find(id) != m_SoundMap.end())
	{
		delete[] id;
		return false;
	}
	dsDuplicate *newdupsound = new dsDuplicate();
	if(!newdupsound->Duplicate((LPCTSTR)filename, DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLVOLUME | 
		DSBCAPS_CTRLPAN , dupnum, ds_DS))
	{
		return false;
	}
	m_DupSoundMap.insert(std::make_pair(id, newdupsound));
	return true;
}

bool WavSound::Play(wchar_t* index)
{
	//如果能成功執行play就傳回true,其餘皆傳false
	if (!isStart)
		return false;
	m_SoundMapPos = m_SoundMap.find(index);
	if (m_SoundMapPos != m_SoundMap.end())
	{
		if(m_SoundMapPos->second->Play())
			return true;
	}
	return false;
}

bool WavSound::Play(wchar_t*index, int index2)
{
	//如果能成功執行play就傳回true,其餘皆傳false
	if (!isStart)
		return false;
	m_DupSoundMapPos = m_DupSoundMap.find(index);
	if (m_DupSoundMapPos != m_DupSoundMap.end())
	{
		if(m_DupSoundMapPos->second->Play(index2))
			return true;
	}
	return false;
}


bool WavSound::Stop(wchar_t* index)
{
	//如果能成功執行stop就傳回true,其餘皆傳false
	if (!isStart)
		return false;
	m_SoundMapPos = m_SoundMap.find(index);
	if (m_SoundMapPos != m_SoundMap.end())
	{
		if(m_SoundMapPos->second->Stop())
			return true;
	}
	return false;
}

bool WavSound::Stop(wchar_t* index, int index2)
{
	//如果能成功執行stop就傳回true,其餘皆傳false
	if (!isStart)
		return false;
	m_DupSoundMapPos = m_DupSoundMap.find(index);
	if (m_DupSoundMapPos != m_DupSoundMap.end())
	{
		if(m_DupSoundMapPos->second->Stop(index2))
			return true;
	}
	return false;
}

bool WavSound::RePlay(wchar_t* index)
{
	//如果能成功執行replay就傳回true,其餘皆傳false
	if (!isStart)
		return false;
	m_SoundMapPos = m_SoundMap.find(index);
	if (m_SoundMapPos != m_SoundMap.end())
	{
		if(m_SoundMapPos->second->RePlay())
			return true;
	}
	return false;
}


bool WavSound::RePlay(wchar_t* index, int index2)
{
	//如果能成功執行replay就傳回true,其餘皆傳false
	if (!isStart)
		return false;
	m_DupSoundMapPos = m_DupSoundMap.find(index);
	if (m_DupSoundMapPos != m_DupSoundMap.end())
	{
		if(m_DupSoundMapPos->second->RePlay(index2))
			return true;
	}
	return false;
}

bool WavSound::Pause(wchar_t* index)
{
	//如果能成功執行pause就傳回true,其餘皆傳false
	if (!isStart)
		return false;
	m_SoundMapPos = m_SoundMap.find(index);
	if (m_SoundMapPos != m_SoundMap.end())
	{
		if(m_SoundMapPos->second->Pause())
			return true;
	}
	return false;
}


bool WavSound::Pause(wchar_t* index, int index2)
{
	//如果能成功執行pause就傳回true,其餘皆傳false
	if (!isStart)
		return false;
	m_DupSoundMapPos = m_DupSoundMap.find(index);
	if (m_DupSoundMapPos != m_DupSoundMap.end())
	{
		if(m_DupSoundMapPos->second->Pause(index2))
			return true;
	}
	return false;
}

void WavSound::MoveParameters(wchar_t* index, DWORD Frequency, LONG Pan, LONG Volume)
{
	m_SoundMapPos = m_SoundMap.find(index);
	if (m_SoundMapPos != m_SoundMap.end())
	{
		m_SoundMapPos->second->MoveParameters(Frequency, Pan, Volume);
		return;
	}
}

void WavSound::MoveParameters(wchar_t* index, int index2, DWORD Frequency, LONG Pan, LONG Volume)
{
	m_DupSoundMapPos = m_DupSoundMap.find(index);
	if (m_DupSoundMapPos != m_DupSoundMap.end())
	{
		m_DupSoundMapPos->second->MoveDuplicateParameters(index2, Frequency, Pan, Volume);
		return;
	}
}

void WavSound::Release()
{
	for(m_SoundMapPos = m_SoundMap.begin(); m_SoundMapPos != m_SoundMap.end(); m_SoundMapPos++)
	{
		delete[] (m_SoundMapPos->first);
		m_SoundMapPos->second->Release();
		delete (m_SoundMapPos->second);
		m_SoundMapPos->second = NULL;
	}
	m_SoundMap.clear();
	for(m_DupSoundMapPos = m_DupSoundMap.begin(); m_DupSoundMapPos != m_DupSoundMap.end(); m_DupSoundMapPos++)
	{
		delete[] (m_DupSoundMapPos->first);
		m_DupSoundMapPos->second->Release();
		delete (m_DupSoundMapPos->second);
		m_DupSoundMapPos->second = NULL;
	}
	m_DupSoundMap.clear();
	m_vSound.clear();
	m_mDupSound.clear();
}

WavSound::~WavSound()
{
	Release();
	ds_DS->Release();
}

void WavSound::StopDevice()
{
	if (!isStart)
		return;
	int forindex;
	for (m_SoundMapPos = m_SoundMap.begin(); m_SoundMapPos != m_SoundMap.end(); m_SoundMapPos++)
	{
		if (m_SoundMapPos->second->isPlaying())
		{
			//停止播放目前播放中的音檔,然後放入vector裡
			m_SoundMapPos->second->Pause();
			m_vSound.push_back(m_SoundMapPos->second);
		}
	}
	for (m_DupSoundMapPos = m_DupSoundMap.begin(); m_DupSoundMapPos != m_DupSoundMap.end(); m_DupSoundMapPos++)
	{
		for (forindex=0; forindex < m_DupSoundMapPos->second->GetNum(); forindex++)
		{
			if (m_DupSoundMapPos->second->isPlaying(forindex))
			{
				m_DupSoundMapPos->second->Pause(forindex);
				m_mDupSound.insert(std::make_pair(forindex, m_DupSoundMapPos->second));
			}
		}
	}
	isStart = false;
}

void WavSound::StartDevice()
{
	if (isStart)
		return;
	for (m_vSoundPos = m_vSound.begin(); m_vSoundPos != m_vSound.end(); m_vSoundPos++)
	{
		(*m_vSoundPos)->Play();
	}
	m_vSound.clear();
	for (m_mDupSoundPos = m_mDupSound.begin(); m_mDupSoundPos != m_mDupSound.end(); m_mDupSoundPos++)
	{
		m_mDupSoundPos->second->Play(m_mDupSoundPos->first);
	}
	m_mDupSound.clear();
	isStart = true;
}

void WavSound::SetLooping(wchar_t* index, bool isLooping)
{
	m_SoundMapPos = m_SoundMap.find(index);
	if (m_SoundMapPos != m_SoundMap.end())
	{
		m_SoundMapPos->second->SetLooping(isLooping);
		return;
	}
	m_DupSoundMapPos = m_DupSoundMap.find(index);
	if (m_DupSoundMapPos != m_DupSoundMap.end())
		m_mDupSoundPos->second->SetLooping(isLooping);
}

void WavSound::AnsiToUnicode(wchar_t *unicode, const char *ansi)
{
	int n;
	n = MultiByteToWideChar(CP_ACP, 0, ansi, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, 0, ansi, -1, unicode, n);
} 