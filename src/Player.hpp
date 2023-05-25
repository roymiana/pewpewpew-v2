#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Weapon.hpp"
#include "Bullet.hpp"
#include <iostream>
#include <math.h>

class Player : public sf::Drawable, public sf::Transformable
{
public:

	bool load(const std::string &file);
	void animate();
	void move(float time, sf::RenderWindow& window);
	void update(float time);

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Texture _texture;
	sf::Sprite _sprite;
	sf::IntRect _rectSourceSprite;

	sf::SoundBuffer m_soundBuffer;
	sf::Sound m_sound;

	Weapon rocket;
	Bullet missile;

	bool moving;
	bool walkingRight;
	bool falling;
	float fallTime;
	bool jumped;
	float angle;
	bool mouseRight;
	sf::Vector2f hut;

	bool pressedTrigger;
	float bulletVelocity;
	float shootAngle;
	float timeShoot;

	//states
	int kills;
	float health;

};

bool collide(int x, int y);
float degreeToRadian(float);

#endif