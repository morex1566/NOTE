class ManagerObserver
{
public:
	virtual void notify()
	{

	}
	
private:
	std::vector<ManagerObserver*> observers;
};

template <class T>
class Singleton
{
public:
	Singleton(const Singleton&) = delete;
	Singleton operator=(const Singleton&) = delete;
	~Singleton(){}

	static T& getInstance()
	{
		static T instance;
		return instance;
	}

private:
	Singleton() {}
};

class Manager abstract : public ManagerObserver
{
public:
	virtual ~Manager() = 0;

private:
	std::vector<Manager*> managers;
};

class RenderManager : public Manager
{
	
};


int main()
{
	
}
