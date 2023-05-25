#include <SFML/Window/Event.hpp>
#include <iostream>

#include "State_Intro.hpp"
#include "State_Menu.hpp"

StateIntro::StateIntro(StateManager& stateManager, sf::RenderWindow& window)
: State{ stateManager, window } {
	m_timePassed = 0.0f;
	timeIsPassed = false;

	sf::Vector2u windowSize = sf::Vector2u(WINDOW_HEIGHT, WINODW_WIDTH); //creates variable for window size

	//for background
	m_background.loadFromFile("content/introback.png"); //loads image file
	m_backSprite.setTexture(m_background); //sets sprite texture from image
	m_backSprite.setScale(sf::Vector2f(	//scales background into window size
		(float)WINDOW_HEIGHT/m_background.getSize().x
		,(float)WINODW_WIDTH/m_background.getSize().y));
	m_backSprite.setOrigin(m_background.getSize().x / 2.0f, m_background.getSize().y / 2.0f); //sets origin at center
	m_backSprite.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f); //set position at center

	//for title
	m_introTexture.loadFromFile("content/introtitle.png");
	m_introSprite.setTexture(m_introTexture);
	// m_introSprite.setScale(sf::Vector2f(1.5f,1.5f));
	m_introSprite.setOrigin(m_introTexture.getSize().x / 2.0f,
		m_introTexture.getSize().y / 2.0f);

	m_introSprite.setPosition(windowSize.x / 2.0f,0);

	//for text
	m_font.loadFromFile("content/font.otf");
	m_text.setFont(m_font);
	m_text.setString({ "Press SPACE to continue" });
	m_text.setCharacterSize(24);
	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	m_text.setPosition(windowSize.x / 2.0f, (windowSize.y / 2.0f) + 100.0f);

	//for music
	theme.openFromFile("content/title.flac");
	theme.play();
	theme.setVolume(50.0f);
	theme.setLoop(true);

    std::cout << "[StateIntro] Initialized\n";
}

StateIntro::~StateIntro() {
    std::cout << "[StateIntro] Destroyed\n";
}

void StateIntro::pause() {

}

void StateIntro::resume() {

}

void StateIntro::processEvents() {
    sf::Event event;

    while (m_window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                m_stateManager.quit();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case sf::Keyboard::Space: {
						if(timeIsPassed){
							std::unique_ptr<State> stateMenu(new StateMenu(m_stateManager, m_window));
							m_stateManager.changeState(std::move(stateMenu));
						}
                        return;
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

void StateIntro::update(const sf::Time& dt) {
	m_timePassed += dt.asSeconds();
	if(m_timePassed < 5.0f  && !timeIsPassed){ // Less than five seconds.
		// std::cout<<m_timePassed<<std::endl;
		//for transition of the title
		m_introSprite.setPosition(
			m_introSprite.getPosition().x,
			m_introSprite.getPosition().y + (48 * dt.asSeconds())); //moves it down
	}
	else if(m_timePassed >= 5 && !timeIsPassed){
		timeIsPassed = true;
	}
}

void StateIntro::draw() {
	m_window.clear();
    // m_window.clear(sf::Color::Black);
	m_window.draw(m_backSprite); //draws background
	m_window.draw(m_introSprite); //draws title
	if(timeIsPassed){
		if(m_timePassed < 0.5f)
			m_window.draw(m_text); //if 5 seconds has passed, text is drawn
		else if(m_timePassed > 1.0f){
			m_timePassed = 0.0f;
		}
	}
    m_window.display();
}