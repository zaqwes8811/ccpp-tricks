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
 * Importing boost metaprogramming facilities into Hypertable::Meta.
 * (http://www.boost.org/doc/libs/1_53_0/libs/mpl/doc/index.html).
 */

#ifndef HYPERTABLE_META_H
#define HYPERTABLE_META_H

#include <boost/mpl/list.hpp>
#include <boost/mpl/fold.hpp>

/**
 * Provides selected metaprogramming facilities in the Meta namespace
 */
namespace Hypertable { namespace Meta {

  /** @addtogroup Common
   *  @{
   */

  using namespace boost;
  using namespace boost::mpl;

  /** @} */

}} // namespace Hypertable::Meta

#endif /* HYPERTABLE_META_H */
