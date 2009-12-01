
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
	DWORD				 m_Size ;//���ɤj�p
	WAVEFORMATEX		 m_Format ;//�����ɮ榡
	LPDIRECTSOUNDBUFFER8  m_Buffer ;//����w�İ�
	bool m_isLooping;
public :
	//�P�_�w�İϸ�ƬO�_��,���N�۰ʧ@���խ״_
	void Restore(LPDIRECTSOUNDBUFFER8 buffer );
	//�[���W�v�B�n�D�B���q
	void MoveParameters(DWORD Frequency, LONG Pan, LONG Volume);
	//�P�_�O�_����
	bool isPlaying();
	//�H�U4�Ӥ��O�O����B����B�����B�Ȱ������
	bool Stop();
	bool Play();
	bool RePlay();
	bool Pause();
	//���J���ɨëإ�
	bool Create( LPCTSTR file, DWORD flags, LPDIRECTSOUND8 ds_DS, bool isLooping = false);
	//����إߪ�����
	void Release();
	//�]�w�O�_�i��`��
	inline void SetLooping(bool isLooping){m_isLooping = isLooping;}
	//���o�إ߭��ɪ��w�İ�, �]��m_Buffer�Oprivate, dsDuplicate���ઽ�����o
	inline LPDIRECTSOUNDBUFFER8 GetBuffer(){return m_Buffer;};
	//���o���ɬO�_���`��
	inline bool GetIsLooping(){return m_isLooping;}
	dsSound();
	~dsSound();

};

/*/////////////////////////////////////////////

���Ƽ��񪫥�

/*/////////////////////////////////////////////
class dsDuplicate : public dsSound 
{
private :
	int m_Num ;//�`�ƶq
	LPDIRECTSOUNDBUFFER8 *m_Duplicate ;
	//�P�_��index�O�_����
	bool IsExist(int index);
public :
	//�H�U4�Ӥ��O�O����B����B�����B�Ȱ������
	bool Stop(int index);
	bool Play(int index);
	bool RePlay(int index);
	bool Pause(int index);
	//�إߦh�����ɪ����
	bool Duplicate( LPCTSTR file, DWORD flags, int num, LPDIRECTSOUND8 ds_DS, bool isLooping = false);
	//�[���W�v�B�n�D�B���q
	void MoveDuplicateParameters( int index, DWORD Frequency, LONG Pan, LONG Volume);
	//�惡class����l��
	void Init();
	//���񦹦h������
	void Release();
	//�P�_�O�_����
	bool isPlaying(int index);
	//���o���h�����ɪ��Ӽ�
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
	//���J�ëإߤ@�ӳ�@����,�ɦW��char*
	bool CreatSound(const char* filename, wchar_t* index);
	//���J�ëإߤ@�Ӧ�dupnum�Ӥ��e���h������,�ɦW��char*
	bool CreatSound(const char* filename, wchar_t* index, int dupnum);
	//���J�ëإߤ@�ӳ�@����,�ɦW��wchar_t*
	bool CreatSound(wchar_t* filename, wchar_t* index);
	//���J�ëإߤ@�Ӧ�dupnum�Ӥ��e���h������,�ɦW��wchar_t*
	bool CreatSound(wchar_t* filename, wchar_t* index, int dupnum);
	//����ثe�Ҧ�����
	void StopDevice();
	//����ϥ�StopDevice()���e�٦b���񪺭���
	void StartDevice();
	//�H�U4�ӬO��@���ɥΪ�����B����B�����B�Ȱ�
	bool Play(wchar_t* index);
	bool Stop(wchar_t* index);
	bool RePlay(wchar_t* index);
	bool Pause(wchar_t* index);
	//�H�U4�ӬO�h�����ɥΪ�����B����B�����B�Ȱ�
	bool Play(wchar_t* index, int index2);
	bool Stop(wchar_t* index, int index2);
	bool RePlay(wchar_t* index, int index2);
	bool Pause(wchar_t* index, int index2);
	//�]�w�Y�ӳ�@���ɩΦh�����ɬO�_�`������
	void SetLooping(wchar_t* index, bool isLooping);
	//�W��Y�ӳ�@���ɪ��W�v�B�n�D�B���q
	void MoveParameters(wchar_t* index, DWORD Frequency, LONG Pan, LONG Volume);
	//�W��Y�Ӧh�����ɪ��W�v�B�n�D�B���q
	void MoveParameters(wchar_t* index, int index2, DWORD Frequency, LONG Pan, LONG Volume);
	//����Ҧ�����
	void Release();
};

#endif
