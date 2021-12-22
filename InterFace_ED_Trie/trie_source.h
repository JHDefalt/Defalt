#ifndef TRIE_SOURCE_H
#define TRIE_SOURCE_H

#include<QMessageBox>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<fstream>
#include<Windows.h>
#include<vector>
using namespace std;

struct node
{
    bool isWord;
    char ch;
    string word, translate;
    node* nextCh[26];
};

class trie_source
{
private:
    node* root;
public:
    node* dict;
    node* ans;
    string pre;
    string path;
    string target_word;
    string target_translate;
    string target_nature;
    string target_mean;

    trie_source();
    node* buildTrie(node* root);
    node* read();
    node* search(node* root);
    void updataLack();
    void rewrite(node* node);
    void insert();
    void cut();
    void changeWord(string nword, string ntranslate);
    bool checkWord();
    void print(node* temp);
    node* retAT();
};

#endif // TRIE_SOURCE_H
