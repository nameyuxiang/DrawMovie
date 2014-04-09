#pragma once
#include"cocos2d.h"
class node: public cocos2d::CCSprite
{
public:
	//属性
	int tag;
	int color;
	int id;
	static int amount;
	static int count;
	static int a[6][6];
	static bool start ;
	static int beforeTag ;
	static int currentTag ;

	//带参数的构造函数完成了坐标的确定、图片的选取、amount自加、id、tag复制
	node(int positionX, int positionY);
	node(void);
	~node(void);
	void blink();
private:
	int positionX;
	int positionY;

	

	
};


