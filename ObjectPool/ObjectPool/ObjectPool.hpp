#include<string>
#include<functional>
#include<memory>
#include<map>

using namespace std;

const int MaxObjectNum = 10;

template<typename T>
class ObjectPool{
	template<typename... Args>
	using Constructor = std::function<std::shared_ptr<T>(Args...)>;

public:
	template<typename... Args>
	void Init(size_t num, Args&&... args)
	{
		if (num <= 0 && num > MaxObjectNum)
		{
			throw std::logic_error("object num is out of range./n");
		}
		auto constructName = typeid(Constructor<Args...>).name();
		for (size_t i = 0; i < num; ++i)
		{
			object_map.emplace(constructName, shared_ptr<T>(new T(std::forward<Args>(args)...), [this, constructName](T* p)
			{
				object_map.emplace(std::move(constructName), shared_ptr<T>(p));
			}));
		}
	}

	template<typename... Args>
	std::shared_ptr<T> Get()
	{
		string constructName = typeid(Constructor<Args...>).name();
		auto range = object_map.equal_range(constructName);
		for (auto it = range.first; it != range.second; it++)
		{
			auto ptr = it->second;
			object_map.erase(it);
			return ptr;
		}
		return nullptr;
	}

private:
	multimap<string, std::shared_ptr<T>> object_map;
};