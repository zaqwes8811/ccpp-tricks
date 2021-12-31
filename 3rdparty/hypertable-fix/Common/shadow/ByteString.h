/*
 * Copyright (C) 2007-2012 Hypertable, Inc.
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
 * A serializable ByteString.
 * This file implements a serizable byte string.
 */

#ifndef HYPERTABLE_BYTESTRING_H
#define HYPERTABLE_BYTESTRING_H

#include <iostream>

#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>

#include "DynamicBuffer.h"
#include "Serialization.h"

namespace Hypertable {

  /** @addtogroup Common
   *  @{
   */

  /**
   * A class managing one or more serializable ByteStrings
   */
  class ByteString {
  public:
    /** Default constructor: starts with an empty string */
    ByteString() : ptr(0) { }

    /** Overloaded constructor: takes ownership of a pointer
     *
     * @param buf The pointer with data
     */
    ByteString(const uint8_t *buf) : ptr(buf) { }

    /** Retrieves the length of the serialized string
     *
     * @return The length of the serialized string
     */
    size_t length() const {
      if (ptr == 0)
        return 1;
      const uint8_t *tmp_ptr = ptr;
      uint32_t len = Serialization::decode_vi32(&tmp_ptr);
      return (tmp_ptr - ptr) + len;
    }

    /** Retrieves the next serialized String in the buffer */
    uint8_t *next() {
      uint8_t *rptr = (uint8_t *)ptr;
      uint32_t len = Serialization::decode_vi32(&ptr);
      ptr += len;
      return rptr;
    }

    /** Retrieves the decoded length and returns a pointer to the string
     *
     * @param dptr A pointer to the string data
     * @return The decoded length of the string data
     */
    size_t decode_length(const uint8_t **dptr) const {
      *dptr = ptr;
      return Serialization::decode_vi32(dptr);
    }

    /** Writes the data of this ByteString into a pointer
     *
     * @param dst A pointer which will receive the serialized data
     * @return The size of the data which was copied
     */
    size_t write(uint8_t *dst) const {
      size_t len = length();
      if (ptr == 0)
        Serialization::encode_vi32(&dst, 0);
      else
        memcpy(dst, ptr, len);
      return len;
    }

    /** Returns a pointer to the String's deserialized data
     *
     * @return A const char * pointer to the deserialized data
     */
    const char *str() const {
      const uint8_t *rptr = ptr;
      Serialization::decode_vi32(&rptr);
      return (const char *)rptr;
    }

    /** Returns true if this ByteArray is not empty
     *
     * @return True if this ByteArray is not empty, otherwise false
     */
    operator bool () const {
      return ptr != 0;
    }

    /** The pointer to the serialized data */
    const uint8_t *ptr;
  };

  /** Serializes and appends a byte array to a DynamicBuffer object
   *
   * @param dst_buf The DynamicBuffer which will receive the data
   * @param value A pointer to the data which is appended
   * @param value_len The size of the data, in bytes
   */
  inline void append_as_byte_string(DynamicBuffer &dst_buf, const void *value,
          uint32_t value_len) {
    dst_buf.ensure(7 + value_len);
    Serialization::encode_vi32(&dst_buf.ptr, value_len);
    if (value_len > 0) {
      memcpy(dst_buf.ptr, value, value_len);
      dst_buf.ptr += value_len;
      *dst_buf.ptr = 0;
    }
  }

  /** Serializes and appends a string to a DynamicBuffer object
   *
   * @param dst_buf The DynamicBuffer which will receive the data
   * @param str A pointer to a zero-terminated buffer with the data
   */
  inline void append_as_byte_string(DynamicBuffer &dst_buf, const char *str) {
    append_as_byte_string(dst_buf, str, strlen(str));
  }

  /** @}*/

} // namespace Hypertable


#endif // HYPERTABLE_BYTESTRING_H

