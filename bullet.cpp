#include <iostream>
#include "game_system.hpp"
#include "game_parameters.hpp"
#include "bullet.hpp"

using gs = GameSystem;
using param = Parameters;

unsigned char Bullet::_bulletPointer;
Bullet Bullet::_bullets[256];

Bullet::Bullet()
{
}

void Bullet::update(const float& dt)
{
	for(int i = 0; i < 256; ++i)
	{
		_bullets[i]._update(dt);
	}
}

void Bullet::render(sf::RenderWindow& window)
{
	for (int i = 0; i < 256; ++i)
		window.draw(_bullets[i]);
}

void Bullet::fire(const sf::Vector2f& pos, const bool mode)
{
	Bullet& bullet = _bullets[++_bulletPointer];
	if(mode)
		bullet.setTextureRect(sf::IntRect(sf::Vector2i(param::sprite_size, param::sprite_size), 
		sf::Vector2i(param::sprite_size, param::sprite_size)));
	else
		bullet.setTextureRect(sf::IntRect(sf::Vector2i(param::sprite_size * 2, param::sprite_size),
			sf::Vector2i(param::sprite_size, param::sprite_size)));
	bullet.setPosition(pos);
	bullet._mode = mode;
}

void Bullet::init()
{
	for (int i = 0; i < 256; ++i)
	{
		_bullets[i].setTexture(gs::spritesheet);
		_bullets[i].setOrigin(param::sprite_size / 2.f, param::sprite_size / 2.f);
		_bullets[i].setPosition(-100.f, -100.f);
	}
}

void Bullet::_update(const float& dt)
{
	if(getPosition().y <- param::sprite_size || getPosition().y > param::gameHeight + param::sprite_size)
	{
		return;
	}
	else
	{
		move(sf::Vector2f(0, dt * param::bullet_speed * (_mode ? -1.0f : 1.0f)));
		const sf::FloatRect boundingBox = getGlobalBounds();
		std::shared_ptr<Ship>& player = gs::ships[0];
		for(std::shared_ptr<Ship>& s : gs::ships)
		{
			if (_mode && s == player)
			{
				continue;
			}

			if(!_mode && s != player)
			{
				continue;
			}

			if (!s->is_exploded() &&
				s->getGplobalBounds().intersects(boundingBox))
			{
				s->explode();
				setPosition(sf::Vector2f(-100, -100));
				return;
			}
		}
	}
}