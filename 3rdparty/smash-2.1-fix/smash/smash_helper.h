#ifndef SMASH_HELPER_H_
#define SMASH_HELPER_H_

#include <boost/tuple/tuple.hpp>

#include <vector>
#include <string>

std::vector<unsigned char>
helper_handleRequest(const std::vector<unsigned char>& request, const int isAuthorized);

boost::tuple<unsigned char, std::string>
helper_getPDUAndCommunity(const std::vector<unsigned char>& request);

#endif
