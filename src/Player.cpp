#include "Player.hpp"
#include "Level.hpp"
#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif

const float velocity = 1.5f;
const float jumpVelocity = 5.0f;
const float gravity = 5.0f;

bool collide(int x, int y)
{
	int tile = level[x + y * 25];
	if (tile > 0)
	{
		return true;
	}
	else
		return false;
}

float degreeToRadian(float degree)
{
	return degree * (M_PI / 180);
}

bool Player::load(const std::string& file)
{
	_texture.loadFromFile(file);
	sf::IntRect rect(0, 0, 31, 51);
	sf::Sprite temp(_texture, rect);

	_rectSourceSprite = rect;
	_sprite = temp;

	m_soundBuffer.loadFromFile("content/ugh.wav");
	m_sound.setBuffer(m_soundBuffer);

	rocket.load("content/rocket.png");
	missile.load("content/missile2.png");

	kills = 0;
	health = 100.0f;
	angle = 0.0f;
	hut = sf::Vector2f(0, 0);

	_sprite.setPosition(100, 0);
	_sprite.setOrigin(0.0, 0.0);
	rocket.setPosition(100, 0);

	walkingRight = true;
	fallTime = 0.0f;
	jumped = false;
	falling = false;
	moving = false;
	mouseRight = true;
	pressedTrigger = false;
	bulletVelocity = 0.0f;
	shootAngle = 0.0f;
	timeShoot = 0.0f;
	return true;
}

void Player::animate()
{
	if (mouseRight)
	{
		if (!falling)
		{
			if (!moving)
			{
				_rectSourceSprite.top = 0;

				if (_rectSourceSprite.left >= 256 - 32)
					_rectSourceSprite.left = 0;
				else
					_rectSourceSprite.left += 32;
			}
			else if (walkingRight)
			{
				_rectSourceSprite.top = 102;

				if (_rectSourceSprite.left >= 256 - 32)
					_rectSourceSprite.left = 0;
				else
					_rectSourceSprite.left += 32;
			}
			else if (!walkingRight)
			{
				_rectSourceSprite.top = 102;

				if (_rectSourceSprite.left <= 0)
					_rectSourceSprite.left = 224;
				else
					_rectSourceSprite.left -= 32;
			}
		}
		else
		{
			_rectSourceSprite.top = 204;
			if (fallTime < 1.0 && jumped)
				_rectSourceSprite.left = 0;
			else
				_rectSourceSprite.left = 32;
		}
	}
	else
	{
		if (!falling)
		{
			if (!moving)
			{
				_rectSourceSprite.top = 51;

				if (_rectSourceSprite.left >= 256 - 32)
					_rectSourceSprite.left = 0;
				else
					_rectSourceSprite.left += 32;
			}
			else if (!walkingRight)
			{
				_rectSourceSprite.top = 153;

				if (_rectSourceSprite.left >= 256 - 32)
					_rectSourceSprite.left = 0;
				else
					_rectSourceSprite.left += 32;
			}
			else if (walkingRight)
			{
				_rectSourceSprite.top = 153;

				if (_rectSourceSprite.left <= 0)
					_rectSourceSprite.left = 224;
				else
					_rectSourceSprite.left -= 32;
			}
		}
		else
		{
			_rectSourceSprite.top = 204;
			if (fallTime < 1.0 && jumped)
				_rectSourceSprite.left = 96;
			else
				_rectSourceSprite.left = 64;
		}
	}

	_sprite.setTextureRect(_rectSourceSprite);
}

void Player::move(float time, sf::RenderWindow& window)
{
	float xPosition, yPosition;
	int i, j, k, l;
	bool collideX1 = false, collideX2 = false, collideY1 = false;
	moving = false;

	hut = sf::Vector2f(sf::Mouse::getPosition(window));
	hut.x = hut.x - _sprite.getPosition().x;
	hut.y = hut.y - _sprite.getPosition().y;
	angle = atan(hut.y / hut.x) * (180 / M_PI);
	bulletVelocity = sqrt(pow(hut.x, 2) + pow(hut.y, 2));
	if (hut.x < 0)
		angle += 180;
	else if (hut.x > 0 && hut.y < 0)
		angle += 360;

	for (i = 2; i <= 35; i++)
	{
		xPosition = _sprite.getPosition().x + 2.0f;
		yPosition = _sprite.getPosition().y + i;
		if (collide(int(xPosition / 48), int(yPosition / 48)))
		{
			// std::cout<<"wall"<<std::endl;
			collideX1 = true;
			break;
		}
	}
	for (k = 2; k <= 35; k++)
	{
		xPosition = _sprite.getPosition().x + 30.0f;
		yPosition = _sprite.getPosition().y + i;
		if (collide(int(xPosition / 48), int(yPosition / 48)))
		{
			collideX2 = true;
			break;
		}
	}
	for (j = 12; j <= 24; j += 12) //ceiling
	{
		xPosition = _sprite.getPosition().x + j;
		yPosition = _sprite.getPosition().y + 10.0f;
		if (collide(int(xPosition / 48), int(yPosition / 48)))
		{
			collideY1 = true;
			if (fallTime < 1.0f)
				fallTime = 1.0f;
			break;
		}
	}
	for (l = 8; l <= 26; l += 14) //ground
	{
		xPosition = _sprite.getPosition().x + l;
		yPosition = _sprite.getPosition().y + 50.0f;
		if (collide(int(xPosition / 48), int(yPosition / 48)))
		{
			// collideY2 = true;
			falling = false;
			moving = false;
			// std::cout << "ground"<<std::endl;
			break;
		}
		// moving = true;
		falling = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !collideX1)
	{
		_sprite.move(-velocity, 0.0f);
		walkingRight = false;
		moving = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !collideX2)
	{
		_sprite.move(velocity, 0.0f);
		walkingRight = true;
		moving = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !collideY1 && !jumped)
	{
		jumped = true;
		_sprite.move(0, -jumpVelocity);
		m_sound.play();
	}
	// if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && falling){
	// 	// jumped = true;
	// 	_sprite.move(0, velocity );
	// }

	// (void)time;
	if (jumped || falling)
	{
		fallTime += time;
		if (jumped && !collideY1)
			_sprite.move(0, -jumpVelocity + (gravity * fallTime));
		else
			_sprite.move(0, (gravity * fallTime));
	}
	if (!falling)
	{
		fallTime = 0.0f;
		jumped = false;
	}

	if (angle > 90 && angle < 270)
		mouseRight = false;
	else
		mouseRight = true;

	rocket.changeAngle(angle, _sprite.getPosition().x, _sprite.getPosition().y);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !pressedTrigger)
	{
		pressedTrigger = true;
		shootAngle = degreeToRadian(angle);
		missile.start(rocket.position(), mouseRight, shootAngle);
	}
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	(void)states;
	if (pressedTrigger)
		target.draw(missile);
	target.draw(rocket);
	target.draw(_sprite);
}

void Player::update(float time)
{
	// if(moving){
	// 	if(walkingRight){
	// 		animate(true, true);
	// 	}
	// 	else
	// 	{
	// 		animate(true, false);
	// 	}

	// }
	// else if(!moving){
	// 	if(walkingRight)
	// 		animate(false, true);
	// 	else
	// 		animate(false, false);
	// }
	// animate();
	if (pressedTrigger)
	{
		timeShoot += time;
		missile.travel(jumpVelocity * cos(shootAngle), (jumpVelocity * sin(shootAngle)) + (gravity * timeShoot));
	}
}