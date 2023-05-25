#include "Weapon.hpp"

bool Weapon::load(const std::string& file){
	_texture.loadFromFile(file);
	sf::IntRect rect(0, 0, 54, 21);
	sf::Sprite temp(_texture, rect);

	_rectSourceSprite = rect;
	_sprite = temp;
	_sprite.setOrigin(21, 10.5f);
	return true;
}

void Weapon::changeAngle(float angle, float x, float y){
	_sprite.setRotation(angle);
	// std::cout<<angle<<std::endl;
	if(angle > 90 && angle < 270){
		_sprite.setScale(1, -1);
	}
	else{

		_sprite.setScale(1, 1);
	}

	_sprite.setPosition(x+14, y +20);

}

sf::Vector2f Weapon::position(){
	return _sprite.getPosition();
}

void Weapon::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	(void)states;
	target.draw(_sprite);
}
