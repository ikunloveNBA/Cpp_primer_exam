#include<iostream>
#include<memory>
#include<string>
#include<vector>
#include<initializer_list>
#include<new>
#include<fstream>
#include<sstream>
#include<cstring>
#include<map>
#include<set>
using namespace std;
#pragma warning(disable:4996)

//const对象虽然不能被改变，但是可以被动态创建并销毁

//12.6
vector<int>* returnPtr()
{
	return new vector<int>();
}

void readPtr(istream& is, vector<int>*& v1)
{
	int i;
	while (is >> i)
	{
		v1->push_back(i);
	}
}

void printPtr(vector<int>*& v1)
{
	for (auto it = v1->cbegin(); it != v1->cend(); it++)
	{
		cout << *it << endl;
	}
}

int main121()
{
	vector<int>* v1 = returnPtr();
	readPtr(cin, v1);
	printPtr(v1);
	delete v1;
	v1 = nullptr;
	return 0;
}

//12.7
shared_ptr<vector<int>> returnPtr01()
{
	return make_shared<vector<int>>();
}

void readPtr01(istream& is, vector<int>*& v1)
{
	int i;
	while (is >> i)
	{
		v1->push_back(i);
	}
}

void printPtr01(vector<int>*& v1)
{
	for (auto it = v1->cbegin(); it != v1->cend(); it++)
	{
		cout << *it << endl;
	}
}

int main122()
{
	vector<int>* v1 = returnPtr();
	readPtr(cin, v1);
	printPtr(v1);
	return 0;
}


//接受指针参数的智能指针构造函数是explicit，必须直接初始化
int main123()
{
	//shared_ptr<int> = new int(1024);//不能隐式转换构造
	shared_ptr<int>(new int(1024));//可以直接初始化
	return 0;
}


//C++17之前的版本不支持智能指针默认析构动态数组，需要自己传入删除器

void deleter(int* i)
{
	cout << "调用删除器" << endl;
	delete[]i;
}
int main124()
{
	unique_ptr<int, decltype(deleter)*>p1(new int[10] {1, 2, 3, 4, 5, 6, 7, 8, 9, 0}, deleter);
	for (int i = 0; i < 10; i++)
	{
		cout << *(p1) << endl;
	}
	unique_ptr<int>p2(new int(5));
	cout << *p2 << endl;
	int* p = new int[10] {1, 2, 3, 4, 5, 6};
	for (int i = 0; i < 6; i++)
	{
		cout << p[i] << endl;
	}
	delete[] p;
	p = nullptr;
	return 0;
}

//12.1   //12.19

class StrBlobPtr;
class StrBlob//此类是一个共享相同元素的string的vector类
{
public:
	friend class StrBlobPtr;
	typedef vector<string>::size_type size_type;
	StrBlob();
	StrBlob(initializer_list<string> l1);//含有可变形参列表的构造函数
	size_type size()const { return data->size(); }//返回元素个数
	bool empty()const { return data->empty(); }//元素个数是否为空
	void push_back(const string& t) { data->push_back(t); }//插入元素
	void pop_back();//删除元素
	string& front();//访问首元素
	string& back();//访问尾元素
	StrBlobPtr begin();//首元素迭代器
	StrBlobPtr end();//尾后元素迭代器
private:
	shared_ptr<vector<string>> data;
	//如果data[i]访问不存在的元素，则抛出一个异常
	void check(size_type i, const string& msg)const;
};


class StrBlobPtr//伴随指针类
{
public:
	StrBlobPtr() :curr(0) {}
	StrBlobPtr(StrBlob& a, size_t sz = 0) :wptr(a.data), curr(sz) {}
	string& deref()const;//解引用运算符
	StrBlobPtr& incr();//前缀递增
private:

	shared_ptr<vector<string>>check(size_t, const string&)const;
	weak_ptr<vector<string>> wptr;//指向StrBlobPtr
	size_t curr;//在数组中的当前位置
};


StrBlob::StrBlob() :data(make_shared<vector<string>>()) {}//默认构造函数
StrBlob::StrBlob(initializer_list<string> l1) :data(make_shared<vector<string>>(l1)) {}//拷贝列表构造函数


//如果data[i]访问不存在的元素，则抛出一个异常
void StrBlob::check(size_type i, const string& msg)const
{
	if (i >= data->size())
		throw out_of_range(msg);
}

//删除元素
void StrBlob::pop_back()
{
	check(0, "pop on empty StrBlob");//检查vector是否为空
	data->pop_back();
}

//访问首元素
string& StrBlob::front()
{
	check(0, "front on empty StrBlob");
	return data->front();
}

//访问尾元素
string& StrBlob::back()
{
	check(0, "front on empty StrBlob");
	return data->back();
}

StrBlobPtr StrBlob::begin() { return StrBlobPtr(*this); }//首元素迭代器
StrBlobPtr StrBlob::end() { auto ret = StrBlobPtr(*this, data->size()); return ret; }


//-----------------------------StrBlobPtr实现
shared_ptr<vector<string>>StrBlobPtr::check(size_t i, const string& msg)const
{
	auto ret = wptr.lock();//判断vector是否还存在
	if (!ret)//如果不存在抛出异常
	{
		throw runtime_error("unbound StrBlobPtr");
	}
	if (i >= ret->size())
	{
		throw out_of_range("msg");
	}
	return ret;//否则返回wptr绑定的shared智能指针
}

string& StrBlobPtr::deref()const//解引用运算符
{
	auto p = check(curr, "dereference past end");
	return (*p)[curr];
}

StrBlobPtr& StrBlobPtr::incr()//前缀递增
{
	check(curr, "increment past end of StrBlobPtr");
	++curr;
	return *this;
}

//12.20
int main125()
{
	ifstream ifs("12345.txt");
	string s1;
	StrBlob st1;
	while (getline(ifs, s1))
	{
		st1.push_back(s1);
	}
	for (auto it = st1.begin(); ; it.incr())
	{
		cout << it.deref() << endl;
	}
	return 0;
}

//动态数组并不是数组类型，因此不能对动态数组调用begin和end()以及范围for语句

//12.21
int main126()
{
	unique_ptr<int[]>p1(new int[10] {1, 2, 3, 4, 5, 6, 7, 8, 9, 0});
	for (int i = 0; i < 10; i++)
	{
		cout << p1[i] << endl;
	}

	shared_ptr<int> sp(new int[10] {1, 2, 3, 4, 5, 6, 7, 7, 8, 9}, [](int* i) {delete[] i; });
	for (int i = 0; i < 10; i++)
	{
		cout << *(sp.get() + i) << endl;
	}
	return 0;
}

//12.23
void linkChar01(const char* c1, const char* c2)
{
	char* r = new char[strlen(c1) + strlen(c2) + 1];
	strcpy(r, c1);
	strcat(r, c2);
	cout << r << endl;
}

void linkChar02(const string s1, const string s2)
{
	char* r = new char[strlen(s1.c_str()) + strlen(s2.c_str()) + 1];
	strcpy(r, (s1 + s2).c_str());
	cout << r << endl;
}
int main127()
{
	linkChar01("hello", "world");
	linkChar02("hello", "world");

	return 0;
}


//12.26
void linkChar03(const char* c1, const char* c2)
{
	allocator<char>alloc;
	auto p = alloc.allocate(strlen(c1) + strlen(c2) + 1);//创建内存
	auto q = p;
	alloc.construct(q++);//构造string对象
	strcpy(p, c1);
	strcat(p, c2);
	cout << p << endl;
	while (q != p)
	{
		alloc.destroy(q--);//释放构造的string
	}
	alloc.deallocate(p, strlen(c1) + strlen(c2) + 1);//释放创建内存
}

int main128()
{
	linkChar03("hello", "world");
	return 0;
}

//标准库内容学习总结
//文本查询程序
int main129()
{
	ifstream ifs("12345.txt");
	vector<string> text;
	map<string, set<int>>query;
	string fileCon;
	while (getline(ifs, fileCon))//将文件的每一行保存到vector中
	{
		text.push_back(fileCon);
		int n = text.size() - 1;//行号
		istringstream line(fileCon);
		string word;
		while (line >> word)
		{
			query[word].insert(n);//保存每个单词的行号
		}
	}

	string word;
	cin >> word;
	cout << word << "出现了" << endl;
	for (auto& c : query[word])
	{
		cout << c << ':' << text[c] << endl;
	}
	return 0;
}

class QueryResult;
class TextQuery//文件查询类
{
public:
	typedef vector<string>::size_type line_no;//定义类的行号类型
	TextQuery(ifstream&);//构造函数
	QueryResult query(const string&);//查找单词
private:
	shared_ptr<vector<string>>file;//保存文件内容
	map<string, shared_ptr<set<line_no>>>wm;//保存每个单词对应的行号和次数
};

TextQuery::TextQuery(ifstream&is)//构造函数
{
	string text;
	while (getline(is, text))//按行读取文件
	{
		file->push_back(text);//尾插每行
		int n = file->size() - 1;//设置单词的行数
		istringstream ist(text);
		string word;
		while (ist >> word)//按单词读取每行文本
		{
			auto& lines = wm[word];//如果是个新单词就创建一个空指针
			if (!lines)//如果指针为空就为他创建一个set对象
				lines.reset(new (set<line_no>));
			lines->insert(n);//向set中插入行数
		}
	}
}

QueryResult TextQuery::query(const string& s)//查找单词
{
	static shared_ptr<set<line_no>>nodata(make_shared<set<line_no>>());//创建一个指向空set的指针
	auto loc = wm.find(s);
	if (loc == wm.end())
		return QueryResult(s, nodata, file);//没找到返回静态对象
	else
		return QueryResult(s, loc->second, file);//找到了就返回此对象
}

class QueryResult//查询结果类
{
	friend ostream& print(ostream&, const QueryResult&);
public:
	QueryResult(string s,
		shared_ptr<set<TextQuery::line_no>> ls,
		shared_ptr<vector<string>>t) :
		findWord(s), lines(ls), text(t) {}//构造函数
private:
	string findWord;//要查询的单词
	shared_ptr<set<TextQuery::line_no>>lines;//行号
	shared_ptr<vector<string>>text;//查询的文件
};

//打印查询结果
ostream& print(ostream& os, const QueryResult& q)
{
	os << q.findWord << "一共出现了" << q.lines->size() << "次" << endl;
	os << "分别是：" << endl;
	for (auto& c : *(q.lines))
	{
		cout << ( * (q.text))[c] << endl;
	}
	return os;
}

void runQueries(ifstream& ifs)
{
	TextQuery q(ifs);//初始化文本查询类

	while (true)
	{
		cout << "请输入您想要查找的单词：";
		string word;
		if (!(cin >> word) || word != "q")break;
		print(cout,q.query(word));
	}
	
}

int main()
{
	ifstream ifs("12345.txt");
	runQueries(ifs);
	return 0;
}
