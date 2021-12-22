#include<iostream>
#include<cstring>
#include<fstream>
#include<conio.h>
#include<vector>
#include<stack>
using namespace std;

clock_t a, b;

struct node {
	string word;
	string translate;
	node* lchild;
	node* rchild;
};

class AVLT
{
private:
	node* root;
public:
	AVLT();
	string pre;
	string path;
	string target_word;
	string target_translate;
	string target_nature;
	string target_mean;

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
	void print(node* temp);
	node* retAT();
};
AVLT::AVLT()
{
	pre = "C:\\CurriculumDesign\\ElectronicDictionary-AVL\\Dictionary\\";
}

int AVLT::depth(node* temp) {
	if (temp == NULL) return 0;
	return 1 + max(depth(temp->lchild), depth(temp->rchild));
}
int AVLT::bf(node* temp) {
	return depth(temp->lchild) - depth(temp->rchild);
}
node* AVLT::LL(node* temp) {
	node* s = temp->lchild;
	temp->lchild = s->rchild;
	s->rchild = temp;
	return s;
}
node* AVLT::RR(node* temp) {
	node* s = temp->rchild;
	temp->rchild = s->lchild;
	s->lchild = temp;
	return s;
}
node* AVLT::LR(node* temp) {
	temp->lchild = RR(temp->lchild);
	return LL(temp);
}
node* AVLT::RL(node* temp) {
	temp->rchild = LL(temp->rchild);
	return RR(temp);
}
node* AVLT::buildAVL(node* root) {
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

node* AVLT::read()
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

node* AVLT::search(node* dict) {
	if (dict == NULL) return NULL;
	if (dict->word.compare(target_word) == 0) return dict;
	else
	{
		if (dict->word.compare(target_word) < 0) return search(dict->rchild);
		else return search(dict->lchild);
	}
}
void AVLT::updataLack()
{
	cout << "暂无该词,已上报管理人员..." << endl;
	ofstream ofp;
	ofp.open("C:\\CurriculumDesign\\ElectronicDictionary-AVL\\Dictionary\\!lack.txt", ios::out | ios::app);
	ofp << target_word << " 暂无释义\n";
	ofp.close();
	_getch();
}

void AVLT::rewrite(node* root)
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
void AVLT::insert()
{
	system("cls");
	cout << "更新词库中...";
	string x = target_word, y = target_nature, z = target_mean;
	root = retAT();
	target_word = x, target_translate = y + z;
	root = buildAVL(root);
	ofstream ofp;
	ofp.open(path, ios::out | ios::trunc);
	ofp.close();
	rewrite(root);
	system("cls");
	cout << "\n更新完毕...", _getch();
}

node* AVLT::maxChild(node* temp)
{
	if (temp->rchild == NULL) return temp;
	return maxChild(temp->rchild);
}
node* AVLT::rebuildAVL(node* root)
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
void AVLT::cut()
{
	system("cls");
	cout << "更新词库中...";
	string x = target_word, y = target_translate;
	root = retAT();
	target_word = x, target_translate = y;
	root = rebuildAVL(root);
	ofstream ofp;
	ofp.open(path, ios::out | ios::trunc);
	ofp.close();
	rewrite(root);
	system("cls");
	cout << "\n更新完毕...", _getch();
}

void AVLT::changeAVL(node* root)
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
void AVLT::changeWord(string target, string mean)
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

bool AVLT::checkWord()
{
	for (int i = 0; i < target_word.length(); i++)
	{
		if (target_word[i] >= 65 && target_word[i] <= 90) target_word[i] -= 'a';
		if (target_word[i] < 97 || target_word[i] > 122) return false;
	}
	return true;
}

void AVLT::print(node* temp)
{
	cout << "单词:" << temp->word << "\n释义:\n";
	string nows = temp->translate;
	int pos = 0;
	int start = 0;
	while (pos != nows.npos) {
		pos = nows.find('@', start);
		string sub = nows.substr(start, pos);
		cout << sub << endl;
		if (pos != nows.npos) start = pos + 1, nows = nows.substr(start, nows.length() - pos - 1);
		start = 0;
	}
	cout << "查看完毕后, 按任意键返回...", _getch();
}

node* AVLT::retAT()
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

void menu()
{
	cout << "+--------------------+" << endl
		<< "|    中英词典-AVL    |" << endl
		<< "+--------------------+" << endl
		<< "|     1.查询单词     |" << endl
		<< "|     2.插入单词     |" << endl
		<< "|     3.删除单词     |" << endl
		<< "|     4.修改单词     |" << endl
		<< "|     5.退出词典     |" << endl
		<< "+--------------------|" << endl
		<< "请选择:";
}

int main() {
	AVLT t;
	int choice;
	while (1)
	{
		system("cls");
		menu();
		cin >> choice;
		switch (choice)
		{
		case 1://查询
		{
			cout << "输入想要查询的单词：";
			cin >> t.target_word;
			if (t.checkWord())
			{
				t.path = t.pre + t.target_word[0] + ".txt";
				a = clock();
				node* dict = t.read();
				node* ans = t.search(dict);
				b = clock();
				if (ans == NULL) t.updataLack();
				else t.print(ans);
				cout << "时间消耗：" << b - a << "ms" << endl,_getch();
			}
			else cout << "输入单词格式有误（可能含有空格或汉字，请您检查）...", _getch();
			break;
		}
		case 2://增加
		{
			cout << "输入想要增加的单词：";
			cin >> t.target_word;
			if (t.checkWord())
			{
				t.path = t.pre + t.target_word[0] + ".txt";
				a = clock();
				node* dict = t.read();
				node* ans = t.search(dict);
				if (ans != NULL)
				{
					cout << "单词存在" << endl;
					t.print(ans);
				}
				else
				{
					cout << "输入词性和释义:";
					cin >> t.target_nature >> t.target_mean;
					t.insert();
				}
				b = clock();
				cout << "时间消耗：" << b - a << "ms" << endl, _getch();
			}
			else cout << "输入单词格式有误（可能含有空格或汉字，请您检查）...", _getch();
			break;
		}
		case 3://删除
		{
			cout << "输入想要删除的单词：";
			cin >> t.target_word;
			a = clock();
			if (t.checkWord())
			{
				t.path = t.pre + t.target_word[0] + ".txt";
				node* dict = t.read();
				node* ret = t.search(dict);
				if (ret == NULL) cout << "该单词不存在", _getch();
				else t.cut();
				b = clock();
				cout << "时间消耗：" << b - a << "ms" << endl, _getch();
			}
			else cout << "输入单词格式有误（可能含有空格或汉字，请您检查）...", _getch();
			break;
		}
		case 4://修改
		{
			int ch1, ch2;
			string change_word, change_nature, change_mean;
			cout << "输入想要修改的单词：";
			cin >> t.target_word;
			a = clock();
			if (t.checkWord())
			{
				t.path = t.pre + t.target_word[0] + ".txt";
				node* dict = t.read();
				node* ans = t.search(dict);
				if (ans == NULL) t.updataLack();
				else
				{
					cout << "\n1.修改单词\n2.修改释义\n3.取消修改\n";
					cin >> ch1;
					if (ch1 == 1)
					{
						cout << "输入新单词：";
						cin >> change_word;
						t.changeWord(change_word, ans->translate);
					}
					else if (ch1 == 2)
					{
						cout << "\n1.修改释义\n2.增加释义\n3.取消修改\n";
						cin >> ch2;
						if (ch2 == 1)
						{
							cout << "输入词性和释义：";
							cin >> change_nature >> change_mean;
							t.changeWord(ans->word, change_nature + " " + change_mean);
						}
						else if (ch2 == 2)
						{
							cout << "输入词性和释义：";
							cin >> change_nature >> change_mean;
							t.changeWord(ans->word, ans->translate + "@" + change_nature + " " + change_mean);
						}
					}
					cout << "修改成功，按任意键返回..." << endl, _getch();
				}
				b = clock();
				cout << "时间消耗：" << b - a << "ms" << endl, _getch();
			}
			else cout << "输入单词格式有误（可能含有空格或汉字，请您检查）...", _getch();
			break;
		}
		case 5:
			cout << "感谢使用...";
			return 0;
		}
	}
}