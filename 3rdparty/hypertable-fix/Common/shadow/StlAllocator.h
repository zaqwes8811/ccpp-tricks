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
 * along with Hypertable. If not, see <http://www.gnu.org/licenses/>
 */

/** @file
 * Stl compatible memory allocator based on a %PageArena.
 */

#ifndef HYPERTABLE_STL_ALLOCATOR_H
#define HYPERTABLE_STL_ALLOCATOR_H

#include "PageArenaAllocator.h"

namespace Hypertable {

/** @addtogroup Common
 *  @{
 */

typedef PageArena<uint8_t, DefaultPageAllocator> StlArena;

/**
 * Stl compatible memory allocator based on a %PageArena.
 */
template <typename T, class Impl = PageArenaAllocator<T, StlArena> >
struct StlAllocator : Impl {
 template <typename U>
 StlAllocator(const PageArenaAllocator<U, StlArena> &other)
 : Impl(other) {}

  template <typename U>
  struct rebind { typedef PageArenaAllocator<U, StlArena> other; };

  StlAllocator() {}
  StlAllocator(StlArena &arena) : Impl(arena) {}
};

/** @}*/

} // namespace Hypertable

#endif /* HYPERTABLE_STL_ALLOCATOR_H */
