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

        if (ball.isDead)
        {
            isBallActive = true;
            ball.Fire({ 0.f, 0.f }, 0.f);
            // 게임 재시작 대기
        }
        else if (ball.isBoundBat)
        {
            // 점수 추가
        }

        // 방향키 테스트 코드
        // std::cout << InputMgr::GetAxisRaw(Axis::Horizontal) << ", " << InputMgr::GetAxis(Axis::Horizontal) << std::endl;

        // 마우스 좌표 테스트 코드(숙제)
        /*sf::Vector2f mousePos = InputMgr::GetMousePos();
        std::cout << mousePos.x << ", " << mousePos.y << std::endl;*/

        // 마우스 좌, 우 클릭 테스트 코드
        if (InputMgr::GetMouseButton(sf::Mouse::Right))
            std::cout << "!!!!!" << std::endl;
        if (InputMgr::GetMouseButtonUp(sf::Mouse::Left))
            std::cout << "?????" << std::endl;
        if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
            std::cout << ";;;;;" << std::endl;

        window.clear();
        bat.Draw(window);
        ball.Draw(window);
        window.display();
    }

    return 0;
}