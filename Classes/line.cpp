#include "line.h"
#include"node.h"
#include <math.h>
USING_NS_CC;

line::line(void)
{
	positionX = 0;
	positionY = 0;
	color = 0;
}


line::~line(void)
{
}
line* line::create(node *p1,node *p2)
{
	float p1X = p1->getPositionX();
	float p1Y = p1->getPositionY();
	float p2X = p2->getPositionX();
	float p2Y = p2->getPositionY();
	float lineX = (p1X+p2X)/2;
	float lineY = (p1Y+p2Y)/2;
	line *newline = new line(lineX,lineY,p1->tag,p2->tag);
	//取两点中间的位置为position，取放大倍数，
	CCSize lineSize ;
	float bigWidth = (p1X-p2X)*(p1X-p2X)+(p1Y-p2Y)*(p1Y-p2Y);
	float newLineWidth = sqrt(bigWidth);
	lineSize = newline->getContentSize();
	float newScaleX = newLineWidth/lineSize.width;
	newline->setScaleX(newScaleX); 
	//设置倾斜角度

	float newRotation = -(180/3.14)*acos((p2X-p1X)/newLineWidth);
	newline->setRotation(newRotation);
	return newline;
}

line::line(int positionX, int positionY,int beforeNodeTag,int currentNodeTag)
{
	this->positionX = positionX;
	this->positionY = positionY;
	this->beforeNodeTag = beforeNodeTag;
	this->currentNodeTag = currentNodeTag;
	this->setPosition(ccp(positionX,positionY));
	this->initWithFile("jd~.png");
	amount++;
	id = amount;
	tag = beforeNodeTag*100+currentNodeTag;
}


void line::blink()
{
}
