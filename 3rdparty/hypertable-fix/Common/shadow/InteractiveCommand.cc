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
 * Base class for interactive shell commands.
 */

#include "Common/Compat.h"

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

#include "InteractiveCommand.h"
#include "Usage.h"

using namespace Hypertable;
using namespace std;


void InteractiveCommand::parse_command_line(const char *line) {
  size_t cmd_len = strlen(this->command_text());
  const char *base, *ptr;
  string key, value;

  assert(!strncmp(line, command_text(), cmd_len));

  m_args.clear();

  ptr = line + cmd_len;

  while (true) {
    key = "";
    value = "";

    // skip whitespace
    while (*ptr && isspace(*ptr))
      ptr++;
    if (*ptr == 0)
      break;

    if (*ptr == '\"') {
      if (!parse_string_literal(ptr, key, &ptr))
        exit(1);
    }
    else {
      base = ptr;
      while (true) {
        if (*ptr == '=') {
          key = string(base, ptr-base);
          base = ++ptr;
          if (*base == '\"') {
            if (!parse_string_literal(base, value, &ptr))
              exit(1);
            break;
          }
          else {
            for (ptr = base; *ptr && !isspace(*ptr); ptr++)
              ;
            value = string(base, ptr-base);
            break;
          }
        }
        else if (*ptr == 0 || isspace(*ptr)) {
          key = string(base, ptr-base);
          break;
        }
        ptr++;
      }
    }
    m_args.push_back(pair<string, string>(key, value));
  }
}


bool
InteractiveCommand::parse_string_literal(const char *str, std::string &text,
        const char **endptr) {
  int lastchar = *str;
  const char *ptr, *base;

  assert(*str == '"');

  base = str + 1;

  for (ptr = base; *ptr; ++ptr) {
    if (*ptr == '\"' && lastchar != '\\')
      break;
    lastchar = *ptr;
  }

  if (*ptr == 0) {
    cerr << "Un-terminated string literal." << endl;
    return false;
  }

  text = string(base, ptr-base);

  *endptr = ptr + 1;
  return true;
}
