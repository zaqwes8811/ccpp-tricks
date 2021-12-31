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
 * Escape/Unescape routines for strings.
 */

#ifndef HYPERTABLE_ESCAPER_H
#define HYPERTABLE_ESCAPER_H

#include "Common/String.h"

namespace Hypertable {

  /** @addtogroup Common
   *  @{
   */

  /** Escapes a string
   *
   * @param str The string to escape [in/out]
   * @param escape_chars All characters that are escaped
   */
  void escape(String &str, const String &escape_chars);

  /** Unescapes a string
   *
   * @param str The string to unescape [in/out]
   */
  void unescape(String &str);

  /** @} */
}

#endif // HYPERTABLE_ESCAPER_H
