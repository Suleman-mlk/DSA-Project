#include "url_heuristic.h"
#include <algorithm>
#include <cctype>
#include <string>

using namespace std;

bool isTooLong(string url) { return url.length() > 120; }
bool hasAtSymbol(string url) { return url.find('@') != string::npos; }
bool hasNoHTTPS(string url) { 
    string lower = url; 
    for(char &c : lower) c = tolower(c);
    // Only flag if they explicitly typed http://
    if (lower.find("http://") == 0) return true;
    return false; 
}
bool hasTooManyDots(string url) {
    int d = 0; for(char c : url) if(c == '.') d++; return d > 6;
}
bool hasPercentEncoding(string url) {
    int p = 0; for(char c : url) if(c == '%') p++; return p > 2;
}
bool hasSuspiciousWord(string url) {
    string lower = url; for(char &c : lower) c = tolower(c);
    return (lower.find("login") != string::npos || lower.find("verify") != string::npos ||
            lower.find("update") != string::npos || lower.find("secure") != string::npos);
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
                    try {
                        int num = stoi(part);
                        if (num < 0 || num > 255) return false;
                    } catch (...) { return false; }
                    part = "";
                    dots++;
                } else {
                    part += url[j];
                }
                j++;
            }
            if (part != "") {
                 try {
                    int num = stoi(part);
                    if (num < 0 || num > 255) return false;
                 } catch (...) { return false; }
            }
            if (dots == 3) return true;
            i = j;
        }
    }
    return false;
}

string analyzeURL(string url) {
    int score = 0;
    string reasons = "";

    int len = url.length();
    if (len > 120) {
        score += 10;
        reasons += "URL too long (+10)\n";
    }
    string lower = url;
    for (char &c : lower) c = tolower(c);

    if (lower.find("https://") != 0) {
        score += 6;
        reasons += "Does not use HTTPS (+6)\n";
    }

    int dots = 0;
    int ats = 0;
    int percents = 0;

    for (int i = 0; i < len; i++) {
        char c = url[i];
        if (c == '.') dots++;
        else if (c == '@') ats++;
        else if (c == '%') percents++;
    }

    if (dots > 6) { score += 6; reasons += "Too many dots (+6)\n"; }
    if (ats > 0) { score += 8; reasons += "Contains '@' symbol (+8)\n"; }
    if (percents > 2) { score += 6; reasons += "Many % encodings (+6)\n"; }

    // 4. Keyword Search (on the pre-lowercased string)
    if (lower.find("login") != string::npos || 
        lower.find("verify") != string::npos || 
        lower.find("update") != string::npos || 
        lower.find("secure") != string::npos) {
        score += 10;
        reasons += "Contains suspicious keyword (+10)\n";
    }
    if (hasIPAddress(url)) {
        score += 12;
        reasons += "Contains IP address (+12)\n";
    }
    string risk;
    if (score >= 30) risk = "HIGH RISK";
    else if (score >= 15) risk = "SUSPICIOUS";
    else risk = "LOW RISK";

    return "Score: " + to_string(score) + "\n" + reasons + "Verdict: " + risk + "\n";
}