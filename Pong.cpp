#include "pch.h"
#include "Bat.h"
#include "Ball.h"

int main()
{
    FRAMEWORK.Init(1920, 1080, "Pong");
    FRAMEWORK.Do();
    FRAMEWORK.Release();

    InputMgr::Init();
    Bat bat;

    bool isBallActive = false;

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Time deltaTime = clock.restart();
        float dt = deltaTime.asSeconds();
        InputMgr::Clear();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            InputMgr::UpdateEvent(event);
        }
        InputMgr::Update(dt);

        bat.Update(dt);

        if (!isBallActive)
        {
            ball.shape.setPosition(bat.shape.getPosition());
        }
        else
        {
            ball.Update(dt);
        }

        if (ball.isDead)
        {
            isBallActive = false;
            ball.Fire({ 0.f, 0.f }, 0.f);
            // 게임 재시작 대기
        }
        else if (ball.isBoundBat)
        {
            // 점수 추가
        }

        window.clear();
        bat.Draw(window);
        ball.Draw(window);
        window.display();
    }

    return 0;
}