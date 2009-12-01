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


//�إ��n����
bool dsSound::Create(LPCTSTR file , DWORD flags, LPDIRECTSOUND8 ds_DS,bool isLooping)
{
	HMMIO mmIO = NULL ;
	MMCKINFO mmRiff ;
	MMCKINFO mmChunk ;
	bool ok ;
	LPDIRECTSOUNDBUFFER buffer1=NULL;
	//�P�w�����O�_�w�إ�
	if( !ds_DS ) 
		return false ;
	//�����¤���
	Release();
	//�}��
	mmIO = mmioOpen((LPWSTR) file , NULL , MMIO_ALLOCBUF | MMIO_READ );
	if( mmIO == NULL )
		return false ;
	//���o�n���ɶ}�Y
	mmRiff.fccType = mmioFOURCC( 'W' , 'A' , 'V' , 'E' );
	ok = mmioDescend( mmIO , &mmRiff , NULL , MMIO_FINDRIFF ) == MMSYSERR_NOERROR ;
	//���o���ɮ榡
	if( ok )
	{
		mmChunk.ckid = mmioFOURCC( 'f' , 'm' , 't' , ' ' );
		ok = mmioDescend( mmIO , &mmChunk , &mmRiff , MMIO_FINDCHUNK ) == MMSYSERR_NOERROR ;
	}
	if( ok )
		ok = mmioRead( mmIO , (char*)&m_Format , sizeof( WAVEFORMATEX )) != -1 ;
	if( ok )
		ok = mmioAscend( mmIO , &mmChunk , 0 ) == MMSYSERR_NOERROR ;
	//���o���ɸ�ƶ}�Y
	if( ok )
	{
		mmChunk.ckid = mmioFOURCC( 'd' , 'a' , 't' , 'a' );
		ok = mmioDescend( mmIO , &mmChunk , &mmRiff , MMIO_FINDCHUNK ) == MMSYSERR_NOERROR ;
		m_Size = mmChunk.cksize ;
	}
	//�إ��n���w�İ�
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
	//�إ�DX8�n���w�İ�
	if( ok )
		if( buffer1->QueryInterface( IID_IDirectSoundBuffer8 , (LPVOID*)&m_Buffer ) == DS_OK )
			buffer1->Release();
		else ok = false ;

		//���o�n�����
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
		//��������
		mmioClose( mmIO , 0 );

		m_isLooping = isLooping;

		return ok ;
}

//�O�_���b����
bool dsSound::isPlaying()
{
	DWORD dwStatus;
	//�p�G���o���񪬺A���Ѫ��ܴN�Ǧ^false
	if (m_Buffer->GetStatus(&dwStatus) != DS_OK)
		return false;
	//�p�G���񤤴N�Ǧ^true
	if(dwStatus & DSBSTATUS_PLAYING)
		return true;
	return false;
}


// ����
bool dsSound::Play()
{
	if( m_Buffer )
	{
		Restore(m_Buffer);
		//�p�G�D���񤤴N����,�_�h���������
		if(!isPlaying())
			m_Buffer->Play(0 , 0 , m_isLooping);
		return true;
	}
	return false;
}

//�����
bool dsSound::Stop()
{
	if( m_Buffer ) 
	{
		//����ç⼽��ɶ��]��0
		m_Buffer->Stop(); 
		m_Buffer->SetCurrentPosition(0);
		return true;
	}
	return false;
}

//����
bool dsSound::RePlay()
{
	if(m_Buffer) 
	{
		//����ç⼽��ɶ��]��0,�M��b����
		m_Buffer->Stop(); 
		m_Buffer->SetCurrentPosition(0);
		m_Buffer->Play(0 , 0 , m_isLooping);
		return true;
	}
	return false;
}

//�Ȱ�
bool dsSound::Pause()
{
	if( m_Buffer ) 
	{
		//�����
		m_Buffer->Stop(); 
		return true;
	}
	return false;
}

//��_�n���w�İ�
void dsSound::Restore(LPDIRECTSOUNDBUFFER8 buffer)
{
	DWORD dwStatus;

	//���o�w�İϪ��A
	if( buffer->GetStatus( &dwStatus ) != DS_OK )
		return ;
	//�P�w�w�İϬO�_��
	if( dwStatus & DSBSTATUS_BUFFERLOST )
	{
		//�C�j10ms�յۦ^�ƽw�İ�
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
	//�W�v
	if(m_Buffer->GetFrequency(&oF) == DS_OK)
		if (Frequency + oF >= 100 && Frequency + oF <= 200000)
			m_Buffer->SetFrequency(Frequency + oF);
	//�n�D
	if(m_Buffer->GetPan(&oP) == DS_OK)
		if (Pan + oP >= -10000 && Pan + oP <= 10000)
			m_Buffer->SetPan(Pan + oP);
	//���q
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
//���Ƽ��񪫥�

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
	//�����ƻs�w�İ�
	if(m_Duplicate)
		for(i = 0 ; i < m_Num ; i++)
			if(m_Duplicate[i])
				m_Duplicate[i]->Release();
	//�����ƻs�w�Ī������O����
	free(m_Duplicate);
	//��������w�İ�
	dsSound::Release();
	//�k�s
	Init();
}

bool dsDuplicate::isPlaying(int index)
{
	if (!IsExist(index))
		return false;
	DWORD dwStatus;
	//�p�G���o���񪬺A���Ѫ��ܴN�Ǧ^false
	if (m_Duplicate[index]->GetStatus(&dwStatus))
		return false;
	//�p�G���񤤴N�Ǧ^true
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
		//�p�G�D���񤤴N����,�_�h���������
		if(!isPlaying(index))
		{
			m_Duplicate[index]->Play(0 , 0 , GetIsLooping());

		}
		return true;
	}
	return false;
}

//�����
bool dsDuplicate::Stop(int index)
{
	if (!IsExist(index))
		return false;
	if(m_Duplicate[index]) 
	{
		//����ç⼽��ɶ��]��0
		m_Duplicate[index]->Stop(); 
		m_Duplicate[index]->SetCurrentPosition(0);
		return true;
	}
	return false;
}

//����
bool dsDuplicate::RePlay(int index)
{
	if (!IsExist(index))
		return false;
	if(m_Duplicate[index]) 
	{
		//����ç⼽��ɶ��]��0,�M��b����
		m_Duplicate[index]->Stop(); 
		m_Duplicate[index]->SetCurrentPosition(0);
		m_Duplicate[index]->Play(0, 0, GetIsLooping());
		return true;
	}
	return false;
}

//�Ȱ�
bool dsDuplicate::Pause(int index)
{
	if (!IsExist(index))
		return false;
	if(m_Duplicate[index]) 
	{
		//�����
		m_Duplicate[index]->Stop(); 
		return true;
	}
	return false;
}
// �إ�

bool dsDuplicate::Duplicate(LPCTSTR file , DWORD flags, int num, LPDIRECTSOUND8 ds_DS, bool isLooping)
{
	int i ;
	Release();
	//�إ߸�ƽw�İ�
	if( !Create(file , flags, ds_DS, isLooping))
		return false;
	//�إ߭��Ƽ���w�İϤ����O����
	m_Duplicate = (LPDIRECTSOUNDBUFFER8*)malloc(sizeof( LPDIRECTSOUNDBUFFER ) * num);
	memset(m_Duplicate, 0, sizeof(LPDIRECTSOUNDBUFFER) * num);
	//�إ߽w�İ�
	for(i = 0 ; i < num ; i++)
	{
		if( ds_DS->DuplicateSoundBuffer(GetBuffer() , (LPDIRECTSOUNDBUFFER*)&m_Duplicate[i] )!= DS_OK)
		{
			//�p�G���@�ӫإߥ��ѴN�⤧�e��release�M��Ǧ^false
			for (int i2 = 0; i2 < i; i2++)
				m_Duplicate[i2]->Release();
			return false ;
		}

	}
	m_Num = num ;
	return true ;
}



/*/////////////////////////////////////////////

����

/*/////////////////////////////////////////////
void dsDuplicate::MoveDuplicateParameters( int index , DWORD Frequency, LONG Pan, LONG Volume)
{
	if (!IsExist(index))
		return;
	DWORD oF ;
	LONG oP ;
	LONG oV	;
	//�W�v
	if(m_Duplicate[index]->GetFrequency(&oF) == DS_OK)
		if (Frequency + oF >= 100 && Frequency + oF <= 200000)
			m_Duplicate[index]->SetFrequency(Frequency + oF);
	//�n�D
	if(m_Duplicate[index]->GetPan(&oP) == DS_OK)
		if (Pan + oP >= -10000 && Pan + oP <= 10000)
			m_Duplicate[index]->SetPan(Pan + oP);
	//���q
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
	//Com�����Ϥ�
	CoInitialize(0);
	if( DirectSoundCreate8( NULL, &ds_DS, NULL ) != DS_OK )
		return ;
	// �]�w�s������ 
	if( ds_DS->SetCooperativeLevel( hWnd, DSSCL_PRIORITY ) != DS_OK )
		return ;
	//�]�w����w�İϮ榡
	LPDIRECTSOUNDBUFFER Primary ;

	//�إ߼���w�İ� 
	DSBUFFERDESC dsbd;
	ZeroMemory( &dsbd, sizeof(DSBUFFERDESC) );
	dsbd.dwSize        = sizeof(DSBUFFERDESC);
	dsbd.dwFlags       = DSBCAPS_PRIMARYBUFFER;
	dsbd.dwBufferBytes = 0;
	dsbd.lpwfxFormat   = NULL;

	if( ds_DS->CreateSoundBuffer( &dsbd, &Primary, NULL ) != DS_OK )
		return ;
	//�]�w����榡 
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
	//�]�w�����A��������
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
	//�p�G�ন�\����play�N�Ǧ^true,��l�Ҷ�false
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
	//�p�G�ন�\����play�N�Ǧ^true,��l�Ҷ�false
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
	//�p�G�ন�\����stop�N�Ǧ^true,��l�Ҷ�false
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
	//�p�G�ন�\����stop�N�Ǧ^true,��l�Ҷ�false
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
	//�p�G�ন�\����replay�N�Ǧ^true,��l�Ҷ�false
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
	//�p�G�ন�\����replay�N�Ǧ^true,��l�Ҷ�false
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
	//�p�G�ন�\����pause�N�Ǧ^true,��l�Ҷ�false
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
	//�p�G�ন�\����pause�N�Ǧ^true,��l�Ҷ�false
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
			//�����ثe���񤤪�����,�M���Jvector��
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