#ifndef _ConvertType_H
#define _ConvertType_H
#include <vector>
class ConvertType
{
public:
	static void UnicodeToAnsi(const wchar_t* unicode, char* ansi);
	static void AnsiToUnicode(wchar_t* unicode, const char* ansi);
	static const wchar_t* ReturnUnicode(const char* ansi);
	static wchar_t* ReturnUnicode(const wchar_t* ansi);
	static const char* ReturnAnsi(const wchar_t* ansi);
	static char* ReturnAnsi(const char* ansi);
	static void FreeAllMemory();
private:
	static std::vector<char*> array_char;
	static std::vector<wchar_t*> array_wchar_t;
};


#endif // _ConvertType_H