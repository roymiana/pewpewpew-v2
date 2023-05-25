#include <SFML/Window/Event.hpp>
#include <iostream>

#include "State_Menu.hpp"
#include "State_Intro.hpp"
#include "State_PreGame.hpp"

StateMenu::StateMenu(StateManager& stateManager, sf::RenderWindow& window)
: State{ stateManager, window } {
	currentState = 0;

	sf::Vector2u windowSize = sf::Vector2u(WINDOW_HEIGHT, WINODW_WIDTH); //creates variable for window size

	//background
	m_background.loadFromFile("content/introback.png"); //loads image file
	m_backSprite.setTexture(m_background); //sets sprite texture from image
	m_backSprite.setScale(sf::Vector2f(	//scales background into window size
		(float)WINDOW_HEIGHT/m_background.getSize().x
		,(float)WINODW_WIDTH/m_background.getSize().y));
	m_backSprite.setOrigin(m_background.getSize().x / 2.0f, m_background.getSize().y / 2.0f); //sets origin at center
	m_backSprite.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f); //set position at center


	//how to play
	m_tutexture.loadFromFile("content/howtoplay.png");
	m_tutoSprite.setTexture(m_tutexture);
	m_tutoSprite.setScale(sf::Vector2f(	//scales background into window size
		(float)WINDOW_HEIGHT/m_tutexture.getSize().x
		,(float)WINODW_WIDTH/m_tutexture.getSize().y));
	m_tutoSprite.setOrigin(m_tutexture.getSize().x / 2.0f, m_tutexture.getSize().y / 2.0f); //sets origin at center
	m_tutoSprite.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f); //set position at center

	//buttons
	m_font.loadFromFile("content/font.otf");
	m_text.setFont(m_font);
	m_text.setString(sf::String("MAIN MENU:"));
	m_text.setCharacterSize(30);

	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);

	m_text.setPosition(windowSize.x/2.0f,100);

	m_buttonSize = sf::Vector2f(500.0f,64.0f);
	m_buttonPos = sf::Vector2f(windowSize.x/2.0f,200);
	m_buttonPadding = 4; // 4px.

	std::string str[3];
	str[0] = "PLAY";
	str[1] = "CREDITS";
	str[2] = "EXIT";

	for(int i = 0; i < 3; ++i){
		sf::Vector2f buttonPosition(m_buttonPos.x,m_buttonPos.y +
			(i * (m_buttonSize.y + m_buttonPadding)));
		m_rects[i].setSize(m_buttonSize);
		m_rects[i].setFillColor(sf::Color(44,47,43,255));

		m_rects[i].setOrigin(m_buttonSize.x / 2.0f, m_buttonSize.y / 2.0f);
		m_rects[i].setPosition(buttonPosition);

		m_labels[i].setFont(m_font);
		m_labels[i].setString(sf::String(str[i]));
		m_labels[i].setCharacterSize(24);

		sf::FloatRect rect = m_labels[i].getLocalBounds();
		m_labels[i].setOrigin(rect.left + rect.width / 2.0f,
			rect.top + rect.height / 2.0f);

		m_labels[i].setPosition(buttonPosition);
	}

	//music
	theme1.openFromFile("content/title.flac");
	theme1.play();
	theme1.setVolume(50.0f);
	theme1.setLoop(true);

	//CREDITS
	t_credit.loadFromFile("content/credit.png");
	t_sprite.setTexture(t_credit);
	t_sprite.setScale(sf::Vector2f(	//scales background into window size
		(float)WINDOW_HEIGHT/t_credit.getSize().x
		,(float)WINODW_WIDTH/t_credit.getSize().y));
	t_sprite.setOrigin(0, 0);
	t_sprite.setPosition(0, 0);

    std::cout << "[StateMenu] Initialized\n";
}

StateMenu::~StateMenu() {
    std::cout << "[StateMenu] Destroyed\n";
}

void StateMenu::pause() {

}

void StateMenu::resume() {

}

void StateMenu::processEvents() {
    sf::Event event;
	int click;

    while (m_window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                m_stateManager.quit();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case sf::Keyboard::Escape:{
						if(currentState == 0){
							std::unique_ptr<State> introState(new StateIntro(m_stateManager, m_window));
							m_stateManager.changeState(std::move(introState));
                        return;
						}
						else if(currentState == 1){
							currentState = 0;
						}
						else if(currentState == 2){
							m_stateManager.quit();
						}
					}
					default:
						break;
                }
				break;
			case sf::Event::MouseMoved:
				if(currentState == 0)
					isHovered();
				break;
			case sf::Event::MouseButtonPressed:
				if(currentState == 0){
					click = isClicked();
					if(click == 0){
						std::unique_ptr<State> pregameState(new StatePreGame(m_stateManager, m_window));
						m_stateManager.changeState(std::move(pregameState));
						return;
					}
					else if(click == 1){
						currentState = 1;
					}
				}
				break;
			default:
				break;
        }
    }
}

void StateMenu::update(const sf::Time& dt) {
	(void)dt;
}

void StateMenu::draw() {
	m_window.clear();
    // m_window.clear(sf::Color::Black);
	m_window.draw(m_backSprite);
	m_window.draw(m_text);
	m_window.draw(m_tutoSprite);
	for(int i = 0; i < 3; ++i){
		m_window.draw(m_rects[i]);
		m_window.draw(m_labels[i]);
	}
	if(currentState == 1)
		m_window.draw(t_sprite);
    m_window.display();
}

void StateMenu::isHovered(){
	sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
	bool hovered = false;

	float halfX = m_buttonSize.x / 2.0f;
	float halfY = m_buttonSize.y / 2.0f;
	for(int i = 0; i < 3; ++i){
		if(mousePos.x >= m_rects[i].getPosition().x - halfX &&
			mousePos.x <= m_rects[i].getPosition().x + halfX &&
			mousePos.y >= m_rects[i].getPosition().y - halfY &&
			mousePos.y <= m_rects[i].getPosition().y + halfY)
		{
			if(i == 0){
				m_rects[0].setFillColor(sf::Color::White);
				m_labels[0].setFillColor(sf::Color(44,47,43,255));
			}
			else{
				m_rects[0].setFillColor(sf::Color(44,47,43,255));
				m_labels[0].setFillColor(sf::Color::White);
			}
			if(i == 1){
				m_rects[1].setFillColor(sf::Color::White);
				m_labels[1].setFillColor(sf::Color(44,47,43,255));
			}
			else{
				m_rects[1].setFillColor(sf::Color(44,47,43,255));
				m_labels[1].setFillColor(sf::Color::White);
			}
			if(i == 2){
				m_rects[2].setFillColor(sf::Color::White);
				m_labels[2].setFillColor(sf::Color(44,47,43,255));
			}
			else{
				m_rects[2].setFillColor(sf::Color(44,47,43,255));
				m_labels[2].setFillColor(sf::Color::White);
			}
			hovered = true;
		}
	}
	if(!hovered){
		for(int i = 0; i < 3; ++i){
			m_rects[i].setFillColor(sf::Color(44,47,43,255));
			m_labels[i].setFillColor(sf::Color::White);
		}
	}
}

int StateMenu::isClicked(){
	sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);

	float halfX = m_buttonSize.x / 2.0f;
	float halfY = m_buttonSize.y / 2.0f;
	for(int i = 0; i < 3; ++i){
		if(mousePos.x >= m_rects[i].getPosition().x - halfX &&
			mousePos.x <= m_rects[i].getPosition().x + halfX &&
			mousePos.y >= m_rects[i].getPosition().y - halfY &&
			mousePos.y <= m_rects[i].getPosition().y + halfY)
		{
			if(i == 0){
				return 0;
			}
			else if(i == 1){
				// currentState = 1; //credit state
				return 1;
			}
			else if(i == 2){
				m_stateManager.quit();
				return 2;
			}
		}
	}
	return -1;
}