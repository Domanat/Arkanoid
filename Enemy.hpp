#ifndef ENEMY_H
#define ENEMY_H

#include "Constants.hpp"
#include "Entity.hpp"

class Enemy : public Entity
{
public:
	bool isAlive;


	Enemy(const std::string& filename, int x, int y);

	void collision(int direction);

	virtual void update(float dt) override;

	virtual sf::FloatRect& getRect() override;
	virtual sf::Sprite& getSprite() override;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


#endif