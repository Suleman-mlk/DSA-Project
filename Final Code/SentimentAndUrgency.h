#include<iostream>
#include<string>
using namespace std;
struct WordScore{
    string word;
    int score;
};
void toLower(string &text);
int TotalScore(string text, WordScore keywords[], int size);
void UrgencyTone(int total);