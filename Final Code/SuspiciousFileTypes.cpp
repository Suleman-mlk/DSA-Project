#include"SuspiciousFileTypes.h"
void insertWords(Trie* root,string word){
    Trie* curr=root;
    int digit=0;
    for(int i=0;i<word.length();i++){
        char c=tolower(word[i]);
        if( !isalpha(c) )
            continue;
        int index=c-'a';
        if(curr->child[index]==NULL)
            curr->child[index]=new Trie();
        curr=curr->child[index];
    }
    for(int i=word.length()-1;i>=0;i--){
        if( isdigit(word[i]) ){
            digit=word[i]-'0'; //
            break;
        }
    }
    curr->end=digit;
}
int searchWords(Trie* root,string text){
    Trie* curr=root;
    for(int i=0;i<text.length();i++){
        if(text[i]=='.'){
            for(int j=i+1;isalpha(text[j]) && j<text.length();j++){
            int index=text[j]-'a';
            if(curr->child[index]==NULL)
                return 0;
            curr=curr->child[index];
            }
        return curr->end;
        }
    }
    return 0;
}
