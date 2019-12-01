#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>


using namespace std;
using namespace sf;

constexpr int windowWidth = 800 , windowHeight = 600;

constexpr float ballRadius = 10, ballVelocity = 6;
constexpr float paddleWidth = 60, paddleHeight = 20, paddleVelocity = 5;
constexpr float blockWidth = 40, blockHeight = 20;
constexpr int countBlocksX = 11, countBlocksY = 4;

struct Ball
{
	CircleShape shape;
	Vector2f velocity{ -ballVelocity + 2, ballVelocity };

	Ball(float mX, float mY)
	{
		shape.setPosition(mX, mY);
		shape.setRadius(ballRadius);
		shape.setFillColor(Color::Red);
	}

	void update()
	{
		if (right() >= windowWidth)
			velocity.x = -ballVelocity;
		else if (left() <= 0)
			velocity.x = ballVelocity;
		else if (top() <= 0)
			velocity.y = ballVelocity;
		else if (bottom() >= windowHeight)
			velocity.y = -ballVelocity;

		shape.move(velocity);

	}

	//Wrong patter for sides of ball
	float x() { return shape.getPosition().x; }
	float y() { return shape.getPosition().y; }
	float left() { return shape.getPosition().x; }
	float right() { return shape.getPosition().x + shape.getRadius() * 2; }
	float top() { return shape.getPosition().y; }
	float bottom() { return shape.getPosition().y + shape.getRadius() * 2; }
};

struct Paddle
{
	sf::RectangleShape shape;
	sf::Vector2f velocity;

	Paddle(float mX, float mY)
	{
		shape.setSize(sf::Vector2f(paddleWidth, paddleHeight));
		shape.setPosition(sf::Vector2f(mX, mY));
		shape.setFillColor(sf::Color::Green);
	}

	void update()
	{
		shape.move(velocity);

		if (Keyboard::isKeyPressed(Keyboard::Key::Right) && right() < windowWidth)
			velocity.x = paddleVelocity;
		else if (Keyboard::isKeyPressed(Keyboard::Key::Left) && left() > 0)
			velocity.x = -paddleVelocity;
		else
			velocity.x = 0;

	}

	float x() { return shape.getPosition().x; }
	float y() { return shape.getPosition().y; }
	float left() { return x(); }
	float right() { return x() + shape.getSize().x; }
	float top() { return y(); }
	float bottom() { return y() + shape.getSize().y; }
};

template<class T1, class T2>
bool isCollide(T1 &paddle, T2 &ball)
{
	return ball.right() >= paddle.left() && ball.left() <= paddle.right() && ball.top() <= paddle.bottom() && ball.bottom() >= paddle.top();
}

struct Block
{
	sf::RectangleShape shape;
	bool isVisible = true;

	Block() {}

	Block(float x, float y)
	{
		shape.setSize({ blockWidth, blockHeight });
		shape.setFillColor(sf::Color::Yellow);
		shape.setPosition({ x, y });
	}

	float x() { return shape.getPosition().x; }
	float y() { return shape.getPosition().y; }
	double right() { return shape.getPosition().x + shape.getSize().x; }
	double left() { return shape.getPosition().x; }
	double top() { return shape.getPosition().y; }
	double bottom() { return shape.getPosition().y + shape.getSize().y; }
};

void testCollision(Paddle &paddle, Ball &ball)
{
	if (!isCollide(paddle, ball))
		return;

	ball.velocity.y = -ballVelocity;

	if (ball.x() > paddle.x() + paddleWidth / 2)
		ball.velocity.x = ballVelocity;
	else
		ball.velocity.x = -ballVelocity;
}

void testCollision(Block &block, Ball &ball)
{
	//if there is no collision, quit
	if (!isCollide(block, ball) || !block.isVisible)
		return;

	block.isVisible = false;
	
	//if ball hits block on the top, change y velocity and
	//change x velocity depending on half of the block
	if (block.y() > ball.y())
	{	
		ball.velocity.y = -ballVelocity;
		if (block.x() + blockWidth / 2 <= ball.x())
			ball.velocity.x = ballVelocity;
		else if (block.x() + blockWidth / 2 > ball.x())
			ball.velocity.x = -ballVelocity;
	}
	//If ball hits block at the bottom do the same
	else if (block.y() + blockHeight <= ball.y())
	{
		ball.velocity.y = ballVelocity;

		if (block.x() + blockWidth / 2 <= ball.x())
			ball.velocity.x = ballVelocity;
		else if (block.x() + blockWidth / 2 > ball.x())
			ball.velocity.x = -ballVelocity;
	}
}

int main()
{
	Paddle paddle(windowWidth / 2, windowHeight - paddleHeight);
	Ball ball(paddle.x() + paddleWidth / 2, paddle.y() + ballRadius*2);
	vector<Block> blocks;

	for (int i = 0; i < 10; i++)
	{
		blocks.push_back(Block(80 + (10 + blockWidth) * i, 100));
	}

	RenderWindow window(VideoMode(windowWidth, windowHeight), "Arkanoid - 3");
	window.setFramerateLimit(80);

	while (true)
	{
		window.clear(Color::Black);

		if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) break;

		// Every loop iteration, we need to update the ball.
		ball.update();
		paddle.update();

		testCollision(paddle, ball);

		window.clear();

		for (int i = 0; i < 10; i++)
		{
			testCollision(blocks[i], ball);

			if (blocks[i].isVisible)
				window.draw(blocks[i].shape);
		}
		window.draw(ball.shape);
		window.draw(paddle.shape);
		window.display();
	}

	return 0;
}