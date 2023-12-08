#pragma once
#include<iostream>
#include<string>
using namespace std;
#include"Message.h"

class Folder
{
public:
	Folder(const Folder& f):msgs(f.msgs) { add_to_msg(f); }
	~Folder() { remove_from_msg(); }
	void addMsg(Message* m) { msgs.insert(m); }
	void remMsg(Message* m) { msgs.erase(m); }
private:
	void add_to_msg(const Folder&);
	void remove_from_msg();
	set<Message*>msgs;
};


void Folder::add_to_msg(const Folder&f)
{
	for (auto& c : f.msgs)
	{
		this->msgs.insert(c);
	}
}

void Folder::remove_from_msg()
{
	while (!msgs.empty())
	{
		(*msgs.begin())->remove(*this);
	}
}

#pragma once
#include<iostream>
#include<string>
#include<set>
#include"Folder.h"
using namespace std;

class Folder;

class Message
{
	friend class Folder;
public:
	explicit Message(const string& s = " ") :contents(s) {}//禁止隐式初始化
	//拷贝控制成员，用来管理指向本message的指针
	Message(const Message& m):contents(m.contents),folders(m.folders) { add_to_Folders(m); }
	Message& operator=(const Message&);
	~Message() { this->remove_from_Floders(); }
	void save(Folder&);//从给定的Folder中添加本message
	void remove(Folder&);//从给定的Follder中删除本message
	void addFldr(Folder* f) { folders.insert(f); }//添加给定folder

private:
	string contents;//实际消息文本
	set<Folder*>folders;//包含本message的folder
	void add_to_Folders(const Message&);//将本message添加到folders中指定的Floder
	void remove_from_Floders();//从floders中的每个Floder中删除本message
};

//从给定的Folder中添加本message
void Message:: save(Folder& f)
{
	folders.insert(&f);
	f.addMsg(this);
}

void Message::remove(Folder& f)//从给定的Follder中删除本message
{
	folders.erase(&f);
	f.remMsg(this);
}

#pragma once
#include<iostream>
#include<string>
#include<fstream>
using namespace std;
class Sales_data
{
	//非成员函数的友元声明
	friend Sales_data add(const Sales_data&, const Sales_data&);//将Sales_data对象相加（销量和总销售收入）
	friend istream& read(istream&, Sales_data&);//输入交易信息（某本书的isbn编号、销量、单价）
	friend ifstream& read(ifstream&, Sales_data&);//从文件中读取（某本书的isbn编号、销量、单价）
	friend ostream& print(ostream&, const Sales_data&);//打印交易信息（isbn编号，销量，总销售额，平均售价）
	friend ofstream& print(ofstream&, const Sales_data&);//在文件中打印交易信息（isbn编号，销量，总销售额，平均售价）
	friend ostream& operator<<(ostream&, const Sales_data&);//重载输出运算符
	friend istream& operator>>(istream&,  Sales_data&);//重载输入运算符
	friend bool operator==(const Sales_data& , const Sales_data& );//重载相等运算符
	friend bool operator!=(const Sales_data&, const Sales_data&);//重载不等运算符
public:
	//构造函数
	Sales_data() = default; //合成的默认构造函数
	Sales_data(const string& s) :bookNo(s) {}//只输入编号的构造函数
	Sales_data& operator+=(const Sales_data&);//复合赋值运算符
	//输入编号，销量，单价的构造函数
	Sales_data(const string& s,  const unsigned n,const double p) :bookNo(s), units_sold(n), revenue(p*n) {}
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
	unsigned units_sold=0;//某本书的销量
	double revenue = 0.0;//这本书的总销售收入
};

Sales_data add(const Sales_data&, const Sales_data&);//将Sales_data对象相加（销量和总销售收入）
istream& read(istream&, Sales_data&);//输入交易信息（某本书的isbn编号、销量、单价）
ifstream& read(ifstream&, Sales_data&);//从文件中读取（某本书的isbn编号、销量、单价）
ostream& print(ostream&, const Sales_data&);//打印交易信息（isbn编号，销量，总销售额，平均售价）
ofstream& print(ofstream&, const Sales_data&);//在文件中打印交易信息（isbn编号，销量，总销售额，平均售价）

#include"Sales_data.h"

Sales_data:: Sales_data(istream& is)//调用read输入的构造函数
{
	read(is, *this);//从is读取一条交易信息存入this对象中
}

Sales_data& Sales_data:: combine(const Sales_data& rhs)//将Sales_data对象相加（销量和总销售收入）
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

ifstream& read(ifstream& ifs , Sales_data& item)//从文件中读取（某本书的isbn编号、销量、单价）
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

//重载输出运算符
ostream& operator<<(ostream& os, const Sales_data& item)
{
	os << item.isbn() << " " << item.units_sold << " "
		<< item.revenue << " " << item.avg_price();
	return os;
}

//重载输入运算符
istream& operator>>(istream&is,  Sales_data&item)
{
	double price;
	is >> item.bookNo >> item.units_sold >> price;
	if (is)
		item.revenue = item.units_sold * price;
	else item = Sales_data();//输入失败，对象被赋予默认状态
	return is;
}

 bool operator==(const Sales_data& lhs, const Sales_data& rhs)//重载相等运算符
{
	 return lhs.isbn() == rhs.isbn() &&
		 lhs.units_sold == rhs.units_sold &&
		 lhs.revenue == rhs.revenue;
}

 //重载不等运算符
 bool operator!=(const Sales_data& lhs, const Sales_data& rhs)
 {
	 return !(lhs == rhs);
 }

 //复合赋值运算符
 Sales_data& Sales_data:: operator+=(const Sales_data& rhs)
 {
	 this->units_sold += rhs.units_sold;
	 this->revenue += rhs.revenue;
	 return *this;
 }
