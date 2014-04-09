#pragma once
#include"cocos2d.h"
#include"node.h"
class line: public cocos2d::CCSprite
{
public:
	//属性
	int tag;
	int color;
	int currentNodeTag;
	int beforeNodeTag;
	int id;
	static int amount;
	static int count;
	static int beforeTag;

	//带参数的构造函数完成了坐标的确定、图片的选取、amount自加、id、tag复制
	line(int positionX, int positionY,int currentNodeTag,int beforeNodeTag);
	line(void);
	~line(void);
	void blink();
	static line *create(node *p1,node *p2);
private:
	int positionX;
	int positionY;

	

	
};


