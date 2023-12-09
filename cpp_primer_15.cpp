#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<set>
#include<fstream>
#include<sstream>
#include<functional>
#include<memory>
#include"QueryResult.h"
using namespace std;

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
	static shared_ptr<set<line_no>>nodata(make_shared<set<TextQuery::line_no>>());//创建一个指向空set的指针
	auto loc = wm.find(s);
	if (loc == wm.end())
		return QueryResult(s, nodata, file);//没找到返回静态对象
	else
		return QueryResult(s, loc->second, file);//找到了就返回此对象
}
	

void runQueries(ifstream& ifs)
{
	TextQuery q(ifs);//初始化文本查询类

	while (true)
	{
		cout << "请输入您想要查找的单词：";
		string word;
		if (!(cin >> word) || word != "q")break;
		print(cout, q.query(word));
	}

}

#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<set>
#include"TextQuery.h"
using namespace std;

class QueryResult//查询结果类
{
	friend ostream& print(ostream&, const QueryResult&);
public:
	QueryResult(string s,
		shared_ptr<set<TextQuery::line_no>> ls,
		shared_ptr<vector<string>>t) :
		findWord(s), lines(ls), text(t) {}//构造函数
	set<TextQuery::line_no>::iterator begin(){ return lines->begin(); }
	set<TextQuery::line_no>::iterator end() { return lines->end(); }
	shared_ptr<vector<string>>get_file() { return text; }
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
		cout << (*(q.text))[c] << endl;
	}
	return os;
}

#pragma once
#include<iostream>
#include"TextQuery.h"
#include"Query.h"
using namespace std;
class Query_base
{
	friend class Query;
protected:
	using line_no = TextQuery::line_no;
	virtual ~Query_base() = default;//虚析构
private:
	//eval返回与当前Query匹配的QueryResult
	virtual QueryResult eval(const TextQuery&)const = 0;
	//rep是表示查询的一个string
	virtual string rep()const = 0;
};

#pragma once
#include"Query_base.h"
#include"WordQuery.h"
#include"NotQuery.h"
#include"AndQuery.h"
#include"OrQuery.h"

class Query
{
	friend Query operator~(const Query&);
	friend Query operator|(const Query&, const Query&);
	friend Query operator&(const Query&, const Query&);

public:
	Query(const string&);
	Query(shared_ptr<Query_base>query) :q(query) {}
	//接口函数，对应的Query_base操作
	QueryResult eval(const TextQuery& t)const { return q->eval(t); }
	string rep()const { return q->rep(); }
private:
	
	shared_ptr<Query_base>q;
};

ostream& operator<<(ostream& os, const Query& query)
{
	//Query::rep()通过Query_base的指针对rep()进行了动态调用
	return os << query.rep();
}

inline Query::Query(const string& s) :q(new WordQuery(s)) {}



 #pragma once
#include"Query_base.h"
#include"Query.h"
#include"QueryResult.h"
class NotQuery:public Query_base
{
	friend Query operator~(const Query&);
	NotQuery(const Query& q) :query(q) {}

	using line_no=Query_base::line_no;
	string rep()const override { return "~(" + query.rep()+")"; }
	QueryResult eval(const TextQuery&)const;
	Query query;
};

inline Query operator~(const Query& operand)
{
	return shared_ptr<Query_base>(new NotQuery(operand));
}


QueryResult NotQuery:: eval(const TextQuery&text)const
{
	auto result = query.eval(text);
	auto ret_lines = make_shared<set<line_no>>();
	auto beg = result.begin(), end = result.end();
	auto sz = result.get_file()->size();
	for (size_t n = 0; n != sz;++n)
	{
		if (beg == end || *beg != n)
			ret_lines->insert(n);
		else if (beg != end)
			++beg;
	}
	return QueryResult(rep(), ret_lines, result.get_file());

}

#pragma once
#include"Query_base.h"
#include"Query.h"

class BinaryQuery :public Query_base
{
protected:
	BinaryQuery(const Query& l, const Query& r, string s) :lhs(l), rhs(r), opSym(s) {}
	string rep()const override { return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")"; }
	Query lhs, rhs;//左侧和右侧运算对象
	string opSym;//运算符的名字
};

#pragma once
#include"BinaryQuery.h"
#include<functional>
#include<iterator>
#include<algorithm>
#include<numeric>

class AndQuery :public BinaryQuery
{
	friend Query operator&(const Query&, const Query&);
	AndQuery(const Query& l, const Query& r) :BinaryQuery(l, r, "&") {}
	QueryResult eval(const TextQuery&)const;
};

Query operator&(const Query& l, const Query& r)
{
	return shared_ptr<Query_base>(new AndQuery(l, r));
}

QueryResult AndQuery:: eval(const TextQuery& text)const
{
	auto left = lhs.eval(text), right = rhs.eval(text);
	auto ret_lines = make_shared<set<line_no>>();
	//将两个范围的交集写入一个目的迭代器中
	set_intersection(left.begin(), left.end(), right.begin(), right.end(),
		inserter(*ret_lines, ret_lines->begin()));
	return QueryResult(rep(), ret_lines, left.get_file());
}

#pragma once
#include"BinaryQuery.h"
class OrQuery :public BinaryQuery
{
	friend Query operator|(const Query&, const Query&);
	OrQuery(const Query& l, const Query& r) :BinaryQuery(l, r, "|") {}
	QueryResult eval(const TextQuery&)const;
};

Query operator|(const Query& l, const Query& r)
{
	return shared_ptr<Query_base>(new OrQuery(l, r));
}

QueryResult OrQuery::eval(const TextQuery& text)const 
{
	auto right = rhs.eval(text), left = lhs.eval(text);
	auto ret_lines = make_shared<set<line_no>>(left.begin(), left.end());
	ret_lines->insert(right.begin(), right.end());
	return QueryResult(rep(), ret_lines, left.get_file());
}
