#pragma once

class Bat
{
protected:

public:
	// public���� �����ؼ� �ٱ����� �а� �� �� �ְ� ����
	float spped = 100.f;
	sf::RectangleShape shape;



	void Init();
	void Update(float dt);
	void Draw(sf::RenderWindow& window);
};

