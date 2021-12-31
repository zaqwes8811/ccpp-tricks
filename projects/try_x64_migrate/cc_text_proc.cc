#include "heart/config.h"

#include "inner_reuse/cc_text_proc.h"
#include "hypertable-fix/Common/Logger.h"
#include "heart/cc_g_abstr.h"

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/find.hpp>
#include <boost/bind/bind.hpp>
#include <boost/algorithm/string.hpp>
#include <hypertable-fix/Common/Error.h>

#include <stdexcept>
#include <set>
#include <fstream>
#include <bitset>

#if (defined(__GNUC__) || defined(__GNUG__)) && defined(__MINGW32__)
#  include <windows.h>
#elif (defined(__GNUC__) || defined(__GNUG__)) && defined(__linux__)
#  define __LINUX_HIDE
#elif defined(_MSC_VER) && ((_MSC_VER == 1500) || (_MSC_VER >= 1600))
#  include <windows.h>
#endif

// itoa not standart
//
#include <stdlib.h>
#include <stdio.h>

namespace text_proc {
using namespace std;
using std::copy;
using std::string;
using std::vector;
using std::string;
using std::ifstream;
using std::cout;
using std::endl;
using std::istream_iterator;
using std::istringstream;
using std::back_inserter;
using std::string;
using std::cout;
using std::endl;
using std::set;
using boost::algorithm::trim;

using namespace Hypertable;

std::string encode_datetime_ticket(const std::string& ticket)
{
  string newtime = ticket.substr(11, string::npos);
  string monthnum = ticket.substr(5,2);
  string month = "";
  if(strcmp(monthnum.c_str(),"01") == 0)         month = "Jan";
  else if(strcmp(monthnum.c_str(),"02") == 0)     month = "Feb";
  else if(strcmp(monthnum.c_str(),"03") == 0)     month = "Mar";
  else if(strcmp(monthnum.c_str(),"04") == 0)     month = "Apr";
  else if(strcmp(monthnum.c_str(),"05") == 0)     month = "May";
  else if(strcmp(monthnum.c_str(),"06") == 0)     month = "Jun";
  else if(strcmp(monthnum.c_str(),"07") == 0)     month = "Jul";
  else if(strcmp(monthnum.c_str(),"08") == 0)     month = "Aug";
  else if(strcmp(monthnum.c_str(),"09") == 0)     month = "Sep";
  else if(strcmp(monthnum.c_str(),"10") == 0)     month = "Oct";
  else if(strcmp(monthnum.c_str(),"11") == 0)     month = "Nov";
  else if(strcmp(monthnum.c_str(),"12") == 0)     month = "Dec";
  return "\""
      + month + " " + ticket.substr(8,2) + " "
      + ticket.substr(0,4) + " " + newtime + "\"";
}

std::vector<unsigned char> pack_ip(const std::string& ip)
{
  using namespace text_proc;
  if (ip.empty())
    return vector<unsigned char>(4, 0);

  string ipTmp = replace_with(ip, ".", " ");
  vector<string> d = split_spaces(ipTmp);

  if (d.size() != 4)
    throw std::invalid_argument(FROM_HERE + "Must me 4 digets.");

  vector<unsigned char> ticket;
  ticket.reserve(4);

  foreach_(string e, d) {
    unsigned int val = text_proc::stdStringToSomeDigit<unsigned int>(e);
    ticket.push_back((unsigned char)(val & 0xFF));
  }
  return ticket;
}

boost::tuple<unsigned char, unsigned char, unsigned char> get(unsigned char i)
{
  return boost::tuple<unsigned char, unsigned char, unsigned char>(
        0x0F & ((i / 100) % 10)
        , 0x0F & ((i / 10) % 10)
        , 0x0F & (i % 10)
        );
}

// 4 * 3
std::vector<unsigned char> repack_ethx(
    const std::vector<unsigned char>& in)
{
  if (in.size() != 4 * 3)
    throw std::invalid_argument(FROM_HERE + "Bad format");

  int offset = 4;

  vector<unsigned char> r;
  r.reserve(4 * 3 + 6);

  for (int i = 0; i < 3; ++i) {
    unsigned char i0 = in[0 + i * offset];
    unsigned char i1 = in[1 + i * offset] ;
    unsigned char i2 = in[2 + i * offset];
    unsigned char i3 = in[3 + i * offset];

    vector<unsigned char> tmp(6, 0);

    boost::tuple<unsigned char, unsigned char, unsigned char> v0, v1;
    v0 = get(i0);
    v1 = get(i1);
    tmp[0] = (v0.get<0>() << 4) | v0.get<1>();
    tmp[1] = (v0.get<2>() << 4) | v1.get<0>();
    tmp[2] = (v1.get<1>() << 4) | v1.get<2>();

    //
    v0 = get(i2);
    v1 = get(i3);
    tmp[3] = (v0.get<0>() << 4) | v0.get<1>();
    tmp[4] = (v0.get<2>() << 4) | v1.get<0>();
    tmp[5] = (v1.get<1>() << 4) | v1.get<2>();

    r.insert(r.end(), tmp.begin(), tmp.end());
  }
  return r;
}

vector<unsigned char> pack_ethx(const app_abstr::EthX& t)
{
  vector<unsigned char> r;
  r.reserve(4 * 3);
  vector<unsigned char> quad = pack_ip(t.get<1>());
  r.insert(r.end(), quad.begin(), quad.end());
  quad = pack_ip(t.get<2>());
  r.insert(r.end(), quad.begin(), quad.end());
  quad = pack_ip(t.get<3>());
  r.insert(r.end(), quad.begin(), quad.end());
  return r;
}

bool contain(const std::string& in, const std::string& match) {
  if (in.find(match) != std::string::npos) {
     return true;
  }
  return false;
}

boost::tuple<string, string, string>
split_space_triple(string a)
{
  HT_CHECK(!a.empty());

  // http://stackoverflow.com/questions/765148/how-to-remove-constness-of-const-iterator
  // http://www.aristeia.com/Papers/CUJ_June_2001.pdf
  // boost::range_iterator<string::const_iterator> r = boost::find_nth(a, "ain", 2);

  boost::iterator_range<string::iterator> itInTicket = boost::find_nth(a, " ", 0);
  boost::iterator_range<string::iterator> itTicketMessage = boost::find_nth(a, " ", 1);

  HT_CHECK(itInTicket.end() != a.end());
  HT_CHECK(itTicketMessage.end() != a.end());

  return boost::tuple<string, string, string>(
        string(a.begin(), itInTicket.begin()),
        string(itInTicket.end(), itTicketMessage.begin()),
        string(itTicketMessage.end(), a.end())
        );
}

template <>
std::string to_string<unsigned char>(const unsigned char & value) {
  //throw std::invalid_argument("to_string() not unsigned char!");
  return to_string(static_cast<unsigned int>(value));
}

template <>
std::string to_string<char>(const char & value) {
  //throw std::invalid_argument("to_string() not unsigned char!");
  return to_string(static_cast<int>(value));
}


char utCharToBCD2HB(char value) {
  int low = value%10;
  int high = ((value/10)%10) << 4;
  char result = high + low;
  return result;
}

vector<char> utIntToBCD4HB(int value) {
  vector<char> result;
  result.push_back((utCharToBCD2HB(value%100)) & 0xFF);
  result.push_back((utCharToBCD2HB(value/100)) & 0xFF);
  return result;
}

vector<char> utIntToBCD6HB(int value) {
  vector<char> result;
  result.push_back((utCharToBCD2HB(value%100)) & 0xFF);
  result.push_back((utCharToBCD2HB((value/100)%100)) & 0xFF);
  result.push_back((utCharToBCD2HB(value/10000)) & 0xFF);
  return result;
}

vector<char> utLongToBCD10HB(const int value) {
  vector<char> result;
  int tmpValue = value;
  result.push_back((utCharToBCD2HB(tmpValue%100)) & 0xFF);
  tmpValue /= 100;
  result.push_back((utCharToBCD2HB(tmpValue%100)) & 0xFF);
  tmpValue /= 100;

  result.push_back((utCharToBCD2HB(tmpValue%100)) & 0xFF);
  tmpValue /= 100;
  result.push_back((utCharToBCD2HB(tmpValue%100)) & 0xFF);
  tmpValue /= 100;

  result.push_back((utCharToBCD2HB(tmpValue%100)) & 0xFF);
  tmpValue /= 100;
  result.push_back((utCharToBCD2HB(tmpValue%100)) & 0xFF);
  tmpValue /= 100;

  result.push_back((utCharToBCD2HB(tmpValue%100)) & 0xFF);
  tmpValue /= 100;
  result.push_back((utCharToBCD2HB(tmpValue%100)) & 0xFF);
  tmpValue /= 100;

  result.push_back((utCharToBCD2HB(tmpValue%100)) & 0xFF);
  tmpValue /= 100;
  result.push_back((utCharToBCD2HB(tmpValue%100)) & 0xFF);

  return result;
}


std::vector<std::string> split_spaces(const std::string& str) {
  vector<string> tokens;
  istringstream iss(str);
  copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter<vector<string> >(tokens));
  return tokens;
}

std::string shortIntToBinString(int value) {
  std::bitset<16> x(value);
  std::stringstream ss;
  ss << x;
  return ss.str();
}

int stdStringToInt(const std::string& str) {
  // http://www.cplusplus.com/forum/general/13135/
  // http://www.cplusplus.com/reference/istream/istream/operator%3E%3E/
  //
  // !! http://stackoverflow.com/questions/194465/how-to-parse-a-string-to-an-int-in-c

  /*int result;
  //
  istringstream s;
  s.str(str);
  s >> result;
  if (!s.fail())
    throw std::invalid_argument("Conversion failed in: " + str);*/

  // http://stackoverflow.com/questions/1250795/very-poor-boostlexical-cast-performance
  // Sutter "New C++ task"
  //
  // Slooow. And slooower in multythreading.
  //try {
    //throw boost::bad_lexical_cast();  // Checked.
    return boost::lexical_cast< int >( str );
  //} catch (const boost::bad_lexical_cast& e) {
  //  throw;
  //}
}

std::string int2var_weigth_str(const int value,
                               const int num_symbols) {
  string result;
  int itmp = value;
  for(int i = 0; i < num_symbols; i++) {
    switch( itmp%10 ) {
      case 0: result = "0"+result; break;
      case 1: result = "1"+result; break;
      case 2: result = "2"+result; break;
      case 3: result = "3"+result; break;

      case 4: result = "4"+result; break;
      case 5: result = "5"+result; break;
      case 6: result = "6"+result; break;
      case 7: result = "7"+result; break;

      case 8: result = "8"+result; break;
      case 9: result = "9"+result; break;
    }
    itmp /= 10;
  }
  return result;
}

void IntToUChar(vector<unsigned char>& trank, int value, int numSymb) {
  unsigned char uctmp = 0;
  int intTmp = value;
  deque<unsigned char> dtmp;
  for(int i = 0; i < numSymb; i++) {
    switch( intTmp % 10 ) {
      case 0: uctmp = '0'; break;
      case 1: uctmp = '1'; break;
      case 2: uctmp = '2'; break;
      case 3: uctmp = '3'; break;
      case 4: uctmp = '4'; break;
      case 5: uctmp = '5'; break;
      case 6: uctmp = '6'; break;
      case 7: uctmp = '7'; break;
      case 8: uctmp = '8'; break;
      case 9: uctmp = '9'; break;
    }
    dtmp.push_front(uctmp);
    intTmp /= 10;
  }
  for(int i = 0; i < numSymb; i++) {
    trank.push_back(dtmp[i]);
  }
}

void IntToChar(vector<char>& r_trank, int value, int numSymb) {
  char symbol = 0;
  int intTmp = value;
  std::deque<char> dtmp;

  for(int i = 0; i < numSymb; i++) {
    switch(intTmp % 10) {
      case 0: symbol = '0'; break;
      case 1: symbol = '1'; break;
      case 2: symbol = '2'; break;
      case 3: symbol = '3'; break;
      case 4: symbol = '4'; break;
      case 5: symbol = '5'; break;
      case 6: symbol = '6'; break;
      case 7: symbol = '7'; break;
      case 8: symbol = '8'; break;
      case 9: symbol = '9'; break;
    }
    dtmp.push_front(symbol);
    intTmp /= 10;
  }

  for (int i = 0; i < numSymb; i++) {
    r_trank.push_back(dtmp[i]);
  }
}

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
  string strTmp = replace_with(src, ",", ".");

  double dA = ::strtod(strTmp.c_str(), NULL);
  return dA;
}

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

  return out;
}

unsigned char hex_symbol_strXX2uint8(const string line) {
  char tmp = *(line.end()-1);
  unsigned char result = hex_symbol2uint4(tmp);
  tmp = *(line.end()-2);
  result += 16*hex_symbol2uint4(tmp);
  return result;
}

unsigned char hex_symbol2uint4(const char one_symbol) {
  unsigned char result = 0;
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

std::string hl(unsigned char b1) {
  unsigned char tmp(b1);
  tmp >>= 4; tmp &= 0x0f;
  string s;
  s.push_back(hbCharToChar(tmp));
  tmp = b1; tmp &= 0x0f;
  s.push_back(hbCharToChar(tmp));
  return s;
}

std::string hl(char b1) {
  char tmp(b1);
  tmp >>= 4; tmp &= 0x0f;
  string s;
  s.push_back(hbCharToChar(tmp));
  tmp = b1; tmp &= 0x0f;
  s.push_back(hbCharToChar(tmp));
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

std::string int2str(int value) {
   return to_string(value);
}


unsigned char Yhex2uint4(char at) {
  unsigned char result;
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

unsigned char str2uint8(std::string src) {
  unsigned char result;
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

void  disjoint(const char *pas,int iLenPas,unsigned char* dpas) {
  int k=0;
  for (int i=0; i<iLenPas; i++) {
    dpas[k] = static_cast<unsigned char>(pas[i]>>4);
    dpas[k+1] = static_cast<unsigned char>(pas[i]&0xf);
    k+=2;
  }
}

void  joint(unsigned char* dpas, int iLendpas,char* pas) {
  int k=0;
  for (int i=0; i<(iLendpas/2); i++) {
    pas[i] = static_cast<char>(dpas[k]<<4);
    pas[i] |= static_cast<char>(dpas[k+1]&0xf);
    k+=2;
  }
}

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

// rec1 SP rec2 SP rec3 SP
string Joiner::Join(vector<string> list) {
  string result("");
  foreach_(string record, list) {
    result += record+mkSplitter;
  }
  return result;
}

string Joiner::Join(string first, string last) {
  return first+mkSplitter+last;
}

Joiner Joiner::On(string splitter) {
  return Joiner(splitter);
}

vector<int> split_date_time(const std::string& time_ticket)
{
  vector<int> r;
  vector<string> splitted_spaces_result = split_spaces(time_ticket);
  vector<string> splitted_spaces;
  if (splitted_spaces_result.size() != 2)
    throw std::invalid_argument("time_ticket");

  // Data
  string data = splitted_spaces_result[0];
  data = replace_with(data, "-", " ");
  splitted_spaces = split_spaces(data);
  if (splitted_spaces.size() != 3)
    throw std::invalid_argument("time_ticket");

  {
    vector<int> tmp;
    foreach_(string at, splitted_spaces) {
      tmp.push_back(stdStringToInt(at));
    }

    std::reverse(tmp.begin(), tmp.end());

    r.insert(r.end(), tmp.begin(), tmp.end());
  }

  // Time
  string time = splitted_spaces_result[1];
  time = replace_with(time, ":", " ");
  splitted_spaces = split_spaces(time);
  if (splitted_spaces.size() != 3)
    throw std::invalid_argument("time_ticket");

  foreach_(string at, splitted_spaces) {
    r.push_back(stdStringToInt(at));
  }

  if (r.size() != 6)
    throw std::invalid_argument("time_ticket");

  return r;
}

string CompliteValue(const int value, const int num_digits) {
  string result = "";
  int tmp = value;
  for (int i = 0; i < num_digits; ++i) {
    if (tmp != 0) {
      result += to_string(tmp%10); tmp /= 10;
    } else {
      result += "0";
    }
  }
  // развернуть строку
  reverse(result.begin(), result.end());
  return result;
}

boost::tuple<std::string, std::string>
split_space_pair(const std::string& in) {
  vector<string> r = text_proc::split_spaces(in);

  // remove empty
  r.erase(std::remove_if(r.begin(), r.end()
                         , boost::bind(&std::string::empty, _1)
                         ), r.end());

  if (r.size() != 2)
    throw std::runtime_error("Error occure on split string");

  trim(r.at(0));
  trim(r.at(1));
  return boost::tuple<std::string, std::string>(r.at(0), r.at(1));
}

boost::tuple<std::string, std::string, std::string, std::string>
split_space_quad(const std::string& in) {
  vector<string> r = text_proc::split_spaces(in);

  // remove empty
  r.erase(std::remove_if(r.begin(), r.end()
                         , boost::bind(&std::string::empty, _1)
                         ), r.end());

  if (r.size() != 4)
    throw std::runtime_error("Error occure on split string");

  trim(r.at(0));
  trim(r.at(1));
  trim(r.at(2));
  trim(r.at(3));

  return boost::tuple<std::string
      , std::string
      , std::string
      , std::string>(r.at(0), r.at(1), r.at(2), r.at(3));
}
}  // space




