#include "Bullet.hpp"
#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif

bool Bullet::load(const std::string& file)
{
	_texture.loadFromFile(file);
	_sprite.setTexture(_texture);
	_sprite.setPosition(0, 0);
	_sprite.setOrigin(0, 5.5f);
	return true;
}

void Bullet::start(sf::Vector2f pos, bool right, float angle)
{
	_sprite.setPosition(pos.x + (30 * cos(angle)), pos.y + (30 * sin(angle)));
	if (right)
		_sprite.setScale(-1, 1);
	else
		_sprite.setScale(1, 1);
}

void Bullet::travel(float x, float y)
{
	float angle = atan(y / x) * (180 / M_PI);
	if (x < 0)
		angle += 180;
	else if (x > 0 && y < 0)
		angle += 360;
	_sprite.setRotation(angle);
	_sprite.move(x, y);
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	(void)states;
	target.draw(_sprite);
}

sf::Vector2f Bullet::getPosition()
{
	return _sprite.getPosition();
}
