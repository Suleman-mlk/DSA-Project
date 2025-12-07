#ifndef DOMAIN_SIMILARITY_H
#define DOMAIN_SIMILARITY_H

#include <string>
using namespace std;

void getDomain(string &a, string &b);
int levenshteinDistance(const string &a, const string &b);
double findSimilarity(int distance, const string &a, const string &b);
void showResult(const string &a, const string &b, int distance, double similarity);

#endif