//
//  kkAppDelegate.h
//  Project-iOS
//
//  Created by Robin Kang on 2014. 3. 20..
//  Copyright (c) 2014년 KangRobin. All rights reserved.
//


#import <UIKit/UIKit.h>

@interface kkAppDelegate : UIResponder <UIApplicationDelegate>
{
    void* m_GameLoop;
    void* m_Platform;
    void* m_Graphics;
    void* m_GameLogic;
    void* m_Timer;
}

@property (strong, nonatomic) UIWindow *window;

@property (nonatomic, assign) void* m_Graphics;


- (void)StartRenderLoop;
- (void)ResizeView;


@end
