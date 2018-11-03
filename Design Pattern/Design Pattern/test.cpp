#include"singleton.hpp"
#include<string>
#include<iostream>

using namespace std;

int main()
{
	Singleton<string>::Instance("singleton");
	cout << *Singleton<string>::GetInstance();
	Singleton<string>::DestroyInstace();
	getchar();
	getchar();
}