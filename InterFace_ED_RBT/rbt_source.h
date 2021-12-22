#ifndef RBT_SOURCE_H
#define RBT_SOURCE_H

#include <QMessageBox>
#include<iostream>
#include<cstring>
#include<conio.h>
#include<Windows.h>
#include<fstream>
#include<vector>
#include<stack>
using namespace std;

struct node
{
    string word, translate;
    string color;
    node* lchild;
    node* rchild;
    node* parent;
};

class rbt_source
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

    rbt_source();
    node* Rrotate(node* temp);
    node* Lrotate(node* temp);
    node* fixRBT(node* root);
    node* buildRBT(node* root);
    node* read();
    node* search(node* root);
    void updataLack();
    void rewrite(node* root);
    void insert();
    node* rebuildRBT(node* root);
    void del();
    void changeRBT(node* root);
    void changeWord(string target, string mean);
    bool checkWord();
    node* retAT();
};

#endif // RBT_SOURCE_H
