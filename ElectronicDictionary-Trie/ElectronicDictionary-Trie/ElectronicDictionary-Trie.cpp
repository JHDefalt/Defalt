#include<iostream>
#include<cstring>
#include<algorithm>
#include<fstream>
#include<Windows.h>
#include<conio.h>
#include<vector>
using namespace std;

clock_t a, b;

struct node
{
	bool isWord;
	string word, translate;
	node* nextCh[26];
};

class Trie
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

	Trie();
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

Trie::Trie()
{
	pre = "C:\\CurriculumDesign\\ElectronicDictionary-Trie\\Dictionary\\";
}

node* Trie::buildTrie(node* root)
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
node* Trie::read()
{
	ifstream ifp;
	vector<string> word;
	vector<string> translate;
	node* root = new node;
	memset(root->nextCh, NULL, sizeof(root->nextCh));
	string x = target_word, y = target_translate;
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

node* Trie::search(node* root)
{
	for (char ch : target_word)
	{
		ch -= 'a';
		root = root->nextCh[ch];
		if (root == NULL) return NULL;
	}
	return root;
}
void Trie::updataLack()
{
	cout << "暂无该词,已上报管理人员..." << endl;
	ofstream ofp;
	ofp.open("C:\\CurriculumDesign\\ElectronicDictionary-Trie\\Dictionary\\!lack.txt", ios::out | ios::app);
	ofp << target_word << " 暂无释义\n";
	ofp.close();
	_getch();
}

void Trie::rewrite(node* node)
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
void Trie::insert()
{
	system("cls");
	cout << "更新词库中...";
	string x = target_word, y = target_nature + " " + target_mean;
	root = retAT();
	target_word = x, target_translate = y;
	buildTrie(root);
	ofstream ofp;
	ofp.open(path, ios::out | ios::trunc);
	ofp.close();
	rewrite(root);
	system("cls");
	cout << "\n更新完毕...", _getch();
}

void Trie::cut()
{
	system("cls");
	cout << "更新词库中...";
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

	system("cls");
	cout << "\n更新完毕...", _getch();
}

void Trie::changeWord(string nword, string ntranslate)
{
	system("cls");
	cout << "更新词库中...";
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
	system("cls");
	cout << "\n更新完毕...", _getch();
}

bool Trie::checkWord()
{
	for (int i = 0; i < target_word.length(); i++)
	{
		if (target_word[i] >= 65 && target_word[i] <= 90) target_word[i] -= 'a';
		if (target_word[i] < 97 || target_word[i] > 122) return false;
	}
	return true;
}

void Trie::print(node* temp)
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

node* Trie::retAT()
{
	ifstream ifp;
	vector<string> word;
	vector<string> translate;
	root = new node;
	memset(root->nextCh, NULL, sizeof(root->nextCh));
	ifp.open(path, ios::in);
	char ans[300];
	if (ifp.fail()) cout << "文件打开失败" << endl;
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

void menu()
{
	cout << "+--------------------+" << endl
		<< "|   中英词典-Trie    |" << endl
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
	Trie t;
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
				node* ret = t.search(dict);
				b = clock();
				if (ret == NULL || ret->isWord == false) t.updataLack();
				else t.print(ret);
				cout << "时间消耗：" << b - a << "ms" << endl, _getch();
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
				node* ret = t.search(dict);
				if (ret != NULL) cout << "单词已存在" << endl, t.print(ret);
				else
				{
					cout << "输入词性及释义：";
					cin >> t.target_nature >> t.target_mean;
					t.insert();
					b = clock();
				}
				cout << "时间消耗：" << b - a << "ms" << endl, _getch();
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
				a = clock();
				node* dict = t.read();
				node* ret = t.search(dict);
				if (ret->isWord == false || ret == NULL) cout << "该单词不存在", _getch();
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
			string change_word,change_nature,change_mean;
			cout << "输入想要修改的单词：";
			cin >> t.target_word;
			if (t.checkWord())
			{
				t.path = t.pre + t.target_word[0] + ".txt";
				a = clock();
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
				b = clock();
				cout << "时间消耗：" << b - a << "ms" << endl, _getch();
			}
			else
			{
				cout << "输入单词格式有误（可能含有空格或汉字，请您检查）...", _getch();
			}
			break;
		}
		case 5://退出
		{
			cout << "感谢使用...";
			return 0;
		}
		}
	}
}