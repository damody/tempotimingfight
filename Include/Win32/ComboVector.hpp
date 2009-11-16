
#ifndef ComboVector_I69536f4dm12490dbe5c9mm6927_H
#define ComboVector_I69536f4dm12490dbe5c9mm6927_H
#include <memory.h>

template <class _Ty,int size = 20>	// 會得到一個size-1大小的空間存combo
class ComboVector 
{
public:
	ComboVector();
	~ComboVector();
	bool Add(const _Ty &data);	// 增加一個元素
	void Clear();			// 清除所有元素
	void SetSize(const int newSize);	// 砍掉原來的陣列新建一個新的大小的陣列
	void EatKeys(const int num);		// 吃掉不需要的n個鍵
	bool CheckKeys(const int num, const _Ty *datas) const;	// 判斷絕招陣列
	bool CheckLastKey(const _Ty &datas) const;	// 判斷最後一個鍵
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

