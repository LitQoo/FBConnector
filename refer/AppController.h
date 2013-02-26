//
//  ArcherWorldCupXAppController.h
//  ArcherWorldCupX
//
//  Created by apple on 12. 7. 4..
//  Copyright __MyCompanyName__ 2012년. All rights reserved.
//

#import "Facebook.h"
#import "FBConnector.h"

@class RootViewController;
extern NSString *const FBSessionStateChangedNotification;

@interface AppController : NSObject <FBDialogDelegate,UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate> {
@public
	string fbRValue;
	int fbDelekey;
@protected
    UIWindow *window;
    RootViewController    *viewController;
}

@property (retain, nonatomic) RootViewController* viewController;
@property (nonatomic, retain) Facebook *facebook;
@property   (retain,nonatomic)  UIWindow *window;
@end

