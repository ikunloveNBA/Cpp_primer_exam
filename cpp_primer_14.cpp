#include<iostream>
#include<string>
#include<vector>
#include<iterator>
#include<algorithm>
#include<numeric>
#include<unordered_map>
#include<functional>
#include<map>
using namespace placeholders;
using namespace std;

class PrintString
{
public:
	string operator()(istream& is) { if (getline(is, s1)) return s1;  }
private:
	string s1;
};

//14.34
int main131()
{
	PrintString p;
	cout << p(cin) << endl;
	
	return 0;
}

//14.35
int main132()
{
	PrintString p;
	vector<string>v1;
	int i = 0;
	while (i<10)
	{
		v1.push_back(p(cin));
		i++;
	}
	return 0;
}

//14.37
class Print01
{
public:
	Print01(ostream& o = cout, char c = ' ') :os(o), sep(c) {};
	void operator()(const int& s)const { os << s << sep; }
private:
	ostream& os;
	char sep;
};

int main133()
{
	vector<int>v1{ 1,2,3,4,5,6,7,8,9,0 };
	for_each(v1.cbegin(), v1.cend(), Print01(cerr,'\n'));
	return 0;
}

int main134()
{
	vector<int>v1{ 1,2,3,4,5,6,7,8,9 };
	int a=v1.size();
	cout << a << endl;
	cout << v1[0] << endl;
	return 0;
}

//斐波那契额数列（递归）
int fib(int n)
{
	if (n == 1)return 1;
	if (n == 2)return 1;
	return fib(n - 1) + fib(n - 2);
}

//斐波那契数列（备忘录递归）
int fib01(int n,unordered_map<int,int>&m1)
{
	if (n == 1)return 1;
	if(n == 2)return 1;
	if (m1.find(n) == m1.end())
	{
		m1[n] = (fib01(n-1,m1)+fib01(n-2,m1));
	}
	return m1[n];
}

//斐波那契数列（动态规划）
int fib02(int n)
{
	int a = 1;
	int b = 1;
	for (int i = 3; i <= n; i++)
	{
		int tmp = a + b;
		a = b;
		b = tmp;
	}
	return b;
}


int main135()
{
	unordered_map<int, int> m1;
	cout << fib(10) << endl;
	cout << fib01(10,m1) << endl;
	cout << fib02(10) << endl;
	return 0;
}

//14.37
class IntCompare
{
public:
	IntCompare(int v) :val(v) {}
	bool operator()(int v) { return val == v; }
private:
	int val;
};

int main136()
{
	vector<int>vec = { 1,2,3,2,1 };
	const int oldValue = 2;
	const int newValue = 200;
	IntCompare icmp(oldValue);
	replace_if(vec.begin(), vec.end(), icmp, newValue);
	return 0;
}
//14.38
class StrLen
{
public:
	StrLen(int len) :len(len) {}
	bool operator()(const string& str) { return str.length() == len; }
private:
	int len;
};

void readStr(istream& is,vector<string>&vec)
{
	string word;
	while (is >> word)
	{
		vec.push_back(word);
	}
}


int main137()
{
	vector<string>vec;
	readStr(cin, vec);
	const int minLen = 1;
	const int maxLen = 10;
	for (int i = minLen; i < maxLen; i++)
	{
		StrLen slen(i);
		count_if(vec.end(), vec.end(), slen);
	}
	return 0;
}

//14.44
int add(int a, int b)
{
	return a + b;
}

int mod(int a, int b)
{
	return a % b;
}

class equal1
{
public:
	int operator()(int a, int b) { return a == b; }
};

void binops01( map<string,function<int(int,int)>>&m,int a,int b,string& s)
{
	cout << m[s](a, b) << endl;
}

int main139()
{
	map<string, function<int(int, int)>>binops;
	binops.insert(make_pair("+", add));//函数指针
	auto minus = [](int a, int b) {return a - b; };
	binops.insert({ "-",minus });//命名的lambda表达式
	binops.insert({ "*",[](int a,int b) {return a * b; } });//匿名的lambda表达式
	binops.insert({ "/",divides<int>() });//标准库函数对象
	auto f = bind(mod, _1, _2);
	binops.insert({ "%",f });//bind函数对象
	binops.insert({ "==",equal1()});//重载函数调用运算符的类
	
	return 0;
}

//14.52
class poop
{
public:
	poop(const string i) :s(i) {}
	operator string()const { return s; }//类类型转换
private:
	string s;
};

int main140()
{
	poop p1("asad"), p2("asdadd");
	string s1("qweqe"), s2("uiqwyui");
	poop p3 = s1;
	string s4 = static_cast<string>(p3) + s1;//类类型转换
	return 0;
}

