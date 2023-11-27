#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<deque>
#include<list>
#include<forward_list>
#include<array>
#include<stdexcept>
using namespace std;

//9.2
int main061()
{
	list<deque<int>> l1;

	return 0;
}
//9.4
bool find001(vector<int> v, const int i)
{
	for (auto c : v)
		if (c == i) return true;
	return false;
}

//9.4
int main062()
{
	vector<int> v1{ 2,3,4,1,5,6 };
	cout << find001(v1, 7);
	return 0;
}

//9.5
vector<int>::iterator find002(vector<int>& v, const int i)
{
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		if (*it == i)
		{
			return it;
		}
	}
	return v.end();
}

//9.5
vector<int>::iterator find003(vector<int>::iterator beg, vector<int>::iterator end, const int i)
{
	for (vector<int>::iterator it = beg; it != end; it++)
	{
		if (*it == i)
		{
			return it;
		}
	}
	return end;
}

//9.5
int main063()
{
	vector<int> v1{ 2,3,4,1,5,6 };
	cout << *find002(v1, 4) << endl;
	cout << *find003(v1.begin(), v1.end(), 4) << endl;
	return 0;
}

//9.8
int main064()
{
	string item;
	vector<string>v1{ "kjahdkash" };
	vector<string>::value_type i = v1.back();
	item = v1[0];
	cout << i << endl;
	return 0;
}

//9.11
int main065()
{
	vector<int> v1;
	vector<int>v2{ 1,2,3,4,5,6 };
	vector<int>v3(v2);
	vector<int>v4 = v3;
	vector<int>v5 = { 1,2,3 };
	vector<int>v6(6);
	vector<int>v7(v5.begin(), v5.end());
	vector<int>v8(6, 1);
	cout << v8[5] << endl;

	return 0;
}

//9.15
int main066()
{
	vector<int> v1 = { 1,2,3,4,5,6,7 };
	vector<int> v2 = { 1,2,3,4,5,6,7 };
	vector<int> v3 = { 1,2,3 };
	vector<int> v4 = { 2,3,4,5,6,7,8 };
	cout << (v1 == v2) << endl;
	cout << (v1 == v3) << endl;
	cout << (v1 > v3) << endl;
	cout << (v1 > v4) << endl;

	return 0;
}

//9.16
bool lv_equal(vector<int>& v, list<int>& l)
{
	if (v.size() != l.size())return false;
	auto vb = v.cbegin();
	for (auto lb = l.cbegin(); lb != l.cend(); lb++)
		if (*lb != *(vb++))
			return false;
	return true;
}


int main067()
{
	list<int> l1 = { 1,2,3 };
	vector<int> v1 = { 1,2,3,4,5,6,7 };
	vector<int> v2 = { 1,2,3,4,5,6,7 };
	vector<int> v3 = { 1,2,3 };
	vector<int> v4 = { 2,3,4,5,6,7,8 };
	cout << lv_equal(v1, l1) << endl;
	cout << lv_equal(v2, l1) << endl;
	cout << lv_equal(v3, l1) << endl;
	cout << lv_equal(v4, l1) << endl;

	return 0;
}

//9.18
int main068()
{
	deque<string> d;
	string word;
	while (cin >> word)
		d.push_back(word);
	for (auto it = d.cbegin(); it != d.cend(); it++)
	{
		cout << *it << endl;
	}
	return 0;
}

//9.19
int main069()
{
	list<string> l;
	string word;
	while (cin >> word)
		l.push_back(word);
	for (auto it = l.cbegin(); it != l.cend(); it++)
	{
		cout << *it << endl;
	}
	return 0;
}

//9.20
int main070()
{
	list<int >l1 = { 1,2,3,4,5,6,7,8,9,10 };
	deque<int>d1, d2;
	for (auto lit = l1.cbegin(); lit != l1.end(); lit++)
	{
		if (*lit % 2 == 0)
			d2.push_back(*lit);
		else
			d1.push_back(*lit);
	}
	for (auto dit1 = d1.cbegin(); dit1 != d1.cend(); dit1++)
		cout << *dit1 << endl;
	for (auto dit2 = d2.cbegin(); dit2 != d2.cend(); dit2++)
		cout << *dit2 << endl;

	return 0;
}

//9.24
int main071()
{
	vector<int> v;
	//其他三个不会检查下标是否越界访问，直接运行报错
	cout << v[0] << endl;
	cout << v.at(0) << endl;//抛出异常，下标访问越界
	cout << v.front() << endl;
	cout << *v.cbegin() << endl;

	return 0;
}

//9.25
int main072()
{
	vector<int > v1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	v1.erase(v1.cbegin(), v1.cend());//第二个参数指向想删除范围迭代器的下一个位置
	cout << *v1.cbegin() << endl;
	return 0;
}


//9.26
int main073()
{
	int ia[] = { 0,1,1,2,3,5,8,13,21,55,89 };
	vector<int>v1;
	list<int>l1;
	v1.insert(v1.end(), ia, ia + 11);
	l1.assign(ia, ia + 11);
	auto vit = v1.cbegin();
	auto lit = l1.cbegin();
	while (vit != v1.cend())
	{
		if (!((*vit) & 1))//是偶数
		{
			vit = v1.erase(vit);
		}
		else vit++;
	}
	while (lit != l1.cend())
	{
		if ((*lit) & 1)//是偶数
		{
			lit = l1.erase(lit);
		}
		else lit++;
	}
	for (auto it = v1.cbegin(); it != v1.cend(); it++)
	{
		cout << *it << endl;
	}
	cout << endl;

	for (auto it = l1.cbegin(); it != l1.cend(); it++)
	{
		cout << *it << endl;
	}
	cout << endl;
	return 0;
}

//9.27
int main074()
{
	forward_list<int >fl1 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 14, 13, 15, 18 };
	auto prev = fl1.before_begin();//前驱元素
	auto curr = fl1.begin();//当前元素
	while (curr != fl1.end())
	{
		if (*curr & 1)
		{
			curr = fl1.erase_after(prev);
		}
		else
		{
			prev = curr;
			curr++;
		}
	}
	for (auto it = fl1.cbegin(); it != fl1.cend(); it++)
	{
		cout << *it << endl;
	}
	return 0;
}

//9.28
void find_and_insert(forward_list<string>& fl1, string& s1, string& s2)
{
	auto prev = fl1.before_begin();
	auto curr = fl1.begin();
	bool inserted = false;
	while (curr != fl1.end())
	{
		if (*curr == s1)
		{
			curr = fl1.insert_after(curr, s2);
			inserted = true;
		}

		prev = curr;
		curr++;

	}
	if (inserted = false)
		fl1.insert_after(prev, s2);
}

int main075()
{
	forward_list<string> fl1 = { "sdada","asdajdk","kkahfh","augdasuga","hello","akshkdd","askjdhakshd" };
	string s1 = "hello", s2 = "HELLO";
	find_and_insert(fl1, s1, s2);
	for (auto it = fl1.cbegin(); it != fl1.cend(); it++)
	{
		cout << *it << endl;
	}
	return 0;
}

//9.31
int main076()
{
	list<int>l1 = { 1,2,3,4,5,6,7,8,9,10 };
	auto iter = l1.begin();
	while (iter != l1.end())
	{
		if (*iter & 1)
		{
			iter = l1.insert(iter, *iter);
			iter++; iter++;
		}
		else
		{
			iter = l1.erase(iter);
		}
	}
	for (auto it = l1.cbegin(); it != l1.cend(); it++)
	{
		cout << *it << endl;
	}
	return 0;
}

int main077()
{
	forward_list<int> fl1 = { 1,2,3,4,5,6,7,8,9,10 };
	auto prev = fl1.before_begin();
	auto curr = fl1.begin();
	while (curr != fl1.end())
	{
		if (*curr & 1)
		{
			curr = fl1.insert_after(curr, *curr);
			prev = curr;
			curr++;
		}
		else
		{
			curr = fl1.erase_after(prev);
		}
	}
	for (auto it = fl1.cbegin(); it != fl1.cend(); it++)
	{
		cout << *it << endl;
	}

	return 0;
}

//9.38
int main078()
{
	vector<int> v1;
	int s, c;
	for (s = v1.size(), c = v1.capacity(); s <= c; s++)
		v1.push_back(1);
	cout << v1.size() << ' ' << v1.capacity() << ' ' << endl;

	for (s = v1.size(), c = v1.capacity(); s <= c; s++)
		v1.push_back(1);
	cout << v1.size() << ' ' << v1.capacity() << ' ' << endl;

	for (s = v1.size(), c = v1.capacity(); s <= c; s++)
		v1.push_back(1);
	cout << v1.size() << ' ' << v1.capacity() << ' ' << endl;

	for (s = v1.size(), c = v1.capacity(); s <= c; s++)
		v1.push_back(1);
	cout << v1.size() << ' ' << v1.capacity() << ' ' << endl;

	for (s = v1.size(), c = v1.capacity(); s <= c; s++)
		v1.push_back(1);
	cout << v1.size() << ' ' << v1.capacity() << ' ' << endl;
	for (s = v1.size(), c = v1.capacity(); s <= c; s++)
		v1.push_back(1);
	cout << v1.size() << ' ' << v1.capacity() << ' ' << endl;
	for (s = v1.size(), c = v1.capacity(); s <= c; s++)
		v1.push_back(1);
	cout << v1.size() << ' ' << v1.capacity() << ' ' << endl;
	for (s = v1.size(), c = v1.capacity(); s <= c; s++)
		v1.push_back(1);
	cout << v1.size() << ' ' << v1.capacity() << ' ' << endl;
	for (s = v1.size(), c = v1.capacity(); s <= c; s++)
		v1.push_back(1);
	cout << v1.size() << ' ' << v1.capacity() << ' ' << endl;
	for (s = v1.size(), c = v1.capacity(); s <= c; s++)
		v1.push_back(1);
	cout << v1.size() << ' ' << v1.capacity() << ' ' << endl;
	for (s = v1.size(), c = v1.capacity(); s <= c; s++)
		v1.push_back(1);
	cout << v1.size() << ' ' << v1.capacity() << ' ' << endl;
	return 0;
}

//9.41
int main079()
{
	vector<char> v1 = { 'h','e','l','l','0' };
	string s1(v1.data(), 5);
	string s2(v1.cbegin(), v1.cend());
	cout << s1 << endl << s2 << endl;
	return 0;
}

//9.43
void replace_string1(string& s1, const string& oldVal, const string& newVal)
{
	auto l1 = oldVal.size();
	if (l1 == 0)return;
	auto iter = s1.begin();
	while (iter <= s1.end() - 1)
	{
		auto iter1 = iter;
		auto iter2 = oldVal.begin();
		while (iter2 != oldVal.end() && *iter1 == *iter2)
		{
			iter1++;
			iter2++;
		}
		if (iter2 == oldVal.end())
		{
			iter = s1.erase(iter, iter1);
			if (newVal.size())
			{
				iter2 = newVal.end();
				do
				{
					iter2--;
					iter = s1.insert(iter, *iter2);
				} while (iter2 > newVal.begin());

			}
			iter += newVal.size();
		}
		else iter++;

	}

}

int main080()
{
	string s1 = { "tho thru tho!" };
	replace_string1(s1, "thru", "through");
	cout << s1 << endl;
	replace_string1(s1, "tho", "though");
	cout << s1 << endl;
	replace_string1(s1, "through", " ");
	cout << s1 << endl;
	return 0;
}

//9.44
void replace_string2(string& s1, const string& oldVal, const string& newVal)
{
	int p = 0;
	while ((p = s1.find(oldVal, p)) != string::npos)
	{
		s1.replace(p, oldVal.size(), newVal);
		p += newVal.size();
	}
}

int main081()
{
	string s1 = { "tho thru tho!" };
	replace_string2(s1, "thru", "through");
	cout << s1 << endl;
	replace_string2(s1, "tho", "though");
	cout << s1 << endl;
	replace_string2(s1, "through", " ");
	cout << s1 << endl;
	return 0;
}


//9.45
void add_name_string1(string& name, const string prefix, const string& suffix)
{
	name.insert(name.begin(), prefix.begin(), prefix.end());
	name.append(suffix.begin(), suffix.end());
}

int main082()
{
	string name1 = "James Harden";
	add_name_string1(name1, "Mr.", "II");
	cout << name1 << endl;

	return 0;
}

//9.46
void add_name_string2(string& name, const string prefix, const string& suffix)
{
	name.insert(0, prefix);
	name.insert(name.size(), suffix);
}
int main083()
{
	string name1 = "James Harden";
	add_name_string2(name1, "Mr.", "II");
	cout << name1 << endl;
	return 0;
}

//9.47
void find_char(string& s1, const string& chars)
{
	string::size_type pos = 0;
	while ((pos = s1.find_first_of(chars, pos)) != string::npos)
	{
		cout << s1[pos] << ':' << pos << endl;
		pos++;
	}

}
int main084()
{
	string s1 = "ab2c3d7r4e6";
	find_char(s1, "0123456789");
	find_char(s1, "abcdfghijklmnopqrstuvwxyz");
	return 0;
}

void find_longest(ifstream& ifs)
{
	string s1, longest;
	string::size_type maxsize = 0;
	while (ifs >> s1)
	{
		if (s1.find_first_of("bdfghjklpqty") != string::npos)
		{
			continue;
		}
		if (s1.size() > maxsize)
		{
			maxsize = s1.size();
			longest = s1;
		}
	}
	cout << longest << endl;

}

int main085()
{
	ifstream ifs("12345.txt");
	find_longest(ifs);
	return 0;
}

int main086()
{
	vector<string> v1 = { "123","200","30" };
	int sum = 0;
	for (auto it = v1.begin(); it != v1.end(); it++)
	{
		sum += stoi(*it);
	}
	cout << sum << endl;
	return 0;
}

int main087()
{
	vector<string> v1 = { "123.323","200.123","30.987" };
	double sum = 0;
	for (auto it = v1.begin(); it != v1.end(); it++)
	{
		sum += stod(*it);
	}
	cout << sum << endl;
	return 0;

}

//9.51
class date
{
public:
	friend ostream& operator<<(ostream& out, date& d);
	date() = default;
	date(string& ds);
	unsigned y()const { return year; }
	unsigned m()const { return month; }
	unsigned d()const { return day; }
private:
	unsigned year;
	unsigned month;
	unsigned day;
};

//月份全称
const string month_name[] = { "January","February","March","April","May","June","July",
							 "August","September","October","November","December" };

//月份简称
const string month_abbr[] = { "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sept",
							  "Oct","Nov","Dec" };

//每月天数
const int days[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

inline int get_month(string& ds, int& end_of_month)
{
	int i, j;
	for (i = 0; i < 12; i++)//检测是否为简称
	{
		for (j = 0; j < month_abbr[i].size(); j++)
		{
			if (ds[j] != month_abbr[i][j])break;
		}
		if (j == month_abbr[i].size())break;
	}
	if (i == 12)
		throw invalid_argument("不是合法月份名");//抛出异常（无效参数）
	if (ds[j] == ' ')
	{
		end_of_month = j + 1;
		return i + 1;
	}
	//因为全称长度大于简称，所以如果简称之后为空格就返回，否则进行全称检查
	for (; j < month_name[i].size(); j++)
	{
		if (ds[j] != month_name[i][j])
			break;
	}

	if (j == month_name[i].size() && ds[j] == ' ')
	{
		end_of_month = j + 1;//记录检测完月份之后的字符串下标
		return i + 1;
	}
	throw invalid_argument("不是合法月份名");
}

inline int get_day(string& ds, int month, int& p)
{
	size_t q;
	int day = stoi(ds.substr(p), &q);//从p开始的字符串转换为数值，并且保存第一个非数值字符的下标到q
	if (day<1 || day>days[month])
		throw invalid_argument("不是合法日期值");
	p += q;
	return day;
}

inline int get_year(string& ds, int& p)
{
	size_t q;
	int year = stoi(ds.substr(p), &q);
	if (p + q < ds.size())//如果结尾非年份，则q+p的长度绝对小于正常长度
		throw invalid_argument("非法结尾内容");
	return year;
}

date::date(string& ds)
{
	int p;
	size_t q;
	if ((p = ds.find_first_of("0123456789")) == string::npos)
		throw invalid_argument("没有数字，非法日期！");
	if (p > 0)
	{
		month = get_month(ds, p);
		day = get_day(ds, month, p);
		if (ds[p] != ' ' && ds[p] != ',')
			throw invalid_argument("非法间隔符");
		p++;
		year = get_year(ds, p);
	}
	else
	{
		month = stoi(ds, &q);
		p = q;
		if (month < 1 || month>12)
			throw invalid_argument("不是合法月份值");
		if (ds[p++] != '/')
			throw invalid_argument("不是合法月份值");
		day = get_day(ds, month, p);
		if (ds[p++] != '/')
			throw invalid_argument("不是合法月份值");
		year = get_year(ds, p);

	}

}

ostream& operator<<(ostream& out, date& d)
{
	out << d.y() << "年" << d.m() << "月" << d.d() << "日" << endl;
	return out;
}

int main088()
{
	string dates[] = { "Jan 1,2023","January 10,2023","10/29/2023" };
	try
	{
		for (auto c : dates)
		{
			date d(c);
			cout << d;
		}
	}
	catch (invalid_argument e)
	{
		cout << e.what() << endl;
	}
	return 0;
}
