#include "trie_source.h"

trie_source::trie_source()
{
    pre = "C:\\CurriculumDesign\\ElectronicDictionary-Trie\\Dictionary\\";
}

node* trie_source::buildTrie(node* root)
{
    node* temp = root;
    for (char ch : target_word)
    {
        ch -= 'a';
        if (temp->nextCh[ch] == NULL)
        {
            node* newCh = new node;
            newCh->isWord = false;
            memset(newCh->nextCh, NULL, sizeof(newCh->nextCh));
            temp->nextCh[ch] = newCh;
        }
        temp = temp->nextCh[ch];
    }
    temp->isWord = true;
    temp->word = target_word;
    temp->translate = target_translate;
    return temp;
}
node* trie_source::read()
{
    ifstream ifp;
    vector<string> word;
    vector<string> translate;
    node* root = new node;
    memset(root->nextCh, NULL, sizeof(root->nextCh));
    string x = target_word, y = target_translate;
    ifp.open(path, ios::in);
    char ans[300];
    while (ifp.getline(ans, 300))
    {
        string ret(ans);
        if (ret != "")
        {
            int idx = ret.find(" ", 0);
            word.push_back(ret.substr(0, idx));
            translate.push_back(ret.substr(idx + 1, ret.length() - idx - 1));
        }
    }
    ifp.close();
    if (target_word.length() == 1)
    {
        target_word = word[0], target_translate = translate[0];
        buildTrie(root);
    }
    else
    {
        int l = 0;
        int r = word.size() - 1;
        while (l < r)
        {
            int mid = (l + r) >> 1;
            if (word[mid][1] >= target_word[1]) r = mid;
            else l = mid + 1;
        }
        int left = l;
        l = 0;
        r = word.size() - 1;
        while (l < r)
        {
            int mid = (l + r + 1) >> 1;
            if (word[mid][1] <= target_word[1]) l = mid;
            else r = mid - 1;
        }
        int right = r;
        if (target_word.length() >= 3)
        {
            int l = left;
            int r = right;
            while (l < r)
            {
                int mid = (l + r) >> 1;
                if (word[mid][2] >= target_word[2]) r = mid;
                else l = mid + 1;
            }
            int binLeft = l;
            l = left;
            r = right;
            while (l < r)
            {
                int mid = (l + r + 1) >> 1;
                if (word[mid][2] <= target_word[2]) l = mid;
                else r = mid - 1;
            }
            int binRight = r;
            if (binRight - binLeft == 1)
            {
                target_word = word[binRight], target_translate = translate[binRight];
                buildTrie(root);
            }
            else
            {
                for (int i = binLeft; i <= binRight; i++) target_word = word[i], target_translate = translate[i], buildTrie(root);
            }
        }
        else
        {
            for (int i = left; i <= right; i++) target_word = word[i], target_translate = translate[i], buildTrie(root);
        }
    }
    target_word = x, target_translate = y;
    return root;
}

node* trie_source::search(node* root)
{
    for (char ch : target_word)
    {
        ch -= 'a';
        root = root->nextCh[ch];
        if (root == NULL) return NULL;
    }
    return root;
}
void trie_source::updataLack()
{
    ofstream ofp;
    ofp.open("C:\\CurriculumDesign\\ElectronicDictionary-Trie\\Dictionary\\!lack.txt", ios::out | ios::app);
    ofp << target_word << " ÔÝÎÞÊÍÒå\n";
    ofp.close();
}

void trie_source::rewrite(node* node)
{
    if (node != NULL)
    {
        if (node->isWord == true)
        {
            ofstream ofp;
            ofp.open(path, ios::out | ios::app);
            string translate = node->translate + "\n";
            ofp << node->word << " " << translate;
        }
        for (auto ne : node->nextCh)
        {
            rewrite(ne);
        }
    }
}
void trie_source::insert()
{
    string x = target_word, y = target_nature + " " + target_mean;
    root = retAT();
    target_word = x, target_translate = y;
    buildTrie(root);
    ofstream ofp;
    ofp.open(path, ios::out | ios::trunc);
    ofp.close();
    rewrite(root);
}

void trie_source::cut()
{
    string x = target_word, y = target_translate;
    root = retAT();
    target_word = x, target_translate = y;
    node* temp = root;
    for (char ch : target_word)
    {
        ch -= 'a';
        temp = temp->nextCh[ch];
    }
    temp->isWord = false;
    temp->word = temp->translate = "";
    ofstream ofp;
    ofp.open(path, ios::out | ios::trunc);
    ofp.close();
    rewrite(root);
}

void trie_source::changeWord(string nword, string ntranslate)
{
    string x = target_word, y = target_translate;
    root = retAT();
    target_word = x, target_translate = y;
    node* temp = root;
    for (char ch : target_word)
    {
        ch -= 'a';
        temp = temp->nextCh[ch];
    }
    temp->word = nword;
    temp->translate = ntranslate;
    ofstream ofp;
    ofp.open(path, ios::out | ios::trunc);
    ofp.close();
    rewrite(root);
}

bool trie_source::checkWord()
{
    for (int i = 0; i < target_word.length(); i++)
    {
        if (target_word[i] >= 65 && target_word[i] <= 90) target_word[i] -= 'a';
        if (target_word[i] < 97 || target_word[i] > 122) return false;
    }
    return true;
}

node* trie_source::retAT()
{
    ifstream ifp;
    vector<string> word;
    vector<string> translate;
    root = new node;
    memset(root->nextCh, NULL, sizeof(root->nextCh));
    ifp.open(path, ios::in);
    char ans[300];
    while (ifp.getline(ans, 300)) {
        string ret(ans);
        if (ret != "")
        {
            int idx = ret.find(" ", 0);
            word.push_back(ret.substr(0, idx));
            translate.push_back(ret.substr(idx + 1, ret.length() - idx - 1));
        }
    }
    ifp.close();
    for (int i = 0; i < word.size(); i++) target_word = word[i], target_translate = translate[i], buildTrie(root);
    return root;
}
