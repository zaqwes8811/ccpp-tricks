
#include "smash_helper.h"

#include "smash.h"
#include "inner_reuse/cc_text_proc.h"

#include <algorithm>

std::vector<unsigned char>
helper_handleRequest(const std::vector<unsigned char>& request, const int isAuthorized) {
  if (SNMP_MAX_MSG_LENGTH < request.size())
    throw std::invalid_argument("Bad size");

  smashSnmpPackage_t m;
  memset(&m, 0, sizeof m);
  m.request_length = request.size();
  std::copy(request.begin(), request.end(), m.request);

  int status = smash_parseAndEmitMessage(&m, isAuthorized);
  if (status == SMASH_BUILD_ERROR)
    throw std::invalid_argument("Error on build message: " + text_proc::to_string(status));

  if (status == SMASH_WRONG_ARGS)
    throw std::invalid_argument("Wrong arg: " + text_proc::to_string(status));

  if (status != SMASH_ALL_RIGHT)
    throw std::invalid_argument("Error on emit: " + text_proc::to_string(status));


  return std::vector<unsigned char>(m.response, m.response + m.response_length);
}

boost::tuple<unsigned char, std::string>
helper_getPDUAndCommunity(const std::vector<unsigned char>& request)
{
  if (SNMP_MAX_MSG_LENGTH < request.size())
    throw std::invalid_argument("Bad size");

  smashSnmpPackage_t m;
  memset(&m, 0, sizeof m);
  m.request_length = request.size();
  std::copy(request.begin(), request.end(), m.request);

  int status = smash_parsePDUAndCommunity(&m);
  if (status != SMASH_ALL_RIGHT)
    throw std::invalid_argument("Trouble with extract pdu and ...");

  std::string community(m.mesg.access_info.community_based.string,
                   m.mesg.access_info.community_based.string
                   + m.mesg.access_info.community_based.length);

  return boost::tuple<unsigned char, std::string>(m.mesg.pdutype, community);
}
