#ifndef LINKRATIODETECTOR_H
#define LINKRATIODETECTOR_H
#include <iostream>
#include <string>
using namespace std;

class LinkRatioDetector {
private:
    int maxLinks;
    float suspiciousRatio;
    
    bool isURL(const string& word) {
        if (word.length() < 5) return false;
        if (word.find("http://") == 0) return true;
        if (word.find("https://") == 0) return true;
        if (word.find("www.") == 0) return true;
        if (word.find(".com") != string::npos) return true;
        if (word.find(".org") != string::npos) return true;
        if (word.find(".net") != string::npos) return true;
        return false;
    }
    
    int countWords(const string& text) {
        int wordCount = 0;
        bool inWord = false;
        for (size_t i = 0; i < text.length(); i++) {
            if (text[i] == ' ' || text[i] == '\n' || text[i] == '\t') {
                if (inWord) { wordCount++; inWord = false; }
            } else {
                inWord = true;
            }
        }
        if (inWord) wordCount++;
        return wordCount;
    }

public:
    LinkRatioDetector() : maxLinks(3), suspiciousRatio(0.3f) {}
    
    void analyzeText(const string& text) {
        cout << "\n🔗 LINK RATIO DETECTOR ANALYSIS\n";
        cout << "===============================\n";
        
        int linkCount = 0, wordCount = countWords(text);
        string temp = text + " ";
        string currentWord = "";
        
        for (size_t i = 0; i < temp.length(); i++) {
            if (temp[i] == ' ' || temp[i] == '\n' || temp[i] == '\t') {
                if (!currentWord.empty() && isURL(currentWord)) linkCount++;
                currentWord = "";
            } else {
                currentWord += temp[i];
            }
        }
        
        float linkRatio = wordCount > 0 ? (float)linkCount / wordCount : 0.0f;
        
        cout << "📊 Basic Statistics:\n";
        cout << "   - Total words: " << wordCount << endl;
        cout << "   - Total links: " << linkCount << endl;
        cout << "   - Link-to-word ratio: " << (linkRatio * 100) << "%\n";
        
        if (linkCount > maxLinks) {
            cout << " TOO MANY LINKS DETECTED! Found " << linkCount << " links\n";
        } else {
            cout << "Link count is within acceptable limits.\n";
        }
        
        if (linkRatio > suspiciousRatio) {
            cout << "HIGH LINK DENSITY DETECTED! " << (linkRatio * 100) << "% is links\n";
        } else {
            cout << "Link density is within normal range.\n";
        }
        cout << "===============================\n";
    }
};
#endif
