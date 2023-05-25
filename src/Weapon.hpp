#pragma once
#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Weapon : public sf::Drawable, public sf::Transformable
{
public:

	bool load(const std::string &file);
	void changeAngle(float angle, float x, float y);
	sf::Vector2f position();

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Texture _texture;
	sf::Sprite _sprite;
	sf::IntRect _rectSourceSprite;

};

#endif