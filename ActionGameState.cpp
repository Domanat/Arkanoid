#include "ActionGameState.hpp"
#include <iostream>

ActionGameState::ActionGameState(Game* g) :
	player("images/Player.png"),
	enemy("images/enemy.png")
{
	game = g;

	//background on the level
	levelTexture.loadFromFile("images/wall.png");
	levelSprite.setTexture(levelTexture);

	//background image
	backTexture.loadFromFile("images/GameBackground.jpg");
	background.setTexture(backTexture);

	//brick on the level
	drawBlockTexture.loadFromFile("images/brick.png");
	drawBlock.setTexture(drawBlockTexture);


	view.setSize(sf::Vector2f(windowWidth, windowHeight));
}

void ActionGameState::input()
{
	sf::Event event;

	while (game->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			game->window.close();

		if (event.key.code == sf::Keyboard::Escape)
			game->window.close();
	}

	player.input();
}
		
void ActionGameState::update(float dt)
{
	player.update(dt);
	enemy.update(dt);

	if (player.getRect().intersects(enemy.getRect()) && enemy.isAlive)
	{
		if (player.getSpeed().y > 0)
		{
			player.setSpeed(vertical, -jumpSpeed);
			enemy.isAlive = false;
		}
	}

	//center view to the player;
	view.setCenter(player.getPosition().x, player.getPosition().y);
	game->window.setView(view);
			
	//set background image correct
	background.setPosition(view.getCenter().x - windowWidth / 2, view.getCenter().y - windowHeight / 2);
}

void ActionGameState::draw()
{
	game->window.setView(view);
	game->window.clear();
	game->window.draw(background);
	
		for (int i = 0; i < mapHeight; i++)
		{
			for (int j = 0; j < mapWidth; j++)
			{
				if (map[i][j] == 'B')
				{
					drawBlock.setPosition(j * cellSize, i * cellSize);
					game->window.draw(drawBlock);
				}
				else if (map[i][j] == ' ')
				{
					levelSprite.setPosition(j * cellSize, i * cellSize);
					game->window.draw(levelSprite);
				}
				else
					continue;
			}
		}
	
		
		game->window.draw(player);
		if (enemy.isAlive)
		{
			game->window.draw(enemy);
		}
		game->window.display();
}