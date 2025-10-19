#include <iostream>
#include <string>
#include "ConfidenceExplanation.h"
#include "MultiLanguageDetector.h"
#include "LinkRatioDetector.h"
#include "URLHeuristicAnalyzer.h"
#include"Aho_Corasick.h"
#include"SentimentAndUrgency.h"
#include"SuspiciousFileTypes.h"
#include "url_heuristic.h"
#include "spoof_analysis.h"
#include "domain_similarity.h"
#include "spoof_utils.h"
using namespace std;

int main() {
    
    
    
    ConfidenceExplanation confidenceSystem;
    MultiLanguageDetector languageDetector;
    LinkRatioDetector linkDetector;
    URLHeuristicAnalyzer urlAnalyzer;
    
   
    string safeEmail = "Hello John, I hope you are doing well. We should schedule a meeting next week. You can check the document here: https://company.com/docs/project.pdf";
    
    string phishingEmail = "URGENT: Your account has been compromised! Click here to verify: http://secure-bank-login.com Also check: https://account-recovery.net More info: www.customer-support.org";
    
    string homographEmail = "Hello, this is а mеssаgе with Cyrillic chаrаcters. Your account has been locked: mіcrоsоft.com/login";
    
    //  Safe Email
    cout << "\n" << string(50, '=');
    cout << "\nTEST CASE 1: SAFE EMAIL\n";
    cout << string(50, '=') << endl;
    cout << "Content: " << safeEmail << endl;
    
    languageDetector.analyzeText(safeEmail);
    linkDetector.analyzeText(safeEmail);
    
    bool safeFlags[5] = {false, false, false, false, false};
    string safeFlagNames[5] = {"too_many_links", "urgent_language", "suspicious_domain", "risky_attachment", "suspicious_keywords"};
    confidenceSystem.generateExplanation(safeFlags, safeFlagNames, 5);
    
    //  Phishing Email
    cout << "\n" << string(50, '=');
    cout << "\nTEST CASE 2: PHISHING EMAIL\n";
    cout << string(50, '=') << endl;
    cout << "Content: " << phishingEmail << endl;
    
    languageDetector.analyzeText(phishingEmail);
    linkDetector.analyzeText(phishingEmail);
    
    string urls[] = {"http://secure-bank-login.com", "https://account-recovery.net", "www.customer-support.org"};
    for (int i = 0; i < 3; i++) {
        urlAnalyzer.analyzeURL(urls[i]);
    }
    
    bool phishingFlags[5] = {true, true, true, false, true};
    string phishingFlagNames[5] = {"too_many_links", "urgent_language", "suspicious_domain", "risky_attachment", "suspicious_keywords"};
    confidenceSystem.generateExplanation(phishingFlags, phishingFlagNames, 5);
    
    //  Homograph Attack
    cout << "\n" << string(50, '=');
    cout << "\nTEST CASE 3: HOMOGRAPH ATTACK\n";
    cout << string(50, '=') << endl;
    cout << "Content: " << homographEmail << endl;
    
    languageDetector.analyzeText(homographEmail);
    linkDetector.analyzeText(homographEmail);
    urlAnalyzer.analyzeURL("mіcrоsоft.com/login");
    
    bool homographFlags[5] = {false, true, true, false, false};
    string homographFlagNames[5] = {"too_many_links", "urgent_language", "suspicious_domain", "risky_attachment", "suspicious_keywords"};
    confidenceSystem.generateExplanation(homographFlags, homographFlagNames, 5);
    
    cout << "\n" << string(50, '=');
    cout << "\nSYSTEM ANALYSIS COMPLETE!\n";
    cout << string(50, '=') << endl;

    //......................................................................................................................
    cout<<endl;

    TrieNode* root=new TrieNode();
    int notFound=1;
    string text;
    string word="";
    
    string str[]={"verify","verification","verified","urgent","urgency", "password", "update","action","required","account","Limited","Offer"};
    int size=(sizeof(str)/sizeof(str[0]));
    for(int i=0;i<size;i++){
        insertWord(root,str[i]);
    }
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
        {"gift",1}, {"special",1},{"respond now",3},{"claim reward",3},
        {"response",1},  {"login",2},{"password",2},{"limited time",3},
        {"verify",2},{"attention",2},{"update",2},{"required",2},{"act now",3},
        {"final",3},{"warning",3},{"alert",2},{"confirm",2},{"security",3},
        {"secure",1},{"account",1},{"verified",1}
    };
    size=sizeof(keywords)/sizeof(keywords[0]);
    toLower(text);
    int total=TotalScore(text, keywords, size);
    UrgencyTone(total);

    struct Trie* root1=new Trie();
    notFound=1;
    word="";
    
    string riskyExt[] = {
        "exe5","msi5","bat4","cmd4","com4","scr5","dll4","ps14","vbs4","js4","jar3",
        "sh4","bin4","app5","apk5","dmg4","iso3","msu5","msp5","cab4","deb4","rpm4",
        "docm3","dotm3","xlsm3","pptm3","pptx3","docx2","xlsx2","ppt2","png1","gif1",
        "zip3","rar3","7z3","tar3","gz3","tgz3","bz23","xz3","epub1","mobi1",
        "jar3","war3","ear3","py3","rb3","php3","pl3","odt2","ott2", "jpg1","jpeg1",
        "psd2","xlsb3","odb3","js2","jsx2","ts2","tsx2","wasm4","crt2","pfx4",
        "lnk4","url2","hta4","wsf4","wsc4","hta4","txt1","rtf1","md1","log1",
        "pem2","key2","svg1","html1","htm1","xhtml1","pdf1","bmp1","tiff1","webp1",
        "mp31","wav1","flac1","aac1","ogg1","avi1","wmv1","flv1","webm1","ps1",
        "mp41","mkv1","mov1","iso3","img3","vhd4","vmdk4","apk5","aab5","xapk5",
    };
    size=(sizeof(riskyExt)/sizeof(riskyExt[0]));
    for(int i=0;i<size;i++){
        insertWords(root1,riskyExt[i]);
    }
    for(int i=0;i<text.length();i++){
        if(isalpha(text[i]) || text[i]=='.')
            word +=tolower(text[i]);
        else if(word!=""){
            if(searchWords(root1,word)==1 ||searchWords(root1,word)==2){
                cout<<"Safe file type detected: "<<word<<endl;
                notFound=0;
            }
            else if(searchWords(root1,word)==3){
                cout<<"Archive file detected: "<<word<<" . It may contain hidden files. Recommend: Scan before opening. "<<endl;
                notFound=0;
            }
            else if(searchWords(root1,word)==4){
                cout<<"High-risk script file detected: "<<word<<" . It could execute harmful code."<<endl;
                notFound=0;
            }
            else if(searchWords(root1,word)==5){
                cout<<"Critical threat! Executable file detected: "<<word<<" . Do NOT open."<<endl;
                notFound=0;
            }
            word="";
        }
    }
    if(notFound)
        cout<<"No file detected."<<endl;
    
    //............................................................................................................
    
    cout<<endl;
    
    string realDomain, testDomain;
    cout << "Enter trusted domain: ";
    cin >> realDomain;
    cout << "Enter suspicious domain or URL: ";
    cin >> testDomain;

    cout << "\n==============================\n";
    cout << "URL Heuristic Analysis\n";
    cout << "==============================\n";
    cout << analyzeURL(testDomain) << endl;

    cout << "==============================\n";
    cout << "Visual Spoof Analysis\n";
    cout << "==============================\n";
    SpoofResult spoof = analyzeSpoof(realDomain, testDomain);
    showResult(spoof, realDomain, testDomain);

    cout << "==============================\n";
    cout << "Domain Similarity Analysis\n";
    cout << "==============================\n";
    int distance = levenshteinDistance(realDomain, testDomain);
    double similarity = findSimilarity(distance, realDomain, testDomain);
    showResult(realDomain, testDomain, distance, similarity);

    cout << "\nCombined analysis complete.\n";
    return 0;
}