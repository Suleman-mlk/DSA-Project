#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>
#include <fstream>
#include <cctype> // Required for tolower
#include "domain_similarity.h" 

using namespace std;

struct Node {
    string domain;
    Node* next;
    
    // Constructor for easier node creation
    Node(string d) : domain(d), next(nullptr) {}
};

struct TrustedDB {
    // 1009 is a prime number. Primes reduce the chance of patterns in data causing collisions.
    static const int TABLE_SIZE = 1009; 
    Node* table[TABLE_SIZE];

    // DJB2 Hash Function - A classic, simple, and effective string hash
    int hashFunction(const string &key) {
        unsigned long hash = 5381;
        for (char c : key) {
           hash = (hash * 33) + c;
        }
        return hash % TABLE_SIZE;
    }

    TrustedDB() {
        // Initialize all array slots to NULL (empty shelves)
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr;
        }
    }

    ~TrustedDB() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            Node* current = table[i];
            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
    }

    // O(1) Insertion
    void insert(const string &domain) {
        // 1. Check if it already exists to prevent duplicates
        if (isTrusted(domain)) return; 

        // 2. Calculate which "bucket" (index) this domain belongs to
        int index = hashFunction(domain);
        
        // 3. Create node
        Node* newNode = new Node(domain);
        
        // 4. Insert at HEAD (Standard Linked List insertion)
        newNode->next = table[index];
        table[index] = newNode;
    }

    // O(1) Lookup
    bool isTrusted(const string &domain) {
        int index = hashFunction(domain);
        Node* current = table[index];

        // Walk the list at this specific index
        while (current != nullptr) {
            if (current->domain == domain) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    string getBestMatch(const string &input) {
        string bestMatch = "";
        int minDistance = 2147483647; // Max standard integer value

        // We must check EVERY bucket because similar words might hash to totally different indexes
        for (int i = 0; i < TABLE_SIZE; i++) {
            Node* current = table[i];
            while (current != nullptr) {
                int dist = levenshteinDistance(current->domain, input);
                
                if (dist < minDistance) {
                    minDistance = dist;
                    bestMatch = current->domain;
                }
                // Optimization: Exact match found
                if (minDistance == 0) return bestMatch; 

                current = current->next;
            }
        }
        return bestMatch;
    }

    void loadFromFile(string filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Could not open " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            string clean = "";
            for (char c : line) {
                // Keep only printable characters, ignore whitespace
                if (!isspace(c)) { 
                    clean += tolower(c);
                }
            }
            if (!clean.empty()) {
                insert(clean);
            }
        }
        file.close();
        cout << "Database loaded successfully." << endl;
    }
};

#endif