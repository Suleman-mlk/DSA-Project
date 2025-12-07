#include<string>
#include<cctype>

using namespace std;
struct Trie{
    Trie* child[26];
    int end;
    Trie(){
        for(int i=0;i<26;i++)
            child[i]=NULL;
        end=0;
    }
};
void insertWords(Trie* root,string word);
int searchWords(Trie* root,string text);