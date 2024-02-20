#include "pch.h"
#include "Bat.h"

Bat::Bat(const std::string& name) : GameObject(name)
{
}

void Bat::Update(float dt)
{
	// Å° ÀÔ·Â
	float h = InputMgr::GetAxisRaw(Axis::Horizontal);
	sf::Vector2f pos = shape.getPosition();
	pos.x += h * speed * dt;
	shape.setPosition(pos);
}

void Bat::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

void Bat::SetSize(const sf::Vector2f size)
{
	shape.setSize(size);
}

void Bat::SetFillColor(const sf::Color color)
{
	shape.setFillColor(color);
}
