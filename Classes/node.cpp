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
	this->initNode();
}
void node::initNode()
{
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
void node::specialNodesInit()
{
	specialNodes[0][0] = 4;
	specialNodes[0][1] = 5;
}

void node::specialNodesEnd(int i)
{
	specialNodes[i][0] = 0;
	specialNodes[i][1] = 0;
}
void node::NodeChange(int color)
{	
	this->color=color;
	CCAnimation* animation = CCAnimation::create();
	if(this->color==2)
		animation->addSpriteFrameWithFileName("node2.png");
	else if(this->color==0)
		animation->addSpriteFrameWithFileName("node0.png");

	animation->setDelayPerUnit(2.8f / 14.0f);//必须设置否则不会动态播放
	animation->setRestoreOriginalFrame(false);//是否回到第一帧
	animation->setLoops(1);//重复次数 （-1:无限循环）
	CCFiniteTimeAction * animate = CCAnimate::create(animation);
	this->runAction(animate);
}

void node::nodeRunAnimation()
{
	CCAnimation* animation = CCAnimation::create();
	animation->addSpriteFrameWithFileName("node1.png");
	animation->addSpriteFrameWithFileName("node0.png");

	animation->setDelayPerUnit(2.8f / 14.0f);//必须设置否则不会动态播放
	animation->setRestoreOriginalFrame(true);//是否回到第一帧
	animation->setLoops(-1);//重复次数 （-1:无限循环）

	CCFiniteTimeAction * animate = CCAnimate::create(animation);
	this->runAction(animate);
}


int node::GetNodeX()
{
	return this->positionX;
}


int node::GetNodeY()
{
	return this->positionY;
}

