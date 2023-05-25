#include "PrePlayer.hpp"

#define RATIO 1.28

bool PrePlayer::load(const std::string& file){
	_playerTexture.loadFromFile(file);

	sf::IntRect rectSource(0, 0, 57, 102);
	sf::Sprite spriteSouce(_playerTexture, rectSource);

	_playerRect = rectSource;
	_playerSprite = spriteSouce;
	return true;
}

void PrePlayer::setPosition(float x, float y){
	_playerSprite.setPosition(x, y);
}

void PrePlayer::setOrigin(float x, float y){
	_playerSprite.setOrigin(x, y);
}

void PrePlayer::setScale(float x, float y){
	_playerSprite.setScale(x, y);
}

void PrePlayer::animate(){
	// std::cout<<"Here"<<std::endl;
	if(_playerRect.left >= 684 -57)
		_playerRect.left = 0;
	else{
		_playerRect.left += 57;

	_playerSprite.setTextureRect(_playerRect);
	}
}

void PrePlayer::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	(void)states;
	target.draw(_playerSprite);
}

sf::Sprite PrePlayer::sprite(){
	return _playerSprite;
}