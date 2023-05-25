#include <SFML/Window/Event.hpp>
#include <iostream>

#include "State_PlayGame.hpp"

StatePlayGame::StatePlayGame(StateManager& stateManager, sf::RenderWindow& window)
: State{ stateManager, window } {
	m_background.loadFromFile("content/map_background.png");
	m_backSprite.setTexture(m_background);
	m_backSprite.setOrigin(m_background.getSize().x / 2.0f, m_background.getSize().y / 2.0f);

	m_backSprite.setPosition(600, 450);
	battleground.load("content/Tileset.png", sf::Vector2u(48,48), level, 25,19);

	hud.load();

	Abel.load("content/sprite8x4withjump2.png");
	m_timePassed = 0.0f;
	std::cout << "MAP Creation Successful" <<std::endl;
    std::cout << "[StatePlayGame] Initialized\n";
}

StatePlayGame::~StatePlayGame() {
    std::cout << "[StatePlayGame] Destroyed\n";
}

void StatePlayGame::pause() {

}

void StatePlayGame::resume() {

}

void StatePlayGame::processEvents() {
    sf::Event event;

    while (m_window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                m_stateManager.quit();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case sf::Keyboard::Space: {
						// std::unique_ptr<State> stateMenu(new StateMenu(m_stateManager, m_window));
						// m_stateManager.changeState(std::move(stateMenu));
                        // return;
                    }
                    case sf::Keyboard::Escape:
                        // m_stateManager.quit();
                        return;
					default:
						break;
                }
				break;
			default:
				break;
        }
    }
}

void StatePlayGame::update(const sf::Time& dt) {
	m_timePassed += dt.asSeconds();
	Abel.move(dt.asSeconds(), m_window);
	Abel.update(dt.asSeconds());
	if(m_timePassed > 0.1f){
			// Abel.animate(false, true);
			Abel.animate();
			m_timePassed = 0.0f;
	}
}

void StatePlayGame::draw() {
    m_window.clear();
	m_window.draw(m_backSprite);
	m_window.draw(battleground);
	m_window.draw(hud);
	m_window.draw(Abel);
    m_window.display();
}
