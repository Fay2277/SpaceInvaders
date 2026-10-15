#pragma once
#include <SFML/Graphics.hpp>

class Ship : public sf::Sprite 
{
public:
	Ship();
	Ship(const Ship& s);
	Ship(sf::IntRect ir);

	virtual ~Ship() = 0;
	virtual void update(const float& dt);
	virtual void explode();
	virtual void move_down();

	bool is_exploded() const;

	float explosion_time = 0.1f;

protected:
	sf::IntRect _sprite;
	bool _exploded = false;
};

class Invader : public Ship
{
public:
	Invader();
	Invader(const Invader& inv);
	Invader(sf::IntRect ir, sf::Vector2f pos);
	void update(const float& dt) override;

	static bool direction;
	static float speed;
	static float firetime;
};

class Plazer : public Ship
{
public: 
	Player();
	void update(const float& dt) override;
	void move_down() override {}
	static float firetime;
	static constexpr int speed = 100.f;
};

