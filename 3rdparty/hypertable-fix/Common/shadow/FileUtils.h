/* -*- c++ -*-
 * Copyright (C) 2007-2014 Hypertable, Inc.
 *
 * This file is part of Hypertable.
 *
 * Hypertable is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or any later version.
 *
 * Hypertable is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

/** @file
 * File system utility functions.
 * Helper/Utility functions for accessing files and the file system.
 */

#ifndef Common_FileUtils_h
#define Common_FileUtils_h

extern "C" {
#include <dirent.h>
#include <sys/socket.h>
#include <sys/types.h>
}
#include "Common/String.h"

#include <mutex>
#include <vector>

namespace Hypertable {

  /** @addtogroup Common
   *  @{
   */

  /**
   * The FileUtils class provides static functions to easily access
   * and handle files and the file system.
   */
  class FileUtils {
  public:
    /** Reads a whole file into a String
     *
     * @param fname The file name
     * @param contents A reference to a String which will receive the data
     * @return <i>true</i> on success, <i>false</i> on error
     */
    static bool read(const String &fname, String &contents);

    /** Reads data from a file descriptor into a buffer
     *
     * @param fd The open file descriptor
     * @param vptr Pointer to the memory buffer
     * @param n Maximum size to read, in bytes
     * @return The number of bytes read, or -1 on error
     */
    static ssize_t read(int fd, void *vptr, size_t n);

    /** Reads positional data from a file descriptor into a buffer
     *
     * @param fd The open file descriptor
     * @param vptr Pointer to the memory buffer
     * @param n Maximum size to read, in bytes
     * @param offset The start offset in the file
     * @return The number of bytes read, or -1 on error
     */
    static ssize_t pread(int fd, void *vptr, size_t n, off_t offset);

    /** Writes a String buffer to a file; the file is overwritten if it
     * already exists
     *
     * @param fname Path of the file that is (over)written
     * @param contents The string contents that are written to the file
     * @return Number of bytes written, or -1 on error
     */
    static ssize_t write(const String &fname, const std::string &contents);

    /** Writes a memory buffer to a file descriptor
     *
     * @param fd Open file handle
     * @param vptr Pointer to the memory buffer
     * @param n Size of the memory buffer, in bytes
     * @return Number of bytes written, or -1 on error
     */
    static ssize_t write(int fd, const void *vptr, size_t n);

    /** Writes a string to a file descriptor
     *
     * @param fd Open file handle
     * @param str String to write to file
     * @return Number of bytes written, or -1 on error
     */
    static ssize_t write(int fd, const std::string &str) {
      return write(fd, str.c_str(), str.length());
    }

    /** Atomically writes data from multiple buffers to a file descriptor
     *
     *    struct iovec {
     *      void  *iov_base;    // Starting address
     *      size_t iov_len;     // Number of bytes to transfer
     *    };
     *
     * @param fd Open file handle
     * @param vector An iovec array holding pointers to the data
     * @param count Number of iovec structures in @a vector
     * @return Total number of bytes written, or -1 on error
     */
    static ssize_t writev(int fd, const struct iovec *vector, int count);

    /** Sends data through a network connection; if the socket is TCP then
     * the address is ignored. For UDP sockets the address structure
     * specifies the recipient.
     *
     * @param fd Open file handle/socket descriptor
     * @param vptr Pointer to the memory buffer which is sent
     * @param n Size of the memory buffer, in bytes
     * @param to The recipient's address (only UDP; ignored for TCP sockets)
     * @param tolen Length of the sockaddr structure
     * @return Total number of bytes sent, or -1 on error
     */
    static ssize_t sendto(int fd, const void *vptr, size_t n,
                          const sockaddr *to, socklen_t tolen);

    /** Sends data through a network connection
     *
     * @param fd Open file handle/socket descriptor
     * @param vptr Pointer to the memory buffer which is sent
     * @param n Size of the memory buffer, in bytes
     * @return Total number of bytes sent, or -1 on error
     */
    static ssize_t send(int fd, const void *vptr, size_t n);

    /** Receives data from a network connection and returns the sender's
     * address
     *
     * @param fd Open file handle/socket descriptor
     * @param vptr Pointer to the memory buffer which receives the data
     * @param n Capacity of the memory buffer, in bytes
     * @param from The sender's address
     * @param fromlen Length of the sockaddr structure
     * @return Total number of bytes received, or -1 on error, 0 on eof
     */
    static ssize_t recvfrom(int fd, void *vptr, size_t n,
            struct sockaddr *from, socklen_t *fromlen);

    /** Receives data from a network connection
     *
     * @param fd Open file handle/socket descriptor
     * @param vptr Pointer to the memory buffer which receives the data
     * @param n Capacity of the memory buffer, in bytes
     * @return Total number of bytes received, or -1 on error, 0 on eof
     */
    static ssize_t recv(int fd, void *vptr, size_t n);

    /** Sets fcntl flags of a socket
     *
     * @param fd Open file handle/socket descriptor
     * @param flags The fcntl flags; will be ORed with the existing flags
     * @return true on success, otherwise false (sets errno)
     */
    static bool set_flags(int fd, int flags);

    /** Reads a full file into a new buffer; the buffer is allocated with
     * operator new[], and the caller has to delete[] it.
     *
     * @param fname The file name
     * @param lenp Receives the length of the buffer, in bytes
     * @return A pointer allocated with new[]; needs to be delete[]d by
     *          the caller. Returns 0 on error (sets errno)
     */
    static char *file_to_buffer(const String &fname, off_t *lenp);

    /** Reads a full file into a String
     *
     * @param fname The file name
     * @return A string with the data, or an empty string on error (sets errno)
     */
    static String file_to_string(const String &fname);

    /** Maps a full file into memory using mmap; the mapping will be released
     * when the application terminates (there's currently no munmap)
     *
     * @param fname The file name
     * @param lenp Receives the length of the buffer, in bytes
     * @return A pointer to the mapped data
     */
    static void *mmap(const String &fname, off_t *lenp);

    /** Creates a directory (with all parent directories, if required)
     *
     * @param dirname The directory name to create
     * @return true on success, otherwise falls (sets errno)
     */
    static bool mkdirs(const String &dirname);

    /** Checks if a file or directory exists
     *
     * @return true if the file or directory exists, otherwise false
     */
    static bool exists(const String &fname);

    /** Unlinks (deletes) a file or directory
     *
     * @return true on success, otherwise false (sets errno)
     */
    static bool unlink(const String &fname);

    /** Renames a file or directory
     *
     * @param oldpath The path of the file (or directory) to rename
     * @param newpath The new filename
     * @return true on success, otherwise false (sets errno)
     */
    static bool rename(const String &oldpath, const String &newpath);

    /** Returns the size of a file (0 on error)
     *
     * @param fname The path of the file
     * @return The file size (in bytes) or 0 on error (sets errno)
     */
    static uint64_t size(const String &fname);

    /** Returns the size of a file (-1 on error)
     *
     * @param fname The path of the file
     * @return The file size (in bytes) or -1 on error (sets errno)
     */
    static off_t length(const String &fname);

    /** Adds a trailing slash to a path */
    static void add_trailing_slash(String &path);

    /** Expands a leading tilde character in a filename
     *
     *    Examples:
     *
     *      ~chris/foo -> /home/chris/foo
     *      ~/foo      -> /home/$USER/foo
     *
     *  @return true on success, false on error
     */
    static bool expand_tilde(String &fname);

    /** Reads all directory entries, applies a regular expression and returns
     * those which match.
     *
     * This function will call HT_FATAL on error!
     *
     * @param dirname The directory name
     * @param fname_regex The regular expression; can be empty
     * @param listing Vector with the results
     */
    static void readdir(const String &dirname, const String &fname_regex,
			std::vector<struct dirent> &listing);

    /// Mutex for protecting thread-unsafe glibc library function calls
    static std::mutex ms_mutex;
  };

  /** @} */

}

#endif // Common_FileUtils_h

