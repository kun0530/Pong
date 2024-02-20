#pragma once
#include "GameObject.h"

class Bat : public GameObject
{
protected:

public:
	// public���� �����ؼ� �ٱ����� �а� �� �� �ְ� ����
	sf::RectangleShape shape;

	Bat(const std::string& name);

	void Update(float dt);
	void Draw(sf::RenderWindow& window);

	void SetSize(const sf::Vector2f size);
	void SetFillColor(const sf::Color color);

	const sf::FloatRect& GetGlobalBounds() { return shape.getGlobalBounds(); }
};

