#include "pch.h"
#include "Bat.h"
#include "Ball.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Pong");

    InputMgr::Init();
    Bat bat;
    Ball ball(bat, { { 0.f, 0.f }, { 1920.f, 1080.f } });

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

        if (!isBallActive && InputMgr::GetKeyDown(sf::Keyboard::Space))
        {
            ball.Fire({ 1.f, -1.f }, 1000.f);
            isBallActive = true;
        }

        bat.Update(dt);

        if (!isBallActive)
        {
            ball.shape.setPosition(bat.shape.getPosition());
        }
        ball.Update(dt);

        // InputMgr 테스트 코드
        // std::cout << InputMgr::GetAxisRaw(Axis::Horizontal) << ", " << InputMgr::GetAxis(Axis::Horizontal) << std::endl;
        // 숙제 테스트 코드
        // std::cout << InputMgr::GetMousePos().x << ", " << InputMgr::GetMousePos().y << std::endl;

        window.clear();
        bat.Draw(window);
        ball.Draw(window);
        window.display();
    }

    return 0;
}