#pragma once
#ifndef STATE_INTRO_HPP
#define STATE_INTRO_HPP

#include "StateManager.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class StateIntro : public State {
public:
    StateIntro(StateManager& stateManager, sf::RenderWindow& window);
    ~StateIntro();

    void pause();
    void resume();

    void processEvents();
    void update(const sf::Time& dt);
    void draw();
private:
	//intro title
	sf::Texture m_introTexture;
	sf::Sprite m_introSprite;
	//intro background
	sf::Texture m_background;
	sf::Sprite m_backSprite;
	//intro font
	sf::Font m_font;
	sf::Text m_text;
	//intro music
	sf::Music theme;

	float m_timePassed;
	bool timeIsPassed;
};

#endif