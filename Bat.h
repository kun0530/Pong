#pragma once

class Bat
{
protected:

public:
	// public���� �����ؼ� �ٱ����� �а� �� �� �ְ� ����
	float speed = 300.f;
	sf::RectangleShape shape;

	Bat();


	void Update(float dt);
	void Draw(sf::RenderWindow& window);
};

