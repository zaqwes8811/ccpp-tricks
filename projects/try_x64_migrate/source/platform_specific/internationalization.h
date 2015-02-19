#ifndef INTERN_APP_H_
#define INTERN_APP_H_

/**
  \attention Crossplatform trouble
  http://stackoverflow.com/questions/688760/how-to-create-a-utf-8-string-literal-in-visual-c-2008
  http://www.nubaria.com/en/blog/?p=289
  !! http://www.codeproject.com/Articles/14637/UTF-With-C-in-a-Portable-Way

   Work if (Windows only):
   - sources - utf8 without BOM
   - external (http, snmp, local journal - utf8 without BOM)

   Not work (Windows only):
   - вывод в консоль или в окна
   - скорее всего не работает поиск по строкам

   FIXME: (Windows only) проблема изолирована, но нельзя сказать что полностью решена. ТЗ соответствует
   но лучше чтобы и в констоль выводило.
*/
// Best save in external file
// https://code.google.com/p/inih/
#if defined(_MSC_VER) && _MSC_VER > 1310
// Visual C++ 2005 and later require the source files in UTF-8, and all strings
// to be encoded as wchar_t otherwise the strings will be converted into the
// local multibyte encoding and cause errors. To use a wchar_t as UTF-8, these
// strings then need to be convert back to UTF-8. This function is just a rough
// example of how to do this.
# define doUtf8(str)  str
// Win7/VS2008/Russian not working
//ConvertToUTF8(L##str)
//const char * ConvertToUTF8(const wchar_t * pStr);
#else
// Visual C++ 2003 and gcc will use the string literals as is, so the files
// should be saved as UTF-8. gcc requires the files to not have a UTF-8 BOM.
# define doUtf8(str)  str
#endif

#endif
