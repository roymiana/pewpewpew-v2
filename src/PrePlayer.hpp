#pragma once
#ifndef PREGAME_PLAYER_HPP
#define PREGAME_PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class PrePlayer : public sf::Drawable, public sf::Transformable
{
public:

	bool load(const std::string& file);
	void setPosition(float, float);
	void setOrigin(float, float);
	void setScale(float, float);
	void animate();
	sf::Sprite sprite();

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Texture _playerTexture;
	sf::IntRect _playerRect;
	sf::Sprite _playerSprite;
};


#endif