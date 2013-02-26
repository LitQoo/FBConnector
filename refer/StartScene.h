//
//  GameScene.h
//  ArcherWorldCupX
//
//  Created by apple on 12. 7. 6..
//  Copyright (c) 2012년 __MyCompanyName__. All rights reserved.
//

#ifndef ArcherWorldCupX_StartScene_h
#define ArcherWorldCupX_StartScene_h

#include <string.h>
#include "cocos2d.h"
#include "GameScene.h"
#include "WorldCupScene.h"
#include "WorldCupStartView.h"
#include "OptionView.h"
#include "utf8.h"
#include "fullADScene.h"
#include "SimpleAudioEngine.h"
#include "JNIKelper.h"
#include "KSLabelTTF.h"
#include "LQLabel.h"
#include "LQButton.h"
#include "PSModalAlert.h"
#include "FBConnector.h"
#include "JsonBox.h"
#include "LQTableView.h"
using namespace std;
using namespace cocos2d;

class ShotResult;
class RoundView;
class OverView;
class StartScene : public cocos2d::CCLayer 
{
	public:
    int isFirst;
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
	
    CCLayer *mainView;
    WorldCupStartView *wStartLayer;
    OptionView *optionLayer;
    LQTableView *fbTable;
    bool isMain;
    ~StartScene();
    
    void startSingle();
    void startWorldCup();
    void openWorldCup();
    void openOption();
    void backToWorldCup();
    void backToOption();
    void finishLoadWorldCupStartView(string buff);
    void finishGetID(string buff);
    void pushWorldCupScene(float dt);
    void worldCupError(float dt);
    void worldCupErrorNick(float dt);
    void moreApps();
    void writeNick(CCNode *node);
    void finishLoadWorldCupStartViewOGL();
    virtual void onEnter();
    
    CCSprite *fbLoginButton;
    JsonBox::Array fblist;
    CCLabelTTF *fbLoading;
    CCLabelTTF *fbMessage;
    void FBLogin();
    void FBLogined(JsonBox::Value _value);
    void FBgetScores(JsonBox::Value _value);
    void FBsendInvite(CCNode *_node);
    void FBsendedInvite(JsonBox::Value _value);
    LQTableViewCell* FBTableCell(CCNode *_obj);
    string inviteMsg;
    
    virtual void keyBackClicked() 
	{
        if(isMain==true)CCDirector::sharedDirector()->end();
        //else CCLog("is not main");
	}
    void onEnterTransitionDidFinish();
    
    LAYER_CREATE_FUNC(StartScene);
};

#endif