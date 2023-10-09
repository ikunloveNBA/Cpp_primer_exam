#include<iostream>

//2.3
int main009()
{
	unsigned u = 10, u2 = 42;
	std::cout << u2 - u << std::endl;//大减小，正数
	std::cout << u-u2 << std::endl;//-32转换为无符号数相当于无符号数最大值减32，2^32-32

	int i = 10, i2 = 42;
	std::cout << i2-i << std::endl;
	std::cout << i-12 << std::endl;
	std::cout << i-u << std::endl;
	std::cout << u-i << std::endl;

	return 0;
}

//2.10
std::string global_str;//初始化空串
int global_int;//初始化为0
int main010()
{
	//int local_int;//未定义，出错
	std::string global_str;//空串
	return 0;
}
//2.11
//extern int ix =1024      定义
//int iy                   声明并定义
//extern int iz            声明

//2.17
int main011()//都是10
{
	int i, & ri = i;
	i = 5; ri = 10;
	std::cout << i << "" << ri << std::endl;
	return 0;
}

//2.23
//一般都是合法的，可以判断指针是否为空，也可以设置抛出异常

//2.33
int main012()
{	int i = 0, & r = i;
	auto a = r;

	const int ci = i, & cr = ci;
	auto b = ci;
	auto c = cr;
	auto d = &i;
	auto e = &ci;
	auto& g = ci;

	a = 42;//a是整型
	b = 42;//忽略顶层const，整型
	c = 42;//忽略顶层const，整型
	//d = 42;整型指针
	//e = 42;保留底层const，指向常量的指针，不能改
	//g = 42;整型常量引用，不能改
	return 0;
}

//2.36
int main013()
{
	int a = 3, b = 4;
	decltype(a) c = a;//c是整型
	decltype ((b)) d = a;//d是整型引用
	++c;//c=4,a=3
	++d;//a=4，b=4,c=4，d=4
	std::cout << a << ' '<<b<<' '<< c << ' ' << d << std::endl;
	return 0;
}

//书店程序将在第七章编写，此处不再重复用struct编写
