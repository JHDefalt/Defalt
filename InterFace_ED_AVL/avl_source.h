#ifndef avl_source_H
#define avl_source_H

#include <QMessageBox>
#include<iostream>
#include<cstring>
#include<fstream>
#include<conio.h>
#include<vector>
#include<stack>
using namespace std;

struct node {
    string word;
    string translate;
    node* lchild;
    node* rchild;
};

class avl_source
{
public:
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

    avl_source();
    int depth(node* temp);
    int bf(node* temp);
    node* LL(node* temp);
    node* RR(node* temp);
    node* LR(node* temp);
    node* RL(node* temp);
    node* buildAVL(node* root);
    node* read();
    node* search(node* dict);
    void updataLack();
    void rewrite(node* root);
    void insert();
    node* maxChild(node* temp);
    node* rebuildAVL(node* root);
    void cut();
    void changeAVL(node* root);
    void changeWord(string target, string mean);
    bool checkWord();
    node* retAT();
};

#endif // avl_source_H
