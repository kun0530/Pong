#include "pch.h"
#include "Bat.h"

Bat::Bat(const std::string& name) : GameObject(name)
{
}

void Bat::Update(float dt)
{
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
