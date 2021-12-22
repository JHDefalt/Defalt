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
	if (ifp.fail()) cout << "�ļ���ʧ��" << endl;
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
	cout << "���޸ô�,���ϱ�������Ա..." << endl;
	ofstream ofp;
	ofp.open("C:\\CurriculumDesign\\ElectronicDictionary-Trie\\Dictionary\\!lack.txt", ios::out | ios::app);
	ofp << target_word << " ��������\n";
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
	cout << "���´ʿ���...";
	string x = target_word, y = target_nature + " " + target_mean;
	root = retAT();
	target_word = x, target_translate = y;
	buildTrie(root);
	ofstream ofp;
	ofp.open(path, ios::out | ios::trunc);
	ofp.close();
	rewrite(root);
	system("cls");
	cout << "\n�������...", _getch();
}

void Trie::cut()
{
	system("cls");
	cout << "���´ʿ���...";
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
	cout << "\n�������...", _getch();
}

void Trie::changeWord(string nword, string ntranslate)
{
	system("cls");
	cout << "���´ʿ���...";
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
	cout << "\n�������...", _getch();
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
	cout << "����:" << temp->word << "\n����:\n";
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
	cout << "�鿴��Ϻ�,�����������...", _getch();
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
	if (ifp.fail()) cout << "�ļ���ʧ��" << endl;
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
		<< "|   ��Ӣ�ʵ�-Trie    |" << endl
		<< "+--------------------+" << endl
		<< "|     1.��ѯ����     |" << endl
		<< "|     2.���뵥��     |" << endl
		<< "|     3.ɾ������     |" << endl
		<< "|     4.�޸ĵ���     |" << endl
		<< "|     5.�˳��ʵ�     |" << endl
		<< "+--------------------|" << endl
		<< "��ѡ��:";
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
		case 1://��ѯ
		{
			cout << "������Ҫ��ѯ�ĵ��ʣ�";
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
				cout << "ʱ�����ģ�" << b - a << "ms" << endl, _getch();
			}
			else cout << "���뵥�ʸ�ʽ���󣨿��ܺ��пո���֣�������飩...", _getch();
			break;
		}
		case 2://����
		{
			cout << "������Ҫ���ӵĵ��ʣ�";
			cin >> t.target_word;
			if (t.checkWord())
			{
				t.path = t.pre + t.target_word[0] + ".txt";
				a = clock();
				node* dict = t.read();
				node* ret = t.search(dict);
				if (ret != NULL) cout << "�����Ѵ���" << endl, t.print(ret);
				else
				{
					cout << "������Լ����壺";
					cin >> t.target_nature >> t.target_mean;
					t.insert();
					b = clock();
				}
				cout << "ʱ�����ģ�" << b - a << "ms" << endl, _getch();
			}
			else cout << "���뵥�ʸ�ʽ���󣨿��ܺ��пո���֣�������飩...", _getch();
			break;
		}
		case 3://ɾ��
		{
			cout << "������Ҫɾ���ĵ��ʣ�";
			cin >> t.target_word;
			if (t.checkWord())
			{
				t.path = t.pre + t.target_word[0] + ".txt";
				a = clock();
				node* dict = t.read();
				node* ret = t.search(dict);
				if (ret->isWord == false || ret == NULL) cout << "�õ��ʲ�����", _getch();
				else t.cut();
				b = clock();
				cout << "ʱ�����ģ�" << b - a << "ms" << endl, _getch();
			}
			else cout << "���뵥�ʸ�ʽ���󣨿��ܺ��пո���֣�������飩...", _getch();
			break;
		}
		case 4://�޸�
		{
			int ch1, ch2;
			string change_word,change_nature,change_mean;
			cout << "������Ҫ�޸ĵĵ��ʣ�";
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
					cout << "\n1.�޸ĵ���\n2.�޸�����\n3.ȡ���޸�\n";
					cin >> ch1;
					if (ch1 == 1)
					{
						cout << "�����µ��ʣ�";
						cin >> change_word;
						t.changeWord(change_word, ans->translate);
					}
					else if (ch1 == 2)
					{
						cout << "\n1.�޸�����\n2.��������\n3.ȡ���޸�\n";
						cin >> ch2;
						if (ch2 == 1)
						{
							cout << "������Ժ����壺";
							cin >> change_nature >> change_mean;
							t.changeWord(ans->word, change_nature + " " + change_mean);
						}
						else if (ch2 == 2)
						{
							cout << "������Ժ����壺";
							cin >> change_nature >> change_mean;
							t.changeWord(ans->word, ans->translate + "@" + change_nature + " " + change_mean);
						}
					}
				}
				b = clock();
				cout << "ʱ�����ģ�" << b - a << "ms" << endl, _getch();
			}
			else
			{
				cout << "���뵥�ʸ�ʽ���󣨿��ܺ��пո���֣�������飩...", _getch();
			}
			break;
		}
		case 5://�˳�
		{
			cout << "��лʹ��...";
			return 0;
		}
		}
	}
}