#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable
{
protected:
	sf::Texture texture;
	sf::Sprite sprite;

	float dx, dy;
	bool onGround;
	float frameNumber;

	sf::FloatRect rect;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	
	virtual sf::Sprite& getSprite() = 0;
	virtual sf::FloatRect& getRect() = 0;

	virtual void update(float dt) = 0;;

};

#endif