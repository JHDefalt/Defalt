#include "rbt_source.h"

rbt_source::rbt_source()
{
    pre = "C:\\CurriculumDesign\\ElectronicDictionary-RBT\\Dictionary\\";
}

node* rbt_source::Rrotate(node* temp)
{
    node* tparent = temp->parent;
    if (tparent->parent != NULL) tparent->parent->lchild = temp;
    temp->parent = tparent->parent;
    tparent->lchild = temp->rchild;
    temp->rchild = tparent;
    tparent->parent = temp;
    tparent->color = "red";
    temp->color = "black";
    return temp->lchild;
}
node* rbt_source::Lrotate(node* temp)
{
    node* tparent = temp->parent;
    if (tparent->parent != NULL) tparent->parent->rchild = temp;
    temp->parent = tparent->parent;
    tparent->rchild = temp->lchild;
    temp->lchild = tparent;
    tparent->parent = temp;
    tparent->color = "red";
    temp->color = "black";
    return temp->rchild;
}
node* rbt_source::fixRBT(node * root)
{
    node* uncle = NULL;
    node* parent = NULL;
    node* grandparent = NULL;
    if (root->parent != NULL)
    {
        parent = root->parent;
        if (parent->parent != NULL)
        {
            grandparent = parent->parent;
            if (parent == grandparent->lchild) if (grandparent->rchild != NULL) uncle = grandparent->rchild;
            if (parent == grandparent->rchild) if (grandparent->lchild != NULL) uncle = grandparent->lchild;

            if (parent->color == "red" && parent == grandparent->lchild)
            {
                if (uncle == NULL)
                {
                    parent = Rrotate(parent);
                }
                else
                {
                    if (uncle->color == "red") parent->color = uncle->color = "black";
                }
            }
            else if (parent->color == "red" && parent == grandparent->rchild)
            {
                if (uncle == NULL)
                {
                    parent = Lrotate(parent);
                }
                else
                {
                    if (uncle->color == "red") parent->color = uncle->color = "black";
                }
            }
        }
        else
        {
            root->color = "black";
            return root;
        }
    }
    return root;
}
node* rbt_source::buildRBT(node* root)
{
    int flag = 0;
    node* find = root;
    node* pre = NULL;
    node* temp = new node;
    temp->word = target_word;
    temp->translate = target_translate;
    temp->color = "red";
    temp->parent = temp->lchild = temp->rchild = NULL;
    if (find == NULL)
    {
        root = temp;
    }
    while (find != NULL)
    {
        if (find->word.compare(target_word) > 0)
        {
            flag = -1;
            pre = find;
            find = find->lchild;
        }
        else
        {
            flag = 1;
            pre = find;
            find = find->rchild;
        }
    }
    temp->parent = pre;
    if (flag == -1)
    {
        pre->lchild = temp;
    }
    else if (flag == 1)
    {
        pre->rchild = temp;
    }
    //temp->lchild->color = temp->rchild->color = "black";
    temp = fixRBT(temp);
    return root;
}

node* rbt_source::read()
{
    string x = target_word, y = target_translate;
    ifstream ifp;
    vector<string> word;
    vector<string> translate;
    node* root = new node;
    root = NULL;
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
        node* temp = new node;
        temp->word = word[0];
        temp->translate = translate[0];
        temp->lchild = temp->rchild = NULL;
        return temp;
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
                node* temp = new node;
                temp->word = word[binRight];
                temp->translate = translate[binRight];
                temp->lchild = temp->rchild = NULL;
                return temp;
            }
            else
            {
                for (int i = binLeft; i <= binRight; i++) target_word = word[i], target_translate = translate[i], root = buildRBT(root);
            }
        }
        else
        {
            for (int i = left; i <= right; i++) target_word = word[i], target_translate = translate[i], root = buildRBT(root);
        }
    }
    target_word = x, target_translate = y;
    return root;
}

node* rbt_source::search(node* root)
{
    if (root == NULL) return NULL;
    if (root->word.compare(target_word) == 0) return root;
    else if (root->word.compare(target_word) < 0) return search(root->rchild);
    else return search(root->lchild);
}
void rbt_source::updataLack()
{
    ofstream ofp;
    ofp.open("C:\\CurriculumDesign\\ElectronicDictionary-RBT\\Dictionary\\!lack.txt", ios::out | ios::app);
    ofp << target_word << " 暂无释义\n";
    ofp.close();
}

void rbt_source::rewrite(node* root)
{
    stack<node*> s;
    ofstream ofp;
    ofp.open(path, ios::out | ios::app);

    while (root || !s.empty())
    {
        while (root != NULL)
        {
            s.push(root);
            root = root->lchild;
        }
        if (!s.empty())
        {
            root = s.top(), s.pop();
            ofp << root->word << " " << root->translate + "\n";
            root = root->rchild;
        }
    }
    ofp.close();
}
void rbt_source::insert()
{
    string x = target_word, y = target_nature + " " + target_mean;
    root = retAT();
    target_word = x, target_translate = y;
    root = buildRBT(root);
    ofstream ofp;
    ofp.open(path, ios::out | ios::trunc);
    ofp.close();
    rewrite(root);
}

node* rbt_source::rebuildRBT(node* root)
{
    string x = target_word, y = target_translate;
    stack<node*> s;
    node* newroot = new node;
    newroot = NULL;
    while (root || !s.empty())
    {
        while (root)
        {
            s.push(root);
            root = root->lchild;
        }
        if (!s.empty())
        {
            root = s.top(), s.pop();
            if (root->word.compare(target_word) > 0 || root->word.compare(target_word) < 0) target_word = root->word, target_translate = root->translate, newroot = buildRBT(newroot);
            target_word = x, target_translate = y;
            root = root->rchild;
        }
    }
    return newroot;
}
void rbt_source::del()
{
    string x = target_word, y = target_translate;
    root = retAT();
    target_word = x, target_translate = y;
    node* newroot = rebuildRBT(root);
    ofstream ofp;
    ofp.open(path, ios::out | ios::trunc);
    ofp.close();
    rewrite(newroot);
}

void rbt_source::changeRBT(node* root)
{
    stack<node*> s;
    while (root || !s.empty())
    {
        while (root)
        {
            s.push(root);
            root = root->lchild;
        }
        if (!s.empty())
        {
            root = s.top(), s.pop();
            if (root->word.compare(target_word) == 0) root->word = target_word, root->translate = target_translate;
            root = root->rchild;
        }
    }
}
void rbt_source::changeWord(string target, string mean)
{
    string x = target_word, y = target_translate;
    root = retAT();
    node* temp = root;
    target_word = target, target_translate = mean;
    changeRBT(temp);
    ofstream ofp;
    ofp.open(path, ios::out | ios::trunc);
    ofp.close();
    rewrite(root);
}

bool rbt_source::checkWord()
{
    int length = target_word.length();
    for (int i = 0; i < length; i++)
    {
        if (target_word[i] >= 65 && target_word[i] <= 90) target_word[i] -= 'a';
        if (target_word[i] < 97 || target_word[i] > 122) return false;
    }
    return true;
}
node* rbt_source::retAT()
{
    ifstream ifp;
    vector<string> word;
    vector<string> translate;
    root = new node;
    root = NULL;
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
    int length = word.size();
    for (int i = 0; i < length; i++) target_word = word[i], target_translate = translate[i], root = buildRBT(root);
    return root;
}
