#include "heart/config.h"

#include "cc_io.h"

#include <hypertable-fix/Common/Error.h>
#include <boost/make_shared.hpp>

#include <fstream>
#include <iostream>
#include <algorithm>

namespace cc_io {
using std::fstream;
using std::ifstream;
using std::vector;
using std::string;

boost::shared_ptr<std::vector<std::string> >
textFileToList_light(std::string fname)
{
  boost::shared_ptr<std::vector<std::string> > r
      (new vector<string>());

  ifstream infile(fname.c_str());
  char b[1024];
  while(1) {
    infile.getline(b, sizeof(b));
    string line(b);
    if (!line.empty())
      r->push_back(line);

    if(infile.eof()) {
      break;
    }
  }

  std::reverse((*r).begin(), (*r).end());

  return boost::shared_ptr<std::vector<std::string> >(r);
}

std::vector<std::string> textFileToList(std::string fname)
{
  ifstream infile(fname.c_str());
  const int RD_BUFFER_SIZE = 1024;
  char b[RD_BUFFER_SIZE];
  vector<string> result;
  while(1) {
    infile.getline(b, sizeof(b));
    string oneLine(b);

    // обрабатываем результаты
    result.push_back(oneLine);

    if(infile.eof()) {
      break;
    }
  }

  return result;
}

std::string fileToString(const std::string& filename) {
  // http://demin.ws/blog/russian/2009/02/08/reading-file-via-stl-iterators/
  std::ifstream h(filename.c_str());
  if (h.is_open()) {
    std::string v;
    v.reserve(1024*1024);
    std::copy(
      std::istreambuf_iterator<char>(h),
      std::istreambuf_iterator<char>(),
      std::back_inserter(v)
    );
    return v;
  } else {
    HT_THROW(Hypertable::Error::HYPERSPACE_IO_ERROR, " File not found: " + filename);
  }
}

void fileToString(const std::string& filename, std::string& r_content) {
  // http://demin.ws/blog/russian/2009/02/08/reading-file-via-stl-iterators/
  std::ifstream h(filename.c_str());
  if (h.is_open()) {
    r_content.reserve(1024*1024);
    std::copy(
      std::istreambuf_iterator<char>(h),
      std::istreambuf_iterator<char>(),
      std::back_inserter(r_content)
    );
  } else {
    HT_THROW(Hypertable::Error::HYPERSPACE_IO_ERROR, " File not found: " + filename);
  }
}

void stringToFile(const std::string& text, const std::string& filename) {
  std::fstream stream(filename.c_str(), std::ios::out | std::ios::trunc);//std::ios::app);

  if (!stream.is_open())
    throw std::runtime_error("Can't open file: " + filename);

  stream << text;
  stream.close();
}

}  // space
