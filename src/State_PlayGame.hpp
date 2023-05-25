#pragma once
#ifndef STATE_PLAY_GAME_HPP
#define STATE_PLAY_GAME_HPP

#include "StateManager.hpp"
#include "TileMap.hpp"
#include "Level.hpp"
#include "HUD.hpp"
#include "Player.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class StatePlayGame : public State {
public:
    StatePlayGame(StateManager& stateManager, sf::RenderWindow& window);
    ~StatePlayGame();

    void pause();
    void resume();

    void processEvents();
    void update(const sf::Time& dt);
    void draw();
	void setname(sf::Sprite keeper, sf::Sprite brother);
private:
	TileMap battleground;
    HUD hud;
    Player Abel;

	sf::Texture m_background;
	sf::Sprite m_backSprite;
    float m_timePassed; //fps
};

#endif