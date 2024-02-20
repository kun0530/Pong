#pragma once
#include "GameObject.h"

class Ball : public GameObject
{
protected:
	sf::CircleShape shape;
	float speed = 0.f;
	sf::Vector2f direction = { 0.f, 0.f };

public:
	Ball(const std::string& name);

	void SetFillColor(const sf::Color color);
	const sf::FloatRect& GetGlobalBounds() { return shape.getGlobalBounds(); }

	void Fire(sf::Vector2f d, float s);

	void Update(float dt);
	void Draw(sf::RenderWindow& window);
};

