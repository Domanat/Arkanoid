#include "Player.hpp"
#include <iostream>

Player::Player(const std::string& filename)
{
	texture.loadFromFile(filename);
	sprite.setTexture(texture);

	rect = sf::FloatRect(9 * cellSize, 8 * cellSize, playerWidth, playerHeight);

	dx = dy = speed;
	frameNumber = 0;
	onGround = false;
}

void Player::input()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		dx = speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		dx = -speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (onGround)
		{
			dy = -jumpSpeed;
			onGround = false;
		}
	}
}

void Player::update(float dt)
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

	frameNumber += animationSpeed * dt;

	if (frameNumber > 4)
		frameNumber = 0;

	if (dx > 0)
		sprite.setTextureRect(sf::IntRect(playerWidth * int(frameNumber), 0, playerWidth, playerHeight));
	if (dx < 0)
		sprite.setTextureRect(sf::IntRect(playerWidth * int(frameNumber) + playerWidth, 0, -playerWidth, playerHeight));

	dx = 0;
	sprite.setPosition(rect.left, rect.top);
}

void Player::collision(int direction)
{
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

sf::FloatRect& Player::getRect()
{
	return rect;
}

sf::Sprite& Player::getSprite()
{
	return sprite;
}

sf::Vector2f Player::getSpeed()
{
	return sf::Vector2f(dx, dy);
}

void Player::setSpeed(int direction, float pace)
{
	if (direction == vertical)
		dy = pace;
	else if (direction == horizontal)
		dx = pace;
}

sf::Vector2f Player::getPosition()
{
	return sprite.getPosition();
}


void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}