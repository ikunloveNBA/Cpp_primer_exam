#include<iostream>
#include<string>
#include<stdexcept>
using namespace std;

//5.9,5.10
int main043()
{
	char c;
	int cnt = 0;
	while (cin >> c)
	{
		if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
			++cnt;
	}
	cout << cnt << endl;
	return 0;
}

//5.14
int main044()
{
	string currVal, val;
	int cnt = 1, cnt1 = 0;
	if (cin >> currVal)
	{
		while (cin >> val)
		{
			if (currVal == val)
			{
				++cnt;
				++cnt1;
			}
			else
			{
				if (cnt > 1)
					cout << currVal << " occurs repeatly " << cnt << endl;

				cnt = 1;
				currVal = val;
			}
		}
		if (cnt != 0)
			cout << currVal << " occurs repeatly " << cnt << endl;
		if (cnt1 == 0)
			cout << "no repeat word" << endl;
	}

	return 0;
}

//5.20
int main045()
{
	string s1, tmp;
	int cnt = 0;
	while (cin >> s1)
	{
		if (tmp == s1)
		{
			++cnt;
			break;
		}
		tmp = s1;
	}
	if (cnt == 0)
		cout << "no repeat word" << endl;
	return 0;
}

//try
int main046()
{
	string s1, s2;
	while (cin >> s1 >> s2)
	{
		try
		{
			if (s1 != s2)
				throw runtime_error("String must refer to be same");
		}
		catch (runtime_error err)
		{
			cout << err.what()
				 << "\nTry Again? Enter y or n" << endl;

			char c;
			cin >> c;

			if (!cin || c == 'n')
				break;
		}

	}
	return 0;
}

//5.23 5.24 5.25
int main047()
{
	int a, b;
	while (cin >> a >> b)
	{
		try
		{
			if (b == 0)
			{
				throw runtime_error("除数不能为0");
			}
			cout << a / b << endl;
		}
		catch (runtime_error err)
		{
			cout << err.what() << endl;
			cout << "需要重新开始吗？(y or n)" << endl;
			char c;
			cin >> c;
			if (c != 'y')
			{
				break;
			}
		}
	
	}
	
	return 0;
}
