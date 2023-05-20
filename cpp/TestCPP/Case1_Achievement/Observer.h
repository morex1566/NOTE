#pragma once
#include <functional>
#include <memory>

class Player;

class Observer
{
public:
    
    virtual ~Observer() = default;

    /**
     * @remark Function Pointer를 사용하는 경우
     */
    virtual void OnNotify(void (Player::*function)()) = 0;

    /**
     * @remark std::function을 사용하는 경우
     */
    virtual void OnNotify(std::function<void()> function) = 0;
};