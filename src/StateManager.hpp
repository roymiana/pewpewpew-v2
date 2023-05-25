#pragma once
#ifndef STATE_MANAGER_HPP
#define STATE_MANAGER_HPP

#define WINDOW_HEIGHT 1200
#define WINODW_WIDTH 900

#include <stack>
#include <memory>

#include "State.hpp"

class StateManager {
public:
    StateManager();
    ~StateManager();

    void pushState(std::unique_ptr<State> state);
    void popState();
    void changeState(std::unique_ptr<State> state);

    void processEvents();
    void update(sf::Time dt);
    void draw();

    std::unique_ptr<State> getCurrentState() { return std::move(m_states.top()); }

    bool running()                           { return m_running; }
    void quit()                              { m_running = false; }
private:
    std::stack<std::unique_ptr<State>> m_states;
    bool m_running;
};

#endif