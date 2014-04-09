#include "DrawMovieScene.h"
#include"node.h"
#include"line.h"

USING_NS_CC;
//对node和line的静态变量的初始化
int node::a[6][6];
int node::amount = 0;
bool node::start = true;
int node::beforeTag = 0;
int node::currentTag = 0;
int node::count = 0;

int line::amount = 0;
int line::count = 0;
int line::beforeTag = 0;

//用二维数组描述点与点之间的关系
void shuzu(int a[6][6])
{
	a[1][2] = 1;
	a[1][3] = 1;
	a[1][4] = 1;
	a[1][5] = 0;
	a[2][1] = 1;

	a[2][3] = 1;
	a[2][4] = 0;
	a[2][5] = 1;
	a[3][1] = 1;
	a[3][2] = 1;

	a[3][4] = 1;
	a[3][5] = 1;
	a[4][1] = 1;
	a[4][2] = 0;
	a[4][3] = 1;

	a[4][5] = 0;
	a[5][1] = 0;
	a[5][2] = 1;
	a[5][3] = 1;
	a[5][4] = 0;

}

//闪烁动画

void runAnimate(node *targetNode)
{
		CCAnimation* animation = CCAnimation::create();
		animation->addSpriteFrameWithFileName("jd.png");
		animation->addSpriteFrameWithFileName("jd~.png");

		animation->setDelayPerUnit(2.8f / 14.0f);//必须设置否则不会动态播放
		animation->setRestoreOriginalFrame(true);//是否回到第一帧
		animation->setLoops(-1);//重复次数 （-1:无限循环）
		
		CCFiniteTimeAction * animate = CCAnimate::create(animation);
		targetNode->runAction(animate);
}
void runAnimate(line *targetLine)
{
		CCAnimation* animation = CCAnimation::create();
		animation->addSpriteFrameWithFileName("jd.png");
		animation->addSpriteFrameWithFileName("jd~.png");

		animation->setDelayPerUnit(2.8f / 14.0f);//必须设置否则不会动态播放
		animation->setRestoreOriginalFrame(true);//是否回到第一帧
		animation->setLoops(-1);//重复次数 （-1:无限循环）
		
		CCFiniteTimeAction * animate = CCAnimate::create(animation);
		targetLine->runAction(animate);
}
void DrawMovie::lineAnimate(node *targetNode)
{
	if(node::a[node::beforeTag][node::currentTag]==1)
	{
		node *beforeNode = (node *)this->getChildByTag(node::beforeTag);
		int beforeNodeTag = beforeNode->tag,targetNodeTag = targetNode->tag;
		//使beforeNodeTag为较小的tag
		if(beforeNodeTag>targetNodeTag)
		{
			int c=beforeNodeTag;
			beforeNodeTag =	targetNodeTag;
			targetNodeTag = c;
		}
		int lineTag = beforeNodeTag*100+targetNodeTag;
		line *targetLine = (line *)this->getChildByTag(lineTag);
		runAnimate(targetLine);
		line::beforeTag = lineTag;


	}

}
//用矩形将精灵包起来，然后通过判断触摸的点的position是否在矩形内判断是否触碰到了精灵
bool DrawMovie::isTouchGetNode(node *sprite,CCTouch* touch,int tag)
{
		
		CCPoint touchPoint = touch->getLocationInView();     
		touchPoint = CCDirector::sharedDirector()->convertToGL( touchPoint );         
		CCRect rc1 = sprite->boundingBox(); 
		if(rc1.containsPoint(touchPoint)) return true;
		else return false;
}
CCScene* DrawMovie::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();
	
	// 'layer' is an autorelease object
	DrawMovie *layer = DrawMovie::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool DrawMovie::init()
{

	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
	this->strike=CCMotionStreak::create(1.0f,//尾巴持续的时间
			16.0f,//尾巴大小
			16.0f,//图片的大小
			ccc3(255,255,0),//颜色
			"jd.png"//使用的图片
			);
		addChild(strike,1);
		strike->setPosition(ccp(240,160));
	shuzu(node::a);

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
		// add "DrawMovie" splash screen"
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
										"CloseNormal.png",
										"CloseSelected.png",
										this,
										menu_selector(DrawMovie::menuReInit));
	
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
								origin.y + pCloseItem->getContentSize().height/2));

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu,1);
	CCSprite* pSprite = CCSprite::create("up.png");

	// position the sprite on the center of the screen
	pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(pSprite, 0);
	node *node1 = new node(50,100);
	node *node2 = new node(250,100);
	node *node3 = new node(150,150);
	node *node4 = new node(50,200);
	node *node5 = new node(250,200);
	
	this->addChild(node1,0,node1->tag);
	this->addChild(node2,0,node2->tag);
	this->addChild(node3,0,node3->tag);
	this->addChild(node4,0,node4->tag);
	this->addChild(node5,0,node5->tag);
	//创建lines
	line **lines = (line**)new line;
	int xLine = 0;
	for(int i = 1;i<=node::amount;i++)
		for(int j=i+1;j<=node::amount;j++)
			if(node::a[i][j]==1)
			{
				xLine++;	
				node* nodeI = (node*)this->getChildByTag(i);
				node* nodeJ = (node*)this->getChildByTag(j);
				lines[xLine]=line::create(nodeI,nodeJ);
				this->addChild(lines[xLine],0,lines[xLine]->tag);
			}
	
	return true;
}
void DrawMovie::onEnter(){
	
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,false);
	CCLayer::onEnter();
}

void DrawMovie::onExit(){
	
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}

/*用全局变量start，判断是否是第一个触摸点。
如果不是第一个点，则当前点为i，触摸到点（j）的时候如果可连（a[i][j]==1）时，
将触摸点记录（即为i），a[i][j]=0,a[j][i]=0;触摸点开始闪，之前点停止闪烁
若成功触摸7个线段，所有点开始亮

*/
bool DrawMovie::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	strike->setPosition(touch->getLocation());
	CCLOG("ccTouchBegan");
	node *targetNode;
	CCPoint point = touch->getLocation();
	int tag ;
	if(node::start==true)
	{
		for (tag = 1;tag<=node::amount;tag++)     
		{   
			node* sprite= (node*)this->getChildByTag(tag);   
			if (isTouchGetNode(sprite,touch,tag))
			{   
				targetNode = sprite;
				runAnimate(targetNode);
				node::start = false;
				node::beforeTag = sprite->tag;
				return true;         
			}
		}
	}
	else{
		for (tag = 1;tag<=node::amount;tag++)     
		{   
			node* sprite= (node*)this->getChildByTag(tag);   
			if (isTouchGetNode(sprite,touch,tag)&&tag!=node::beforeTag)
			{   
				sprite = sprite;
				node::currentTag = sprite->tag;
				lineAnimate(sprite);
				runAnimate(sprite);	

//实现算法："如果不是第一个点，则当前点为i，触摸到点（j）的时候如果可连（a[i][j]==1）时，
//将触摸点记录（即为i），a[i][j]=0,a[j][i]=0;触摸点开始闪，之前点停止闪烁"	
				node::a[node::beforeTag][node::currentTag]=0;
				node::a[node::currentTag][node::beforeTag]=0;
				node::count++;
				node *bnode =(node*)this->getChildByTag(node::beforeTag);
				bnode->stopAllActions(); 
			//添加记录了line的beforeTag	
				node::beforeTag = sprite->tag;
				return true;
			}
		}	
	}
	//成功后所有点闪
	if(node::count == 7)
		for(int i =1;i<=5;i++)
		{
			node *blinkNode = (node*)this->getChildByTag(i);
			runAnimate(blinkNode);
		}
	return false;   
}

void DrawMovie::ccTouchMoved(CCTouch* touch, CCEvent* event){
	CCLOG("ccTouchMoved");
	int tag ;
	node *targetNode;
	if(node::start==false)
	{
		for (tag = 1;tag<=node::amount;tag++)     
		{   
			node* sprite= (node*)this->getChildByTag(tag);   
			if (isTouchGetNode(sprite,touch,tag)&&tag!=node::beforeTag)
			{   
				node::currentTag = sprite->tag;
				lineAnimate(sprite);
				runAnimate(sprite);

//实现算法："如果不是第一个点，则当前点为i，触摸到点（j）的时候如果可连（a[i][j]==1）时，
//将触摸点记录（即为i），a[i][j]=0,a[j][i]=0;触摸点开始闪，之前点停止闪烁"
				node::a[node::beforeTag][node::currentTag]=0;
				node::a[node::currentTag][node::beforeTag]=0;
				node::count++;
				node *bnode =(node*)this->getChildByTag(node::beforeTag);
				bnode->stopAllActions();
				node::beforeTag = sprite->tag;
			}
		}
	}
	if(node::count == 7)
		for(int i =1;i<=5;i++)
		{
			node *blinkNode = (node*)this->getChildByTag(i);
			runAnimate(blinkNode);
		}
	strike->setPosition(touch->getLocation());
}

void DrawMovie::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	CCLOG("ccTouchEnded");
}
void DrawMovie::menuReInit(CCObject* pSender)
{
	shuzu(node::a);
	for(int i =1;i<=5;i++)
	{
		node *Node = (node*)this->getChildByTag(i);
		Node->stopAllActions();
		node::start = true;
	}

	for(int i = 1;i<=node::amount;i++)
		for(int j=i+1;j<=node::amount;j++)
			if(node::a[i][j]==1)
			{
				int lineTag = i*100+j;
				line *targetLine = (line *)this->getChildByTag(lineTag);
				targetLine->stopAllActions();
			}

}
void DrawMovie::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}