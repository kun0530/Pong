#pragma once
#include "Scene.h"

class Bat;
class Ball;

class SceneGame : public Scene
{
private:
	Bat* bat;

	Ball* ball;
	sf::Vector2f ballDir = { 0.f, 0.f };
	float ballSpeed = 0.f;

	sf::FloatRect windowBounds;

public:
	SceneGame(SceneIds id);

	bool isDead = false;
	bool isBallActive = false;
	bool isBoundBat = false;
	bool isCollisionBat = false;

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};