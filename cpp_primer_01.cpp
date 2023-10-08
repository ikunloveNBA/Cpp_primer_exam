#include<iostream>

//1.3
int main001()
{
	std::cout << "Hello,World" << std::endl;
	return 0;
}

//1.4
int main002()
{
	int x = 2, y = 3;
	std::cout << x << '*' << y << '=' << x * y << std::endl;
	return 0;
}

//1.5
int main003()
{
	int x = 2, y = 3;
	std::cout << "The multiplication of " << x << " and " << y << " is " << x * y << std::endl;
	return 0;
}

//1.9
int main004()
{
	int i = 50, sum = 0;
	while (i <= 100)
	{
		sum += i;
		++i;
	}
	std::cout << sum << std::endl;
	return 0;
}

//1.10
int main005()
{
	int i = 10;
	while (i >= 0)
	{
		std::cout << i << std::endl;
		--i;
	}
	return 0;
}

//1.11
int main006()
{
	std::cout << "please enter two integers" << std::endl;
	int m = 0, n = 0;
	std::cin >> m >> n;
	while (m < n - 1)
	{
		std::cout << ++m << std::endl;
	}
	return 0;
}

//1.16
int main007()
{
	int i = 0, sum = 0;
	while (std::cin >> i)
	{
		sum += i;		
	}
	std::cout << sum << std::endl;
	return 0;
}

//1.17
int main()//不管输入值相等还是不重复，输出都正常
{
	int currVal = 0, val = 0, cnt = 0;
	if (std::cin >> currVal)
	{
		++cnt;
		while (std::cin >> val)
		{
			if (currVal == val)
			{
				++cnt;
			}
			else
			{
				std::cout << currVal << " occurs " << cnt << std::endl;
				currVal = val;
				cnt = 1;
			}
			
		}
		std::cout << currVal << " occurs " << cnt << std::endl;
		
	}
	return 0;
}

//第一张后续习题由于没有头文件所以不再编写，Sales_item的书店程序完整类会在后续章节写完
