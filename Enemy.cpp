#include "Enemy.hpp"

Enemy::Enemy(const std::string& filename, int x, int y)
{
	texture.loadFromFile(filename);
	sprite.setTexture(texture);

	frameNumber = 0;
	rect = sf::FloatRect(x, y, 30, 32);
	dx = dy = speed/2;
	isAlive = true;
	onGround = false;
}

void Enemy::update(float dt)
{
	rect.left += dx * dt;
	collision(horizontal);
	
	if (!onGround)
	{
		dy += gravity * dt;
		rect.top += dy * dt;
	}

	onGround = false;
	collision(vertical);

	frameNumber += 4 * dt;

	if (frameNumber > 4)
		frameNumber = 0;

	if (dx > 0)
		sprite.setTextureRect(sf::IntRect(30 * int(frameNumber), 0, 30, 32));
	if (dx < 0)
		sprite.setTextureRect(sf::IntRect(30 * int(frameNumber) + 30, 0, -30, 32));

	sprite.setPosition(rect.left, rect.top);
}

void Enemy::collision(int direction)
{
	if (rect.left + rect.width > 20 * cellSize)
	{
		dx = -speed/2;
	}
	else if (rect.left < 8 * cellSize)
		dx = speed/2;


	for (int i = rect.top / cellSize; i < (rect.top + rect.height) / cellSize; i++)
	{
		for (int j = rect.left / cellSize; j < (rect.left + rect.width) / cellSize; j++)
		{
			if (map[i][j] == 'B')
			{
				if (direction == horizontal)
				{
					if (dx > 0)
					{
						rect.left = j * cellSize - rect.width;
					}
					else if (dx < 0)
						rect.left = j * cellSize + cellSize;
				}
				if (direction == vertical)
				{
					if (dy < 0)
					{
						rect.top = i * cellSize + cellSize;
					}
					else if (dy > 0)
					{
						rect.top = i * cellSize - rect.height;
						onGround = true;
					}
					dy = 0;
				}
			}
		}
	}
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