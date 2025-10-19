#include <iostream>
#include "domain_similarity.h"
using namespace std;

int min3(int a, int b, int c) {
    if (a <= b && a <= c) return a;
    if (b <= a && b <= c) return b;
    return c;
}

void getDomain(string &a, string &b) {
    cout << "Enter first domain: ";
    cin >> a;
    cout << "Enter second domain: ";
    cin >> b;
}

int levenshteinDistance(string a, string b) {
    int n = a.length(), m = b.length();
    int dp[101][101];
    for (int i = 0; i <= n; i++) dp[i][0] = i;
    for (int j = 0; j <= m; j++) dp[0][j] = j;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = 1 + min3(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]);
        }
    }
    return dp[n][m];
}

double findSimilarity(int distance, string a, string b) {
    int maxLen = (a.length() > b.length()) ? a.length() : b.length();
    if (maxLen == 0) return 100.0;
    return (1.0 - (double)distance / maxLen) * 100.0;
}

void showResult(string a, string b, int distance, double similarity) {
    cout << "\n--- Domain Similarity Report ---\n";
    cout << "Domain 1: " << a << endl;
    cout << "Domain 2: " << b << endl;
    cout << "Edit Distance: " << distance << endl;
    cout << "Similarity: " << similarity << "%" << endl;

    if (similarity > 85)
        cout << "Warning: Domains look very similar. Possible phishing attempt!\n";
    else
        cout << "Domains seem different and safe.\n";
}
