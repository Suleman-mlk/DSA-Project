#include"SentimentAndUrgency.h"

int TotalScore(string text, WordScore keywords[], int size){
    string word="", prev="", prev2="";
    int totalScore=0;
    for(int i=0;i<text.length();i++){
        if(isalpha(text[i]))
            word+=tolower(text[i]);
        else if(word!=""){
            string one=word;
            string two=prev+" "+word;
            string three=prev2+" "+prev+" "+word;
            bool matched=false;
            for(int j=0;j<size;j++){
                if(!matched && keywords[j].word==three){ 
                    totalScore+=keywords[j].score;
                    matched=true;
                }
                else if(!matched && keywords[j].word==two){
                    totalScore+=keywords[j].score;
                    matched=true;
                }
                else if(!matched && keywords[j].word==one){
                    totalScore+=keywords[j].score;
                    matched=true;
                }
            }
            prev2=prev;
            prev=word;
            word="";
        }
    }
    return totalScore;
}
void UrgencyTone(int total){
    cout<<"Urgency: "<<total<<endl;
    if(total<=3)
        cout<<"Tone: Neutral (No emotional or urgent signs)"<<endl;
    else if(total<=6)
        cout<<"Tone: Suspicious (Mild urgency detected)"<<endl;
    else
        cout<<"Tone: Highly Urgent or Emotional (Potential phishing alert!)"<<endl;
}