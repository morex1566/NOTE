#include "Achievement.h"

#include <iostream>

#include "Player.h"


// TODO : 만약에, 도전과제를 추가해야한다면? OnNotify()를 수정해야 하는건가?
// 그러면 확장성에 있어서 문제가되는게 아닌가?
// 이부분에 대해서 어떻게 해결해야하는가?
void Achievement::OnNotify(void (Player::*function)())
{
    if(function == &Player::Attack && !achievement_.isFirstAttack)
    {
        std::cout << "Achievement : FirstAttack" << std::endl;
        achievement_.isFirstAttack = true;
        
    }

    if(function == &Player::Jump && !achievement_.isFirstJump)
    {
        std::cout << "Achievement : FirstJump" << std::endl;
        achievement_.isFirstJump = true;

    }

    if(function == &Player::Duck && !achievement_.isFirstDucking)
    {
        std::cout << "Achievement : FirstDuck" << std::endl;
        achievement_.isFirstDucking = true;

    }
}

void Achievement::OnNotify(std::function<void()> function)
{
    
}
