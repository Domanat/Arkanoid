#ifndef MENU_GAME_STATE_HPP
#define MENU_GAME_STATE_HPP

#include "GameState.hpp"

class MenuGameState : public GameState
{
private:
	sf::Vector2i mousePos;
	sf::Text text;
	sf::Font font;

public:

	MenuGameState(Game* game);

	virtual void draw();
	virtual void update(float dt);
	virtual void input();

};

#endif