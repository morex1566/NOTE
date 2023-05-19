#pragma once
#include "Observer.h"

// TODO : 만약에, 도전과제를 추가해야한다면? OnNotify()를 수정해야 하는건가?
// 그러면 확장성에 있어서 문제가되는게 아닌가?
// 이부분에 대해서 어떻게 해결해야하는가?
struct ActionAchievement
{
    bool isFirstAttack = false;
    bool isFirstJump = false;
    bool isFirstDucking = false;
};

class Achievement : public Observer
{
public:
    void OnNotify() override;

private:
    ActionAchievement achievement_;
};