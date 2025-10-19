#include "url_heuristic.h"
#include <algorithm>
#include <cctype>

bool isTooLong(string url) {
    return url.length() > 120;
}

bool hasAtSymbol(string url) {
    for (int i = 0; i < url.length(); i++) {
        if (url[i] == '@') return true;
    }
    return false;
}

bool hasIPAddress(string url) {
    for (int i = 0; i < url.length(); i++) {
        if (isdigit(url[i])) {
            int dots = 0;
            string part = "";
            int j = i;
            while (j < url.length() && (isdigit(url[j]) || url[j] == '.')) {
                if (url[j] == '.') {
                    if (part == "") return false;
                    int num = stoi(part);
                    if (num < 0 || num > 255) return false;
                    part = "";
                    dots++;
                } else {
                    part += url[j];
                }
                j++;
            }
            if (part != "") {
                int num = stoi(part);
                if (num < 0 || num > 255) return false;
            }
            if (dots == 3) return true;
            i = j;
        }
    }
    return false;
}

bool hasNoHTTPS(string url) {
    string lower = url;
    for (int i = 0; i < lower.length(); i++) {
        lower[i] = tolower(lower[i]);
    }
    if (lower.find("https://") == 0) return false;
    return true;
}

bool hasSuspiciousWord(string url) {
    string lower = url;
    for (int i = 0; i < lower.length(); i++) {
        lower[i] = tolower(lower[i]);
    }

    if (lower.find("login") != string::npos) return true;
    if (lower.find("verify") != string::npos) return true;
    if (lower.find("update") != string::npos) return true;
    if (lower.find("secure") != string::npos) return true;

    return false;
}

bool hasTooManyDots(string url) {
    int dots = 0;
    for (int i = 0; i < url.length(); i++) {
        if (url[i] == '.') dots++;
    }
    return dots > 6;
}

bool hasPercentEncoding(string url) {
    int count = 0;
    for (int i = 0; i < url.length(); i++) {
        if (url[i] == '%') count++;
    }
    return count > 2;
}

string analyzeURL(string url) {
    int score = 0;
    string reasons = "";

    if (isTooLong(url)) {
        score += 10;
        reasons += "URL too long (+10)\n";
    }
    if (hasAtSymbol(url)) {
        score += 8;
        reasons += "Contains '@' symbol (+8)\n";
    }
    if (hasIPAddress(url)) {
        score += 12;
        reasons += "Contains IP address (+12)\n";
    }
    if (hasNoHTTPS(url)) {
        score += 6;
        reasons += "Does not use HTTPS (+6)\n";
    }
    if (hasSuspiciousWord(url)) {
        score += 10;
        reasons += "Contains suspicious keyword (+10)\n";
    }
    if (hasTooManyDots(url)) {
        score += 6;
        reasons += "Too many dots (+6)\n";
    }
    if (hasPercentEncoding(url)) {
        score += 6;
        reasons += "Many % encodings (+6)\n";
    }

    string risk;
    if (score >= 30) risk = "HIGH RISK";
    else if (score >= 15) risk = "SUSPICIOUS";
    else risk = "LOW RISK";

    string result = "Score: " + to_string(score) + "\n" + reasons + "Verdict: " + risk + "\n";
    return result;
}
