#include "spoof_utils.h"
#include <string>
using namespace std;

// Node structure for linked list
struct Node {
    string key;
    string value;
    Node* next;
    Node(string k, string v) : key(k), value(v), next(nullptr) {}
};

// Function to replace look-alike characters using a linked list
string normalizeDomain(string domain) {
    // Build linked list of lookalikes
    Node* head = new Node("rn", "m");
    head->next = new Node("vv", "w");
    head->next->next = new Node("0", "o");
    head->next->next->next = new Node("1", "l");
    head->next->next->next->next = new Node("3", "e");
    head->next->next->next->next->next = new Node("@", "a");
    head->next->next->next->next->next->next = new Node("$", "s");

    string result;
    for (int i = 0; i < domain.length(); i++) {
        bool replaced = false;

        // check for 2-letter lookalike first
        if (i < domain.length() - 1) {
            string two = domain.substr(i, 2);
            Node* temp = head;
            while (temp) {
                if (temp->key == two) {
                    result += temp->value;
                    i++; // skip next character
                    replaced = true;
                    break;
                }
                temp = temp->next;
            }
            if (replaced) continue;
        }

        // check for 1-letter lookalike
        string one(1, domain[i]);
        Node* temp = head;
        while (temp) {
            if (temp->key == one) {
                result += temp->value;
                replaced = true;
                break;
            }
            temp = temp->next;
        }

        if (!replaced)
            result += domain[i];
    }

    Node* curr = head;
    while (curr) {
        Node* next = curr->next;
        delete curr;
        curr = next;
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
