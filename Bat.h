#pragma once
#include "GameObject.h"

class Bat : public GameObject
{
protected:

public:
	// public으로 노출해서 바깥에서 읽고 쓸 수 있게 설정
	sf::RectangleShape shape;

	Bat(const std::string& name);

	void Update(float dt);
	void Draw(sf::RenderWindow& window);

	void SetSize(const sf::Vector2f size);
	void SetFillColor(const sf::Color color);

	const sf::FloatRect& GetGlobalBounds() { return shape.getGlobalBounds(); }
};

