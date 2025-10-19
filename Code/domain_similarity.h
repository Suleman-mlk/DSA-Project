#ifndef DOMAIN_SIMILARITY_H
#define DOMAIN_SIMILARITY_H

#include <string>
using namespace std;

void getDomain(string &a, string &b);
int levenshteinDistance(string a, string b);
double findSimilarity(int distance, string a, string b);
void showResult(string a, string b, int distance, double similarity);

#endif
