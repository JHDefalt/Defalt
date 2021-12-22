#include "avl_source.h"

avl_source::avl_source()
{
    pre = "Dictionary\\";
}

int avl_source::depth(node* temp) {
    if (temp == NULL) return 0;
    return 1 + max(depth(temp->lchild), depth(temp->rchild));
}
int avl_source::bf(node* temp) {
    return depth(temp->lchild) - depth(temp->rchild);
}
node* avl_source::LL(node* temp) {
    node* s = temp->lchild;
    temp->lchild = s->rchild;
    s->rchild = temp;
    return s;
}
node* avl_source::RR(node* temp) {
    node* s = temp->rchild;
    temp->rchild = s->lchild;
    s->lchild = temp;
    return s;
}
node* avl_source::LR(node* temp) {
    temp->lchild = RR(temp->lchild);
    return LL(temp);
}
node* avl_source::RL(node* temp) {
    temp->rchild = LL(temp->rchild);
    return RR(temp);
}
node* avl_source::buildAVL(node* root) {
    if (root == NULL) {
        node* pnew = new node;
        pnew->word = target_word;
        pnew->translate = target_translate;
        pnew->lchild = pnew->rchild = NULL;
        root = pnew;
        return pnew;
    }
    else if (root->word.compare(target_word) > 0) root->lchild = buildAVL(root->lchild);
    else root->rchild = buildAVL(root->rchild);
    if (bf(root) > 1) {
        if (bf(root->lchild) < 0) return LR(root);
        else return LL(root);
    }
    else if (bf(root) < -1) {
        if (bf(root->rchild) > 0) return RL(root);
        else return RR(root);
    }
    return root;
}

node* avl_source::read()
{
    ifstream ifp;
    vector<string> word;
    vector<string> translate;
    string x = target_word;
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
        target_word = x;
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
            if ((binRight - binLeft) == 1)
            {
                node* temp = new node;
                temp->word = word[binRight];
                temp->translate = translate[binRight];
                temp->lchild = temp->rchild = NULL;
                return temp;
            }
            else
            {
                for (int i = binLeft; i <= binRight; i++) target_word = word[i], target_translate = translate[i], root = buildAVL(root);
            }
        }
        else
        {
            for (int i = left; i <= right; i++) target_word = word[i], target_translate = translate[i], root = buildAVL(root);
        }
    }
    target_word = x;
    return root;
}

node* avl_source::search(node* dict) {
    if (dict == NULL) return NULL;
    if (dict->word.compare(target_word) == 0) return dict;
    else
    {
        if (dict->word.compare(target_word) < 0) return search(dict->rchild);
        else return search(dict->lchild);
    }
}
void avl_source::updataLack()
{
    ofstream ofp;
    ofp.open("C:\\CurriculumDesign\\ElectronicDictionary-AVL\\Dictionary\\!lack.txt", ios::out | ios::app);
    ofp << target_word << " 暂无释义\n";
    ofp.close();
}

void avl_source::rewrite(node* root)
{
    stack<node*> s;
    ofstream ofp;
    ofp.open(path, ios::out | ios::app);

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
            ofp << root->word << " " << root->translate + "\n";
            root = root->rchild;
        }
    }
    ofp.close();
}
void avl_source::insert()
{
    string x = target_word, y = target_nature, z = target_mean;
    root = retAT();
    target_word = x, target_translate = y + z;
    root = buildAVL(root);
    ofstream ofp;
    ofp.open(path, ios::out | ios::trunc);
    ofp.close();
    rewrite(root);
}

node* avl_source::maxChild(node* temp)
{
    if (temp->rchild == NULL) return temp;
    return maxChild(temp->rchild);
}
node* avl_source::rebuildAVL(node* root)
{
    if (root == NULL) return root;
    if (target_word.compare(root->word) < 0) root->lchild = rebuildAVL(root->lchild);
    else if (target_word.compare(root->word) > 0) root->rchild = rebuildAVL(root->rchild);
    else
    {
        if (root->rchild == NULL)
        {
            node* temp = root->lchild;
            delete root;
            return temp;
        }
        else if (root->lchild == NULL)
        {
            node* temp = root->rchild;
            delete root;
            return temp;
        }
        node* max = maxChild(root);
        root->word = max->word;
        root->translate = max->translate;
        target_word = max->word;
        root->rchild = rebuildAVL(max);
    }
    return root;
}
void avl_source::cut()
{
    string x = target_word, y = target_translate;
    root = retAT();
    target_word = x, target_translate = y;
    root = rebuildAVL(root);
    ofstream ofp;
    ofp.open(path, ios::out | ios::trunc);
    ofp.close();
    rewrite(root);
}

void avl_source::changeAVL(node* root)
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
void avl_source::changeWord(string target, string mean)
{
    root = retAT();
    target_word = target, target_translate = mean;
    node* temp = root;
    changeAVL(temp);
    ofstream ofp;
    ofp.open(path, ios::out | ios::trunc);
    ofp.close();
    rewrite(root);
}

bool avl_source::checkWord()
{
    for (int i = 0; i < target_word.length(); i++)
    {
        if (target_word[i] >= 65 && target_word[i] <= 90) target_word[i] -= 'a';
        if (target_word[i] < 97 || target_word[i] > 122) return false;
    }
    return true;
}

node* avl_source::retAT()
{
    ifstream ifp;
    vector<string> word;
    vector<string> translate;
    root = new node;
    root = NULL;
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
    int length = word.size();
    for (int i = 0; i < length; i++) target_word = word[i], target_translate = translate[i], root = buildAVL(root);
    return root;
}
