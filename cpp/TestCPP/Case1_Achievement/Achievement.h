#pragma once
#include "Observer.h"


struct ActionAchievement
{
    bool isFirstAttack = false;
    bool isFirstJump = false;
    bool isFirstDucking = false;
};

class Player;

class Achievement : public Observer
{
public:
    Achievement() = default;
    ~Achievement() override = default;
    
    void OnNotify(void (Player::*function)()) override;
    void OnNotify(std::function<void()> function) override;

private:
    ActionAchievement achievement_;
};