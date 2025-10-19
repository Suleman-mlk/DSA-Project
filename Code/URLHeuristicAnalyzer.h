#ifndef URLHEURISTICANALYZER_H
#define URLHEURISTICANALYZER_H
#include <iostream>
#include <string>
using namespace std;

class URLHeuristicAnalyzer {
private:
    struct SuspiciousPattern {
        string pattern;
        int riskLevel;
        SuspiciousPattern* next;
        SuspiciousPattern(const string& pat, int risk) 
            : pattern(pat), riskLevel(risk), next(nullptr) {}
    };
    SuspiciousPattern* patternsHead;
    
    void addPattern(const string& pattern, int riskLevel) {
        SuspiciousPattern* newPattern = new SuspiciousPattern(pattern, riskLevel);
        if (!patternsHead) {
            patternsHead = newPattern;
        } else {
            newPattern->next = patternsHead;
            patternsHead = newPattern;
        }
    }
    
    bool containsSuspiciousPattern(const string& url) {
        SuspiciousPattern* current = patternsHead;
        while (current) {
            if (url.find(current->pattern) != string::npos) return true;
            current = current->next;
        }
        return false;
    }

public:
    URLHeuristicAnalyzer() : patternsHead(nullptr) {
        addPattern("login", 8); addPattern("verify", 7); addPattern("account", 6);
        addPattern("secure", 5); addPattern("bank", 9); addPattern("paypal", 8);
        addPattern("password", 9); addPattern("update", 6); addPattern("confirm", 7);
    }
    
    void analyzeURL(const string& url) {
        cout << "\n🔍 URL HEURISTIC ANALYSIS\n";
        cout << "========================\n";
        cout << "URL: " << url << endl;
        
        int riskScore = 0;
        
        if (containsSuspiciousPattern(url)) {
            cout << "⚠️  Contains suspicious keywords (phishing attempt)\n";
            riskScore += 30;
        }
        
        if (url.find("192.168.") != string::npos || url.find("10.") != string::npos) {
            cout << "⚠️  Uses IP address instead of domain name\n";
            riskScore += 25;
        }
        
        if (url.length() > 100) {
            cout << "⚠️  Very long URL: " << url.length() << " characters\n";
            riskScore += 15;
        }
        
        cout << "\n📊 RISK ASSESSMENT:\n";
        cout << "   Risk Score: " << riskScore << "/100\n";
        
        if (riskScore >= 60) cout << "   🚨 HIGH RISK: Malicious URL!\n";
        else if (riskScore >= 30) cout << "   ⚠️  MEDIUM RISK: Be cautious\n";
        else cout << "   ✅ LOW RISK: URL appears safe\n";
        
        cout << "========================\n";
    }
    
    ~URLHeuristicAnalyzer() {
        SuspiciousPattern* current = patternsHead;
        while (current) {
            SuspiciousPattern* next = current->next;
            delete current;
            current = next;
        }
    }
};
#endif