#pragma once

class Bat
{
protected:

public:
	// public으로 노출해서 바깥에서 읽고 쓸 수 있게 설정
	float spped = 100.f;
	sf::RectangleShape shape;



	void Init();
	void Update(float dt);
	void Draw(sf::RenderWindow& window);
};

