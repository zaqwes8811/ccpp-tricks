#ifndef ZIP_OPS_H_
#define ZIP_OPS_H_

#include <string>

namespace platform_specific {

/**
  \brief value object
*/
class UpdateZipOps
{
public:
  UpdateZipOps() { }

  std::string getAppRoot();

  std::string getTmpFilenameToStore();

  /**
    \return linux32 or win32
  */
  std::string getDeployVersion();

  bool unpackImage();

  bool unpackImage(const std::string& bin, const std::string& targetDir);
private:

};

}  // space

#endif
