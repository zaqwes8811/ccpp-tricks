//
// Created by zaqwes on 23.08.2022.
//

#include "models.hpp"

#include <thread>
#include <gtest/gtest.h>

TEST(Models, Thread) {

    auto model_fn = []() {
        // Sleep?

        // filter for ADC

        // Push filtered to queue?

        // Time markers? realtime_safe
    };

    auto model_th = std::thread(std::move(model_fn));

    // How to change priority after?
    auto handle = model_th.native_handle();


//    YouTube (https://www.youtube.com/watch?v=Q8vCi3ns0bs)
//    Real-Time Linux on Embedded Multicore Processors - Andreas Ehmanns, Technical Advisor

//    YouTube (https://www.youtube.com/watch?v=T-Qamm11UfI&ab_channel=TheLinuxFoundation)
//    Asymmetric Multiprocessing and Embedded Linux - Marek Novak & Dušan Červenka, NXP Semiconductor

// https://rt.wiki.kernel.org/index.php/Frequently_Asked_Questions
// https://rt.wiki.kernel.org/index.php/HOWTO:_Build_an_RT-application

}