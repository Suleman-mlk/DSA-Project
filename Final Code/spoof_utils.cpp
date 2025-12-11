#include "spoof_utils.h"

string normalizeDomain(string domain) {
    string result = "";
    for (int i = 0; i < domain.length(); i++) {
        if (i < domain.length() - 1) {
            string two = domain.substr(i, 2);
            if (two == "rn") {
                result += 'm';
                i++;
                continue;
            }
            else if (two == "vv") {
                result += 'w';
                i++;
                continue;
            }
        }
        char c = domain[i];
        if (c == '0') {
            result += 'o';
        }
        else if (c == '1') {
            result += 'l';
        }
        else if (c == '3') {
            result += 'e';
        }
        else if (c == '@') {
            result += 'a';
        }
        else if (c == '$') {
            result += 's';
        }
        else {
            result += c;
        }
    }
    return result;
}

float compareDomains(const string &d1, const string &d2) {
    int matches = 0;
    
    if (d1.empty() && d2.empty()) return 100.0f;
    
    int maxLen = max(d1.length(), d2.length());
    if (maxLen == 0) return 0.0f;

    for (int i = 0; i < min(d1.length(), d2.length()); i++) {
        if (d1[i] == d2[i]) matches++;
    }

    float percent = (matches / (float)maxLen) * 100;
    return percent;
}
