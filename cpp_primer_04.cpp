#include<iostream>
#include<string>
#include<vector>
using namespace std;

//4.10
int main039()
{
	int a;
	while (cin >> a && a != 42)
	{
		cout << a << endl;
	}
	return 0;
}

//4.11
int main040()
{
	int a, b, c, d;
	while (cin >> a >> b >> c >> d && a > b && b > c && c > d)
	{
		cout << a <<' '<< b <<' '<< c <<' '<< d << endl;
	}
	return 0;
}

//4.21
int main041()
{
	vector<int>v1 = { 1,2,3,4,5,6,7,8,9,10 };
	for (auto it = v1.begin(); it != v1.end(); ++it)
	{
		*it = (*it % 2 == 1) ? 2 * *it : *it;
		cout << *it << endl;
	}
	return 0;
}

//4.22
// finalrade = ( grade > 30 ) ? "high pass"
//                             : ( grade > 75 ) ? "low pass" 
//                             : ( grade > 60 ) ? "pass" : "fail"

//4.28
int main042()
{
	cout << sizeof(char) << endl;
	cout << sizeof(int) << endl;
	cout << sizeof(int*) << endl;
	cout << sizeof(int&) << endl;
	cout << sizeof(float) << endl;
	cout << sizeof(double) << endl;
	cout << sizeof(long) << endl;
	cout << sizeof(long long) << endl;
	cout << sizeof(unsigned) << endl;
	cout << sizeof(unsigned char) << endl;

	return 0;
}
