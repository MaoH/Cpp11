#include"singleton.hpp"
#include"oberver.hpp"
#include<string>
#include<iostream>
#include<functional>

using namespace std;

void testSingleton()
{
	Singleton<string>::Instance("singleton");
	cout << *Singleton<string>::GetInstance() << endl;;
	Singleton<string>::DestroyInstace();
}

void print(int a, int b)
{
	cout << a << ends << b << endl;
}

void testObserver()
{
	Event<std::function<void(int, int)>> myEvent;
	int k1 = myEvent.Connect([](int a, int b) {cout << a << ends << b << endl; });
	int k2 = myEvent.Connect(std::bind(print, std::placeholders::_1, std::placeholders::_2));
	myEvent.Notify(1, 2);
	myEvent.Disconnect(k1);
	myEvent.Disconnect(k2);
}


int main()
{
	testSingleton();
	testObserver();
	getchar();
	getchar();
}