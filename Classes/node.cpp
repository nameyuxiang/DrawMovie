#include "node.h"
USING_NS_CC;

node::node(void)
{
	positionX = 0;
	positionY = 0;
	color = 0;
}


node::~node(void)
{
}


node::node(int positionX, int positionY)
{
	this->positionX = positionX;
	this->positionY = positionY;
	
	this->setPosition(ccp(positionX,positionY));
	this->initWithFile("jd.png");
	amount++;
	id = amount;
	tag = id;
}

void node::blink()
{
}
