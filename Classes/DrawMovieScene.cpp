#include "DrawMovieScene.h"
#include"node.h"
#include"line.h"
#define aHalfOfNumberOfSpecialNodes 1
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


//初始化specialNodes
int node::specialNodes[aHalfOfNumberOfSpecialNodes][2];


//用二维数组描述点与点之间的关系
void arrayInit(int a[6][6])
{
	a[1][2] = 2;
	a[1][3] = 1;
	a[1][4] = 1;
	a[1][5] = 0;
	a[2][1] = 2;

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



//线段接受参数并响应
void DrawMovie::lineRespond(node *targetNode,int NumberOfLines )
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
	targetLine->LineChange(NumberOfLines);
	line::beforeTag = lineTag;
}
//用矩形将精灵包起来，然后通过判断触摸的点的position是否在矩形内判断是否触碰到了精灵
bool isTouchGetNode(node *sprite,CCTouch* touch,int tag)
{
		
		CCPoint touchPoint = touch->getLocationInView();     
		touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint );         
		CCRect rc1 = sprite->boundingBox(); 
		if(rc1.containsPoint(touchPoint)) return true;
		else return false;
}

//处理当前点，使它发光或跳跃
int DrawMovie::DealNodeAndGetTag(node *Node,CCMotionStreak* strike)
{
	bool isSpecilNode = false;
	int NodeTag = Node->tag;
	for(int i = 0;i<aHalfOfNumberOfSpecialNodes;i++)
	{
		if(Node->tag==node::specialNodes[i][0]||Node->tag==node::specialNodes[i][1]) 
		{
			int j = 1,otherj = 0;
			isSpecilNode = true;
			if(Node->tag==node::specialNodes[i][0])
			{
				j =0;
				otherj = 1;
			}
			Node->stopAllActions();
			Node->NodeChange(0);

			node* otherNode = (node*)this->getChildByTag(node::specialNodes[i][otherj]);
			otherNode->nodeRunAnimation();
			node::specialNodesEnd(i);
			otherNode->color = 0;
			NodeTag = otherNode->tag;
			strike->setPosition(ccp(otherNode->GetNodeX(),otherNode->GetNodeY()));
			}
		}
		if(!isSpecilNode){
			Node->nodeRunAnimation();
			strike->setPosition(ccp(Node->GetNodeX(),Node->GetNodeY()));
		}
		return NodeTag;
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
	gameStart = true;
	this->strike=CCMotionStreak::create(1.0f,//尾巴持续的时间
		4.0f,//尾巴大小
		16.0f,//图片的大小
		ccc3(255,255,0),//颜色
		"node0.png"//使用的图片
		);
	arrayInit(node::a);
	node::specialNodesInit();
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
		// add "DrawMovie" splash screen"

	CCMenuItemImage *pGuess1Item = CCMenuItemImage::create(
										"MovieMenu1-1.png",
										"MovieMenu1-2.png",
										this,
										menu_selector(DrawMovie::menuGuess1));
	CCMenuItemImage *pGuess2Item = CCMenuItemImage::create(
										"MovieMenu2-1.png",
										"MovieMenu2-2.png",
										this,
										menu_selector(DrawMovie::menuGuess2));
	CCMenuItemImage *pReInitItem = CCMenuItemImage::create(
										"CloseNormal.png",
										"CloseSelected.png",
										this,
										menu_selector(DrawMovie::menuReInit));
	pGuess1Item->setPosition(ccp(origin.x + visibleSize.width - pGuess1Item->getContentSize().width/2 ,
								180));
	pGuess2Item->setPosition(ccp(origin.x + visibleSize.width - pGuess2Item->getContentSize().width/2 ,
								120));
	pReInitItem->setPosition(ccp(origin.x + visibleSize.width - pReInitItem->getContentSize().width/2 ,
								origin.y + pReInitItem->getContentSize().height/2));
	CCMenu* pGuessMenu = CCMenu::create(pGuess1Item,pGuess2Item,NULL);
	pGuessMenu->setPosition(CCPointZero);
	this->addChild(pGuessMenu,1);
	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pReInitItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu,1);

	CCSprite* p1backSprite = CCSprite::create("background.png");
	CCSprite* p2backSprite = CCSprite::create("background.png");
	p1backSprite->setPosition(ccp(visibleSize.width/2 + origin.x-180, visibleSize.height/2 + origin.y));
	p2backSprite->setPosition(ccp(visibleSize.width/2 + origin.x+180, visibleSize.height/2 + origin.y));
	this->addChild(p1backSprite, 0);
	this->addChild(p2backSprite, 0);
	// position the sprite on the center of the screen

	// add the sprite as a child to this layer
	CCSprite* pSprite = CCSprite::create("up.png");
	pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(pSprite, 0);
	node *node1 = new node(50,100);
	node *node2 = new node(250,100);
	node *node3 = new node(150,150);
	node *node4 = new node(50,200);
	node *node5 = new node(250,200);
	
	this->addChild(node1,1,node1->tag);
	this->addChild(node2,1,node2->tag);
	this->addChild(node3,1,node3->tag);
	this->addChild(node4,1,node4->tag);
	this->addChild(node5,1,node5->tag);
	//创建lines
	line **lines = (line**)new line;
	int xLine = 0;
	for(int i = 1;i<=node::amount;i++)
		for(int j=i+1;j<=node::amount;j++)
			if(node::a[i][j]>=1)
			{
				xLine++;	
				node* nodeI = (node*)this->getChildByTag(i);
				node* nodeJ = (node*)this->getChildByTag(j);
				lines[xLine]=line::create(nodeI,nodeJ,node::a[i][j]);
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

*/
bool DrawMovie::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	
	CCLOG("ccTouchBegan");
	strike->setPosition(touch->getLocation());
	if(gameStart==true)
	{
		addChild(strike,1);
		gameStart = false;
	}
	int NodeTag = 1;
	CCPoint point = touch->getLocation();
	int tag =0;
	if(node::start==true)
	{
		
		for (tag = 1;tag<=node::amount;tag++)     
		{   
			node* Node= (node*)this->getChildByTag(tag);   
			if (isTouchGetNode(Node,touch,tag))
			{   
				NodeTag = DealNodeAndGetTag(Node,strike);
				node::start = false;
				node::beforeTag = NodeTag;
				return true;
			}
		}
	}
	else{
		for (tag = 1;tag<=node::amount;tag++)     
		{   
			node* Node = (node*)this->getChildByTag(tag);   
			if (isTouchGetNode(Node,touch,tag)&&tag!=node::beforeTag)
			{   
				node::currentTag = Node->tag;
				if(node::a[node::beforeTag][node::currentTag]>0)
				{
					lineRespond(Node,(node::a[node::beforeTag][node::currentTag]-1));
				
				//实现算法："如果不是第一个点，则当前点为i，触摸到点（j）的时候如果可连（a[i][j]==1）时，
				//将触摸点记录（即为i），a[i][j]=0,a[j][i]=0;触摸点开始闪，之前点停止闪烁"	
					node::a[node::beforeTag][node::currentTag]--;
					node::a[node::currentTag][node::beforeTag]--;

					NodeTag = DealNodeAndGetTag(Node,strike);
					node::count++;
					node *bnode =(node*)this->getChildByTag(node::beforeTag);
					for(int i = 0;i<aHalfOfNumberOfSpecialNodes;i++)
						if(NodeTag!=node::specialNodes[i][0]&&NodeTag!=node::specialNodes[i][1])
						{
							bnode->stopAllActions(); 
							bnode->NodeChange(bnode->color);
						}
				//添加记录了line的beforeTag	
					node::beforeTag = NodeTag;
					return true;
				}
			}
		}	
	}
	return false;   
}

void DrawMovie::ccTouchMoved(CCTouch* touch, CCEvent* event){
	CCLOG("ccTouchMoved");
	int tag ,NodeTag = 1;
	if(node::start==false)
	{
		for (tag = 1;tag<=node::amount;tag++)     
		{   
			node* Node= (node*)this->getChildByTag(tag);   
			if (isTouchGetNode(Node,touch,tag)&&tag!=node::beforeTag)
			{  
				
				node::currentTag = Node->tag;
				if(node::a[node::beforeTag][node::currentTag]>0)
				{
					lineRespond(Node,(node::a[node::beforeTag][node::currentTag]-1));
				
				//实现算法："如果不是第一个点，则当前点为i，触摸到点（j）的时候如果可连（a[i][j]==1）时，
				//将触摸点记录（即为i），a[i][j]=0,a[j][i]=0;触摸点开始闪，之前点停止闪烁"
					node::a[node::beforeTag][node::currentTag]--;
					node::a[node::currentTag][node::beforeTag]--;
					NodeTag = DealNodeAndGetTag(Node,strike);
					node::count++;
					node *bnode =(node*)this->getChildByTag(node::beforeTag);
					bnode->stopAllActions();
					bnode->NodeChange(bnode->color);
					node::beforeTag = NodeTag;
				}
			}
		}
	}

}

void DrawMovie::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	CCLOG("ccTouchEnded");
}
void DrawMovie::menuReInit(CCObject* pSender)
{
	node::start = true;
	node::count = 0;

	line::amount = 0;
	line::count = 0;
	line::beforeTag = 0;

	arrayInit(node::a);
	node::specialNodesInit();
	if(node::beforeTag!=0)
	{
		//把之前闪烁点初始化
		node *Node = (node*)this->getChildByTag(node::beforeTag);
		Node->stopAllActions();
		node::currentTag = 0;
		if(node::beforeTag!=0)
		{
			node::beforeTag = 0;
			for(int i = 1;i<=node::amount;i++)
				for(int j=i+1;j<=node::amount;j++)
					if(node::a[i][j]>=1)
					{
						int lineTag = i*100+j;
						line *targetLine = (line *)this->getChildByTag(lineTag);
						targetLine->LineChange(node::a[i][j]);
					}
		}
		//把所有点初始化
		for(int nodeTag = 1;nodeTag<=node::amount;nodeTag++)
		{
			node *Node = (node*)getChildByTag(nodeTag);
			Node->initNode();
		}
	}
}
void DrawMovie::menuGuess1(CCObject* pSender)
{
	if(line::amount==15)
	{
		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
		CCSprite *pFail = CCSprite::create("Fail.png");
		pFail->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
		this->addChild(pFail,1);
	}
}
void DrawMovie::menuGuess2(CCObject* pSender)
{
	if(line::amount==15)
	{
		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
		CCSprite *pSuccess = CCSprite::create("Success.png");
		pSuccess->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
		this->addChild(pSuccess,1);
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