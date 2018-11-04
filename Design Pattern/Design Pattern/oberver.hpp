#include<list>
#include<map>



//Observer Pattern
class Subject;

class Observer {
public:
	virtual ~Observer() {}
	virtual void Update(Subject *subject) = 0;

protected:
	Observer() {}
};



class Subject {
public:
	virtual ~Subject() {}
	virtual void Attach(Observer *o)
	{
		_observers.push_back(o);
	}

	virtual void Detach(Observer *o)
	{
		_observers.remove(o);
	}

	virtual void Notify()
	{
		for (std::list<Observer*>::iterator it = _observers.begin(); it != _observers.end(); ++it)
		{
			(*it)->Update(this);
		}
	}

private:
	std::list<Observer*> _observers;
};




// improve Observer Pattern with C++11

class NonCopyable {
protected:
	NonCopyable() = default;
	~NonCopyable() = default;
	NonCopyable(const NonCopyable&) = delete;
	NonCopyable& operator = (const NonCopyable&) = delete;
};

template<typename Func>
class Event :NonCopyable {
public:
	Event()
	{}

	int Connect(const Func&& f)
	{
		return Assign(f);
	}

	int Connect(const Func& f)
	{
		return Assign(f);
	}

	void Disconnect(int key)
	{
		m_connections.erase(key);
	}

	template<typename... Args>
	void Notify(Args&&... args)
	{
		for (auto& it : m_connections)
		{
			it.second(std::forward<Args>(args)...);
		}
	}
private:
	template<typename F>
	int Assign(F&& f)
	{
		int k = m_observerID++;
		m_connections.emplace(k, std::forward<F>(f));
		return k;
	}

private:
	int m_observerID = 0;
	std::map<int, Func> m_connections;
};