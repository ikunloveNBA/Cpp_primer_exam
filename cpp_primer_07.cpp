#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;

class Person
{
	//非成员函数的友元声明
	friend istream& read(istream&, Person&);//读取人的信息
public:
	//构造函数
	Person() = default;
	Person(const string& name, const string& address) :p_name(name), p_address(address) {}
	Person(istream&);

	string name()const { return p_name; }//返回人员姓名
	string address()const { return p_address; }//返回人员地址

private:
	string p_name;//姓名
	string p_address;//住址
};

istream& read(istream&, Person&);//读取人的信息
ostream& print(ostream&, const Person&);//打印人的信息

Person::Person(istream& is)
{
	read(is, *this);
}

istream& read(istream& is, Person& item)//读取人的信息
{
	is >> item.p_name >> item.p_address;
	return is;
}
ostream& print(ostream& os, const Person& item)//打印人的信息
{
	os << item.name() << ' ' << item.address();
	return os;
}

class Window_mgr;

class Screen
{
public:
	typedef string::size_type pos;//给size_type 起别名，起别名要放到类的开头

	friend class Window_mgr;//将窗口类设为友元
	//friend void Window_mgr::clear(ScreenIndex);//只将clear函数设为友元,这种定义方式最好两个类在同一文件

	//构造函数
	Screen() = default;
	//接受指定高和宽，并将contents初始化成给定数量的字符
	Screen(pos ht, pos wd, char c) :height(ht), width(wd), contents(ht* wd, c) {}
	//接受指定高和宽，并将contents初始化成给定数量的空白
	Screen(pos ht, pos wd) :height(ht), width(wd), contents(ht* wd, ' ') {}

	//读取光标处的字符
	char get()const { return contents[cursor]; }//隐式内联

	//读取光标处的字符
	inline char get(pos r, pos c)const;//显示内联

	//将光标移动到指定行列
	Screen& move(pos r, pos c);//能在之后被设为内联

	//设置光标所在位置的字符
	Screen& set(char);

	//设置给定行列的字符
	Screen& set(pos, pos, char);

	//打印屏幕内容
	Screen& display(ostream& os) { do_display(os);  return *this; };//普通版本
	const Screen& display(ostream& os)const { do_display(os); return *this; }//常量引用版本

private:
	pos cursor = 0;//光标的位置
	pos height = 0, width = 0;//屏幕的高和宽
	string contents;//屏幕的内容
	//可变数据成员，即使在const函数中也可以改变
	mutable size_t access_ctr = 0;//用于记录成员函数被调用的次数
	void do_display(ostream& os) const { os << contents; }//打印Screen的实际操作
};

//获取指定行列的字符
inline char Screen::get(pos r, pos c)const//显示内联
{
	pos row = r * width;
	return contents[row + c];
}

//将光标移动到指定行列
inline Screen& Screen::move(pos r, pos c)//能在之后被设为内联
{
	pos row = r * width;
	cursor = row + c;
	return *this;
}

//设置光标所在位置的字符
inline Screen& Screen::set(char c)
{
	this->contents[this->cursor] = c;
	return *this;
}

//设置给定行列的字符
inline Screen& Screen::set(pos r, pos c, char ch)
{
	this->contents[r * width + c] = ch;
	return *this;
}


class Window_mgr
{
public:
	//窗口中每个屏幕的编号
	using ScreenIndex = vector<Screen>::size_type;

	//按照编号将指定的屏幕变成空白
	void clear(ScreenIndex);

private:
	//默认情况下，一个Windows_mgr包含一个标准尺寸的空白Screen
	vector<Screen> screens{ Screen(24,80,' ') };//列表初始化
};


//按照编号将指定的屏幕变成空白
void Window_mgr::clear(ScreenIndex i)
{
	screens[i].contents = (screens[i].height * screens[i].width, ' ');
}




//书店程序
class Sales_data
{
	//非成员函数的友元声明
	friend Sales_data add(const Sales_data&, const Sales_data&);//将Sales_data对象相加（销量和总销售收入）
	friend istream& read(istream&, Sales_data&);//输入交易信息（某本书的isbn编号、销量、单价）
	friend ifstream& read(ifstream&, Sales_data&);//从文件中读取（某本书的isbn编号、销量、单价）
	friend ostream& print(ostream&, const Sales_data&);//打印交易信息（isbn编号，销量，总销售额，平均售价）
	friend ofstream& print(ofstream&, const Sales_data&);//在文件中打印交易信息（isbn编号，销量，总销售额，平均售价）

public:
	//构造函数
	Sales_data() = default; //合成的默认构造函数
	Sales_data(const string& s) :bookNo(s) {}//只输入编号的构造函数
	//输入编号，销量，单价的构造函数
	Sales_data(const string& s, const unsigned n, const double p) :bookNo(s), units_sold(n), revenue(p* n) {}
	//用explicit关键字限定构造函数不能隐式创建类对象，并且转换构造函数只能适用于一个形参的构造函数
	//只能在类内声明构造函数时使用explicit关键字，在类外部定义时不能重复
	explicit Sales_data(istream&);//调用read输入的构造函数
	//Sales_data() :Sales_data(" ", 0, 0.0) {}//委托构造函数,这也是一个默认构造函数，与合成默认构造函数会有二义性

	string isbn()const { return bookNo; }//返回isbn编号
	Sales_data& combine(const Sales_data&);//将Sales_data对象相加（销量和总销售收入）

private:
	//设为显示内联
	inline double avg_price()const { return units_sold ? revenue / units_sold : 0; }//平均售价
	string bookNo;//书的ISBN编号
	unsigned units_sold = 0;//某本书的销量
	double revenue = 0.0;//这本书的总销售收入
};

Sales_data add(const Sales_data&, const Sales_data&);//将Sales_data对象相加（销量和总销售收入）
istream& read(istream&, Sales_data&);//输入交易信息（某本书的isbn编号、销量、单价）
ifstream& read(ifstream&, Sales_data&);//从文件中读取（某本书的isbn编号、销量、单价）
ostream& print(ostream&, const Sales_data&);//打印交易信息（isbn编号，销量，总销售额，平均售价）
ofstream& print(ofstream&, const Sales_data&);//在文件中打印交易信息（isbn编号，销量，总销售额，平均售价）



Sales_data::Sales_data(istream& is)//调用read输入的构造函数
{
	read(is, *this);//从is读取一条交易信息存入this对象中
}

Sales_data& Sales_data::combine(const Sales_data& rhs)//将Sales_data对象相加（销量和总销售收入）
{
	units_sold += rhs.units_sold;
	revenue = rhs.revenue;
	return *this;
}

Sales_data add(const Sales_data& lhs, const Sales_data& rhs)//将Sales_data对象相加（销量和总销售收入）
{
	Sales_data sum = lhs;
	sum.combine(rhs);
	return sum;
}

istream& read(istream& is, Sales_data& item)//输入交易信息（isbn编号、销量、单价）
{
	double price = 0;
	is >> item.bookNo >> item.units_sold >> price;
	item.revenue = price * item.units_sold;
	return is;
}

ifstream& read(ifstream& ifs, Sales_data& item)//从文件中读取（某本书的isbn编号、销量、单价）
{
	double price = 0.0;
	ifs >> item.bookNo >> item.units_sold >> price;
	item.revenue = price * item.units_sold;
	return ifs;
}

ostream& print(ostream& os, const Sales_data& item)//打印交易信息（isbn编号，销量，总销售额，平均售价）
{
	os << item.isbn() << ' ' << item.units_sold << ' '
		<< item.revenue << ' ' << item.avg_price();
	return os;
}

ofstream& print(ofstream& ofs, const Sales_data& item)//在文件中打印交易信息（isbn编号，销量，总销售额，平均售价）
{
	ofs << item.isbn() << ' ' << item.units_sold << ' '
		<< item.revenue << ' ' << item.avg_price();
	return ofs;
}
