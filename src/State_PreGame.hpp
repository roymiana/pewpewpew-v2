#pragma once
#ifndef STATE_PRE_GAME_HPP
#define STATE_PRE_GAME_HPP

#include "StateManager.hpp"
#include "PrePlayer.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

struct Name
{
	std::string labels[4] = { "Abel", "Cain", "Player 1", "Player 2" };
	sf::Text txt[4], ready[3];
	sf::Font font;
};

class StatePreGame : public State {
public:
    StatePreGame(StateManager& stateManager, sf::RenderWindow& window);
    ~StatePreGame();

    void pause();
    void resume();

    void processEvents();
    void update(const sf::Time& dt);
    void draw();
	void setname(sf::Sprite keeper, sf::Sprite brother);
private:
	sf::Texture m_background;
	sf::Sprite m_backSprite;
	sf::RectangleShape m_filter;

	sf::SoundBuffer m_soundBuffer;
	sf::Sound m_sound;

	PrePlayer Abel;
	PrePlayer Cain;

	Name name;

	int currentState; //0 = both not ready , 1 =  one is ready, 2 = 2 is ready,  3 = start
	float m_timePassed;
};

#endif