#include"impl.cpp"
#include<iostream>


template <typename T>
detail_range::impl<T> range(T end)
{
	return{ {}, end, 1 };
}

template <typename T>
detail_range::impl<T> range(T begin, T end)
{
	return{ begin ,end, 1 };
}

template <typename T, typename U>
auto range(T begin, T end, U steps) -> detail_range::impl<decltype(begin + steps)>
{
	using r_t = detail_range::impl<decltype(begin + steps)>;
	return r_t(begin, end, steps );
}


int main()
{
	using namespace std;

	for (auto i : range(15))
	{
		cout << i << ends;
	}
	cout << endl;
	for (auto i : range(1, 15))
	{
		cout << i << ends;
	}
	cout << endl;
	for (auto i : range(0, 15, 2))
	{
		cout << i << ends;
	}
	cout << endl;
	for (auto i : range('a', 'z'))
	{
		cout << i << ends;
	}
	cout << endl;
	for (auto i : range(0, 1, 0.1))
	{
		cout << i << ends;
	}
	cout << endl;
	getchar();
	getchar();
}