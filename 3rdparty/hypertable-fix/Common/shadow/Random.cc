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
 * Random number generator for int32, int64, double and ascii arrays.
 */

#include "Common/Compat.h"
#include "Common/Logger.h"

#include "Random.h"

namespace {
  const char cb64[] =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
}

using namespace Hypertable;

boost::mt19937 Random::ms_rng(1);

void Random::fill_buffer_with_random_ascii(char *buf, size_t len) {
  size_t in_i = 0, out_i = 0;
  uint32_t u32;
  uint8_t *in;

  while (out_i < len) {
    u32 = number32();
    in = (uint8_t *)&u32;
    in_i = 0;

    buf[out_i++] = cb64[in[in_i] >> 2];
    if (out_i == len)
      break;

    buf[out_i++] = cb64[((in[in_i] & 0x03) << 4) | ((in[in_i+1] & 0xf0) >> 4)];
    if (out_i == len)
      break;

    buf[out_i++] = cb64[((in[in_i+1] & 0x0f) << 2)|((in[in_i+2] & 0xc0) >> 6)];
    if (out_i == len)
      break;

    buf[out_i++] = cb64[ in[in_i+2] & 0x3f];

    in_i += 3;
  }

}


void Random::fill_buffer_with_random_chars(char *buf, size_t len,
        const char *charset) {
  size_t in_i = 0, out_i = 0;
  uint32_t u32;
  uint8_t *in;
  size_t set_len = strlen(charset);

  HT_ASSERT(set_len > 0 && set_len <= 256);

  while (out_i < len) {
    u32 = number32();
    in = (uint8_t *)&u32;

    in_i = 0;
    buf[out_i++] = charset[in[in_i] % set_len];
    if (out_i == len)
      break;

    in_i++;
    buf[out_i++] = charset[in[in_i] % set_len];
    if (out_i == len)
      break;

    in_i++;
    buf[out_i++] = charset[in[in_i] % set_len];
    if (out_i == len)
      break;

    in_i++;
    buf[out_i++] = charset[in[in_i] % set_len];
  }
}

double Random::uniform01() {
  static boost::uniform_01<boost::mt19937> u01(ms_rng);
  return u01();
}

