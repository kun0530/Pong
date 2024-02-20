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



	// window �浹 ó��(����)
	const sf::FloatRect& ballBounds = shape.getGlobalBounds();
	// ���1. �浹 �� ���� ���� �������� ��ġ�� ����
	/*if (ballBounds.top < windowBounds.top ||
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
	}*/
	// ���2. direction�� ���� �������� ����
	if (ballBounds.top < windowBounds.top && direction.y < 0.f) // ���� �浹
	{
		direction.y *= -1.f;
	}
	if (ballBounds.top + ballBounds.height > windowBounds.top + windowBounds.height && direction.y > 0.f) // �Ʒ��� �浹
	{
		direction.y *= -1.f;
	}
	if (ballBounds.left < windowBounds.left && direction.x < 0.f) // ���� �浹
	{
		direction.x *= -1.f;
	}
	if (ballBounds.left + ballBounds.width > windowBounds.left + windowBounds.width && direction.x > 0.f) // ������ �浹
	{
		direction.x *= -1.f;
	}

	// bat �浹 ó��
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
