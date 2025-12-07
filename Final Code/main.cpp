#include <iostream>
#include <string>
#include <fstream>
#include "ConfidenceExplanation.h"
#include "MultiLanguageDetector.h"
#include "LinkRatioDetector.h"
#include"Aho_Corasick.h"
#include"SentimentAndUrgency.h"
#include"SuspiciousFileTypes.h"
#include "url_heuristic.h"
#include "spoof_analysis.h"
#include "domain_similarity.h"
#include "spoof_utils.h"
#include "hashtable.h"
using namespace std;

int main() {

    ConfidenceExplanation confidenceSystem;
    MultiLanguageDetector languageDetector;
    LinkRatioDetector linkDetector;

    string emailContent;
    int emailType;

    cout << "Enter the email content:\n";
    getline(cin, emailContent);

    cout << "\nSelect email type:\n";
    cout << "1 - Safe Email\n";
    cout << "2 - Phishing Email\n";
    cout << "3 - Homograph Attack Email\n";
    cout << "Enter choice (1-3): ";
    cin >> emailType;
    cin.ignore(); // Clear newline from input buffer

    cout << "\n" << string(50, '=');
    cout << "\nEMAIL ANALYSIS\n";
    cout << string(50, '=') << endl;
    cout << "Content: " << emailContent << endl;

    // Analyze language and link ratio
    languageDetector.analyzeText(emailContent);
    linkDetector.analyzeText(emailContent);

    // Set flags for confidence explanation
    bool flags[5] = {false, false, false, false, false};
    string flagNames[5] = {"too_many_links", "urgent_language", "suspicious_domain", "risky_attachment", "suspicious_keywords"};

    if (emailType == 2) { // Phishing
        flags[0] = true;  // too_many_links
        flags[1] = true;  // urgent_language
        flags[2] = true;  // suspicious_domain
        flags[4] = true;  // suspicious_keywords
    } else if (emailType == 3) { // Homograph
        flags[1] = true; // urgent_language
        flags[2] = true; // suspicious_domain
    }
    // Safe email: all flags remain false

    confidenceSystem.generateExplanation(flags, flagNames, 5);

    cout << "\n" << string(50, '=');
    cout << "\nSYSTEM ANALYSIS COMPLETE!\n";
    cout << string(50, '=') << endl;
        
    TrieNode* root=new TrieNode();
    int notFound=1;
    string text;
    string word="";
    ifstream file("keywords.txt");
    if(!file){
        cout<<"keywords.txt is not found/opening."<<endl;
        return 0;
    }
    string keyword;
    while(getline(file,keyword)){
        insertWord(root,keyword);
    }
    file.close();
    cout<<"Paste text here: ";
    getline(cin,text);
    text +='-';
    for(int i=0;i<text.length();i++){
        if(isalpha(text[i]))
            word +=tolower(text[i]);
        else if(word!=""){
            if(searchWord(root,word)==1){
                cout<<"Suspicious word detected: "<<word<<endl;
                notFound=0;
            }
            word="";
        }
    }
    if(notFound)
        cout<<"Safe: No suspicious activity detected."<<endl;
    
    WordScore keywords[] = {
        {"urgent",2},{"immediately",3},{"hurry",2},{"important",2},
        {"offer",2},{"free",1},{"ending soon",2},{"expiring soon",2},
        {"gift",1}, {"special",1},{"respond now",3},{"reward",2},{"claim",1},
        {"response",1},{"login",2},{"password",2},{"time",1},
        {"verify",2},{"attention",2},{"update",2},{"required",2},{"act now",3},
        {"final",3},{"warning",3},{"alert",2},{"confirm",2},{"security",3},
        {"secure",1},{"account",1},{"verified",1},{"limited",1}
    };

    int size;
    size=sizeof(keywords)/sizeof(keywords[0]);
    int total=TotalScore(text, keywords, size);
    UrgencyTone(total);
    struct Trie* root1=new Trie();
    notFound=1;
    word="";
    
    file.open("extensions.txt");
    if(!file){
        cout<<"wordScore.txt is not found."<<endl;
        return 0;
    }
    keyword="";
    while(getline(file,keyword))
        insertWords(root1,keyword);
    file.close();
    for(int i=0;i<text.length();i++){
        if(isalpha(text[i]) || text[i]=='.')
            word +=tolower(text[i]);
        else if(word!=""){
            int result=searchWords(root1,word);
            if(result==1 ||result==2){
                cout<<"Safe file type detected: "<<word<<endl;
                notFound=0;
            }
            else if(result==3){
                cout<<"Archive file detected: "<<word<<" . It may contain hidden files. Recommend: Scan before opening. "<<endl;
                notFound=0;
            }
            else if(result==4){
                cout<<"High-risk script file detected: "<<word<<" . It could execute harmful code."<<endl;
                notFound=0;
            }
            else if(result==5){
                cout<<"Critical threat! Executable file detected: "<<word<<" . Do NOT open."<<endl;
                notFound=0;
            }
            word="";
        }
    }
    if(notFound)
        cout<<"No file detected."<<endl;

    TrustedDB db;
    db.loadFromFile("trusted_domains.txt");

    string testDomain;
    cout << "\n--- Phishing URL Detector ---\n";
    cout << "Enter suspicious domain or URL: ";
    getline(cin, testDomain);
    for (auto & c: testDomain) c = tolower(c);  //move to lower case first
    string cleanDomain = "";
    for(char c : testDomain) {
        if(c != ' ' && c != '\t') cleanDomain += c;
    }
    testDomain = cleanDomain;
    
if (testDomain.empty()) {
    cout << "Error: Input cannot be empty.\n";
    return 1;
}
  string rawInput = testDomain;
    // Remove http:// or https://
if (testDomain.find("https://") == 0) testDomain = testDomain.substr(8);
else if (testDomain.find("http://") == 0) testDomain = testDomain.substr(7);

// Then remove www. (Existing code)
if (testDomain.length() > 4 && testDomain.substr(0, 4) == "www.") {
    testDomain = testDomain.substr(4);
}    
    // 2. Run Fast Heuristics first (Low cost)
    cout << "\n==============================\n";
    cout << "URL Heuristic Analysis\n";
    cout << "==============================\n";
    cout << analyzeURL(rawInput) << endl;

    // 3. Check Database for Exact Match (O(log N) speed)
    if (db.isTrusted(testDomain)) {
        cout << "EXACT MATCH FOUND: This domain is in your trusted database.\n";
        cout << "Status: SAFE\n";
        return 0; 
    }

    // 4. If not found, find the Closest Match in the Tree
    string bestMatch = db.getBestMatch(testDomain);

    if (bestMatch.empty()) {
        cout << "No data in database to compare against.\n";
        return 1;
    }

    cout << "Exact match not found. Checking against closest target: " << bestMatch << "\n";

    // 5. Run Deep Analysis on the detected target
    cout << "==============================\n";
    cout << "Visual Spoof Analysis\n";
    cout << "==============================\n";
    SpoofResult spoof = analyzeSpoof(bestMatch, testDomain);
    showResult(spoof, bestMatch, testDomain);

    cout << "==============================\n";
    cout << "Domain Similarity Analysis\n";
    cout << "==============================\n";
    
    int dist = levenshteinDistance(bestMatch, testDomain);
    double similarity = findSimilarity(dist, bestMatch, testDomain);
    showResult(bestMatch, testDomain, dist, similarity);

    cout << "\nAnalysis complete.\n";
    return 0;   
        
}