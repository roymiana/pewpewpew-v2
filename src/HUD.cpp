#include "HUD.hpp"

bool HUD::load(){
	//hudback
		hud_texture.loadFromFile("content/hud.png");
		hud_sprite.setTexture(hud_texture);
		hud_sprite.setOrigin(0.0, 0.0);
		hud_sprite.setPosition(0.0, 0.0);

		//healthbar
		bar_texture.loadFromFile("content/healthbar.png");
		bar_sprite.setTexture(bar_texture);
		bar_sprite.setOrigin(0.0, 0.0);
		bar_sprite.setPosition(300, 30);
		//bar_sprite.scale(0.5, 1);

		//second healthbar
		bars_texture.loadFromFile("content/healthbar.png");
		bars_sprite.setTexture(bars_texture);
		bars_sprite.setOrigin(0.0, 0.0);
		bars_sprite.setPosition(681, 30);

		//firstkill
		kfont.loadFromFile("content/font.otf");
		ktext.setFont(kfont);
		kk.str(std::string()); //clear the string
		kk << 0; //first.kills;
		ktext.setString(kk.str().c_str());
		ktext.setCharacterSize(22);
		ktext.setOrigin(0.0, 0.0);
		ktext.setPosition(192.0, 36.0);

		//second
		ksfont.loadFromFile("content/font.otf");
		kstext.setFont(ksfont);
		ks.str(std::string()); //clear the string
		ks << 0; //second.kills;
		kstext.setString(ks.str().c_str());
		kstext.setCharacterSize(22);
		kstext.setOrigin(0.0, 0.0);
		kstext.setPosition(985.5, 36.0);

		//gameclock
		ttFont.loadFromFile("content/font.otf");
		ttText.setFont(ttFont);
		tt.str(std::string()); //clear the string
		tt << 0; //deltaTime;
		ttText.setString(tt.str().c_str());
		ttText.setCharacterSize(22);
		ttText.setOrigin(0.0, 0.0);
		ttText.setPosition(571.5, 837.0);

		return true;
}

void HUD::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	(void)states;
	target.draw(hud_sprite);
	target.draw(ktext);
	target.draw(kstext);
	target.draw(bar_sprite);
	target.draw(bars_sprite);
	target.draw(ttText);
}