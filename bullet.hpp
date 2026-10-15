#pragma once
#include <SFML/Graphics.hpp>

class Bullet : public sf::Sprite 
{
public: 

	static void update(const float &dt);

	static void render(sf::RenderWindow& window);

	static void fire(const sf::Vector2f& pos, const bool mode);

	static void init();

	~Bullet() = default;

protected:
		
	Bullet();
	bool _mode;

	void _update(const float& dt);
	static unsigned char _bulletPointer;
	static Bullet _bullets[256];
};



