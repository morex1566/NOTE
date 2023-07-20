// dead lock practice
// how to solve?
// 1. atomic - > low performance + low expansion
// 2. mutex

#include <iostream>
#include <string>
#include <thread>
#include <atomic>
#include <vector>
#include <mutex>


using int32 = unsigned __int32;
int32 g_data1 = 0;
std::atomic<int32> g_data2 = 0;

void add()
{
	for (int i =0; i < 100'000; i++)
	{
		g_data1++;
		g_data2.fetch_add(1);
	}
}

void sub()
{
	for (int i = 0; i < 100'000; i++)
	{
		g_data1--;
		g_data2.fetch_sub(1);
	}
}


std::vector<int32> v1;
std::vector<int32> v2;
std::mutex m;

// 실수할 수 있으니, 스마트 mutex를 생성합니다
// RAII
// SFINAE
template <typename T> using IsMutex = std::enable_if_t<std::is_base_of<std::mutex, T>::value, T>;
template <typename T, typename = IsMutex<T>>
class smart_mutex // std::lock_guard
{
public:
	smart_mutex(T& m)
	{
		mutex = &m;

		mutex->lock();
	}

	~smart_mutex()
	{
		mutex->unlock();
	}

	T* mutex;
};


void push()
{
	for (int i = 0; i < 10'000; i++)
	{
		v1.push_back(i);
	}

	// 현재 mutex는 재귀적으로 실행할 수 없도록 만들어져 있습니다.
	// 가급적 mutex가 재귀적으로 만들어질 수 있어야 합니다. 복잡한 프로젝트일 수록, mutex안에서 겹치는 경우가 발생하기 때문에
	for (int i = 0; i < 10'000; i++)
	{
		smart_mutex<std::mutex> sm(m);
		// m.lock() -> error!
		v2.push_back(i);
		// m.unlock() -> error!
	}
}


// 좀 더 실무적인 dead lock Error?
// dead lock의 해결책 ? : 순차적으로 mutex를 사용하도록 제어한다 
// graph에서 cycle이 일어나는걸로 dead lock을 체크할 수 있다.



int main()
{
	std::thread t1(add);
	std::thread t2(sub);

	t1.join();
	t2.join();

	std::cout << g_data1 << std::endl;
	std::cout << g_data2 << std::endl;



	std::thread t3(push);
	std::thread t4(push);

	v1.reserve(100'000);
	v2.reserve(100'000);

	t3.join();
	t4.join();

	std::cout << v1.size() << std::endl;
	std::cout << v2.size() << std::endl;

}