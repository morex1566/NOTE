#pragma once
#include <memory>
#include <vector>

#include "Observer.h"


class Player
{
public:
    void Attack();
    void Jump();
    void Duck();

public:
    /**
     * TODO : Template의 조건설정할 때, 어떤 네임스페이스 안에 있는 class만 가능하도록 설정해보자
     */
    std::vector<std::weak_ptr<Observer>> observers;
};
