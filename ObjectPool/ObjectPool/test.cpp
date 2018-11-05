#include<iostream>
#include<string>
#include"ObjectPool.hpp"

using namespace std;

struct BigObject
{
	BigObject(){}

	BigObject(int a){}

	BigObject(int a, int b) {}

	void print(const string& str)
	{
		cout << str << endl;
	}
};

void print(shared_ptr<BigObject> p, const string& str)
{
	if (p != nullptr)
	{
		p->print(str);
	}
}

int main()
{
	ObjectPool<BigObject> pool;

	pool.Init(2);
	{
		auto p1 = pool.Get();
		print(p1, "p1");
		auto p2 = pool.Get();
		print(p2, "p2");
	}

	auto p3 = pool.Get();
	print(p3, "p3");

	pool.Init(2, 1);
	auto p4 = pool.Get<int>();
	print(p4, "p4");

	pool.Init(2, 1, 1);
	auto p5 = pool.Get<int, int>();
	print(p5, "p5");

	getchar();
	getchar();
}