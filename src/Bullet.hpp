#pragma once
#ifndef BULLET_HPP
#define BULLET_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

class Bullet : public sf::Drawable, public sf::Transformable
{
public:

	bool load(const std::string &file);
	void start(sf::Vector2f pos, bool right, float angle);
	void travel(float x, float y);
	bool collided(sf::Vector2f pos);
	sf::Vector2f getPosition();
private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Texture _texture;
	sf::Sprite _sprite;

};

#endif