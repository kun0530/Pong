#include "pch.h"
#include "Bat.h"
#include "Ball.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Pong");

    InputMgr::Init();

    Bat bat;
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

        // 테스트 코드
        // std::cout << InputMgr::GetAxisRaw(Axis::Horizontal) << ", " << InputMgr::GetAxis(Axis::Horizontal) << std::endl;
        // 숙제 테스트 코드
        // std::cout << InputMgr::GetMousePos().x << ", " << InputMgr::GetMousePos().y << std::endl;

        window.clear();
        bat.Draw(window);
        window.display();
    }

    return 0;
}