
#if !defined(WAVESOUND_H_)
#define WAVESOUND_H_

#include <mmsystem.h>
#include <dsound.h>
#include <map>
#include <vector>
#include <algorithm>
#include <wtypes.h>
#include "../DX9/DateType.h"

#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dsound.lib")
#pragma comment(lib,"winmm.lib")

class dsSound
{
private :
	DWORD				 m_Size ;//音檔大小
	WAVEFORMATEX		 m_Format ;//音效檔格式
	LPDIRECTSOUNDBUFFER8  m_Buffer ;//播放緩衝區
	bool m_isLooping;
public :
	//判斷緩衝區資料是否遺失,有就自動作嘗試修復
	void Restore(LPDIRECTSOUNDBUFFER8 buffer );
	//加減頻率、聲道、音量
	void MoveParameters(DWORD Frequency, LONG Pan, LONG Volume);
	//判斷是否播放中
	bool isPlaying();
	//以下4個分別是停止、播放、重播、暫停的函數
	bool Stop();
	bool Play();
	bool RePlay();
	bool Pause();
	//載入音檔並建立
	bool Create( LPCTSTR file, DWORD flags, LPDIRECTSOUND8 ds_DS, bool isLooping = false);
	//釋放建立的音檔
	void Release();
	//設定是否進行循環
	inline void SetLooping(bool isLooping){m_isLooping = isLooping;}
	//取得建立音檔的緩衝區, 因為m_Buffer是private, dsDuplicate不能直接取得
	inline LPDIRECTSOUNDBUFFER8 GetBuffer(){return m_Buffer;};
	//取得音檔是否為循環
	inline bool GetIsLooping(){return m_isLooping;}
	dsSound();
	~dsSound();

};

/*/////////////////////////////////////////////

重複播放物件

/*/////////////////////////////////////////////
class dsDuplicate : public dsSound 
{
private :
	int m_Num ;//總數量
	LPDIRECTSOUNDBUFFER8 *m_Duplicate ;
	//判斷此index是否有效
	bool IsExist(int index);
public :
	//以下4個分別是停止、播放、重播、暫停的函數
	bool Stop(int index);
	bool Play(int index);
	bool RePlay(int index);
	bool Pause(int index);
	//建立多重音檔的函數
	bool Duplicate( LPCTSTR file, DWORD flags, int num, LPDIRECTSOUND8 ds_DS, bool isLooping = false);
	//加減頻率、聲道、音量
	void MoveDuplicateParameters( int index, DWORD Frequency, LONG Pan, LONG Volume);
	//對此class做初始化
	void Init();
	//釋放此多重音檔
	void Release();
	//判斷是否播放中
	bool isPlaying(int index);
	//取得此多重音檔的個數
	inline int GetNum(){return m_Num;};
	dsDuplicate();
	~dsDuplicate();
};

class WavSound
{
private:
	bool isStart;
	LPDIRECTSOUND8 ds_DS;
	std::map<wchar_t* const, dsSound*, wcharcmp> m_SoundMap;
	std::map<wchar_t* const, dsSound*, wcharcmp>::iterator m_SoundMapPos;
	std::map<wchar_t* const, dsDuplicate*, wcharcmp> m_DupSoundMap;
	std::map<wchar_t* const, dsDuplicate*, wcharcmp>::iterator m_DupSoundMapPos;
	std::vector<dsSound*> m_vSound;
	std::vector<dsSound*>::iterator m_vSoundPos;
	std::map<int, dsDuplicate*> m_mDupSound;
	std::map<int, dsDuplicate*>::iterator m_mDupSoundPos;
	void AnsiToUnicode(wchar_t *unicode, const char *ansi);
public:
	WavSound(HWND hWnd , DWORD Channels = 2 , DWORD Freq =  22050 , DWORD BitRate = 16);
	~WavSound();
	//載入並建立一個單一音檔,檔名用char*
	bool CreatSound(const char* filename, wchar_t* index);
	//載入並建立一個有dupnum個內容的多重音檔,檔名用char*
	bool CreatSound(const char* filename, wchar_t* index, int dupnum);
	//載入並建立一個單一音檔,檔名用wchar_t*
	bool CreatSound(wchar_t* filename, wchar_t* index);
	//載入並建立一個有dupnum個內容的多重音檔,檔名用wchar_t*
	bool CreatSound(wchar_t* filename, wchar_t* index, int dupnum);
	//停止目前所有音檔
	void StopDevice();
	//播放使用StopDevice()之前還在播放的音檔
	void StartDevice();
	//以下4個是單一音檔用的播放、停止、重播、暫停
	bool Play(wchar_t* index);
	bool Stop(wchar_t* index);
	bool RePlay(wchar_t* index);
	bool Pause(wchar_t* index);
	//以下4個是多重音檔用的播放、停止、重播、暫停
	bool Play(wchar_t* index, int index2);
	bool Stop(wchar_t* index, int index2);
	bool RePlay(wchar_t* index, int index2);
	bool Pause(wchar_t* index, int index2);
	//設定某個單一音檔或多重音檔是否循環播放
	void SetLooping(wchar_t* index, bool isLooping);
	//增減某個單一音檔的頻率、聲道、音量
	void MoveParameters(wchar_t* index, DWORD Frequency, LONG Pan, LONG Volume);
	//增減某個多重音檔的頻率、聲道、音量
	void MoveParameters(wchar_t* index, int index2, DWORD Frequency, LONG Pan, LONG Volume);
	//釋放所有音檔
	void Release();
};

#endif
