#include<string>
#include<cctype>
using namespace std;

struct TrieNode{
    TrieNode* child[26];
    int end;
    TrieNode(){
        for(int i=0;i<26;i++)
            child[i]=NULL;
        end=0;
    }
};
void insertWord(TrieNode* root,string word);
int searchWord(TrieNode* root,string text);
