#pragma once
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
	amount++;
	id = amount;
	tag = id;
	color = 0;
	this->positionX = positionX;
	this->positionY = positionY;
	
	this->setPosition(ccp(positionX,positionY));
	for(int i = 0;i<=aHalfOfNumberOfSpecialNodes;i++)
	{
		if(specialNodes[i][0]==tag||specialNodes[i][1]==tag)
		{
			color = 2;
			break;
		}
		else
		{
			color = 0;
		}	
	}
	if(color==0) this->initWithFile("node0.png");
	if(color==2) this->initWithFile("node2.png");

}

void node::blink()
{
}
int node::GetNodeX()
{
	return this->positionX;
}


int node::GetNodeY()
{
	return this->positionY;
}

