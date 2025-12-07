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

// Ensure this matches header: const string &a, const string &b
int levenshteinDistance(const string &a, const string &b) {
    string s1 = a;
    string s2 = b;
    
    // Truncate if too long (Fix from before)
    if (s1.length() > 100) s1 = s1.substr(0, 100);
    if (s2.length() > 100) s2 = s2.substr(0, 100);

    int n = s1.length(), m = s2.length();
    if (n == 0) return m;
    if (m == 0) return n;

    int dp[101][101];
    for (int i = 0; i <= n; i++) dp[i][0] = i;
    for (int j = 0; j <= m; j++) dp[0][j] = j;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = 1 + min3(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]);
        }
    }
    return dp[n][m];
}

// FIX: Added const string &a, const string &b
double findSimilarity(int distance, const string &a, const string &b) {
    int maxLen = (a.length() > b.length()) ? a.length() : b.length();
    if (maxLen == 0) return 100.0;
    return (1.0 - (double)distance / maxLen) * 100.0;
}

// FIX: Added const string &a, const string &b
void showResult(const string &a, const string &b, int distance, double similarity) {
    cout << "\n--- Domain Similarity Report ---\n";
    cout << "Domain 1: " << a << endl;
    cout << "Domain 2: " << b << endl;
    cout << "Edit Distance: " << distance << endl;
    cout << "Similarity: " << similarity << "%" << endl;

    if (similarity > 85  && similarity!=100)
        cout << "Warning: Domains look very similar. Possible phishing attempt!\n";
    else
        cout << "Domains seem different and safe.\n";
}