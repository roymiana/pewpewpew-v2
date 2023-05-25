#pragma once
#ifndef HUD_HPP
#define HUD_HPP

#include <SFML/Graphics.hpp>
#include <sstream>

class HUD : public sf::Drawable, public sf::Transformable
{
public:

	bool load();

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	//total time
	sf::Font ttFont;
	sf::Text ttText;
	std::stringstream tt;

	//hud
	sf::Texture hud_texture;
	sf::Sprite hud_sprite;

	//healthbar first
	sf::Texture bar_texture;
	sf::Sprite bar_sprite;

	//healthbar second
	sf::Texture bars_texture;
	sf::Sprite bars_sprite;

	//kills first player
	sf::Font kfont;
	sf::Text ktext;
	std::stringstream kk;

	//kills second
	sf::Font ksfont;
	sf::Text kstext;
	std::stringstream ks;
};

#endif