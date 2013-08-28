// encoding : utf8
// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

// C++
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>

// App
#include <uni_convertors/simple_type_processors.h>

namespace simple_type_processors {
using namespace std;
using std::copy;
using std::string;

#ifndef _GCC
std::string CString2string(CString &CStringIn) {
  CT2CA pszConvertedAnsiString(CStringIn);
  string PortName(pszConvertedAnsiString);
  return PortName;
}
#endif

string replace_with(const std::string & src, const std::string & what, const std::string & with)
{    
  string result = src;
    if (what != with) {
        std::string temp;
        std::string::size_type prev_pos = 0, pos = result.find(what, 0);
        while (std::string::npos != pos) {
            temp += std::string(result.begin() + prev_pos, result.begin() + pos) + with;
            prev_pos = pos + what.size();
            pos = result.find(what, prev_pos);
        }
        if (!temp.empty()) {
            result = temp + std::string(result.begin() + prev_pos, result.end());
            if (std::string::npos == with.find(what)) {
                result = replace_with(result, what, with);
            }
        }
    }
  return result;
}

double string2double(const std::string &src) {
  // если есть меняем запятую на точку
  string strTmp = replace_with(src, ",", ".");

  // преобразуем в переменную двойной точности
  double dA = ::strtod(strTmp.c_str(), NULL);
  return dA;
}
///
void stringProcessing(std::string &s, unsigned int pos) {
  // добавляем запятую
  if(pos != 0)
    s.insert(pos, ",");
  else 
    pos = s.size();

  // удаляем ненужные нули
  string::iterator ini(s.begin());
  for(unsigned int i = 0; i < pos-1; i++) {
    if(*s.begin() == '0') 
      s.erase(ini);
    else break;
  }
}
//
char hbCharToChar(char tmp) {
  char out = '\0';
  tmp &= 0x0f; // на всякий случай
  switch(tmp) {  // 0-15 - только полбайта
    case 0 : { out = '0'; } break;
    case 1 : { out = '1'; } break;
    case 2 : { out = '2'; } break;
    case 3 : { out = '3'; } break;
    case 4 : { out = '4'; } break;
    case 5 : { out = '5'; } break;
    case 6 : { out = '6'; } break;
    case 7 : { out = '7'; } break;
    case 8 : { out = '8'; } break;
    case 9 : { out = '9'; } break;
    case 10 : { out = 'A'; } break;
    case 11 : { out = 'B'; } break;
    case 12 : { out = 'C'; } break;
    case 13 : { out = 'D'; } break;
    case 14 : { out = 'E'; } break;
    case 15 : { out = 'F'; } break;
    default : {} break;
  }

  ///
  return out;
}

uint8 hex_symbol_strXX2uint8(const string line) {
  char tmp = *(line.end()-1);
  uint8 result = hex_symbol2uint4(tmp);
  tmp = *(line.end()-2);
  result += 16*hex_symbol2uint4(tmp);
  return result;
}

uint4 hex_symbol2uint4(const char one_symbol) {
  uint4 result = 0;
  char symbol = one_symbol;
  //symbol &= 0x0f; // на всякий случай
  switch(symbol) {  // 0-15 - только полбайта
    case '0': { result = 0; } break;
    case '1': { result = 1; } break;
    case '2': { result = 2; } break;
    case '3': { result = 3; } break;
    
    case '4': { result = 4; } break;
    case '5': { result = 5; } break;
    case '6': { result = 6; } break;
    case '7': { result = 7; } break;
    
    case '8': { result = 8; } break;
    case '9': { result = 9; } break;
    case 'A': { result = 10; } break;
    case 'B': { result = 11; } break;
    
    case 'C': { result = 12; } break;
    case 'D': { result = 13; } break;
    case 'E': { result = 14; } break;
    case 'F': { result = 15; } break;
    default : {} break;
  }
  return result;
}

//////////
std::string hl(char b1){ 
  char tmp(b1);
  tmp >>= 4; tmp &= 0x0f;
  ///
  string s;
  s.push_back(hbCharToChar(tmp));
  tmp = b1; tmp &= 0x0f;
  s.push_back(hbCharToChar(tmp));
  
  //
  return s;
}
std::string hlh(char b1, char b2) 
{
  char tmp(b1);
  tmp >>= 4; tmp &= 0x0f;  // старщий полубайт
  string s;
  s.push_back(hbCharToChar(tmp));
  tmp = b1; tmp &= 0x0f;  // младший первого
  s.push_back(hbCharToChar(tmp));
  tmp = b2;
  tmp >>= 4; tmp &= 0x0f;  // старщий полубайт второго
  s.push_back(hbCharToChar(tmp));

  //
  return s;
}
std::string lhl(char b1, char b2){
  char tmp(b1);
  tmp &= 0x0f;  // младший полубайт первого
  string s;
  s.push_back(hbCharToChar(tmp));
  tmp = b2; 
  tmp >>= 4; tmp &= 0x0f;  // старший второго
  s.push_back(hbCharToChar(tmp));
  tmp = b2;
  tmp &= 0x0f;  // младщий второго
  s.push_back(hbCharToChar(tmp));

  //
  return s;
}
int charToInt(char cTmp_0) {
  int Itog = 0;
    char cTmp_1 = cTmp_0;
  cTmp_1 %= 16; cTmp_1 &= 0x0f;
  Itog = static_cast<int>(cTmp_1);  // 0-16
  cTmp_1 = cTmp_0; cTmp_1 >>= 4; cTmp_1 &= 0x0f;
  Itog += (16*static_cast<int>(cTmp_1)); 
  return Itog;
}

std::vector<std::string> SplitSpaces(std::string str) {
  vector<string> tokens;
  istringstream iss(str);
  copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter<vector<string> >(tokens));
  return tokens;
}

std::wstring StringToWString(const std::string& s)
 {
   std::wstring temp(s.length(),L' ');
   std::copy(s.begin(), s.end(), temp.begin());
   return temp; 
 }


 std::string WStringToString(const std::wstring& s)
 {
   std::string temp(s.length(), ' ');
   std::copy(s.begin(), s.end(), temp.begin());
   return temp; 
 }

#ifndef _GCC
 std::wstring Utf8ToUtf16(const std::string &s)
{
    std::wstring ret;
    int len = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), s.length(), NULL, 0);
    if (len > 0)
    {
      ret.resize(len);
      MultiByteToWideChar(CP_UTF8, 0, s.c_str(), s.length(), const_cast<wchar_t*>(ret.c_str()), len);
    }
    return ret;
}

std::string Utf16ToUtf8(const std::wstring &s)
{
    std::string ret;
    int len = WideCharToMultiByte(CP_UTF8, 0, s.c_str(), s.length(), NULL, 0, NULL, NULL);
    if (len > 0)
    {
      ret.resize(len);
      WideCharToMultiByte(CP_UTF8, 0, s.c_str(), s.length(), const_cast<char*>(ret.c_str()), len, NULL, NULL);
    }
    return ret;
}

std::wstring ANSIToUtf16(const std::string &s)
{
    std::wstring ret;
    int len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), s.length(), NULL, 0);
    if (len > 0)
    {
      ret.resize(len);
      MultiByteToWideChar(CP_ACP, 0, s.c_str(), s.length(), const_cast<wchar_t*>(ret.c_str()), len);
    }
    return ret;
}
std::string Utf16ToANSI(const std::wstring &s)
{
    std::string ret;
    int len = WideCharToMultiByte(CP_ACP, 0, s.c_str(), s.length(), NULL, 0, NULL, NULL);
    if (len > 0)
    {
      ret.resize(len);
      WideCharToMultiByte(CP_ACP, 0, s.c_str(), s.length(), const_cast<char*>(ret.c_str()), len, NULL, NULL);
    }
    return ret;
}
#endif // _GCC

std::string stringAppendInt(std::string name, int value) {
  string result = "";
  char tmp[20];
  result += name;
  result += "=";  

  // Danger!!
  itoa(value,tmp,10);  
  result+=tmp;

  return result;
}

std::string double2str_dot_y(const double value) {
  double dbl_copy = value;
  dbl_copy *= 10;
  int int_copy = static_cast<int>(dbl_copy);
  double result = int_copy/10.0;
  std::string str = to_string(result);
  return str;
}

std::string double2str_dot_yy(const double value) {
  double dbl_copy = value;
  dbl_copy *= 100;
  int int_copy = static_cast<int>(dbl_copy);
  double result = int_copy/100.0;
  std::string str = to_string(result);
  return str;
}

string int2str(int value) {
  char chb[10];
  string result(itoa(value, chb, 10));
  return result;
}

uint8 Yhex2uint4(char at) {
  uint8 result;
  switch(at) {
    case '0' : result = 0; break;
    case '1' : result = 1; break;
    case '2' : result = 2; break;
    case '3' : result = 3; break;
    
    case '4' : result = 4; break;
    case '5' : result = 5; break;
    case '6' : result = 6; break;
    case '7' : result = 7; break;
    
    case '8' : result = 8; break;
    case '9' : result = 9; break;
    case 'A' : result = 10; break;
    case 'B' : result = 11; break;
    
    case 'C' : result = 12; break;
    case 'D' : result = 13; break;
    case 'E' : result = 14; break;
    case 'F' : result = 15; break;
    
    default: result = 0; break;
  }
  return result;
}

uint8 str2uint8(std::string src) {
  uint8 result; 
  using std::string;
  string::iterator at = src.end();
  at--;
  char tmp = *at;
  result = Yhex2uint4(tmp);
  at--;
  tmp = *at;
  result += Yhex2uint4(*at)*16;
  return result;
}

int strXX2uint8(std::string src) {
  // копируем последние два символа в новую строку
  string lastTwoSymbols;
  const int kReserved = 100;
  lastTwoSymbols.reserve(kReserved);
  string::iterator end = src.end();
  end -= 2;  // Так можно вообще? 
  lastTwoSymbols.assign(end, src.end());

  // сам перевод
  int result = ::atoi(lastTwoSymbols.c_str());
  return result;
}

int _only_ipv4(parameters& p, std::string& value) {
  value="";
  int iNum=0;
  std::string in;
  int  iCnt =0;
  char  tmp[10];
  parameters::iterator pIter;
  for (pIter = p.begin(); pIter != p.end(); pIter++) { 
    in = pIter->second;
    if(in.find(":")==std::string::npos) {
      if (value.length()>0) value+=",";
      value += in;iNum++;
    }
  }
  return iNum;
}

int _only_ipv4_mask(parameters& p,std::string& value) {
  value="";
  int iNum=0;
  std::string in;
 
  int  iCnt =0;
  char  tmp[10];

  parameters::iterator pIter;
  for (pIter = p.begin(); pIter != p.end(); pIter++) { 
    in = pIter->second;
    if(in.find(".")!=std::string::npos) {
      if (value.length()>0) value+=",";
      value += in;iNum++;
    }
  }
  return iNum;
}

void  disjoint(char *pas,int iLenPas,uint8* dpas) {
  int k=0;
  for (int i=0; i<iLenPas; i++) {
    dpas[k] = static_cast<uint8>(pas[i]>>4);
    dpas[k+1] = static_cast<uint8>(pas[i]&0xf);
    k+=2;
  }
}

void  joint(uint8* dpas, int iLendpas,char* pas) {
  int k=0;
  for (int i=0; i<(iLendpas/2); i++) {
    pas[i] = static_cast<char>(dpas[k]<<4);
    pas[i] |= static_cast<char>(dpas[k+1]&0xf);
    k+=2;
  }
}


//replace ## by " \r\n"
void replace_space(char *buf) {
  char* cur = buf;
  int  icnt = 0;
  while (cur[0]!=0) {
    if (cur[0]=='#') {
      icnt++;
      if (icnt == 2) {
        icnt =0;
        //find "##", now replace by " \r\n"
        cur[0]='\n';
        cur--;
        cur[0]=' ';
        cur++;
      }
    }
    else if(icnt!=0) {
      icnt =0;
    }
    cur++;
  }
}

//replace " \r\n" by ##
void replace_trellis(char *buf) {
  char* cur = buf;
  int  icnt = 0;
  while (cur[0]!=0) {   
    if ((cur[0]=='\r') || (cur[0]=='\n')) {
      icnt++;
      if (icnt == 2) {
        icnt =0;
        //find "\r\n", now replace by "##"
        cur[0]='#';
        cur--;
        cur[0]='#';
        cur++;
      }
    }
    else if(icnt!=0) {
      icnt =0;
    }
    cur++;
  }
}

//replace "+" by " "
void replace_pl(char *buf) {
  char * cur = buf;
  while (cur[0]!=0) {
    if (cur[0]=='+')  cur[0]=' ';
    cur++;
  }
}


void _split_parametrs(std::string& s, parameters& p)
{
  // r=1&t=2 -> map(("r","1"),("t","2"))
  std::string in(s);
  std::string inpart;
  std::string name;
  std::string value;

  while(in.length())
  {
    if(in.find("&")!=std::string::npos)
    {
    inpart=in.substr(0,in.find("&"));
    in.erase(0,in.find("&")+1);
    }
    else
    {
    inpart=in;
    in="";
    }

    if(inpart.find("=")!=std::string::npos)
    {
    name=inpart.substr(0,inpart.find("="));
    value=inpart.substr(inpart.find("=")+1,inpart.length()-inpart.find("=")-1);
    }
    else
    {
    name=inpart;
    value="";
    }
    //value=decoder.decode(value);
    p.insert(parameters::value_type(name, value));
  }
}

void _split_parametrs2(std::string& s, parameters& p)
{
  // r=1&t=2 -> map(("r","1"),("t","2"))
  std::string in(s);
  std::string inpart;
  std::string name;
  std::string value;
  int  iCnt =0;
  char  tmp[10];

  while(in.length())
  {
    if(in.find(",")!=std::string::npos)
    {
      inpart=in.substr(0,in.find(","));
    in.erase(0,in.find(",")+1);
    }
    else
    {
    inpart=in;
    in="";
    }
   
    _itoa(iCnt,tmp,10);  iCnt++;
    name=tmp;
    value=inpart;
   
    //value=decoder.decode(value);
    p.insert(parameters::value_type(name, value));
  }
}
} // namespace
