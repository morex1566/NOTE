#include "Player.h"

#include <iostream>

void Player::Attack()
{
    std::cout<< "Attacking" << std::endl;

    for (auto& observer : observers)
    {
        // TODO : 여기서 attack()함수를 하드코딩으로 넘기지 말고 현재 실행중인 함수의 타입과 주소정보를 통해 전달하면 좋지 않을까?
        observer.lock()->OnNotify(&Player::Attack);
    }
}

void Player::Jump()
{
    std::cout << "Jumping" << std::endl;
}

void Player::Duck()
{
    std::cout << "Ducking" << std::endl;
}
