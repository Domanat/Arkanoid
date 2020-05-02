#ifndef ACTION_GAME_STATE_HPP
#define ACTION_GAME_STATE_HPP

#include "GameState.hpp"
#include "TextureManager.hpp"

class ActionGameState : public GameState
{
private:
	sf::View view;

	//------Change all that textures on texture manager!!---------------------

	//background inside level
	sf::Texture skyLowTexture;
	sf::Sprite skyLowSprite;

	sf::Texture skyUpTexture;
	sf::Sprite skyUpSprite;

	//textures for block which we use to draw level;
	sf::Texture drawBlockTexture;
	sf::Sprite drawBlock;

	//------------------------------------------------------------------

	Player player;
	Enemy enemy;

public:

	ActionGameState(Game* game);

	virtual void input();
	virtual void update(float dt);
	virtual void draw();
};

#endif