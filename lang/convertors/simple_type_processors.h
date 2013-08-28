// encoding : utf8
// "Copyright [year] <Copyright Owner>"
/**
  file : #include <uni_convertors/convertors.h>
*/
/*
  Конверторы стандартных типов

  thinks : 
    Для других наверное лучше сделать отдельное простр. 
    или директивыми управлять
*/

#ifndef UNI_CONVERTORS_SIMPLE_TYPE_PROCESSORS_H_
#define UNI_CONVERTORS_SIMPLE_TYPE_PROCESSORS_H_

// C++
#include <map>
#include <string>
#include <vector>

// Other
#ifndef _GCC
#ifndef _SECURE_ATL
  #define _SECURE_ATL 1
#endif
#ifndef VC_EXTRALEAN
  #define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit
// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#ifndef _AFX_NO_OLE_SUPPORT
  #include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
  #include <afxcmn.h>                     // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
  #include <afxsock.h>            // MFC socket extensions
#define _WIN32_DCOM 
//#define  DONT_SHOW_NOSYNC
#define    USE_EFW

// App cfg.
#define CODE_USE
#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

#endif  // _GCC


// !! для преобразований hex-asdf-hex исп только заглавные буквы
//
//
namespace simple_type_processors {
typedef std::map<std::string, std::string> parameters;
typedef unsigned char uint8;
typedef unsigned char uint4;

#ifndef _GCC
std::string CString2string(CString& name);
#endif

std::string replace_with(const std::string & src, 
                         const std::string & what, 
                         const std::string & with);
double string2double(const std::string& src);

///
std::string hl(char b1);  // не дороговато ли возвращать строку, может лучше ссылку передать
std::string hlh(char b1, char b2);  // еще один простейший преобразователь
std::string lhl(char b1, char b2); 

uint4 hex_symbol2uint4(const char one_symbol);
uint8 hex_symbol_strXX2uint8(const std::string line);

void stringProcessing(std::string &s, unsigned int pos);  // xx(pos c 1) = x0x1(,pos)xpos...
char hbCharToChar(char value);  // 0x0y -> char число
int charToInt(char value);  // один символ 
std::vector<std::string> SplitSpaces(std::string value);

// Prototype for conversion functions
std::wstring StringToWString(const std::string& s);
std::string WStringToString(const std::wstring& s);

#ifndef _GCC
std::wstring Utf8ToUtf16(const std::string &s);
std::string Utf16ToUtf8(const std::wstring &s);
std::wstring ANSIToUtf16(const std::string &s);
std::string Utf16ToANSI(const std::wstring &s);
std::string ANSIToUtf8(const std::string &s);
std::string Utf8ToANSI(const std::string &s);
#endif

std::string stringAppendInt(std::string name, int value);

template <typename T>
std::string to_string(T const& value) {
  std::stringstream sstr;
  sstr << value;
  return sstr.str();
}

// из double в строку формата xxx.y
//
std::string double2str_dot_y(const double value);

// из double в строку формата xxx.yy
//
std::string double2str_dot_yy(const double value);

//
//
std::string int2str(int value);

// "XX" = (uint8)X*16+X
// берет два последних символа
//
uint8 str2uint8(std::string);

// asdfasdfFF = 255
//
//
int strXX2uint8(std::string);

//
int _only_ipv4(parameters& p, std::string& value);
int _only_ipv4_mask(parameters& p, std::string& value);
void  disjoint(char *pas, int iLenPas, uint8* dpas);
void  joint(uint8* dpas, int iLendpas, char* pas);
// replace ## by " \r\n"
void replace_space(char *buf);
// replace " \r\n" by ##
void replace_trellis(char *buf);
// replace "+" by " "
void replace_pl(char *buf);

void _split_parametrs(std::string& s, parameters& p);
void _split_parametrs2(std::string& s, parameters& p);
}
#endif  // UNI_CONVERTORS_SIMPLE_TYPE_PROCESSORS_H_