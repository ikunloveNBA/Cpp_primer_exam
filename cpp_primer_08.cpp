#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
using namespace std;

//8.1
istream& func001(istream& is)
{
	int v;
	while (is>>v,!is.eof())
	{
		if (is.bad())
		{
			throw runtime_error("IO流错误");

		}
		
		if (is.fail())
		{
			cerr << "数据错误请重试" << endl;
			is.clear();
			is.ignore(100, '\n');
			continue;
		}
		cout << v << endl;
	}
	is.clear();
	return is;
}

//8.4
void readFile01(const string fileName,vector<string>& v)
{
	string line;

	ifstream ifs;
	ifs.open(fileName);
	while (getline(ifs, line))
	{
		v.push_back(line);
	}
	ifs.close();
	/*for (vector<string>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << endl;
	}*/
}

void readFile02(const string fileName, vector<string>& v)
{
	string line;

	ifstream ifs;
	ifs.open(fileName);
	while (ifs>>line)
	{
		v.push_back(line);
	}
	ifs.close();
	for (vector<string>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << endl;
	}
}

//8.8
void printFile01(const string fileName, vector<string>& v)
{
	string line;
	ofstream ofs;
	ofs.open(fileName,ofstream ::out|ofstream::app);
	
	for (vector<string>::iterator it = v.begin(); it != v.end(); it++)
	{
		ofs << *it << endl;
	}
	ofs.close();
}

//8.8
int main058()
{
	vector<string> v;
	readFile01("12345.txt", v);
	printFile01("12345.txt", v);
	return 0;
}

//8.10
int main059()
{
	vector<string> v;
	readFile01("12345.txt", v);
	string item;
	
	for (vector<string>::iterator it = v.begin(); it != v.end(); it++)
	{
		istringstream iss(*it);
		iss >> item;
	}
	cout << item<< endl;

	return 0;
}

//8.11
int main060()
{
	vector<string> v;
	readFile01("12345.txt", v);
	string item;
	ostringstream ofs1;
	for (vector<string>::iterator it = v.begin(); it != v.end(); it++)
	{
		ofs1 << *it;
	}
	cout << ofs1.str() << endl;

	return 0;
}
