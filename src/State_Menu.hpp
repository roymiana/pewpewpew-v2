#pragma once
#ifndef STATE_MENU_HPP
#define STATE_MENU_HPP

#include "StateManager.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class StateMenu : public State {
public:
    StateMenu(StateManager& stateManager, sf::RenderWindow& window);
    ~StateMenu();

    void pause();
    void resume();

    void processEvents();
    void update(const sf::Time& dt);
    void draw();
private:
	sf::Font m_font;
	sf::Text m_text;

	sf::Texture m_background;
	sf::Sprite m_backSprite;
	sf::Texture m_tutexture;
	sf::Sprite m_tutoSprite;

	sf::Vector2f m_buttonSize;
	sf::Vector2f m_buttonPos;
	unsigned int m_buttonPadding;

	sf::RectangleShape m_rects[3];
	sf::Text m_labels[3];

	sf::Music theme1;

	int currentState;

	sf::Texture t_credit;
	sf::Sprite t_sprite;

	void isHovered();
	int isClicked();
};

#endif