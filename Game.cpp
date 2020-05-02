#include "Game.hpp"
#include "GameState.hpp"
#include "MenuGameState.hpp"
#include "ActionGameState.hpp"
#include <iostream>

Game::Game() :
	window(sf::VideoMode(windowWidth, windowHeight), "RiverPort")
{
	

	pushState(new ActionGameState(this));
}

Game::~Game()
{
	while (!states.empty())
		states.pop();
}

void Game::start()
{
	sf::Clock clock;

	while (window.isOpen())
	{
		float dt = clock.restart().asSeconds();

		if (peekState() == nullptr)
			continue;

		peekState()->input();
		peekState()->update(dt);
		peekState()->draw();
	}
}

void Game::pushState(GameState* state)
{
	states.push(state);
}

void Game::popState()
{
	states.pop();
}

GameState* Game::peekState()
{
	return states.empty() ? nullptr : states.top();
}

void Game::changeState(GameState* state)
{
	if (!states.empty())
		states.pop();

	states.push(state);
}
