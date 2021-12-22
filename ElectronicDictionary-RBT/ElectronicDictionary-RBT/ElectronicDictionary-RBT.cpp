#include<iostream>
#include<cstring>
#include<conio.h>
#include<Windows.h>
#include<fstream>
#include<vector>
#include<stack>
using namespace std;

clock_t a, b;

struct node
{
	string word, translate;
	string color;
	node* lchild;
	node* rchild;
	node* parent;
};

class RBT
{
private:
	node* root;
public:
	string pre;
	string path;
	string target_word;
	string target_translate;
	string target_nature;
	string target_mean;

	RBT();
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
	void print(node* temp);
	node* retAT();
};

RBT::RBT()
{
	pre = "C:\\CurriculumDesign\\ElectronicDictionary-RBT\\Dictionary\\";
}

node* RBT::Rrotate(node* temp)
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
node* RBT::Lrotate(node* temp)
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
node* RBT::fixRBT(node * root)
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
node* RBT::buildRBT(node* root)
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

node* RBT::read()
{
	string x = target_word, y = target_translate;
	ifstream ifp;
	vector<string> word;
	vector<string> translate;
	node* root = new node;
	root = NULL;
	ifp.open(path, ios::in);
	char ans[300];
	if (ifp.fail()) cout << "文件打开失败" << endl;
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

node* RBT::search(node* root)
{
	if (root == NULL) return NULL;
	if (root->word.compare(target_word) == 0) return root;
	else if (root->word.compare(target_word) < 0) return search(root->rchild);
	else return search(root->lchild);
}
void RBT::updataLack()
{
	cout << "暂无该词,已上报管理人员..." << endl;
	ofstream ofp;
	ofp.open("C:\\CurriculumDesign\\ElectronicDictionary-RBT\\Dictionary\\!lack.txt", ios::out | ios::app);
	ofp << target_word << " 暂无释义\n";
	ofp.close();
	_getch();
}

void RBT::rewrite(node* root)
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
void RBT::insert()
{
	system("cls");
	cout << "更新词库中...";
	string x = target_word, y = target_nature + " " + target_mean;
	root = retAT();
	target_word = x, target_translate = y;
	root = buildRBT(root);
	ofstream ofp;
	ofp.open(path, ios::out | ios::trunc);
	ofp.close();
	rewrite(root);
	system("cls");
	cout << "\n更新完毕...", _getch();
}

node* RBT::rebuildRBT(node* root)
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
void RBT::del()
{
	system("cls");
	cout << "更新词库中...";
	string x = target_word, y = target_translate;
	root = retAT();
	target_word = x, target_translate = y;
	node* newroot = rebuildRBT(root);
	ofstream ofp;
	ofp.open(path, ios::out | ios::trunc);
	ofp.close();
	rewrite(newroot);
	system("cls");
	cout << "\n更新完毕...", _getch();
}

void RBT::changeRBT(node* root)
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
void RBT::changeWord(string target, string mean)
{
	system("cls");
	cout << "更新词库中...";
	string x = target_word, y = target_translate;
	root = retAT();
	node* temp = root;
	target_word = target, target_translate = mean;
	changeRBT(temp);
	ofstream ofp;
	ofp.open(path, ios::out | ios::trunc);
	ofp.close();
	rewrite(root);
	system("cls");
	cout << "\n更新完毕...", _getch();
}

bool RBT::checkWord()
{
	for (int i = 0; i < target_word.length(); i++)
	{
		if (target_word[i] >= 65 && target_word[i] <= 90) target_word[i] -= 'a';
		if (target_word[i] < 97 || target_word[i] > 122) return false;
	}
	return true;
}
void RBT::print(node* temp)
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
	cout << "查看完毕后,按任意键返回...", _getch();
}
node* RBT::retAT()
{
	ifstream ifp;
	vector<string> word;
	vector<string> translate;
	root = new node;
	root = NULL;
	ifp.open(path, ios::in);
	char ans[300];
	if (ifp.fail()) cout << "文件打开失败" << endl;
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
	for (int i = 0; i < word.size(); i++) target_word = word[i], target_translate = translate[i], root = buildRBT(root);
	return root;
}

void menu()
{
	cout << "+--------------------+" << endl
		<< "|    中英词典-RBT    |" << endl
		<< "+--------------------+" << endl
		<< "|     1.查询单词     |" << endl
		<< "|     2.插入单词     |" << endl
		<< "|     3.删除单词     |" << endl
		<< "|     4.修改单词     |" << endl
		<< "|     5.退出词典     |" << endl
		<< "+--------------------|" << endl
		<< "请选择:";
}

int main()
{
	RBT t;
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
				cout << "时间消耗：" << b - a << "ms" << endl, _getch();
				if (ans == NULL) t.updataLack();
				else t.print(ans);
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
				node* dict = t.read();
				node* ans = t.search(dict);
				if (ans != NULL)
				{
					cout << "单词已存在，信息如下\n";
					t.print(ans);
				}
				else
				{
					cout << "输入词性和释义:";
					cin >> t.target_nature >> t.target_mean;
					t.insert();
				}
			}
			else cout << "输入单词格式有误（可能含有空格或汉字，请您检查）...", _getch();
			break;
		}
		case 3://删除
		{
			cout << "输入想要删除的单词：";
			cin >> t.target_word;
			if (t.checkWord())
			{
				t.path = t.pre + t.target_word[0] + ".txt";
				node* dict = t.read();
				node* ret = t.search(dict);
				if (ret == NULL) cout << "该单词不存在", _getch();
				else t.del();
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
				}
			}
			else cout << "输入单词格式有误（可能含有空格或汉字，请您检查）...", _getch();
			break;
		}
		case 5:
		{
			cout << "感谢使用...";
			return 0;
		}
		}
	}
}