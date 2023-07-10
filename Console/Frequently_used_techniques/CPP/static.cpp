#include <iostream>
#include <string>

class Manager {
public:
	static int data;
};

int Manager::data = 4;

class ClassManager : public Manager {
public:

};

class WindowManager : public Manager {
public:

};

int main() {
    Manager manager;

    ClassManager* classManager = new ClassManager;
    WindowManager* windowManager = new WindowManager;

    std::cout << classManager->data;

    classManager->data  = 5;
    std::cout << windowManager->data;
    return 0;
}