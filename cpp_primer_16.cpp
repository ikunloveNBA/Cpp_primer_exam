#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<functional>
#include<type_traits>
#include<utility>
using namespace std;

//16.4
template<typename I,typename T >
I mFind(I b,I e, const T& val)
{
	while (b != e && *b != val)
	{
		b++;
		
	}
	return b;
}


int main143()
{
	vector<int>v = { 1,2,3,4,5 };
	list<string>l = { "hello","adsda","yeeuq" };

	auto iter = mFind(v.cbegin(), v.cend(), 9);
	if (iter == v.end())
		cout << "没有找到" << endl;
	else
		cout << "找到了"<<*iter << endl;

	auto iter1 = mFind(l.cbegin(), l.cend(), "hello");
	if (iter1 == l.end())
		cout << "没有找到" << endl;
	else
		cout << "找到了"<<*iter1 << endl;
	return 0;
}

//16.5
template<typename T,size_t N>
void  mPrint(const T (&a)[N])
{
	for (auto it = begin(a); it != end(a); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

int main144()
{
	int a[5] = { 1,2,3,4,5 };
	string s[3] = { "asd","hello","akdhkd" };
	char c[6] = { "hello" };
	mPrint(a);
	mPrint(s);
	mPrint(c);
	return 0;
}

//16.6
template<typename T,size_t N>
const T* mBegin(const T(&a)[N])
{
	return &a[0];
}

template<typename T,size_t N>
const T* mEnd(const T(&a)[N])
{
	return &a[0] + N;
}

template<typename T,size_t N>
constexpr int arr_size(const T(&a)[N])
{
	return N;
}

template<typename T,size_t N>
void Mprint01(const T(&a)[N])
{
	for (int i = 0; i < arr_size(a); i++)
	{
		cout << a[i] << " ";
		cout << endl;
	}
}

int main145()
{
	int a[5] = { 1,2,3,4,5 };
	string s[3] = { "hello","allo","world" };
	Mprint01(a);
	Mprint01(s);
	return 0;
}

//16.10 模板函数默认值
template<typename T,typename F=less<T>>
int mcompare(const T &v1,const T&v2,F f=F())
{
	if (f(v1, v2))return -1;
	if (f(v2, v1))return 1;
	return 0;
}

//16.19
template<typename T>
void mPrint02(const T&t)
{
	for (typename T::size_type i = 0; i < t.size(); i++)
	{
		cout << t.at(i) << " ";
	}
	cout << endl;
}

int main146()
{
	string s = "Hello";
	mPrint02(s);
	vector<int>a = { 1,2,3,4,5 };
	mPrint02(a);
	return 0;
}


//16.20
template<typename T>
void mPrint03(const T& t)
{
	for (auto i = t.begin(); i != t.end(); i++)
	{
		cout << *i << " ";
	}
	cout << endl;
}

int main147()
{
	string s = "Hello";
	mPrint03(s);
	
	return 0;
}

//16.21
class DebugDelete
{
public:
	DebugDelete(ostream& s = cerr) :os(s) {}
	template<typename T>void operator()(T* p)const
	{
		os << "deleting unique_ptr" << endl; delete p;
	}
private:
	ostream& os;
};

int main148()
{
	unique_ptr<int, DebugDelete>p(new int, DebugDelete());
	unique_ptr<string, DebugDelete>p1(new string, DebugDelete());
	return 0;
}

//16.37
template<typename T1,typename T2>
T1 m_sum(T2 a, T2 b)
{
	return a + b;
}

int main149()
{
	int i = 1, j = 2;
	auto val=m_sum<double>(i,j);
	return 0;
}

//16.38
template<typename T>
auto func01(T beg, T end)->decltype(*beg)//自动推导类型
{
	return *beg;
}

template<typename T>//（去拷贝操作，头文件type_traits）标准类型转换模板
auto func02(T beg, T end)->typename remove_reference<decltype(*beg)>::type//返回元素的拷贝
{
	return *beg;
}

int main150()
{
	vector<int>v1 = { 1,2,3,4,5,6,7,8,9 };
	cout << func01(v1.begin(), v1.end()) << endl;
	return 0;
}

int main151()
{
	using intRef = int&;
	int a = 1;
	intRef& b = a;
	b = 10;
	cout << a << endl;
	cout << b << endl;
	return 0;
}

template<typename T>
typename remove_reference<T>::type&& m_move(T && i)
{
	return static_cast<typename remove_reference<T>::type&&>(i);
}

void func04(int i, string s)
{
	cout << i <<""<< s << endl;
}

/*在这个程序中，main函数没有输出123是因为在A a(A())这一行代码中，A()是一个临时对象，
它是通过移动构造函数A(A&& a)来初始化a的。然而，在这个移动构造函数中，虽然它被定义了，
但是它并没有被调用。这是因为编译器会对这个临时对象进行优化，将其直接转换为A a;这样的
形式，从而避免了调用移动构造函数。因此，main函数没有输出123*/
//class A
//{
//public:
//	A( A&& a)noexcept { cout << "123" << endl; }
//	A() :i(0) {}
//	A(int i1):i(i1) {}
//private:
//	int i;
//};
//
//int main152()
//{
//	A a(A(1));
//	A b(move(a));
//	return 0;
//	
//}

int main152()
{
	/*int &&b = 10;
	b = 5;
	string s1 = "asdasd";
	string&& s2 = move(s1).c_str();
	string&& s3 = s2;
	cout << b << endl;*/
	return 0;
}

class B
{
public:
	B() :i(new int) {}
	//B(const B& b) { i = new int(*b.i); }
	~B() { delete i; }
	void Bprint()
	{
		cout <<"变量i的地址："<< &i << endl;
	}

	int* i;
};

B func05()
{
	B temp;
	temp.Bprint();
	cout << "temp类的地址：" << &temp << endl;
	return temp;
}


int main153()
{
	B b1 = func05();
	b1.Bprint();
	cout << "b1的地址：" << &b1 << endl;
	return 0;
}

class A
{
private:
	char* x;
public:
	A() :x(new char('x')) {};
	~A() { delete x; }
	void test() { cout << *x << endl; };
};

A func()
{
	A temp;
	 cout << (unsigned)&temp << endl;
	return temp;
}



int main154()
{
	A a = func();
	cout << (unsigned)&a << endl;
	a.test();
	return 0;
}

int main155()
{
	int a = 10;
	int&& b = move(a);
	string s1 = "asdasd";

	cout << &a << endl;
	cout << move(s1).c_str() << endl;
	cout << &b << endl;
	return 0;
}

class C
{
public:

};

int&& func05(int &&i)
{

	return move(i);
}

int main156()
{
	int&& j = func05(5);
	return 0;
}

template<typename F,typename T1,typename T2>
void func06(F f,T1 &&t1,T2&&t2)
{
	f(forward<T1>(t1),forward<T2>( t2));
}

void func07(int &&i,int&j)
{
	cout << ++i <<" "<< ++j << endl;
}

int main157()
{
	int i = 10;
	func06(func07, 10, i);
	return 0;
}

template<typename T>
void func07(const T&t)
{
	cout << t << endl;
}

template<typename T,typename...Args>
void func07(const T& t, const Args&...a)
{
	
	cout << sizeof...(Args) << endl;
	cout << sizeof...(a) << endl;
	cout << t << endl;
	func07(a...);

}

int main158()
{
	int i = 0;
	string s = "dadsa";
	char c[5] = "sads";
	func07(i,s,c,40,"hello");
	vector<int>v1;
	v1.push_back(1);
	v1.emplace_back(1);
	return 0;
}


template<typename ...Args>
string make_string(Args&&...args)
{
	string s(forward<Args>(args)...);
	return s;
}

template<typename T,typename ...Args>
T make_BP(Args&& ...args)
{
	return static_cast<T>(new Args(forward<Args>(Args)...));
}


int main159()
{
	string s = make_string(10, 'a');
	cout << s << endl;
	return 0;
}

template<typename T>
int occurs(const vector<T>& v, T&& t)
{
	int ret = 0;
	for (auto a : v)
		if (a == t)
			ret++;
	
	cout << "普通化版本" << endl;
	return ret;
}

template<>
int occurs(const vector<const char*>& v,  const char* && c)
{
	int ret = 0;
	for (auto a : v)
		if (!strcmp(a, c))
			ret++;
	cout << "const char* 特例化版本" << endl;
	return ret;
}




//const char*不能用普通模板类比较只能用特例化的模板
int main()
{
	const char c[10] = { "asdasd" };
	vector<int>v1 = { 1,2,3,4,5,6 };
	vector<double>v2 = { 1.1,1.2,3.3,4.7,6.5 };
	vector<string>v3 = { "hello","allo","als" };
	vector<const char*>v4 = {"sadasda","qweliqwe","qkehiqwh"};
	occurs(v1, 2);
	occurs(v2, 2.2);
	occurs(v3, string("hello"));
	occurs(v4, static_cast<const char*>("asdad"));

	return 0;
}
