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
 * Importing boost::thread and boost::thread_group into the Hypertable
 * namespace.
 */

#ifndef HYPERTABLE_THREAD_H
#define HYPERTABLE_THREAD_H

#include <boost/thread.hpp>
#include "Common/Logger.h"

namespace Hypertable {

/** @addtogroup Common
 *  @{
 */

#ifdef BOOST_HAS_PTHREADS
#  define HT_THREAD_ID_DECL(_var_) pthread_t _var_
#  define HT_THREAD_ID_SET(_var_) _var_ = pthread_self()
#else
#  define HT_THREAD_ID_DECL(_var_)
#  define HT_THREAD_ID_SET(_var_)
#endif

typedef boost::thread           Thread;
typedef boost::thread_group     ThreadGroup;

namespace ThisThread {
  using namespace boost::this_thread;
}

/** @} */

} // namespace Hypertable

#endif // HYPERTABLE_THREAD_H
