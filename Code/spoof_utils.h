#ifndef SPOOF_UTILS_H
#define SPOOF_UTILS_H

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

// Replaces look-alike letters with their real versions
string normalizeDomain(string domain);

// Checks similarity between two domains (simple % match)
float compareDomains(const string &d1, const string &d2);

#endif
