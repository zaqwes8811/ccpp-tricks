#ifndef CC_IO_H_OWN_
#define CC_IO_H_OWN_

#include <boost/shared_ptr.hpp>

#include <string>
#include <vector>

namespace cc_io {
// in
std::vector<std::string> textFileToList(std::string fname);
std::string fileToString(const std::string& filename);
void fileToString(const std::string& filename, std::string& r_content);

/**
  \brief
  - trim empty strings
  - reverse list best here
*/
boost::shared_ptr<std::vector<std::string> >
textFileToList_light(std::string fname);

// out
void stringToFile(const std::string& text, const std::string& filename);
}  // space

#endif
