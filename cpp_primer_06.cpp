#include<iostream>
#include<string>
#include<initializer_list>
#include<vector>
using namespace std;

//6.3
int fact(int val)
{
	int ret = 1;
	while (val > 1)
	{
		ret *= val--;
	}
	return ret;
}

//6.4
int userFact()
{
	int n;
	cin >> n;
	return fact(n);
}

int main048()
{
	cout << userFact() << endl;
	return 0;
}

//6.7
size_t count_calls()
{
	static size_t ctr = 0;
	return ctr++;
}

int main049()
{
	for (size_t i = 0; i < 20; i++)
		cout << count_calls() << endl;
	return 0;
}

//6.10
void my_swap(int& a, int& b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

int main050()
{
	int a, b;
	cin >> a >> b;
	cout << a << ' ' << b << endl;
	my_swap(a, b);
	cout << a << ' ' << b << endl;
	return 0;
}

//6.15,查找字符出现次数，并返回第一次出现的位置
string::size_type find_char(const string& s, char c, string::size_type& occurs)
{
	auto ret = s.size();
	occurs = 0;
	for (decltype(ret) i = 0; i < s.size(); ++i)
	{
		if (s[i] == c)
		{
			if (ret == s.size())
			{
				ret = i;
			}
			++occurs;
		}
	}
	return ret;
}

int main051()
{
	string s1 = "becabcaaacdefgghkj";
	char c1 = 'a';
	string::size_type ctr;
	auto index = find_char(s1, c1, ctr);
	cout << index << ' ' << ctr << endl;
	return 0;
}

//6.17
bool isUpper(const string& s)
{
	for (auto c : s)
		if (isupper(c))
			return true;
	return false;
}

void changeToLower(string& s)
{
	for (auto& c : s)
		c = tolower(c);
}

int main052()
{
	string s1 = "asjgddAHDashdakjjh";
	cout << isUpper(s1) << endl;
	changeToLower(s1);
	cout << s1 << endl;
	return 0;
}

//6.25
int main053(int argc, char** argv)
{
	string str;
	for (int i = 0; i != argc; ++i)
	{
		str += argv[i];
	}
	cout << str << endl;
	return 0;
}

//6.27
int calSum(initializer_list<int> l1)
{
	int sum = 0;
	for (auto c : l1)
		sum += c;
	return sum;
}

int main054()
{
	cout << calSum({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }) << endl;
	return 0;
}

//6.36
string(&func01(string(&s)[10]))[10];

//6.37
typedef string s2[10];
s2& func02();

using s3 = string[10];
s3& fun03();

auto fun04()->string(&) [10];

string s4[10];
decltype(s4) &func05();


//6.42
string make_plural(size_t ctr, const string& word, const string& ending="s")
{
	return ctr > 1 ? word + ending : word;
}
int main055()
{
	size_t ctr = 2;
	cout << make_plural(ctr,"word") << endl;
	return 0;
}

//6.44
inline bool isShorter(const string& s1, const string& s2)
{
	return s1.size() < s2.size();
}

string(&func03(string(&s1)[10]))[10];
int(*func04())();

//6.54
int func05(int a, int b)
{
	return a + b;
}

int func06(int a, int b)
{
	return a - b;
}

int func07(int a, int b)
{
	return a * b;
}

int func08(int a, int b)
{
	return a / b;
}
int main056()
{
	vector<int(*) (int, int)>v1 = {func05,func06,func07,func08};
	int a = 10, b = 5;
	for (auto c : v1)
	{
		cout << c(a, b) << endl;
	}
	return 0;
}
