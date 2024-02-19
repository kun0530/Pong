#include "pch.h"
#include "Ball.h"

Ball::Ball(Bat& b, const sf::FloatRect& bounds)
	: bat(bat), windowBounds(bounds)
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
}

void Ball::Update(float dt)
{
	sf::Vector2f pos = shape.getPosition();
	pos += direction * speed * dt;
	shape.setPosition(pos);



	// 충돌 처리
}

void Ball::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}
