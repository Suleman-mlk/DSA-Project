#ifndef SPOOF_ANALYSIS_H
#define SPOOF_ANALYSIS_H

#include <iostream>
#include <string>
using namespace std;

// Holds final result data
struct SpoofResult {
    float similarity;
    string verdict;
};

// Function declarations
void getDomains(string &realDomain, string &testDomain);
SpoofResult analyzeSpoof(const string &realDomain, const string &testDomain);
void showResult(const SpoofResult &r, const string &realDomain, const string &testDomain);

#endif
