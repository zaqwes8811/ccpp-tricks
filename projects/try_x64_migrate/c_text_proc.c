#include "heart/config.h"

#include "inner_reuse/c_text_proc.h"
#include "platform_specific/network_main_header.h"

#include "at91lib/used/rtc/rtc.h"

#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

static const char HEX_STRING_[]={"0123456789ABCDEF"};

#if (defined(__GNUC__) || defined(__GNUG__)) && defined(__linux__)
#define max(a, b) \
    ({__typeof__(a) _a = (a); \
    __typeof__(b) _b = (b); \
    _a > _b ? _a : _b; })
#elif (defined(__GNUC__) || defined(__GNUG__)) && defined(__MINGW32__)
//#  define max std::max
#endif

int utBCD4HBToInt(int value) {
  int result = (value & 0x0f);
  result += ((value & 0xf0) >> 4)*10;
  result += ((value & 0xf00) >> 8)*100;
  result += ((value & 0xf000) >> 12)*1000;
  return result;
}

char utBCD2HBToChar(char value) {
  int result = (value & 0x0f);
  result += ((value & 0xf0) >> 4)*10;
  return result;
}

int utBCD5HBToInt(int value) {
  int result = 0;
  result  = (value & 0x0f);
  result += ((value & 0xf0) >> 4)*10;
  result += ((value & 0xf00) >> 8)*100;
  result += ((value & 0xf000) >> 12)*1000;
  result += ((value & 0xf0000) >> 16)*10000;
  return result;
}

int utBCD7HBToInt(int value) {
  int result = (value & 0x0f);
  result += ((value & 0xf0) >> 4)*10;
  result += ((value & 0xf00) >> 8)*100;
  result += ((value & 0xf000) >> 12)*1000;
  result += ((value & 0xf0000) >> 16)*10000;
  result += ((value & 0xf00000) >> 20)*100000;
  result += ((value & 0xf000000) >> 24)*1000000;
  return result;
}

/*
long utBCD10HBToLong(long value) {
  long result = (value & 0x0f);
  result += ((value & 0xf0) >> 4)*10;

  result += ((value & 0xf00) >> 8)*100;
  result += ((value & 0xf000) >> 12)*1000;

  result += ((value & 0xf0000) >> 16)*10000;
  result += ((value & 0xf00000) >> 20)*100000;

  result += ((value & 0xf000000) >> 24)*1000000;
  result += ((value & 0xf0000000) >> 28)*10000000;

  result += ((value & (long)0xf00000000) >> 32)*100000000;
  result += ((value & (long)0xf000000000) >> 36)*1000000000;
  return result;
}
*/

unsigned long imsMaskedBitToByte(unsigned char* D, unsigned char Bit) {
  unsigned char d = *D;
  if (d & Bit) 
    return 1; 
  else 
    return 0; 
}  

// App
int chttpGetParamsInQString(const char* qstring, int size) {
  const int MAX_SIZE = 512;
  int i = 0;
  int result = 0;

  // Check args
  if (0 == qstring || size < 0) 
    return 0;

  for (i = 0; i < size; i++) {
    if (i > MAX_SIZE) 
      break;
    if ('=' == qstring[i]) result++;  
  }
  return result;
}

char irZerocpySafe(char *out, const char *in, int Len) {
  char n = 0;  
  
  if (0 == out || 0 == in || Len < 0) {
      return 0;
  }
  
  while (*in) {
      *out++ = *in++; 
      n++;
      if (n >= Len) 
        break;
  }    
  *out = 0;
  return n;
}

/**
*  About:
*    Converts a string to an interger
*/
int ir_atoi(const char* sValue) {
  int Value = 0;
  int Digit = 0;
  char c = 0;
  
  if (0 == sValue) 
    return 0;
    
  while ((c = *sValue++) != '\0') {
    if (c >= '0' && c <= '9') {
      Digit = (int) (c - '0');
    } else {
      break;
    }
    Value = (Value * 10) + Digit;
  }
  return Value;
}

 /* reverse:  переворачиваем строку s на месте */
 void reverse(char s[])
 {
     int i = 0; 
     int j = 0;
     char c = 0;
     if (0 == s) 
      return;
 
     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
 }

void ir_ltoa(long int n, char* str) {
  unsigned long i;
  unsigned char j,p;
  i=1000000000L;
  p=0;
  if (n<0) {
    n -= n;
    *str++ = '-';
  };

  do {
    j = (unsigned char) (n / i);
    if (j || p || (i==1)) {
      *str++ = j + '0';
      p = 1;
    }

    n %= i;
    i /= 10L;
  } while (i!=0);
  *str = 0;
}

unsigned long ir_iptol(const char *ip) {
  unsigned long ipl = 0;
  unsigned long b = 0;
  int i = 0; 
  int m = 0;
  for (b = ipl = 0ul, m = 4, i = 0; ; i++) {
    switch (ip[i]) {
      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9':
        b = b*10 + ip[i] - '0';
        break;
      default:
        ipl = (ipl << 8ul) + b;
        if ('.' != ip[i] || 0 == (--m)) 
          return ipl;
        b = 0;
        break;
    }
  }
}

int ctext_utf8CpyLocal(char *out, const char *in) {
  int n = 0;  
  const int table[128] = {                    
        0x82D0,0x83D0,0x9A80E2,0x93D1,0x9E80E2,0xA680E2,0xA080E2,0xA180E2,
        0xAC82E2,0xB080E2,0x89D0,0xB980E2,0x8AD0,0x8CD0,0x8BD0,0x8FD0,    
        0x92D1,0x9880E2,0x9980E2,0x9C80E2,0x9D80E2,0xA280E2,0x9380E2,0x9480E2,
        0,0xA284E2,0x99D1,0xBA80E2,0x9AD1,0x9CD1,0x9BD1,0x9FD1,               
        0xA0C2,0x8ED0,0x9ED1,0x88D0,0xA4C2,0x90D2,0xA6C2,0xA7C2,              
        0x81D0,0xA9C2,0x84D0,0xABC2,0xACC2,0xADC2,0xAEC2,0x87D0,              
        0xB0C2,0xB1C2,0x86D0,0x96D1,0x91D2,0xB5C2,0xB6C2,0xB7C2,              
        0x91D1,0x9684E2,0x94D1,0xBBC2,0x98D1,0x85D0,0x95D1,0x97D1,            
        0x90D0,0x91D0,0x92D0,0x93D0,0x94D0,0x95D0,0x96D0,0x97D0,
        0x98D0,0x99D0,0x9AD0,0x9BD0,0x9CD0,0x9DD0,0x9ED0,0x9FD0,
        0xA0D0,0xA1D0,0xA2D0,0xA3D0,0xA4D0,0xA5D0,0xA6D0,0xA7D0,
        0xA8D0,0xA9D0,0xAAD0,0xABD0,0xACD0,0xADD0,0xAED0,0xAFD0,
        0xB0D0,0xB1D0,0xB2D0,0xB3D0,0xB4D0,0xB5D0,0xB6D0,0xB7D0,
        0xB8D0,0xB9D0,0xBAD0,0xBBD0,0xBCD0,0xBDD0,0xBED0,0xBFD0,
        0x80D1,0x81D1,0x82D1,0x83D1,0x84D1,0x85D1,0x86D1,0x87D1,
        0x88D1,0x89D1,0x8AD1,0x8BD1,0x8CD1,0x8DD1,0x8ED1,0x8FD1
  };
  while (*in)
      if (*in & 0x80) {
          int v = table[(int)(0x7f & *in++)];
          if (!v) 
            continue;
          *out++ = (char)v; 
          n++;
          *out++ = (char)(v >> 8); 
          n++;
          if (v >>= 16) {
              *out++ = (char)v; n++;
          }    
      } else {
          *out++ = *in++; 
          n++;
      }    
  *out = 0;
  return n;
}

char ctext_longToString(char* const p, unsigned long value) {
//#ifdef G_WINDOWS_OS
  //p[0] = '1';
  //p[1] = '2';
  //p[2] = '3';
  //p[3] = '\0';
  //return 0;
//#else
  return ut_long_to_string(p, value);
//#endif  // G_WINDOWS_OS
}

void irBCDULongToFloatString(
    char* const outBuffer, const int MAX_SIZE,
    const unsigned long BCD_VALUE,
    const int COUNT_DIGITS,
    const int COUNT_AFTER_DOT)
  {
  static const char BCD_MAP_[] =
    {'0', '1', '2', '3',
     '4', '5', '6', '7',
     '8', '9'};
  const char HF_MASK_ = 0x0F;
  unsigned long tmp = BCD_VALUE;
  int pos = 0;
  int effective = 0;
  const int WORK_COUNT_DIGITS = max(COUNT_DIGITS, COUNT_AFTER_DOT+1);
  char tmpBuffer[1024];
  char* p = &tmpBuffer[0];
  memset(tmpBuffer, 0, sizeof tmpBuffer * sizeof tmpBuffer[0]);

  if (0 == outBuffer
      || MAX_SIZE < 0
      || COUNT_AFTER_DOT < 0
      || COUNT_DIGITS > MAX_SIZE-1
      || WORK_COUNT_DIGITS > 8
      )
    return;


  // Выделяем представление в виде цифр
  {
    for (pos = 0; pos < WORK_COUNT_DIGITS; ++pos) {
      int digit = tmp & HF_MASK_;
      if (digit < 10) {
        *p = BCD_MAP_[digit];
      }
      p++;
      tmp >>= 4;
    }
  }

  // Поиск первых нулевых символов
  // Нужно найти эфф. число символов
  // Сперва идут младшие
  {
    int i = WORK_COUNT_DIGITS-1;
    // Вот он фейл!
    // 090 -> 0 - нужно в обратном порядке искать!
    while (tmpBuffer[i] == '0' && i >= 0) {
     // effective++;
      i--;
    }
    effective = i+1;

    if (effective <= COUNT_AFTER_DOT)
      effective = COUNT_AFTER_DOT+1;

    if (0 == effective )
      effective++;
  }

  // Как читаем
  if (0 == COUNT_AFTER_DOT) p = &outBuffer[effective-1];
  else p = &outBuffer[effective];

  // Заполняем результат
  for (pos = 0; pos < effective; ++pos) {
    *p = tmpBuffer[pos];
    if (pos == COUNT_AFTER_DOT-1 && COUNT_AFTER_DOT > 0) {
      p--;
      *p = '.';
    }
    p--;
  }
}



unsigned char utBCDToUChar(unsigned char D) {
  unsigned char H =
    ((D >> 4) * 10) + (D & 0x0F);
  return H;
}

void ctext_intToStrPadded(char* const buffer,
                          const int buffer_size,
                          const int value,
                          const int num_symbols)
  {
  int tmp = value;
  int i = 0;
  char* out = buffer;

  if (buffer_size < num_symbols+1) return;

  for (i = 0; i < num_symbols; i++) {
    int current_idx = num_symbols-i-1;
    switch(tmp % 10) {
      case 0:
        out[current_idx] = '0';
        break;
      case 1:
        out[current_idx] = '1';
        break;
      case 2: out[current_idx] = '2'; break;
      case 3: out[current_idx] = '3'; break;

      case 4: out[current_idx] = '4'; break;
      case 5: out[current_idx] = '5'; break;
      case 6: out[current_idx] = '6'; break;
      case 7: out[current_idx] = '7'; break;

      case 8: out[current_idx] = '8'; break;
      case 9: out[current_idx] = '9'; break;
      default: out[current_idx] = 'F'; break;
    }

    if (buffer == out+current_idx) break;
    tmp /= 10;
  }
  buffer[num_symbols] = '\0';
}


unsigned char ut_hex_to_dec(unsigned char H){
  unsigned char D = 0;
  if (H > 99)
    return(0x99);

  D = H/10;
  D <<= 4;
  D=D | (H % 10);
  return D;
}

unsigned short ut_short_dec_to_hex(unsigned short D) {
  unsigned short I = 0;
  unsigned short H = D;
  I = H & 0x000F;
  H >>= 4;
  I += (H & 0x000F) * 10;
  H >>= 4;
  I += (H&0x000F)*100;
  H >>= 4;
  I += (H & 0x000F)*1000;
  return I;
}

unsigned short ut_hex_to_decS(unsigned short I){
  unsigned short D,K;
  if (I == 0)
    return (0);
  if (I > 9999)
    return 0x9999;

  D = (I/1000)<<12;
  K = I%1000;
  D |= (K/100)<<8;
  K = I%100;
  D |= (K/10)<<4;
  K = I%10;
  D |= K;
  return D;
}

unsigned int ut_hex_to_decI(unsigned int L){
unsigned int D,K,I;
   I=L;
   if (I>99999999) return(0x99999999);

   D=(I/10000000)<<28;
   K=I%10000000;

   D|=(K/1000000)<<24;
   K=K%1000000;
   D|=(K/100000)<<20;
   K=K%100000;
   D|=(K/10000)<<16;
   K=K%10000;

   D|=(K/1000)<<12;
   K=K%1000;
   D|=(K/100)<<8;
   K=K%100;
   D|=(K/10)<<4;
   K=K%10;
   D|=K;
   return(D);}

unsigned int utULongBCDToULong(unsigned int D) {
  // Защиты нет вообще!
  unsigned int result = 0;
  unsigned int h = 0;
  h = D;

  //
  if ((h & 0x000F) < 10) result =(h & 0x000F)*1;
  h >>= 4;
  if ((h & 0x000F) < 10) result += (h & 0x000F)*10;
  h >>= 4;
  if ((h & 0x000F) < 10) result += (h & 0x000F)*100;
  h >>= 4;
  if ((h & 0x000F) < 10) result += (h & 0x000F)*1000;
  h >>= 4;
  if ((h & 0x000F) < 10) result += (h & 0x000F)*10000;
  h >>= 4;
  if ((h & 0x000F) < 10) result += (h & 0x000F)*100000;
  h >>= 4;
  if ((h & 0x000F) < 10) result += (h & 0x000F)*1000000;
  h >>= 4;
  if ((h & 0x000F) < 10) result += (h & 0x000F)*10000000;
  return result;
}

char ut_hex_to_char(unsigned char x){
  return HEX_STRING_[x & 0x0F];
}


char CharUpCase(char c) {
  if ((c >= 'a') && (c <= 'z')) {
    c &= 0xdf;
  }
  return c;
}

char CharLoCase(char c) {
  if ((c >= 'A') && (c <= 'Z')) {
    c |= 0x20;
  }
  if(c==0) c=' ';
  return c;
}

void ShortToStr(char* const Buf, const unsigned short S){
  unsigned long l;
  char* p = 0;
  char x = 0;
  p = Buf+4;
  l=ut_hex_to_decI(S);
  for (x=0;x<5;x++) {
    *p-- = HEX_STRING_[(char)l&0x0F];
    l>>=4;
  }
}

void CharToStr(char * Buf, unsigned char B){
  unsigned short s;
  char * p,x;
  p=Buf+2;
  s=ut_hex_to_decS(B);
  for (x=0;x<3;x++) {*p--=HEX_STRING_[(char)s&0x0F]; s>>=4;}
}

char ut_long_to_string(char* const Buf, unsigned long B){
  char* p = 0;
  unsigned char d = 0;
  unsigned char bz = 1;
  unsigned long l = 0;
  char s = 28;
  char len = 0;
  char xx = 0;
  p=Buf;
  l=ut_hex_to_decI(B);
  for (xx = 0; xx < 8; xx++){
    d=(char)((l>>s)&0x0F);
    if ((!((d==0) && (bz==1))) || ((xx==7)&&bz)) {
       *p++=HEX_STRING_[d];
       bz=0;
       len++;
    }
    s-=4;
  }
  return len;
}

void print_oid(const asn1OidElem_t* oid, const int len) {
  int i = 0;
  for (i = 0; i < len; i++) {
    printf("%ld", (long)oid[i]);
    printf(", ");
  }
  printf("\n");
}











