#pragma once
#ifndef GAME_HPP
#define GAME_HPP

#include "State_Intro.hpp"

class Game {
public:
    Game() {}
    void run();
private:
    static const sf::Time TimePerFrame;

    StateManager m_stateManager;
    sf::RenderWindow m_window;
};

#endif