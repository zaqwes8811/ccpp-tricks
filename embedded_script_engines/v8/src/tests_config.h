#ifndef TESTS_CONFIG_H_
#define TESTS_CONFIG_H_

// C++
#include <string>

#define IN_OWN_PROJECT

//static const std::string kPathToTestScripts = "..\\..\\third_party\\v8\\scripts\\";
#ifdef IN_OWN_PROJECT
static const std::string kPathToTestScripts = "..\\..\\scripts\\";
#endif

#endif  // TESTS_CONFIG_H_