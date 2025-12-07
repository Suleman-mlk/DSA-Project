#include "Aho_Corasick.h"

void insertWord(TrieNode* root,string word){
    TrieNode* curr=root;
    for(int i=0;i<word.length();i++){
        char c=tolower(word[i]);
        if( !isalpha(c) )
            continue;
        int index=c-'a';
        if(curr->child[index]==NULL)
            curr->child[index]=new TrieNode();
        curr=curr->child[index];
    }
    curr->end=1;
}
int searchWord(TrieNode* root,string text){
    TrieNode* curr=root;
    for(int i=0;i<text.length();i++){
        char c=tolower(text[i]);
        if(!isalpha(c))
            continue;
        int index=c-'a';
        if(curr->child[index]==NULL)
            return 0;
        curr=curr->child[index];
    }
    return curr->end;
}
