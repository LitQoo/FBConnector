//
//  GameScene.cpp
//  ArcherWorldCupX
//
//  Created by apple on 12. 7. 6..
//  Copyright (c) 2012년 __MyCompanyName__. All rights reserved.
//

#include "StartScene.h"
using namespace cocos2d;
using namespace CocosDenshion;


CCScene* StartScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    StartScene *layer = StartScene::create();
	
    // add layer as a child to scene
    scene->addChild(layer);
	
    // return the scene
    return scene;
}


bool StartScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
	CCLog("appStart~~1");
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
//    JNIKelper::getInstance()->callJava_simple("topAdmob");
//    JNIKelper::getInstance()->callJava_simple("showAdmob");
#endif
    setKeypadEnabled(true);
    
    isFirst = CCUserDefault::sharedUserDefault()->getIntegerForKey("isFirst");
    if(isFirst!=7){   
        //CCLog("is first : set sound");
        CCUserDefault::sharedUserDefault()->setBoolForKey("sound", true);
        CCUserDefault::sharedUserDefault()->setBoolForKey("review", false);
        //CCLog("is first : set flag");
        CCUserDefault::sharedUserDefault()->setStringForKey("flag", "us");
        CCUserDefault::sharedUserDefault()->setStringForKey("nick", "");
        //CCLog("is first ");
        CCUserDefault::sharedUserDefault()->setIntegerForKey("isFirst", 7);
        CCUserDefault::sharedUserDefault()->setIntegerForKey("maxPoint", 0);
        CCUserDefault::sharedUserDefault()->setIntegerForKey("gold", 0);
        CCUserDefault::sharedUserDefault()->setIntegerForKey("silver", 0);
        CCUserDefault::sharedUserDefault()->setIntegerForKey("bronze", 0);
        CCUserDefault::sharedUserDefault()->setIntegerForKey("topten", 0);
        //CCLog("is first");
        
        CCUserDefault::sharedUserDefault()->flush();
    }
    
    
    isMain=true;

    CCSprite *bg1 = CCSprite::create("topBG1.png");
    bg1->setAnchorPoint(ccp(0,0));
    this->addChild(bg1,1);
    
    CCSprite *bg2 = CCSprite::create("bottomBG1.png");
    bg2->setAnchorPoint(ccp(0,0));
    this->addChild(bg2,2);
    
    
    wStartLayer = new WorldCupStartView;
    wStartLayer->initWithDelegate(this, menu_selector(StartScene::startWorldCup), menu_selector(StartScene::backToWorldCup));
    wStartLayer->setPosition(ccp(0,480));
    this->addChild(wStartLayer,3);
    
    optionLayer = new OptionView;
    optionLayer->initWithDelegate(this, menu_selector(StartScene::backToOption));
    optionLayer->setPosition(ccp(0,480));
    this->addChild(optionLayer,3);
    
    mainView = new CCLayer;
    mainView->init();
    mainView->setAnchorPoint(ccp(0.5,0.5));
    mainView->setPosition(ccp(0,0));
    this->addChild(mainView,3);
    
    
    CCSprite *mainBg = CCSprite::create("viewbg.png");
    mainBg->setAnchorPoint(ccp(0.5,0.5));
    mainBg->setPosition(ccp(160,215));
    mainView->addChild(mainBg,3);
    
    inviteMsg = "Invite";
//    CCSprite *mainMenuImg = CCSprite::create("mainMenu.png");
//    mainMenuImg->setAnchorPoint(ccp(0.5,0.5));
//    mainMenuImg->setPosition(ccp(160,140));
//    mainView->addChild(mainMenuImg,4);

    CCSprite *mainPan = CCSprite::create("title.png");
    mainPan->setAnchorPoint(ccp(0.5,0.5));
    mainPan->setPosition(ccp(160,385));
    mainView->addChild(mainPan,4);

    
    CCSprite *fb_tableBack = CCSprite::create("fb_tableBack.png");
    fb_tableBack->setAnchorPoint(ccp(0.5,0.5));
    fb_tableBack->setPosition(ccp(160,240));
    mainView->addChild(fb_tableBack,4);
    
    fbTable = new LQTableView;
    fbTable->init(26, 118, 268, 245, this, callTableCell_selector(StartScene::FBTableCell));
    mainView->addChild(fbTable,5);
    fbTable->release();
    
    
    fbLoginButton = CCSprite::create("fb_login.png");
    fbLoginButton->setAnchorPoint(ccp(0.5,0.5));
    fbLoginButton->setPosition(ccp(160,240));
    mainView->addChild(fbLoginButton,7);
    
    fbLoading = CCLabelTTF::create("Loading..", "apple godhic", 20);
    fbLoading->setColor(ccc3(255, 255, 255));
    fbLoading->setPosition(ccp(160,240));
    mainView->addChild(fbLoading,6);
    
    fbMessage = CCLabelTTF::create("Connect with your friends through Facebook. \n\n We will not upload anything to Facebook without the user’s permission. :)", CCSizeMake(250,200), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter, "", 14);
    fbMessage->setColor(ccc3(255, 255, 255));
    fbMessage->setPosition(ccp(125,115));
    fbLoginButton->addChild(fbMessage,6);
        
    //We will not upload anything to Facebook without the user’s permission.
    //Connect with your friends through Facebook.
    
    {
        LQButton *menu = new LQButton;
        menu->init();
        menu->setAnchorPoint(ccp(0.5,0.5));
        menu->setFrame(126,115, 250, 230);
        menu->setTargetAndSelector(this, menu_selector(StartScene::FBLogin));
        menu->setBackgroundColor(ccc4(0, 0, 0, 0));
        fbLoginButton->addChild(menu,10);
        menu->release();
    }
    
    CCSprite *menu_all = CCSprite::create("menu_all.png");
    menu_all->setAnchorPoint(ccp(0.5,0.5));
    menu_all->setPosition(ccp(160,60));
    mainView->addChild(menu_all,4);
    
    {
        LQButton *menu = new LQButton;
        menu->init();
        menu->setAnchorPoint(ccp(0.5,0.5));
        menu->setFrame(67,80, 82, 34);
        menu->setTargetAndSelector(this, menu_selector(StartScene::openOption));
        menu->setBackgroundColor(ccc4(0, 0, 0, 0));
        mainView->addChild(menu,10);
        menu->release();
    }
    {
        LQButton *menu = new LQButton;
        menu->init();
        menu->setAnchorPoint(ccp(0.5,0.5));
        menu->setFrame(67,41, 82, 34);
        menu->setTargetAndSelector(this, menu_selector(StartScene::moreApps));
        menu->setBackgroundColor(ccc4(0, 0, 0, 0));
        mainView->addChild(menu,10);
        menu->release();
    }
    
    {
        LQButton *menu = new LQButton;
        menu->init();
        menu->setAnchorPoint(ccp(0.5,0.5));
        menu->setFrame(147,62, 59, 73);
        menu->setTargetAndSelector(this, menu_selector(StartScene::startSingle));
        menu->setBackgroundColor(ccc4(0, 0, 0, 0));
        mainView->addChild(menu,10);
        menu->release();
    }
    
    {
        LQButton *menu = new LQButton;
        menu->init();
        menu->setAnchorPoint(ccp(0.5,0.5));
        menu->setFrame(239,62, 110, 73);
        menu->setTargetAndSelector(this, menu_selector(StartScene::openWorldCup));
        menu->setBackgroundColor(ccc4(0, 0, 0, 0));
        mainView->addChild(menu,10);
        menu->release();
    }
    
    
//    LQLabel *test = new LQLabel;
//    test->init();
//    test->setAnchorPoint(ccp(0.5,0.5));
//    test->setFrame(160, 390, 200, 30);
//    test->setShadowColor(ccc3(180, 180, 0));
//    test->setShadow(true, 2);
//    test->setText("Archer World Cup");
//    test->setTextSize(30);
//    test->setTextColor(ccYELLOW);
//    mainView->addChild(test,4);
//    test->release();

//
//    CCMenuItemImage *menu1 = CCMenuItemImage::create("menu01.png", "menu01.png", this, menu_selector(StartScene::startSingle));
//    CCMenuItemImage *menu2 = CCMenuItemImage::create("menu02.png", "menu02.png", this, menu_selector(StartScene::openWorldCup));
//    CCMenuItemImage *menu3 = CCMenuItemImage::create("menu03.png", "menu03.png", this, menu_selector(StartScene::openOption));
//    CCMenuItemImage *menu4 = CCMenuItemImage::create("menu04.png", "menu04.png", this, menu_selector(StartScene::moreApps));
//  
//    CCMenu *mainMenu = CCMenu::create(menu1,menu2,menu3,menu4,NULL);
//    mainMenu->alignItemsVertically();
//    mainMenu->setAnchorPoint(ccp(0,0));
//    mainMenu->setPosition(ccp(160,125));
//    mainView->addChild(mainMenu,4);
//    
//    LQButton *menu = new LQButton;
//    menu->init();
//    menu->setAnchorPoint(ccp(0.5,0.5));
//    menu->setFrame(0,0, 100, 100);
//    menu->setText("fblogin");
//    menu->setTextSize(20);
//    // menu->setShadowColor(ccc3(180, 180, 0));
//    // menu->setShadow(true, 1);
//    menu->setTextColor(ccWHITE);
//    menu->setTargetAndSelector(this, menu_selector(StartScene::FBLogin));
//    menu->setBackgroundColor(ccc4(0, 0, 0, 255));
//    this->addChild(menu,22.);
    if(FBConnector::get()->isUsed()){
        CCLog("init login");
        fbLoginButton->setVisible(false);
        FBConnector::get()->login(this, fb_selector(StartScene::FBLogined));
    }

    
	return true;
}
void StartScene::onEnter(){
    CCLayer::onEnter();
    
    if(FBConnector::get()->isLogin()){
        switch (rand()%3) {
            case 0:inviteMsg="Invite";
                break;
            case 1:inviteMsg="Together";
                break;
            case 2:inviteMsg="Battle";
                break;
            default:
                break;
        }
        fbTable->reset();
        fbLoginButton->setVisible(false);
        fbLoading->setString("Load ranking..");
        fbLoading->setVisible(true);
        FBConnector::get()->getScores(this, fb_selector(StartScene::FBgetScores));
    }
    
}
void StartScene::FBLogin(){
    fbLoginButton->setVisible(false);
    fbLoading->setVisible(true);
    CCLog("start fblogin1");
    FBConnector::get()->login(this, fb_selector(StartScene::FBLogined));
    CCLog("start fblogin1");
}
void StartScene::FBLogined(JsonBox::Value _value){
    
    CCLog("start fblogined");
    JsonBox::Object _info = _value.getObject();
    CCLog("ok %s",_value.getString().c_str());
    
    if(_info["error"].getInt()==FBSuccess){
        fbLoginButton->setVisible(false);
        FBConnector::get()->getScores(this, fb_selector(StartScene::FBgetScores));
        fbLoading->setString("Load ranking..");
        fbLoading->setVisible(true);
    }else{
        fbMessage->setString("Error, try again");
        fbLoginButton->setVisible(true);
    }
}

void StartScene::FBgetScores(JsonBox::Value _value){
    CCLog("getscores..0");
    JsonBox::Array scorearray = _value.getArray();

    CCLog("getscores..1");
    if(scorearray.size()>0){
        
        
        CCLog("getscores..2");
        fblist.clear();
        fblist=_value.getArray();
        fbTable->loadTable(fblist.size());
        fbLoading->setVisible(false);
    }
}

LQTableViewCell* StartScene::FBTableCell(CCNode *_obj){
    int row= _obj->getTag();
    JsonBox::Object scoreinfo = fblist[row].getObject();
    JsonBox::Object user = scoreinfo["user"].getObject();
    int score = scoreinfo["score"].getInt();
    ccColor4B backcolor;
    
    if(score<0){
        backcolor=ccc4(59, 89, 151, 200);
    }else if(row==0){
        backcolor=ccc4(255, 228, 0, 255);
    }else if(row==1){
        backcolor=ccc4(180, 180, 180, 255);
    }else if(row==2){
        backcolor=ccc4(200, 170, 130, 255);
        
    }else{
        backcolor=ccc4(59, 89, 151, 200);
    }
    LQTableViewCell *cell = LQTableViewCell::create(0, 0, 280, 40,backcolor);
    
    
    CCLabelTTF *rank = CCLabelTTF::create(CCString::createWithFormat("%d",row+1)->getCString(), CCSizeMake(50, 50), kCCTextAlignmentCenter, "", 25);
    rank->setAnchorPoint(ccp(0.5,0.5));
    rank->setPosition(ccp(20,10));
    cell->addChild(rank,1);
    
    CCSprite *_pic = FBConnector::get()->getProfileSprite(user["id"].getString(), 40, 40);
    _pic->setAnchorPoint(ccp(0.5,0.5));
    _pic->setPosition(ccp(60,20));
    cell->addChild(_pic,1);
    
    CCLabelTTF *name = CCLabelTTF::create(user["name"].getString().c_str(), CCSizeMake(100, 15), kCCTextAlignmentLeft, "", 12);
    name->setAnchorPoint(ccp(0.5,0.5));
    name->setPosition(ccp(140,32));
    cell->addChild(name,1);
    

    
    
    
    string _scoreMsg;
    string _inviteMsg;
    if(score<0){
        _scoreMsg="0";
        _inviteMsg=inviteMsg;
    }else{
        _scoreMsg=CCString::createWithFormat("%d",score)->getCString();
        _inviteMsg="Battle";
    }
    
    CCLabelTTF *_score = CCLabelTTF::create(_scoreMsg.c_str(), CCSizeMake(100, 25), kCCTextAlignmentLeft, "", 20);
    _score->setAnchorPoint(ccp(0.5,0.5));
    _score->setPosition(ccp(140,12));
    cell->addChild(_score,1);
    
    LQButton *invite = new LQButton;
    invite->init();
    invite->setAnchorPoint(ccp(0.5,0.5));
    invite->setFrame(235,20, 50, 30);
    invite->setText(_inviteMsg.c_str());
    invite->setTextColor(ccc3(0, 0, 0));
    invite->setBackgroundColor(ccc4(255, 255, 255,255));
    invite->setTargetAndSelector(this, menu_selector(StartScene::FBsendInvite));
    invite->setTag(row);
    cell->addChild(invite,10);
    invite->release();
    
    return cell;
    
}
void StartScene::FBsendInvite(CCNode *_node){
    int row = _node->getTag();
    JsonBox::Object _scores = fblist[row].getObject();
    JsonBox::Object _user = _scores["user"].getObject();
    srand(time(NULL));
    if(rand()%10<2 || _scores["score"].getInt()<0){
        FBConnector::get()->sendInvite(_user["id"].getString(),"ArcherWorldCup", "Play with me!", "http://litqoo.com/ArcherWorldCup", "http://litqoo.com/ArcherWorldCup/icon.jpg", this, fb_selector(StartScene::FBsendedInvite));
    }else{
        FBConnector::get()->sendRequest(_user["id"].getString(), "Play with me!", "", this, fb_selector(StartScene::FBsendedInvite));
    }
}

void StartScene::FBsendedInvite(JsonBox::Value _value){
    
}
void StartScene::onEnterTransitionDidFinish(){
    string nick = CCUserDefault::sharedUserDefault()->getStringForKey("nick");
    if(nick==""){   
        PSModalAlertShowAlert("Welcome!", "You need to set the country and Nick-name.", 1,"OK",this,callfunc_selector(StartScene::writeNick));
    }
}

void StartScene::writeNick(CCNode *_node){
    this->openOption();
    optionLayer->nick->attachWithIME();
}
void StartScene::moreApps(){
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    JNIKelper::getInstance()->callJava_simple("showMoreApps");
#endif
}
void StartScene::openOption(){
    isMain=false;
    CCMoveTo *moveTo = CCMoveTo::create(0.2, ccp(0,480));
    mainView->runAction(moveTo);
    
    CCMoveTo *moveTo2 = CCMoveTo::create(0.2, ccp(0,0));
    optionLayer->runAction(moveTo2);
}
void StartScene::backToWorldCup(){
    isMain=true;
    wStartLayer->closeWebView();
    
    CCMoveTo *moveTo = CCMoveTo::create(0.2, ccp(0,0));
    mainView->runAction(moveTo);
    
    CCMoveTo *moveTo2 = CCMoveTo::create(0.2, ccp(0,480));
    wStartLayer->runAction(moveTo2);
    
}
void StartScene::backToOption(){
    isMain=true;
    
    if(CCUserDefault::sharedUserDefault()->getStringForKey("nick").length()>0){
    optionLayer->closeOption();
    
    CCMoveTo *moveTo = CCMoveTo::create(0.2, ccp(0,0));
    mainView->runAction(moveTo);
    
    CCMoveTo *moveTo2 = CCMoveTo::create(0.2, ccp(0,480));
    optionLayer->runAction(moveTo2);
        
    }else{
        optionLayer->nick->attachWithIME();
    }
}

void StartScene::startSingle(){
    GameScene *singleScene=GameScene::create();
    CCDirector::sharedDirector()->pushScene((CCScene *)singleScene);
}



void StartScene::openWorldCup(){
    
    isMain=false;
    
    CCMoveTo *moveTo = CCMoveTo::create(0.2, ccp(0,480));
    mainView->runAction(moveTo);
    
    CCMoveTo *moveTo2 = CCMoveTo::create(0.2, ccp(0,0));
    wStartLayer->runAction(moveTo2);
    
    wStartLayer->loadWebView();
    
}
//void StartScene::finishLoadWorldCupStartView(string buff){
//    //CCLog("loaded webView33 : %s",buff.c_str());
//    
//
//    
//    if (buff=="") {
//        this->schedule(schedule_selector(StartScene::worldCupError));
//        return;
//    }else {
//        this->schedule(schedule_selector(StartScene::finishLoadWorldCupStartViewOGL));
//    }
//    //CCLog("online start menu visible true");
//}

//void StartScene::finishLoadWorldCupStartViewOGL(){
//    wStartLayer->startButton->setVisible(true);
//    wStartLayer->closeButton->setVisible(true);
//}


void StartScene::startWorldCup(){
    
    
    
    wStartLayer->startButton->setVisible(false);
    wStartLayer->closeButton->setVisible(false);
    //CCLog("online start menu visible false");
    
    string mynick = CCUserDefault::sharedUserDefault()->getStringForKey("nick");
    
    if (mynick=="") {
        PSModalAlertShowAlert("Error", "set your nickname in option", 1,"OK",this,callfunc_selector(StartScene::backToWorldCup));
        return;
    }

    int gold = CCUserDefault::sharedUserDefault()->getIntegerForKey("gold");
    int silver = CCUserDefault::sharedUserDefault()->getIntegerForKey("silver");
    int bronze = CCUserDefault::sharedUserDefault()->getIntegerForKey("bronze");
    int topten = CCUserDefault::sharedUserDefault()->getIntegerForKey("topten");
    
    if(gold && silver && bronze && topten){}
    
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    
    string ServerURL = "http://www.litqoo.com/app/archery2/android_getNewID.php";		//아이디 받을주소

    
    //닉네임받아오기
    string nick = CCUserDefault::sharedUserDefault()->getStringForKey("nick"); //NSDefault::getUserName();
    string flag = CCUserDefault::sharedUserDefault()->getStringForKey("flag");
    string request = KS_Util::stringWithFormat("%s?nick=%s&flag=%s&g=%d&s=%d&b=%d&t=%d&fbid=%s",
                                               ServerURL.c_str(),
                                               KS_Util::ansi2UTF8(nick).c_str(),
                                               flag.c_str(),
                                               gold,silver,bronze,topten,FBConnector::get()->userID.c_str());
 
    JNIKelper::getInstance()->callJava_getDataFromURL(request, this,recv_selector(StartScene::finishGetID));
#endif
    
    
}


void StartScene::finishGetID(string buff){
    
    int tempid = atoi(buff.c_str());
    
    
    if(tempid==-1){
        this->schedule(schedule_selector(StartScene::worldCupErrorNick));    

        return;
    }else if(tempid<=0){
        this->schedule(schedule_selector(StartScene::worldCupError));
        return;
    }
    
    
    CCUserDefault::sharedUserDefault()->setStringForKey("onlineID", buff);
    CCUserDefault::sharedUserDefault()->flush();

    
    
    this->schedule(schedule_selector(StartScene::pushWorldCupScene));
    
}
void StartScene::worldCupErrorNick(float dt){
    
    
    
    wStartLayer->startButton->setVisible(true);
    wStartLayer->closeButton->setVisible(true);
    
    this->unschedule(schedule_selector(StartScene::worldCupErrorNick));
    
    PSModalAlertShowAlert("Error", "Please change your nick-name and connect again.", 1,"OK",this,callfunc_selector(StartScene::backToWorldCup));
    
}
void StartScene::worldCupError(float dt){
    
    wStartLayer->startButton->setVisible(true);
    wStartLayer->closeButton->setVisible(true);
    
    this->unschedule(schedule_selector(StartScene::worldCupError));
    
    
    PSModalAlertShowAlert("Error", "Check your network state", 1,"OK",this,callfunc_selector(StartScene::backToWorldCup));
    

}
void StartScene::pushWorldCupScene(float dt){
    //CCLog("online start menu visible true");
    
    
    this->unschedule(schedule_selector(StartScene::pushWorldCupScene));
    
    wStartLayer->startButton->setVisible(true);
    wStartLayer->closeButton->setVisible(true);
    
    this->backToWorldCup();
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    JNIKelper::getInstance()->callJava_simple("deleteWebView");
#endif
    
    
    WorldCupScene *onlineScene=WorldCupScene::create();
    CCDirector::sharedDirector()->pushScene((CCScene *)onlineScene);
}



StartScene::~StartScene(){
    mainView->release();
    wStartLayer->release();
    optionLayer->release();
}
//void GameScene::menuCloseCallback(CCObject* pSender)
//{
//    CCDirector::sharedDirector()->end();
//	
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif
//}
