#ifndef URL_HEURISTIC_H
#define URL_HEURISTIC_H

#include <string>
using namespace std;

bool isTooLong(string url);
bool hasAtSymbol(string url);
bool hasIPAddress(string url);
bool hasNoHTTPS(string url);
bool hasSuspiciousWord(string url);
bool hasTooManyDots(string url);
bool hasPercentEncoding(string url);
string analyzeURL(string url);

#endif
