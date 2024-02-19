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

	sf::Vector2f pos = shape.getPosition();
	pos += direction * speed * dt;
	shape.setPosition(pos);



	// window 面倒 贸府(槛力)
	const sf::FloatRect& ballBounds = shape.getGlobalBounds();
	if (ballBounds.top < windowBounds.top ||
		ballBounds.top + ballBounds.height > windowBounds.top + windowBounds.height)
	{
		pos -= direction * speed * dt;
		shape.setPosition(pos);
		direction.y *= -1.f;
	}
	if (ballBounds.left < windowBounds.left ||
		ballBounds.left + ballBounds.width > windowBounds.left + windowBounds.width)
	{
		pos -= direction * speed * dt;
		shape.setPosition(pos);
		direction.x *= -1.f;
	}

	// bat 面倒 贸府
	const sf::FloatRect& batBounds = bat.shape.getGlobalBounds();
	if (ballBounds.intersects(batBounds) && direction.y > 0)
	{
		direction.y *= -1.f;
		isBoundBat = true;
	}
}

void Ball::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}
