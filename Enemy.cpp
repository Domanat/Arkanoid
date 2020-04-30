#include "Enemy.hpp"

Enemy::Enemy(const std::string& filename)
{
	texture.loadFromFile(filename);
	sprite.setTexture(texture);
	sprite.scale(1.5, 1.5);

	frameNumber = 0;
	rect = sf::FloatRect(13 * cellSize, 9 * cellSize, 28, 33);
	dx = dy = speed;
	isAlive = true;
}

void Enemy::update(float dt)
{
	//rect.left += dx * dt;

		/*if (rect.left <= 28 * cellSize || rect.left + rect.width > 37 * cellSize)
		{
			dx = -speed;
		}*/

		//if (frameNumber > 3)
		//	frameNumber = 0;

	if (dx > 0)
		sprite.setTextureRect(sf::IntRect(0 * int(frameNumber), 0, 32, 32));
	if (dx < 0)
		sprite.setTextureRect(sf::IntRect(0 * int(frameNumber) + 32, 0, -32, 32));

	sprite.setPosition(rect.left, rect.top);
}

sf::FloatRect& Enemy::getRect()
{
	return rect;
}

sf::Sprite& Enemy::getSprite()
{
	return sprite;
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}