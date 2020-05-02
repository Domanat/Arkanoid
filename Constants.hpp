#ifndef CONST_H
#define CONST_H

#include <SFML/Graphics.hpp>

const int mapHeight = 21;
const int mapWidth = 50;
const int speed = 280;
const int jumpSpeed = 470;
const int cellSize = 32;
const int playerWidth = 32;
const int playerHeight = 32;
const int gravity = 1000;
const int animationSpeed = 7;
const int horizontal = 0;
const int vertical = 1;
const int windowWidth = 1280;
const int windowHeight = 720;

const sf::String map[mapHeight] =
{
	"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
	"B                                               B",
	"B                                               B",
	"B         BBBBB                                 B",
	"B BBBBB                            BBBBBBB      B",
	"B                       BBBB          B        BB",
	"B              BBBB                   B         B",
	"BB                                    B         B",
	"B       BBBBBBBBB                           BBBBB",
	"BBB                   BB                        B",
	"B                     BB                        B",
	"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB   BBBB   BBBB",
	"B                               BB              B",
	"B                               BBBBB       BBBBB",
	"B BBB         BBBBBBBB          B               B",
	"B                                        BBBBBBBB",
	"B       BB                              BB      B",
	"BBBBB             BBBBBBBB             B        B",
	"B       BBBBB                                   B",
	"B                                               B",
	"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB"
};


#endif