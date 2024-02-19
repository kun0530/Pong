#include "pch.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "Pong");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    InputMgr::Init();

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

        // 테스트 코드
        std::cout << InputMgr::GetAxisRaw(Axis::Horizontal) << ", " <<
            InputMgr::GetAxis(Axis::Horizontal) << std::endl;

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}