#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "cocos2d.h"
#include "node.h"
USING_NS_CC;
class DrawMovie : public cocos2d::CCLayer
{
public:
	//声明拖尾类
	CCMotionStreak* strike;
	//划线函数
	void drawLine(node *p1,node *p2);
	void drawLines();
	bool isTouchGetNode(node *sprite,CCTouch* touch,int tag);
	void lineAnimate(node *sprite);
	//响应触屏动作
	//重写触屏回调函数
	virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	virtual void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	virtual void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	
	//重写生命周期函数
	virtual void onEnter();
	virtual void onExit();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::CCScene* scene();

	void menuReInit(CCObject* pSender);
	// a selector callback
	void menuCloseCallback(CCObject* pSender);
	
	// implement the "static node()" method manually
	CREATE_FUNC(DrawMovie);
};

#endif // __DrawMovie_SCENE_H__
