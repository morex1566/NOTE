#include <iostream>
#include <unordered_set>
#include <thread>


class ManagerObserver
{
public:
	void attachObserver(ManagerObserver* observer)
	{
		observers.insert(observer);
	}

	void detachObserver(ManagerObserver* observer)
	{
		observers.erase(observers.find(observer));
	}
private:
	std::unordered_set<ManagerObserver*> observers;
};

template <class T>
class Singleton
{
public:
	Singleton(const Singleton&) = delete;
	void operator=(const Singleton&) = delete;
	~Singleton(){}

	static T& getInstance()
	{
		static T instance;
		return instance;
	}
};

class Manager : public ManagerObserver
{
public:
	virtual ~Manager() = 0;

private:
	std::unordered_set<Manager*> managers;
};

class RenderManager : public Manager, public Singleton<RenderManager>
{
public:
	RenderManager() = default;
	~RenderManager() = default;
};

class GameObjectManager : public Manager, public Singleton<GameObjectManager>
{

};


int main()
{
	Manager& render_manager = RenderManager::getInstance();
}

//class Parent
//{
//public:
//	virtual ~Parent() {}
//
//	virtual void function()
//	{
//		std::cout << "parent";
//	}
//};
//
//class Child : public Parent
//{
//public:
//	void function() override
//	{
//		Parent::function();
//
//		std::cout << "child";
//	}
//};
//
//int main()
//{
//	Parent* parent = new Child();
//
//	parent->function();
//
//	delete parent;
//}
