//
// Created by zaqwes on 17.09.2022.
//

#pragma once

#include <string>
#include <vector>

#include "mission-critical-sw-experiments/tests/arena.hpp"

namespace leetcode {
using namespace std;

// TODO(me) RVO check

string convert_ref(string s, int numRows) {
    if (numRows == 1) return s;

    vector<string> rows(min(numRows, int(s.size())));
    int curRow = 0;
    bool goingDown = false;

    for (char c : s) {
        rows[curRow] += c;
        if (curRow == 0 || curRow == numRows - 1) goingDown = !goingDown;
        curRow += goingDown ? 1 : -1;
    }

    string ret;
    for (string row : rows) ret += row;
    return ret;
}

string convert_base(string s, int numRows) {
    // Idea: Add some to s in order to align it, store size. It can break alg

    // string result;
    if (numRows == 1) {
        // result.swap(s);
        return s;  // result;  // RVO?
    }

    static const auto sso_capacity = std::string().capacity();

    const auto ssz = s.size();

    static constexpr auto maybeReserve = [&](string& s, int sz) {
        if (sz > sso_capacity) {
            s.reserve(sz);
        }
    };

    // Idea: Can reuse s, but no RVO
    // strings
    // https://habr.com/ru/company/oleg-bunin/blog/352280/

    // Idea: allocate close. Automatically with SSO
    string* row_to_slice = new string[numRows];

    const int kStride = (numRows - 1) * 2;
    const int kMaxStideLength = ssz / kStride + 1;

    // Preallocate
    maybeReserve(row_to_slice[0], ssz);  // First one will be result
    for (auto i = 1; i < numRows; ++i) {
        maybeReserve(row_to_slice[i], kMaxStideLength);
    }

    int size = 0;
    if (ssz % kStride) {
        size = ssz / kStride + 1;  // had bug really, it was protected by condition inside
    } else {
        size = ssz / kStride;
    }

    // Idea: Split to boxes
    // Idea: Prefect part
    for (auto iter = 0; iter < size; ++iter) {
        int counter = 0;
        int direction = 1;

        // char buf[kStride];
        // for (int subidx = 0; subidx < kStride; ++subidx) {
        //     const auto internal_ptr = iter * kStride + subidx;
        //     if (internal_ptr >= ssz) {
        //         break;
        //     }
        //     buf[subidx] = s[internal_ptr];
        // }
        for (int subidx = 0; subidx < kStride; ++subidx) {
            const auto internal_ptr = iter * kStride + subidx;
            if (internal_ptr >= ssz) {
                break;
            }

            if (subidx == numRows) {
                counter -= 2;
                direction = -1;
            }

            // Idea: It's not cache write efficiton it's good idea to add two at same time
            //   But it's read cache efficient
            row_to_slice[counter] += s[internal_ptr];

            counter += direction;
        }
    }

    // SSO guess. With SSO reserver is pessimization
    string result = std::move(row_to_slice[0]);

    for (auto i = 1; i < numRows; ++i) {
        result += row_to_slice[i];  // no copy needed if we store directly
    }

    delete[] row_to_slice;

    return result;
}

string convert_best(string s, int numRows) {
    // Idea: Add some to s in order to align it, store size. It can break alg

    // string result;
    if (numRows == 1) {
        return s;
    }

    static const auto sso_capacity = std::string().capacity();

    const auto ssz = s.size();

    static constexpr auto maybeReserve = [&](string& s, int sz) {
        if (sz > sso_capacity) {
            s.reserve(sz);
        }
    };

    // Idea: Can reuse s, but no RVO
    // strings
    // https://habr.com/ru/company/oleg-bunin/blog/352280/

    // Idea: allocate close. Automatically with SSO
    string* row_to_slice = new string[numRows - 1];

    const int kStride = (numRows - 1) * 2;
    const int kMaxStideLength = ssz / kStride + 1;

    // Preallocate
    // maybeReserve(row_to_slice[0], ssz);  // First one will be result
    for (auto i = 0; i < numRows - 1; ++i) {
        maybeReserve(row_to_slice[i], kMaxStideLength);
    }

    int size = 0;
    if (ssz % kStride) {
        size = ssz / kStride + 1;  // had bug really, it was protected by condition inside
    } else {
        size = ssz / kStride;
    }

    // Idea: Split to boxes
    // Idea: Prefect part
    int in_place_counter = 0;
    auto siter = s.begin();
    auto send = s.cend();

    // TODO() Rangebase loop
    for (auto iter = 0; iter < size; ++iter) {
        int counter = 0;
        int direction = 1;

        for (int subidx = 0; subidx < kStride; ++subidx) {
            // const auto internal_ptr = iter * kStride + subidx;
            // if (internal_ptr >= ssz) {
            //     break;
            // }

            if (siter == send) {
                break;
            }

            if (subidx == numRows) {
                counter -= 2;
                direction = -1;
            }

            // Idea: It's not cache write efficiton it's good idea to add two at same time
            //   But it's read cache efficient
            const auto current_letter = *siter;  // s[internal_ptr];
            // ++internal_ptr;
            ++siter;
            if (counter == 0) {
                s[in_place_counter] = current_letter;
                // *wr_iter = current_letter;  // ? why doesn't work. Iter inavalidation?
                ++in_place_counter;
                // ++wr_iter;
            } else {
                row_to_slice[counter - 1] += current_letter;
            }

            counter += direction;
        }
    }

    // s.insert(s.begin() + in_place_counter, row_to_slice[0].begin(), row_to_slice[0].end());
    //    s.resize(in_place_counter);
    //    for (auto i = 0; i < numRows - 1; ++i) {
    //        s.insert(s.end(), row_to_slice[i].begin(), row_to_slice[i].end());
    //    }

    s.replace(in_place_counter, row_to_slice[0].size(), row_to_slice[0]);
    in_place_counter += row_to_slice[0].size();
    for (auto i = 1; i < numRows - 1; ++i) {
        s.replace(in_place_counter, row_to_slice[i].size(), row_to_slice[i]);
        in_place_counter += row_to_slice[i].size();
    }

    delete[] row_to_slice;

    return s;
}

// TODO() arena
// TODO() split direct move and back
// TODO() don't use input string - less branches

}  // namespace leetcode