/*
	warning	: 'friend' keyword는 상속받지 않습니다.
	해결	: 각각 개별적으로 선언해줘야 합니다.
	의미	: 'friend'는 상속받지 않습니다.
			 1. 부모의 친구라고 해서, 자식의 친구라는 주장은 모호합니다.
             2. 개별적으로 친구를 선언해줘야 합니다.
*/

#include <iostream>

class ParentFrined;
class Son;
class Parent;

class ParentFrined
{
    friend class Parent;
private:
    int data = 4;
};

class Parent
{
public:
    ParentFrined pf = ParentFrined();

    void function()
    {
        pf.data;
    }
};

class Son : public Parent
{
    void function()
    {
        // warning triggered!
        //pf.data;
    }
};