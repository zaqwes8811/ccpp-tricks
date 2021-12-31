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
 * Discrete Random Generator creating a zipfian distribution.
 * See http://en.wikipedia.org/wiki/Zipf%27s_law
 */

#ifndef HYPERTABLE_DISCRETERANDOMGENERATORZIPF_H
#define HYPERTABLE_DISCRETERANDOMGENERATORZIPF_H

#include "Common/Compat.h"

#include <vector>
#include <cmath>

#include "DiscreteRandomGenerator.h"

namespace Hypertable {

  /** @addtogroup Common
   *  @{
   */

  /**
   * Generate samples from Zipf distribution
   * http://en.wikipedia.org/wiki/Zipf%27s_law
   *
   * Designed for case where parameter 0 < s < 1, under which condition the
   * probability of the number k (ie of rank k) occuring is
   * (www.icis.ntu.edu.sg/scs-ijit/1204/1204_6.pdf):
   *
   * Pk = C/k^s where C is approximated by (1-s)/(N^(1-s))
   *
   * From the paper listed above a default s=0.8 the most popular 20% occur
   * with a cumulative probability of about 72% for a large number of samples.
   *
   * In this class, m_s replaces s, m_C replaces C and m_max_val replaces N
   */
  class DiscreteRandomGeneratorZipf: public DiscreteRandomGenerator {
  public:
    /** Constructor; sets the "s" of the algorithm */
    DiscreteRandomGeneratorZipf(double s = 0.8);

    /**
     * Returns the probability of generating val + 1 from this distribution
     * Uses val + 1 because dist. pmf is undefined at 0.
     * Works for the range [0, max_val]
     * @return probability of generating val + 1 from this distribution
     */
    double pmf(uint64_t val);

  private:
    /** true if `m_norm` was initialized */
    bool m_initialized;

    /** The 's' of the zipfian algorithm */
    double m_s;

    /** Helper for calculating the probability in pmf() */ 
    double m_norm;
  };

  /** @}*/

} // namespace Hypertable

#endif // HYPERTABLE_DISCRETERANDOMGENERATORZIPF_H
