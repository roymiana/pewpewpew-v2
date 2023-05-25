#include "Game.hpp"

const sf::Time Game::TimePerFrame = sf::seconds(1.0f / 60.0f);

void Game::run() {
    m_window.create(sf::VideoMode{ WINDOW_HEIGHT, WINODW_WIDTH }, "PewPewPew", sf::Style::Titlebar | sf::Style::Close);

    std::unique_ptr<State> stateIntro(new StateIntro(m_stateManager, m_window));
    m_stateManager.changeState(std::move(stateIntro));

    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (m_stateManager.running()) {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;

        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;

            m_stateManager.processEvents();
            m_stateManager.update(TimePerFrame);
        }
        m_stateManager.draw();
    }
}