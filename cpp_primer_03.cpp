#define _CRT_SECURE_NO_WARNINGS//所有习题均用vs2022编译并通过，cstring中有很多不安全的函数，加这个头文件不报错
#include<iostream>
#include<string>
#include<vector>
#include<cstring>
using namespace std;

//3.2
int main014()
{
	string line;
	while (getline(cin, line))
	{
		cout << line << endl;
	}
	return 0;
}

int main015()
{
	string line;
	while (cin>>line)
	{
		cout << line << endl;
	}
	return 0;
}

//3.4
int main016()
{
	string s1, s2, s3;
	cin >> s1 >> s2;
	if (s1 != s2)
	{
		s3 = (s1 > s2) ? s1 : s2;
		cout << s3 << endl;
	}
	return 0;
}

int main017()
{
	string s1, s2, s3;
	cin >> s1 >> s2;
	if (s1.size() != s2.size())
	{
		s3 = (s1.size() > s2.size()) ? s1 : s2;
		cout << s3 << endl;
	}
	return 0;
}

//3.5
int main018()
{
	string s1, s2;
	while (cin>>s1)
	{
		s2 += s1;
		s2 = s2 + ' ';
	}
	cout << s2 << endl;

	return 0;
}

//3.6
int main019()
{
	string s1;
	cin >> s1;
	for (auto& c : s1)
	{
		c = 'X';
	}
	cout << s1 << endl;
	return 0;
}

//3.7
int main020()//改成char没区别
{
	string s1;
	cin >> s1;
	for (char& c : s1)
	{
		c = 'X';
	}
	cout << s1 << endl;
	return 0;
}

int main021()
{
	string s1, s2;
	cin >> s1;
	for (auto c : s1)
	{
		if (!ispunct(c))
		{
			s2 += c;
		}
	}
	cout << s2 << endl;
	return 0;
}

//3.14
int main022()
{
	int a, b = 0;
	vector<int> v1;
	while (cin >> a)
	{
		v1.push_back(a);
		cout << v1[b++] << endl;
	}
	
	return 0;
}

//3.15
int main023()
{
	int b = 0;
	string a;
	vector<string> v1;
	while (cin >> a)
	{
		v1.push_back(a);
		cout << v1[b++] << endl;
	}

	return 0;
}

//3.17
int main024()
{
	string s1;
	vector<string> v1;
	while (cin >> s1)
	{
		for (auto& c : s1)
		{
			c = toupper(c);
		}
		v1.push_back(s1);
	}
	for (vector<string>::iterator it = v1.begin(); it != v1.end(); it++)
	{
		cout << *it << endl;
	}
	return 0;
}

//3.20
int main025()
{
	int n;
	vector<int> v1;
	while (cin >> n)
	{
		v1.push_back(n);
	}
	for (decltype(v1.size()) i = 0; i < v1.size() - 1; i+=2)
	{
		cout << v1[i] + v1[i + 1] << endl;
	}
	if (v1.size() % 2 != 0)
	{
		cout << v1[v1.size() - 1] << endl;
	}
	return 0;
}

int main026()
{
	int n;
	vector<int> v1;
	while (cin >> n)
	{
		v1.push_back(n);
	}
	for (decltype(v1.size()) i = 0; i < v1.size()/2; i++)
	{
		cout << v1[i] + v1[v1.size()-1-i] << endl;
	}
	if (v1.size() % 2 != 0)
	{
		cout << v1[v1.size()/2] << endl;
	}
	return 0;
}

//3.23
int main027()
{
	vector<int>v1;
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i);
	}
	for (auto it = v1.begin(); it != v1.end() && !v1.empty(); it++)
	{
		*it = *it * 2;
	}
	for (auto it = v1.begin(); it != v1.end() && !v1.empty(); it++)
	{
		cout << *it << endl;
	}
	return 0;
}

//3.31
int main028()
{
	int arr[10] = { 0 };
	for (int i = 0; i < 10; i++)
	{
		arr[i] = i;
	}
	for (int i = 0; i < 10; i++)
	{
		cout << arr[i] << endl;
	}
	return 0;
}

//3.32
int main029()
{
	int arr[10] = { 0 }, arr1[10] = {0};
	for (int i = 0; i < 10; i++)
	{
		arr[i] = i;
		arr1[i] = arr[i];
	}
	
	return 0;
}
//3.35
int main030()
{
	int arr[10] = { 1,2,3,4,5,6,7,8,9,0 };
	int* p = arr;
	while (p < &arr[10])
	{
		*(p++) = 0;
	}
	for (int i = 0; i < 10; i++)
	{
		cout << arr[i] << endl;
	}
	return 0;
}

int main031()
{
	int arr[10] = { 1,2,3,4,5,6,7,8,9,0 };
	int* beg = begin(arr), * last = end(arr);
	while (beg!=last)
	{
		*(beg++) = 0;
	}
	for (int i = 0; i < 10; i++)
	{
		cout << arr[i] << endl;
	}
	return 0;
}

int main032()
{
	string s1= "asdgdadasd";
	string s2 = "asdfhskdhkshsdfksfhs";
	char c1[] = "kahskahdkashd", c2[] = "alsjdlaslasjdlajashjkdah";
	if (s1 == s2)
	{
		cout << "相等" << endl;
	}
	else if (s1 > s2)
	{
		cout << "大于" << endl;
	}
	else if (s1 < s2)
	{
		cout << "小于" << endl;
	}

	if (strcmp(c1, c2) == 0)
	{
		cout << "等于" << endl;
	}
	else if (strcmp(c1, c2) > 0)
	{
		cout << "大于" << endl;
	}
	else
	{
		cout << "小于" << endl;
	}
	return 0;
}

//3.40
int main033()//strcpy等函数不安全，编译通过记得加宏定义 #define _CRT_SECURE_NO_WARNINGS
{
	char c1[] = "askhdashdasjhjad";
	char c2[] = "SKDJAHDASKHDKAKASJ";
	char* c3 = new char[strlen(c1) + strlen(c2)+1];//C++11后数组必须使用常量确定大小，如果想在运行时确定大小只能动态分配
	strcpy(c3, c1);
	strcat(c3, c2);
	cout << c3 << endl;
	delete[] c3;
	return 0;
}

//3.41
int main034()
{
	int arr[10] = { 1,2,3,4,5,6,7,8,9,0 };
	vector<int> v1(begin(arr), end(arr));
	for (auto it = v1.begin(); it != v1.end(); it++)
	{
		cout << *it << endl;
	}
	return 0;
}

//3.42
int main035()
{
	vector<int> v1;
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i);
	}
	int arr[10] = {0};
	auto it = v1.begin();
	for (auto& c : arr)
	{
		c = *it;
		it++;
		cout << c << endl;
	}
	return 0;
}

//3.43
int main036()
{
	int ia[5][3] = { {1,2,3},{7,8,9},{7,6,5},{3,6,7},{8,7,0} };

	//版本1
	for (int (& row)[3] : ia)
	{
		for (int &col : row)
			cout << col << ' ';
		cout << endl;
	}

	//版本2
	for (int i=0;i<5;i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << ia[i][j] << ' ';
		}
		cout << endl;
	}

	//版本3
	for (int (*p)[3]=ia;p!=ia+5;p++)
	{
		for (int* q = *p; q != *p + 3; q++)//p是数组的指针，解引用后是数组，q是数组首地址
		{
			cout << *q << ' ';
		}
		cout << endl;
	}
	return 0;
}

//3.44
using my_array = int[3];
//或typedef int array[3];
int main037()
{
	int ia[5][3] = { {1,2,3},{7,8,9},{7,6,5},{3,6,7},{8,7,0} };

	//版本1
	for (my_array &row : ia)
	{
		for (int& col : row)
			cout << col << ' ';
		cout << endl;
	}

	//版本2
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << ia[i][j] << ' ';
		}
		cout << endl;
	}

	//版本3
	for (my_array *p = ia; p != ia + 5; p++)
	{
		for (int* q = *p; q != *p + 3; q++)//p是数组的指针，解引用后是数组，q是数组首地址
		{
			cout << *q << ' ';
		}
		cout << endl;
	}
	return 0;
}

//3.45
int main038()
{
	int ia[5][3] = { {1,2,3},{7,8,9},{7,6,5},{3,6,7},{8,7,0} };

	//版本1
	for (auto &row: ia)
	{
		for (int& col : row)
			cout << col << ' ';
		cout << endl;
	}

	//版本2
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << ia[i][j] << ' ';
		}
		cout << endl;
	}

	//版本3
	for (auto p= ia; p != ia + 5; p++)
	{
		for (int* q = *p; q != *p + 3; q++)//p是数组的指针，解引用后是数组，q是数组首地址
		{
			cout << *q << ' ';
		}
		cout << endl;
	}
	return 0;
}
