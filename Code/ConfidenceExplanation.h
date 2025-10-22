#ifndef CONFIDENCEEXPLANATION_H
#define CONFIDENCEEXPLANATION_H
#include <iostream>
#include <string>
using namespace std;

class ConfidenceExplanation {
private:
    struct RuleNode {
        string ruleName;
        string explanation;
        RuleNode* next;
        RuleNode(const string& name, const string& expl) 
            : ruleName(name), explanation(expl), next(nullptr) {}
    };
    RuleNode* head;
    
public:
    ConfidenceExplanation() : head(nullptr) {
        addRule("too_many_links", "This message contains an unusually high number of links, which is common in phishing attempts.");
        addRule("urgent_language", "The message uses urgent or threatening language to pressure quick action without thinking.");
        addRule("suspicious_domain", "The domain name looks suspicious or is very similar to a trusted website.");
        addRule("risky_attachment", "The message contains potentially dangerous file attachments that could harm your computer.");
        addRule("suspicious_keywords", "The message contains words commonly used in phishing scams.");
    }
    
    void addRule(const string& ruleName, const string& explanation) {
        RuleNode* newRule = new RuleNode(ruleName, explanation);
        if (!head) {
            head = newRule;
        } else {
            RuleNode* current = head;
            while (current->next) current = current->next;
            current->next = newRule;
        }
    }
    
    string getExplanation(const string& ruleName) {
        RuleNode* current = head;
        while (current) {
            if (current->ruleName == ruleName) return current->explanation;
            current = current->next;
        }
        return "No explanation found for: " + ruleName;
    }
    
    void generateExplanation(bool* flags, const string* flagNames, int flagCount) {
        cout << "\n🔍 SECURITY ANALYSIS REPORT:\n";
        cout << "============================\n";
        bool anyIssues = false;
        for (int i = 0; i < flagCount; i++) {
            if (flags[i]) {
                anyIssues = true;
                cout  << getExplanation(flagNames[i]) << endl;
            }
        }
        if (!anyIssues) {
            cout << " No security issues detected. This message appears safe.\n";
        }
        cout << "============================\n";
    }
    
    ~ConfidenceExplanation() {
        RuleNode* current = head;
        while (current) {
            RuleNode* next = current->next;
            delete current;
            current = next;
        }
    }
};
#endif
