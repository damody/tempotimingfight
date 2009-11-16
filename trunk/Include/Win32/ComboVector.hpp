
#ifndef ComboVector_I69536f4dm12490dbe5c9mm6927_H
#define ComboVector_I69536f4dm12490dbe5c9mm6927_H
#include <memory.h>

template <class _Ty,int size = 20>	// �|�o��@��size-1�j�p���Ŷ��scombo
class ComboVector 
{
public:
	ComboVector();
	~ComboVector();
	bool Add(const _Ty &data);	// �W�[�@�Ӥ���
	void Clear();			// �M���Ҧ�����
	void SetSize(const int newSize);	// �屼��Ӫ��}�C�s�ؤ@�ӷs���j�p���}�C
	void EatKeys(const int num);		// �Y�����ݭn��n����
	bool CheckKeys(const int num, const _Ty *datas) const;	// �P�_���۰}�C
	bool CheckLastKey(const _Ty &datas) const;	// �P�_�̫�@����
	bool IsNull() const;
private:
	_Ty* Keys;
	int head;
	bool nothing;
	int max;
};

template <class _Ty,int size>
bool ComboVector<_Ty, size>::IsNull() const
{
	return nothing;
}

template <class _Ty,int size>
ComboVector<_Ty, size>::ComboVector():head(0),nothing(true),max(size)
{
	Keys = new _Ty[size];
	memset(Keys,0,sizeof(_Ty)*size);
}

template <class _Ty,int size>
bool ComboVector<_Ty, size>::Add(const _Ty &data)
{
	nothing = false;
	if (head<max)
	{
		Keys[head] = data;
		++head;
		return true;
	}
	return false;
}

template <class _Ty,int size>
void ComboVector<_Ty, size>::Clear()
{
	head = 0;
	nothing = true;
}

template <class _Ty,int size>
void ComboVector<_Ty, size>::SetSize( const int newSize )
{
	nothing = true;
	head = 0;
	max = newSize;
	delete[] Keys;
	Keys = new _Ty[newSize];
	memset(Keys,0,sizeof(_Ty)*newSize);
}

template <class _Ty,int size>
void ComboVector<_Ty, size>::EatKeys( const int num )
{
	if (head <= num)
	{
		nothing = true;
		head = 0;
	}
	else
		head -= num;
}

template <class _Ty,int size>
bool ComboVector<_Ty, size>::CheckKeys( const int num, const _Ty *datas ) const
{
	for (int i = 0;i < num;i++)
	{
		if (datas[i] != Keys[head-num+i]) return false;
	}
	return true;
}

template <class _Ty,int size>
bool ComboVector<_Ty, size>::CheckLastKey( const _Ty &data ) const
{
	if (data != Keys[head-1]) return false;
	return true;
}

template <class _Ty,int size>
ComboVector<_Ty, size>::~ComboVector()
{
	delete[] Keys;
}

#endif // ComboVector_I69536f4dm12490dbe5c9mm6927_H

