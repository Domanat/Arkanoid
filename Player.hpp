#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Constants.hpp"
#include "Entity.hpp"

class Player : public Entity
{
private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void collision(int direction);

	sf::Vector2i mousePosInWorld;
	sf::RenderWindow* window;
public:
	Player(const std::string& filename);

	virtual void update(float dt) override;
	void update(float dt, sf::RenderWindow& window);
	void input();
	
	sf::Vector2f getPosition();
	sf::Vector2f getSpeed();
	void setSpeed(int direction, float pace);
	virtual sf::Sprite& getSprite() override;
	virtual sf::FloatRect& getRect() override;
	
};

#endif