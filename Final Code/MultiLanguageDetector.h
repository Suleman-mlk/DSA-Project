#ifndef MULTILANGUAGEDETECTOR_H
#define MULTILANGUAGEDETECTOR_H
#include <iostream>
#include <string>
#include <cwctype>
using namespace std;

class MultiLanguageDetector {
private:
    struct CharMapping {
        wchar_t similarChar;
        char baseChar;
        CharMapping* next;
        CharMapping(wchar_t simChar, char base) 
            : similarChar(simChar), baseChar(base), next(nullptr) {}
    };
    CharMapping* head;

public:
    MultiLanguageDetector() : head(nullptr) {
        addMapping(L'а', 'a'); addMapping(L'е', 'e'); addMapping(L'о', 'o');
        addMapping(L'р', 'p'); addMapping(L'с', 'c'); addMapping(L'у', 'y');
        addMapping(L'х', 'x'); addMapping(L'Α', 'A'); addMapping(L'Β', 'B');
    }
    
    void addMapping(wchar_t similarChar, char baseChar) {
        CharMapping* newMapping = new CharMapping(similarChar, baseChar);
        if (!head) {
            head = newMapping;
        } else {
            CharMapping* current = head;
            while (current->next) current = current->next;
            current->next = newMapping;
        }
    }
    
    char getBaseChar(wchar_t unicodeChar) {
        CharMapping* current = head;
        while (current) {
            if (current->similarChar == unicodeChar) return current->baseChar;
            current = current->next;
        }
        return '\0';
    }
    
    bool isSuspiciousUnicode(wchar_t unicodeChar) {
        return getBaseChar(unicodeChar) != '\0';
    }
    
    void analyzeText(const string& text) {
        cout << "\nMULTI-LANGUAGE DETECTION ANALYSIS\n";
        cout << "===================================\n";
        
        wstring wideText(text.begin(), text.end());
        
        int englishCount = 0, cyrillicCount = 0, greekCount = 0, arabicCount = 0;
        for (size_t i = 0; i < wideText.length(); i++) {
            wchar_t ch = wideText[i];
            if ((ch >= L'a' && ch <= L'z') || (ch >= L'A' && ch <= L'Z')) englishCount++;
            else if ((ch >= L'а' && ch <= L'я') || (ch >= L'А' && ch <= L'Я')) cyrillicCount++;
            else if ((ch >= L'α' && ch <= L'ω') || (ch >= L'Α' && ch <= L'Ω')) greekCount++;
            else if (ch >= L'ا' && ch <= L'ي') arabicCount++;
        }
        
        string mainScript = "English/Latin";
        if (cyrillicCount > englishCount) mainScript = "Cyrillic";
        else if (greekCount > englishCount) mainScript = "Greek";
        else if (arabicCount > englishCount) mainScript = "Arabic";
        
        cout << "Main Script Detected: " << mainScript << endl;
        
        bool hasSuspiciousUnicode = false;
        for (size_t i = 0; i < wideText.length(); i++) {
            if (isSuspiciousUnicode(wideText[i])) {
                hasSuspiciousUnicode = true;
                break;
            }
        }
        
        if (hasSuspiciousUnicode) {
            cout << "SUSPICIOUS UNICODE CHARACTERS DETECTED!\n";
            cout << "   This may be a homograph attack using characters that look like English letters.\n";
        } else {
            cout << "No suspicious Unicode characters detected.\n";
        }
        cout << "===================================\n";
    }
    
    ~MultiLanguageDetector() {
        CharMapping* current = head;
        while (current) {
            CharMapping* next = current->next;
            delete current;
            current = next;
        }
    }
};
#endif