#include "pch.h"
#include "Bat.h"
#include "Ball.h"

Ball::Ball(Bat& b, const sf::FloatRect& bounds)
	: bat(b), windowBounds(bounds)
{
	shape.setRadius(10.f);
	shape.setPosition({ 1920.f / 2.f, 1080.f - 100.f });
	shape.setFillColor(sf::Color::White);
	Utils::SetOrigin(shape, Origins::BC);
}

void Ball::Fire(sf::Vector2f d, float s)
{
	direction = d;
	speed = s;
	isDead = false;
}

void Ball::Update(float dt)
{
	isBoundBat = false;

	sf::Vector2f prevPos = shape.getPosition();
	sf::Vector2f pos = prevPos;
	pos += direction * speed * dt;
	shape.setPosition(pos);



	// window 충돌 처리(숙제)
	const sf::FloatRect& ballBounds = shape.getGlobalBounds();
	float ballLeft = ballBounds.left;
	float ballRight = ballBounds.left + ballBounds.width;
	float ballTop = ballBounds.top;
	float ballBottom = ballBounds.top + ballBounds.height;

	float windowLeft = windowBounds.left;
	float windowRight = windowBounds.left + windowBounds.width;
	float windowTop = windowBounds.top;
	float windowBottom = windowBounds.top + windowBounds.height;

	// 방법1. 충돌 시 공을 직접 프레임의 위치로 조정
	if (ballBottom > windowBottom + 300.f)
	{
		isDead = true;
	}
	else if (ballTop < windowTop)
	{
		shape.setPosition(prevPos);
		direction.y *= -1.f;
	}
	else if (ballLeft < windowLeft || ballRight > windowRight)
	{
		shape.setPosition(prevPos);
		direction.x *= -1.f;
	}
	// 방법2. direction에 방향 조건으로 조절
	//if (ballTop < windowTop && direction.y < 0.f) // 위쪽 충돌
	//{
	//	direction.y *= -1.f;
	//}
	//if (ballBottom > ballBottom && direction.y > 0.f) // 아래쪽 충돌
	//{
	//	direction.y *= -1.f;
	//}
	//if (ballLeft < windowLeft && direction.x < 0.f) // 왼쪽 충돌
	//{
	//	direction.x *= -1.f;
	//}
	//if (ballRight > windowRight && direction.x > 0.f) // 오른쪽 충돌
	//{
	//	direction.x *= -1.f;
	//}

	// bat 충돌 처리
	const sf::FloatRect& batBounds = bat.shape.getGlobalBounds();
	if (ballBounds.intersects(batBounds) && direction.y > 0)
	{
		float batLeft = batBounds.left;
		float batRight = batBounds.left + batBounds.width;
		float batTop = batBounds.top;
		float batBottom = batBounds.top + batBounds.height;

		if (ballBottom > batTop || ballTop < batBottom)
		{
			direction.y *= -1.f;
		}
		else if (ballLeft > batRight || ballRight < batLeft)
		{
			direction.x *= -1.f;
		}
		shape.setPosition(prevPos);
		isBoundBat = true;
	}
}

void Ball::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}
