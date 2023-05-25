#include <SFML/Window/Event.hpp>
#include <iostream>

#include "State_PreGame.hpp"
#include "State_Menu.hpp"
#include "State_PlayGame.hpp"

#define originX 29
#define originY 51

#define posY 450
#define AbelposX 300
#define CainposX 900

StatePreGame::StatePreGame(StateManager& stateManager, sf::RenderWindow& window)
: State{ stateManager, window } {
	m_timePassed = 0.0f;
	currentState = 0;

	///background
	m_background.loadFromFile("content/introback.png");
	m_backSprite.setTexture(m_background);
	m_backSprite.setScale(sf::Vector2f(	//scales background into window size
		(float)WINDOW_HEIGHT/m_background.getSize().x
		,(float)WINODW_WIDTH/m_background.getSize().y));
	m_backSprite.setOrigin(0, 0);
	m_backSprite.setPosition(0, 0);

	//filter
	m_filter.setSize(sf::Vector2f(WINDOW_HEIGHT,WINODW_WIDTH));
	m_filter.setPosition(0, 0);
	m_filter.setFillColor(sf::Color(0, 0, 0, 150));

	//Abel player
	Abel.load("content/blue68.png");
	Abel.setOrigin(originX, originY);
	Abel.setPosition(AbelposX, posY);

	//Cain player
	Cain.load("content/pink68.png");
	Cain.setOrigin(originX, originY);
	Cain.setPosition(CainposX, posY);
	Cain.setScale(-1.0f, 1.0f);

	//sound
	m_soundBuffer.loadFromFile("content/ugh.wav");
	m_sound.setBuffer(m_soundBuffer);

	setname(Abel.sprite(), Cain.sprite());

    std::cout << "[StatePreGame] Initialized\n";
}

StatePreGame::~StatePreGame() {
    std::cout << "[StatePreGame] Destroyed\n";
}

void StatePreGame::pause() {

}

void StatePreGame::resume() {

}

void StatePreGame::processEvents() {
    sf::Event event;
	if(currentState == 5){
			std::unique_ptr<State> statePlay(new StatePlayGame(m_stateManager, m_window));
			m_stateManager.changeState(std::move(statePlay));
			return;
	}
    while (m_window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                m_stateManager.quit();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case sf::Keyboard::Space:
						if(currentState == 0 || currentState == 1){
							name.ready[1].setString("READY");
							Cain.load("content/pinkflex68.png");
							Cain.setOrigin(originX, originY);
							Cain.setPosition(CainposX, posY);
							Cain.setScale(-1.0f, 1.0f);
							m_sound.play();
							if(currentState == 0)
								currentState = 2;
							else
								currentState = 3;
						}
						break;
					case sf::Keyboard::Return:
						if(currentState == 0 || currentState == 2){
							name.ready[0].setString("READY");
							Abel.load("content/blueflex68.png");
							Abel.setOrigin(originX, originY);
							Abel.setPosition(AbelposX, posY);
							m_sound.play();
							if(currentState == 0)
								currentState = 1;
							else
								currentState = 3;
						}
						else if(currentState == 3){
							name.ready[2].setString("GAME COMMENCING...");
							name.ready[2].setPosition(posY - 150, name.ready[2].getPosition().y);
							m_timePassed = 0.0f;
							currentState = 4;
						}
						break;
                    case sf::Keyboard::Escape:
						if(currentState == 1){
							Abel.load("content/blue68.png");
							Abel.setOrigin(originX, originY);
							Abel.setPosition(AbelposX, posY);
							name.ready[0].setString("Press Enter");
							currentState = 0;
						}
						else if(currentState == 2){
							Cain.load("content/pink68.png");
							Cain.setOrigin(originX, originY);
							Cain.setPosition(CainposX, posY);
							Cain.setScale(-1.0f, 1.0f);
							name.ready[1].setString("Press Space");
							currentState  = 0;
						}
						else if(currentState == 3){
							Abel.load("content/blue68.png");
							Abel.setOrigin(originX, originY);
							Abel.setPosition(AbelposX, posY);
							name.ready[0].setString("Press Enter");

							Cain.load("content/pink68.png");
							Cain.setOrigin(originX, originY);
							Cain.setPosition(CainposX, posY);
							Cain.setScale(-1.0f, 1.0f);
							name.ready[1].setString("Press Space");

							currentState  = 0;
						}
                        break;
					default:
						break;
                }
				break;
			default:
				break;
        }
    }
}

void StatePreGame::update(const sf::Time& dt) {
	m_timePassed += dt.asSeconds();

	if(currentState == 0){
		if(m_timePassed > 0.1f){
			Abel.animate();
			Cain.animate();
			m_timePassed = 0.0f;
		}
	}
	else if(currentState == 1){
		if(m_timePassed > 0.1f){
			Cain.animate();
			m_timePassed = 0.0f;
		}
	}
	else if(currentState == 2){
		if(m_timePassed > 0.1f){
			Abel.animate();
			m_timePassed = 0.0f;
		}
	}
	else if(currentState == 4){
		std::cout << m_timePassed << std::endl;
		if(m_timePassed >= 3.0f)
			currentState = 5;
	}
}

void StatePreGame::draw() {
    m_window.clear();

	m_window.draw(m_backSprite);
	m_window.draw(m_filter);

	if(currentState >= 3){
		m_window.draw(name.ready[2]);
	}
	for (int i = 0; i < 4; i++)
		m_window.draw(name.txt[i]);
	for (int i = 0; i < 2; i++)
		m_window.draw(name.ready[i]);

	m_window.draw(Abel);
	m_window.draw(Cain);
    m_window.display();
}

void StatePreGame::setname(sf::Sprite keeper, sf::Sprite brother){
	int ctr = 0, dis1 = 100, dis2 = 100;
	if (!name.font.loadFromFile("content/font.otf")) {

	}
	for (ctr = 0; ctr < 4; ctr++) {
		if (ctr % 2 == 0) {
			name.txt[ctr].setFont(name.font);
			name.txt[ctr].setFillColor(sf::Color::White);
			name.txt[ctr].setString(name.labels[ctr]);
			name.txt[ctr].setPosition(keeper.getPosition().x - 150, keeper.getPosition().y - dis1);
			dis1 += 50;
		}
		else {
			name.txt[ctr].setFont(name.font);
			name.txt[ctr].setFillColor(sf::Color::White);
			name.txt[ctr].setString(name.labels[ctr]);
			name.txt[ctr].setPosition(brother.getPosition().x - 150, brother.getPosition().y - dis2);
			dis2 += 50;
		}
	}
	name.ready[0].setFont(name.font);
	name.ready[1].setFont(name.font);
	name.ready[2].setFont(name.font);
	name.ready[2].setString("PRESS ENTER TO START");
	name.ready[2].setPosition(keeper.getPosition().x , keeper.getPosition().y + dis1);
	name.ready[2].setFillColor(sf::Color::White);
	name.ready[0].setString("Press Enter");
	name.ready[1].setString("Press Space");
	name.ready[0].setPosition(keeper.getPosition().x - 150, keeper.getPosition().y + dis1 / 2);
	name.ready[0].setFillColor(sf::Color::White);
	name.ready[1].setPosition(brother.getPosition().x - 150, brother.getPosition().y + dis2 / 2);
	name.ready[1].setFillColor(sf::Color::White);
}