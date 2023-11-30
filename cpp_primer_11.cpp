#include<iostream>
#include<map>
#include<utility>
#include<string>
#include<set>
#include<algorithm>
#include<numeric>
#include<vector>
#include<fstream>
#include<sstream>
using namespace std;

//11.15
int main112()
{
	map<int, string>m1;
	string s1 = "adasds";
	m1.insert({ 1,s1 });
	m1.insert(make_pair(2,s1));
	m1.insert(pair<int, string>(1, s1));
	m1.insert(map<int, string>::value_type(1, s1));
	return 0;
}

//11.16
int main113()
{
	map<string, size_t>word_count;
	string word;
	while (cin >> word)
	{
		auto ret = word_count.insert({ word,1 });
		if (!ret.second)//map的insert返回一个pair，first是一个map迭代器，second是bool表示是否插入成功
		{
			++ret.first->second;//计数器加1
		}
	}
	return 0;
}

//11.17
int main114()
{
	multimap<int, string>m1;
	m1.insert({ 1,"asda" });
	m1.insert({ 1,"dadasadasd" });
	map<int, string>m2;
	
	return 0;
}

//11.18
int main115()
{
	multimap<int, string>m1;
	m1.insert({ 1,"asdasd" });
	m1.insert({ 1,"kasdhkaj" });
	m1.insert({ 1,"akjsdha" });
	m1.insert({ 1,"kuwhehqwui" });
	auto it = m1.find(1);
	auto mit = m1.count(1);
	while (mit--)
	{
		cout << it->second << endl;
		it++;
	}
	return 0;
}

//11.19
int main116()
{
	multimap<int, string>m1;
	m1.insert({ 1,"asdasd" });
	m1.insert({ 1,"kasdhkaj" });
	m1.insert({ 1,"akjsdha" });
	m1.insert({ 1,"kuwhehqwui" });
	for (auto beg = m1.lower_bound(1); beg != m1.upper_bound(1); beg++)
	{
		cout << beg->second << endl;
	}
	return 0;
}


//.11.20
int main117()
{
	multimap<int, string>m1;
	m1.insert({ 1,"asdasd" });
	m1.insert({ 1,"kasdhkaj" });
	m1.insert({ 1,"akjsdha" });
	m1.insert({ 1,"kuwhehqwui" });
	for (auto it = m1.equal_range(1); it.first != it.second; it.first++)
	{
		cout << it.first->second << endl;
	}
	return 0;
}


//11.31
int main118()
{
	multimap<string, string>m1;
	m1.insert({ "mark","asdsaf" });
	m1.insert({ "mark","khfhdfhs" });
	m1.insert({ "mark","iuqhewiuqwh" });
	m1.insert({ "mark","hasga" });
	m1.insert({ "juce","qkwheqwh" });
	m1.insert({ "juce","czkjhjka" });
	m1.insert({ "juce","qwheqwehw" });
	m1.insert({ "jack","jadfkakjf" });
	m1.insert({ "jack","qjeqhwhe" });
	m1.insert({ "jack","qkwewqhuiwuh" });
	m1.insert({ "jack","dabjk" });
	m1.erase(m1.find("juce"));
	cout << m1.erase("juce") << endl;
	for (auto it = m1.begin(); it != m1.end(); it++)
	{
		cout << it->first << ':' << it->second << endl;
	}
	return 0;
}


bool compare01(const pair<string,string>&lhs,const pair<string,string>&rhs)
{
	return lhs.second < rhs.second;
}

//11.32
int main119()
{
	multimap<string, string>m1;
	m1.insert({ "mark","asdsaf" });
	m1.insert({ "mark","khfhdfhs" });
	m1.insert({ "mark","iuqhewiuqwh" });
	m1.insert({ "mark","hasga" });
	m1.insert({ "juce","qkwheqwh" });
	m1.insert({ "juce","czkjhjka" });
	m1.insert({ "juce","qwheqwehw" });
	m1.insert({ "jack","jadfkakjf" });
	m1.insert({ "jack","qjeqhwhe" });
	m1.insert({ "jack","qkwewqhuiwuh" });
	m1.insert({ "jack","dabjk" });
	vector<pair<string, string>> v1(m1.begin(), m1.end());
	sort(v1.begin(), v1.end(), compare01);
	for (auto it = v1.begin(); it != v1.end(); it++)
	{
		cout << it->first << ":" << it->second << endl;
	}
	return 0;
}

//11.33
map<string, string>buildMap(ifstream& file)//建立单词转换规则
{
	map<string, string>trans_map;
	string key;
	string value;
	while (file>>key&&getline(file,value))
	{
		if (!key.empty())
		{
			trans_map[key] = value.substr(1);
		}
		else
			throw runtime_error("no rule for" + key);
	}
	return trans_map;
}

const string& transform(const string& s, map<string, string>& m)//生成转换文本
{
	auto it = m.find(s);
	if (it != m.cend())
	{
		return it->second;
	}
	return s;
}

void word_transform(ifstream&file,ifstream& input)//输出转换文本
{
	map<string, string>trans_map = buildMap(file);
	string text;
	while (getline(input,text))
	{
		istringstream stream(text);
		string word;
		while (stream>>word)
		{
			cout << transform(word, trans_map) << ' ';
		}
		cout << endl;
	}

}

int main120()
{
	ifstream ifs1("123.txt"), ifs2("1234.txt");
	word_transform(ifs1,ifs2);
	return 0;
}

