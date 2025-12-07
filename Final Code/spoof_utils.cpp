#include "spoof_utils.h"

// Function to replace look-alike characters using a hash map
string normalizeDomain(string domain) {
    unordered_map<string, string> lookalikes = {
        {"rn", "m"},
        {"vv", "w"},
        {"0", "o"},
        {"1", "l"},
        {"3", "e"},
        {"@", "a"},
        {"$", "s"}
    };

    string result;
    for (int i = 0; i < domain.length(); i++) {
        // check for 2-letter lookalike first
        if (i < domain.length() - 1) {
            string two = domain.substr(i, 2);
            if (lookalikes.find(two) != lookalikes.end()) {
                result += lookalikes[two];
                i++; // skip next character
                continue;
            }
        }

        string one(1, domain[i]);
        if (lookalikes.find(one) != lookalikes.end())
            result += lookalikes[one];
        else
            result += domain[i];
    }

    return result;
}

// Function to compare domains and find similarity %
float compareDomains(const string &d1, const string &d2) {
    int matches = 0;
    int maxLen = max(d1.length(), d2.length());

    for (int i = 0; i < min(d1.length(), d2.length()); i++) {
        if (d1[i] == d2[i]) matches++;
    }

    float percent = (matches / (float)maxLen) * 100;
    return percent;
}
