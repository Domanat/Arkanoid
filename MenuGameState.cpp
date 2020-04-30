#include "MenuGameState.hpp"
#include "ActionGameState.hpp"
#include "Constants.hpp"
#include <iostream>

MenuGameState::MenuGameState(Game* g)
{
	game = g;
	font.loadFromFile("fonts/MenuFont.ttf");
	text.setFont(font);
	text.setString("Start Game");
	text.setCharacterSize(100);
	text.setFillColor(sf::Color(255, 102, 102));
	text.setStyle(sf::Text::Bold);
	text.setPosition(450, 100);

	backTexture.loadFromFile("images/MenuBackground.png");
	background.setTexture(backTexture);
}

void MenuGameState::input()
{
	sf::Event event;
	while (game->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			game->window.close();

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left && text.getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y)))
			{
				game->changeState(new ActionGameState(game));
			}
		}
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		game->window.close();
}

void MenuGameState::update(float dt)
{
	mousePos = sf::Mouse::getPosition(game->window);
}

void MenuGameState::draw()
{
	game->window.clear(sf::Color::Black);
	game->window.draw(background);
	game->window.draw(text);

	game->window.display();
}