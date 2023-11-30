#include<iostream>
#include<vector>
#include<list>
#include<algorithm>
#include<numeric>
#include<functional>
#include<iterator>
#include<fstream>
#include<sstream>
using namespace std;
using namespace std::placeholders;

//10.1
int main090()
{
	int val;
	vector<int> v1;
	while (cin >> val)
	{
		v1.push_back(val);
	}
	int val2 = 3;
	cout << count(v1.begin(), v1.end(), val2) << endl;
	return 0;
}

//10.2
int main091()
{
	list<string> l1;
	string s1;
	while (cin >> s1)
	{
		l1.push_back(s1);
	}
	cout << count(l1.begin(), l1.end(), "abcde") << endl;
	return 0;
}


//10.3
int main092()
{
	vector<int> v1{ 1,2,3,4,5,6,7,8,9,10 };
	int sum = accumulate(v1.begin(), v1.end(), 100);//最后一个参数决定了返回值类型和和初值
	//并且第三个运算符类型必须重载了+法运算符
	cout << sum << endl;
	return 0;
}

//10.6
int main093()
{
	vector<int> v1;
	fill_n(back_inserter(v1), 10, 0);

	for (auto it = v1.cbegin(); it != v1.cend(); it++)
	{
		cout << *it << endl;
	}
	return 0;
}

//10.9
void elimDumps(vector<string>& v1)
{
	sort(v1.begin(), v1.end());
	for (auto it = v1.cbegin(); it != v1.cend(); it++)
	{
		cout << *it << endl;
	}
	auto end_unique = unique(v1.begin(), v1.end());
	for (auto it = v1.cbegin(); it != v1.cend(); it++)
	{
		cout << *it << endl;
	}
	v1.erase(end_unique, v1.cend());
	for (auto it = v1.cbegin(); it != v1.cend(); it++)
	{
		cout << *it << endl;
	}

}

bool isShorter(const string& s1, const string& s2)
{
	return s1.size() < s2.size();
}

int main094()
{
	vector<string>v1 = { "fox", "jumps", "over", "quick", "red", "slow", "turtle", "red", "over" };
	elimDumps(v1);
	sort(v1.begin(), v1.end(), isShorter);
	for (auto it = v1.cbegin(); it != v1.cend(); it++)
	{
		cout << *it << endl;
	}
	stable_sort(v1.begin(), v1.end(), isShorter);
	for (auto it = v1.cbegin(); it != v1.cend(); it++)
	{
		cout << *it << endl;
	}
	return 0;
}

//10.13
bool moreFive(const string& s)
{
	return s.size() < 5;
}


int main095()
{
	vector<string> v1 = { "dasdasdas", " " ,"akshdkashdkj","a","askhdkas","sad","asjkdjash","iuqweuqwhh" };
	auto a = partition(v1.begin(), v1.end(), moreFive);
	for (auto it = a; it != v1.cend(); it++)
	{
		cout << *it << endl;
	}
	return 0;
}

//10.14
int main096()
{
	auto f = [](const int a, const int b) {return a + b; };
	cout << f(3, 4) << endl;
	return 0;
}

//10.15
int main097()
{
	int a = 10;
	auto f = [a](const int b) {return a + b; };
	cout << f(10) << endl;
	return 0;
}


//10.16
void biggies01(vector<string>& words, vector<string>::size_type sz)
{
	elimDumps(words);
	stable_sort(words.begin(), words.end(), [](const string& a, const string& b)
		                                      {return a.size() < b.size(); });
	auto f= find_if(words.begin(), words.end(), [sz](const string& a) {return a.size() > sz; });
	for_each(f, words.end(), [](const string& s) {cout << s << " "; });
	cout << endl;
}

//10.18
void biggies02(vector<string>& words, vector<string>::size_type sz)
{
	elimDumps(words);
	stable_sort(words.begin(), words.end(), [](const string& a, const string& b)
		{return a.size() < b.size(); });
	auto f = partition(words.begin(), words.end(), [sz](const string& a) {return a.size() < sz; });
	for_each(f, words.end(), [](const string& s) {cout << s << " "; });
	cout << endl;
}

int main098()
{
	int i = 14;
	auto f = [i]()mutable {return ++i; };//改变的只是lambda中i的值，原变量i不变
	cout << f() << endl;//变量i的值是在创建lambda时拷贝，不是调用时拷贝
	cout << f() << endl;
	cout << i << endl;
	int a = 1;
	auto p = [&a]() {return a++; };//而引用捕捉改变的是原变量的值，注意区别
	cout << p() << endl;
	cout << p() << endl;
	cout << a << endl;
	return 0;
}

//10.20
int main099()
{
	 vector<string>v1 = { "dasdasd","askhdkashda","asas","uuahsdukash","dysgd","isdaidaiu" };
	 cout << count_if(v1.begin(), v1.end(), [](const string& a) {return a.size() > 6; });
	return 0;
}

//10.21
int main100()
{
	int i = 10;
	auto f = [i]()mutable ->bool {if (i > 0) { i--; return false; } else return true; };
	while (f() != true)
	{
		cout << f() << endl;
	}
	return 0;
}

//10.24
bool check_size(const string& s,string:: size_type sz)
{
	return s.size() <= sz;
}
int main101()
{
	string s1= "jashdajdh";
	vector<int > v1 = { 1,2,3,4,5,6,7,8,12,13,20 };
	auto p = find_if(v1.begin(), v1.end(), bind(check_size, s1, _1));
	cout << s1 << ':' << p - v1.begin()+1 << endl;
	return 0;
}

//10.25
void biggies03(vector<string>& words, vector<string>::size_type sz)
{
	elimDumps(words);
	stable_sort(words.begin(), words.end(), [](const string& a, const string& b)
		{return a.size() < b.size(); });
	auto f = partition(words.begin(), words.end(), bind(check_size,_1,sz));
	for_each(f, words.end(), [](const string& s) {cout << s << " "; });
	cout << endl;
}

//10.27
int main102()
{
	vector<int>v1 = { 1,1,2,3,4,5,5,5,5,6,7,8,8,9,9,10,11,11,12 };
	list<int> l1, l2;
	l2.resize(12);
	unique_copy(v1.begin(), v1.end(), back_inserter(l1));
	unique_copy(v1.begin(), v1.end(), l2.begin());

	for (auto& c : l1)
		cout << c << endl;

	for (auto& c : l2)
		cout << c << endl;
	return 0;
}

//10.28
int main103()
{
	vector<int >v1 = { 1,2,3,4,5,6,7,8,9 };
	list<int>v2, v3, v4;
	unique_copy(v1.begin(), v1.end(), back_inserter(v2));
	unique_copy(v1.begin(), v1.end(), inserter(v3, v3.begin()));
	unique_copy(v1.begin(), v1.end(), front_inserter(v4));
	for (auto& c : v1)
		cout << c << ' ';
	cout << endl;
	for (auto& c : v2)
		cout << c << ' ';
	cout << endl;
	for (auto& c : v3)
		cout << c << ' ';
	cout << endl;
	for (auto& c : v4)
		cout << c << ' ';
	cout << endl;
	return 0;
}

//10.29
int main104()
{
	ifstream ifs("12345.txt");
	istream_iterator<string> it(ifs), eof;
	vector<string> v1(it, eof);
	for (auto& c : v1)
		cout << c << endl;
	return 0;
}

//10.30
int main105()
{
	istream_iterator<int> it(cin), eof;
	ostream_iterator<int> cit(cout, " ");
	vector<int> v1(it, eof);
	sort(v1.begin(), v1.end());
	copy(v1.begin(),v1.end(), cit);
	return 0;
}

//10.31
int main106()
{
	istream_iterator<int> it(cin), eof;
	ostream_iterator<int> cit(cout, " ");
	vector<int> v1(it, eof);
	sort(v1.begin(), v1.end());
	unique_copy(v1.begin(), v1.end(), cit);
	return 0;
}

//10.33
void printFile(const string file1,const string file2,const string file3)
{
	ifstream ifs(file1);
	ofstream ofs1(file2), ofs2(file3);
	istream_iterator<int> it(ifs), eof;
	ostream_iterator<int> cit1(ofs1," "), cit2(ofs2,"\n");
	while (it != eof)
	{
		if (*it % 2 == 0)
		{
			*cit2 = *it;
		}
		else
		{
			*cit1 = *it;
		}
		++it;
	}
}

int main107()
{
	printFile("12345.txt", "123.txt", "1234.txt");
	return 0;
}

//10.34
int main108()
{
	vector<int>v1{ 1,2,3,4,5,6,7 };
	reverse_iterator<vector<int>::iterator>bit(v1.rbegin());
	reverse_iterator<vector<int>::iterator>it(v1.rend());
	while (bit != it)
	{
		cout << *bit << endl;
		bit++;
	}
	return 0;
}


//10.35
int main109()
{
	vector<int>v1{ 1,2,3,4,5,6,7,8,9 };
	for (auto it = v1.rbegin(); it != v1.rend(); it++)
	{
		cout << *it << endl;
	}
	return 0;
}

//10.36
int main110()
{
	list<int> l1{ 1,2,0,0,3,4,5,0,6,7,8,9 };
	auto it=find(l1.rbegin(), l1.rend(), 0);
	
	cout << *it << endl;
	return 0;
}

//10.37
int main111()
{
	vector<int>v1{ 1,2,3,4,5,6,7,8,9,10 };
	list<int>l1;
	copy(v1.rbegin()+2, v1.rend()-2, back_inserter(l1));
	for (auto c : l1)
	{
		cout << c << endl;
	}
	return 0;
}

