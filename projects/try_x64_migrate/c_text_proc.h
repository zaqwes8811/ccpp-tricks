#ifndef REUSE_H_
#define REUSE_H_

#include "platform_specific/c_platform_spec_types.h"

#include <asn1/asn1.h>

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

#ifdef G_WINDOWS_OS
#include <stdlib.h>

int    bcmp(const void *, const void *, size_t n); /* LEGACY, see memcmp */
void   bcopy(const void *, void *, size_t n); /* LEGACY, see memcpy, memmove */
void   bzero(void *, size_t); /* LEGACY, see memset */
int    ffs(int);
char  *index(const char *, int); /* LEGACY, see strchr */
char  *rindex(const char *, int); /* LEGACY, see strrchr */
int    strcasecmp(const char *, const char *);
int    strncasecmp(const char *, const char *, size_t n);

#endif

#ifndef G_WINDOWS_OS
int ir_atoi(const char  * sValue);
void ir_ltoa(long int n,char *str);
#endif

char irZerocpySafe(char *out, const char *in, int Len);

char irDouble2StringDotYY(char* const Dest, const unsigned char * const Data, const char Len,const char dig);

char ctext_longToString(char* const p, unsigned long value);
EXTERNC int ctext_utf8CpyLocal(char *out, const char *in);
unsigned long imsMaskedBitToByte(unsigned char* D, unsigned char Bit);

/**
  \brief BCD
*/
EXTERNC int utBCD4HBToInt(int value);
EXTERNC char utBCD2HBToChar(char value);
EXTERNC int utBCD5HBToInt(int value);
EXTERNC int utBCD7HBToInt(int value);

/**
  \attention on arm long size trouble - long - 4 byte?
*/
long utBCD10HBToLong(long value);

/**
  \attention Уровень защиты слабоват! Максимум 4*2 символов
*/
void irBCDULongToFloatString(
    char* const outBuffer, const int MAX_SIZE,
    const unsigned long BCD_VALUE,
    const int COUNT_DIGITS,
    const int COUNT_AFTER_DOT);

unsigned char utBCDToUChar(unsigned char D);
unsigned char ut_hex_to_dec(unsigned char H);
unsigned short ut_hex_to_decS(unsigned short I);

/**

*/
unsigned short ut_short_dec_to_hex(unsigned short D);
unsigned int utULongBCDToULong(unsigned int D);
unsigned int ut_hex_to_decI(unsigned int L);
char ut_hex_to_char(unsigned char x);

char CharUpCase(char c);
char CharLoCase(char c);
void ShortToStr(char* const Buf, const unsigned short S);
void CharToStr(char* Buf, unsigned char B);
char ut_long_to_string(char* const Buf, unsigned long B);
void print_oid(const asn1OidElem_t* oid, const int len);

/**
  \brief int value -> [123\0]
  \param num_symbols -> сколько запишим

  \return stirng
*/
EXTERNC void ctext_intToStrPadded(
    char* const string, const int buffer_size,
    const int value,
    const int num_symbols);

#undef EXTERNC

#endif  // REUSE_H_
