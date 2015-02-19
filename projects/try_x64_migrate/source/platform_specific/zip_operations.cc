#include "heart/config.h"

#include "zip_operations.h"
#include "platform_specific/os_access.h"

#include <hypertable-fix/own_logger.h>

namespace platform_specific {
using std::string;

string getZipperFileName()
{
#if defined(G_DEBIAN_SK_MAT91SAM9G45_M10)
  return "tar";
#elif defined(G_UBUNTU_12_04_DESK)
  return "tar";
#elif defined(G_WINDOWS_EMB)
  return "D:\\bin\\7-zip\\7z.exe";
#elif defined (G_WINDOWS_DESK)
   return "D:\\work\\bin\\7-Zip\\7z.exe";
#else
#  error("Unknown options")
#endif
}

string getZipperArgs(const std::string& bin, const std::string& targetDir)
{
#if defined(G_DEBIAN_SK_MAT91SAM9G45_M10)
  return "-xzf " + bin + " -C "+ targetDir;
#elif defined(G_UBUNTU_12_04_DESK)
  return "-xzf " + bin + " -C "+ targetDir;
#elif defined(G_WINDOWS_EMB)
  return "7z.exe x " + bin + " -o"+ targetDir + " -raoa";
#elif defined (G_WINDOWS_DESK)
   return "7z.exe x " + bin + " -o"+ targetDir + " -raoa";
#else
#  error("Unknown options")
#endif
}

std::string UpdateZipOps::getAppRoot()
{
#if defined(G_DEBIAN_SK_MAT91SAM9G45_M10)
   return "/mnt/mmcblk0p1/application";
#elif defined(G_UBUNTU_12_04_DESK)
   return "/home/zaqwes/application";
#elif defined(G_WINDOWS_EMB)
   return "d:\\application";
#elif defined (G_WINDOWS_DESK)
   return "d:\\application";
#else
#  error("Unknown options")
#endif
}

std::string UpdateZipOps::getTmpFilenameToStore()
{
#if defined(G_DEBIAN_SK_MAT91SAM9G45_M10)
  return "/mnt/mmcblk0p1/tmp.tar.gz";
#elif defined(G_UBUNTU_12_04_DESK)
  return "/home/zaqwes/tmp.tar.gz";
#elif defined(G_WINDOWS_EMB)
  return "D:\\tmp.zip";
#elif defined (G_WINDOWS_DESK)
  return "D:\\tmp.zip";
#else
#  error("Unknown options")
#endif
}

std::string UpdateZipOps::getDeployVersion() {
#if defined(G_DEBIAN_SK_MAT91SAM9G45_M10)
  return "linux.armv5te.tar.gz";
#elif defined(G_UBUNTU_12_04_DESK)
  return "linux.x86.tar.gz";
#elif defined(G_WINDOWS_EMB)
  return "winxpe.x86.zip";
#elif defined (G_WINDOWS_DESK)
  return "win_xp_7.x86.zip";
#else
#  error("Unknown options")
#endif
}

bool UpdateZipOps::unpackImage()
{
  return unpackImage(getTmpFilenameToStore(), getAppRoot());
}

bool UpdateZipOps::unpackImage(const std::string& bin, const std::string& targetDir)
{
  string exe = getZipperFileName();
  string arg = getZipperArgs(bin, targetDir);
  return platform_specific::os::os_sync_run_command(exe, arg);
}

}  // space
