/*
 *  목표 : Observer pattern, factory pattern에 대해서 학습
 */


#include "Achievement.h"
#include "Player.h"

int main(int argc, char* argv[])
{
    auto achievement = std::make_shared<Achievement>();
    
    auto player = Player();
    {
        player.observers.emplace_back(achievement);
        player.Attack();
        player.Attack();
    }

    
    return 0;
}
