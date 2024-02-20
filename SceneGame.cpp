#include "pch.h"
#include "SceneGame.h"
#include "Bat.h"
#include "Ball.h"

SceneGame::SceneGame(SceneIds id) : Scene(id)
{
}

void SceneGame::Init()
{
	RES_MGR_FONT.Load("fonts/DS-DIGI.ttf");

	bat = new Bat("Bat");
	bat->SetSize({ 100.f, 5.f });
	bat->SetPosition({ FRAMEWORK.GetWindowSize().x / 2.f, FRAMEWORK.GetWindowSize().y - 100.f });
	bat->SetFillColor(sf::Color::White);
	bat->SetOrigin(Origins::TC);

	ball = new Ball("Ball");
	ball->SetPosition({ FRAMEWORK.GetWindowSize().x / 2.f,
		FRAMEWORK.GetWindowSize().y - 100.f });
	ball->SetFillColor(sf::Color::White);
	ball->SetOrigin(Origins::BC);
	AddGo(ball);
}

void SceneGame::Release()
{
	Scene::Release();
}

void SceneGame::Enter()
{
	isDead = false;
	isBallActive = false;
	isBoundBat = false;
	isCollisionBat = false;

	windowBounds = { { 0.f, 0.f }, { FRAMEWORK.GetWindowSize().x, FRAMEWORK.GetWindowSize().y } };
}

void SceneGame::Exit()
{
}

void SceneGame::Update(float dt)
{
	isBoundBat = false;

	if (!isBallActive && InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		ball->Fire({ 1.f, -1.f }, 1000.f);
		isBallActive = true;
	}

	float h = InputMgr::GetAxisRaw(Axis::Horizontal);
	sf::Vector2f batPos = bat->GetPosition();
	batPos.x += h * batSpeed * dt;
	bat->SetPosition(batPos);

	sf::Vector2f ballPrevPos = ball->GetPosition();
	sf::Vector2f ballPos = ballPrevPos;
	ballPos += ballDir * ballSpeed * dt;
	ball->SetPosition(ballPos);

	const sf::FloatRect& ballBounds = ball->GetGlobalBounds();
	float ballLeft = ballBounds.left;
	float ballRight = ballBounds.left + ballBounds.width;
	float ballTop = ballBounds.top;
	float ballBottom = ballBounds.top + ballBounds.height;

	float windowLeft = windowBounds.left;
	float windowRight = windowBounds.left + windowBounds.width;
	float windowTop = windowBounds.top;
	float windowBottom = windowBounds.top + windowBounds.height;

	if (ballBottom > windowBottom + 300.f)
	{
		isDead = true;
	}
	else if (ballTop < windowTop)
	{
		ball->SetPosition(ballPrevPos);
		ballDir.y *= -1.f;
	}
	else if (ballLeft < windowLeft || ballRight > windowRight)
	{
		ball->SetPosition(ballPrevPos);
		ballDir.x *= -1.f;
	}

	const sf::FloatRect& batBounds = bat->GetGlobalBounds();
	if (ballBounds.intersects(batBounds))
	{
		if (!isCollisionBat)
		{
			float batLeft = batBounds.left;
			float batRight = batBounds.left + batBounds.width;
			float batTop = batBounds.top;
			float batBottom = batBounds.top + batBounds.height;

			if (ballBottom > batTop || ballTop < batBottom)
			{
				ballPrevPos.y *= -1.f;
			}
			else if (ballLeft > batRight || ballRight < batLeft)
			{
				ballPrevPos.x *= -1.f;
			}
			ball->SetPosition(ballPrevPos);
			isBoundBat = true;
			isCollisionBat = true;
		}
	}
	else
	{
		isCollisionBat = false;
	}
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
