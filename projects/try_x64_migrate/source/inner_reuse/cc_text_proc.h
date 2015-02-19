
#ifndef UNI_CONVERTORS_SIMPLE_TYPE_PROCESSORS_H_
#define UNI_CONVERTORS_SIMPLE_TYPE_PROCESSORS_H_

#include "heart/cc_g_abstr.h"

#include <boost/tuple/tuple.hpp>
#include <boost/lexical_cast.hpp>

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <deque>
#include <stdexcept>

namespace text_proc {

/**
  \attention much copy and can't put const. Need think. No time now.
*/
boost::tuple<std::string, std::string, std::string>
split_space_triple(std::string a);

std::vector<std::string>
split_spaces(const std::string& str);

boost::tuple<std::string, std::string>
split_space_pair(const std::string& in);

boost::tuple<std::string, std::string, std::string, std::string>
split_space_quad(const std::string& in);

/**
  \attention use very often!

  \attention troubles with char
*/
template <typename T>
std::string to_string(const T& value) {
  std::stringstream sstr;
  sstr << value;
  return sstr.str();
}

std::vector<unsigned char> pack_ip(const std::string& ip);
std::vector<unsigned char> pack_ethx(const app_abstr::EthX& t);
std::vector<unsigned char> repack_ethx(const std::vector<unsigned char>& in);

// http://www.boost.org/doc/libs/1_48_0/doc/html/boost_lexical_cast/frequently_asked_questions.html
// non unsigned char
template<typename T>
T stdStringToSomeDigit(const std::string& str) {
  return boost::lexical_cast< T >( str );
}

/**
  \attention
  http://msdn.microsoft.com/ru-ru/library/c401y1kb.aspx
  http://www.linux.org.ru/forum/development/1177896
*/
template <>
std::string to_string<unsigned char>(const unsigned char & value);
template <>
std::string to_string<char>(const char & value);

//template <>
std::string shortIntToBinString(int value);

/**
  \brief may throw

  \attention may be very slow! if need perf. think about reimplementation
*/
int stdStringToInt(const std::string& snum);

std::string replace_with(const std::string & src,
                         const std::string & what,
                         const std::string & with);
// replace ## by " \r\n"
void replace_space(char *buf);

// replace " \r\n" by ##
void replace_trellis(char *buf);

// replace "+" by " "
void replace_pl(char *buf);

double string2double(const std::string& src);

std::string hl(unsigned char b1);
std::string hl(char b1);  // не дороговато ли возвращать строку, может лучше ссылку передать
std::string hlh(char b1, char b2);  // еще один простейший преобразователь
std::string lhl(char b1, char b2);

unsigned char hex_symbol2uint4(const char one_symbol);
unsigned char hex_symbol_strXX2uint8(const std::string line);

char hbCharToChar(char value);  // 0x0y -> char число
int charToInt(char value);  // один символ

// из double в строку формата xxx.y
std::string double2str_dot_y(const double value);

// из double в строку формата xxx.yy
std::string double2str_dot_yy(const double value);
std::string int2str(int tmp);

/**
  \brief "XX" = (uint8)X*16+X берет два последних символа
*/
unsigned char str2uint8(std::string);

// asdfasdfFF = 255
int strXX2uint8(std::string);

void  disjoint(const char *pas, int iLenPas, unsigned char* dpas);
void  joint(unsigned char* dpas, int iLendpas, char* pas);

/**
  В класс собрать нужно бы, может потом пригодится
*/
void IntToUChar(std::vector<unsigned char>& trank, int value, int numSymb);
void IntToChar(std::vector<char>& trank, int value, int numSymb);

std::string int2var_weigth_str(const int value, const int num_symbols);

class Joiner {
 public:
   Joiner(std::string splitter) : mkSplitter(splitter) {}

  // rec1 SP rec2 SP rec3 SP
  std::string Join(std::vector<std::string> list);
  std::string Join(std::string first, std::string last);
  static Joiner On(std::string splitter);

 private:
  const std::string mkSplitter;
};

/**
// Строку с датой в массив
//
 \param[in] "2012-04-15 15:15:26"

//"15.04.2012 15:19:26"
//
// Returns:
//   [15, 4, 2012, 15, 19, 26]
*/
std::vector<int> split_date_time(const std::string& time_ticket);

std::string encode_datetime_ticket(const std::string& ticket);

// Дополняет число до
//
//
std::string CompliteValue(const int value, const int num_digits);

char utCharToBCD2HB(char value);
std::vector<char> utIntToBCD4HB(int value);
std::vector<char> utIntToBCD6HB(int value);
std::vector<char> utLongToBCD10HB(const int value);

int utBCD4HBToInt(int value);
char utBCD2HBToChar(char value);
int utBCD5HBToInt(int value);
int utBCD7HBToInt(int value);
long utBCD10HBToLong(long value);

bool contain(const std::string& in, const std::string& match);
}

#endif  // UNI_CONVERTORS_SIMPLE_TYPE_PROCESSORS_H_
