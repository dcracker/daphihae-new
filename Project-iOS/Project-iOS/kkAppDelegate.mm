//
//  kkAppDelegate.m
//  Project-iOS
//
//  Created by Robin Kang on 2014. 3. 20..
//  Copyright (c) 2014년 KangRobin. All rights reserved.
//

#import "kkAppDelegate.h"

#include "Common/MainGameLoop.h"
#include "iOSGraphics.h"
#include "iOSPlatform.h"
#include "iOSTimer.h"
#include "OpenGLTest.h"
#include <unistd.h>

@implementation kkAppDelegate

@synthesize m_Graphics;



- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    // Override point for customization after application launch.

    NSString* strPath = [[NSBundle mainBundle] resourcePath];
    chdir( [strPath cStringUsingEncoding:NSUTF8StringEncoding] );

    CIOSGraphics* graphics = new CIOSGraphics();
    CIOSPlatform* platform = new CIOSPlatform( graphics );
    OpenGLTest* game = new OpenGLTest( platform );
    CIOSTimer* timer = new CIOSTimer();
    
    MainGameLoop* gameLoop = new MainGameLoop( game, platform, timer );
    
    m_Graphics = (void*)graphics;
    m_Platform = (void*)platform;
    m_GameLogic = (void*)game;
    m_Timer = (void*)timer;
    m_GameLoop = (void*)gameLoop;
    
    gameLoop->PushMessage( MainGameLoop::MSG_WINDOW_SET, NULL );

    return YES;
}
							
- (void)applicationWillResignActive:(UIApplication *)application
{
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
    NSLog( @"application did enter background" );
    MainGameLoop* gameLoop = (MainGameLoop*)m_GameLoop;
    gameLoop->Stop();
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
    NSLog( @"application did become active" );
    [self StartRenderLoop];
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
    NSLog( @"application will terminate" );
    
    MainGameLoop* gameLoop = (MainGameLoop*)m_GameLoop;
    gameLoop->Stop();
    
    delete (CIOSGraphics*)m_Graphics;
    delete (CIOSPlatform*)m_Platform;
    delete (OpenGLTest*)m_GameLogic;
    delete (CIOSTimer*)m_Timer;
    delete (MainGameLoop*)m_GameLoop;
}

- (void)StartRenderLoop
{
    CIOSGraphics* graphics = (CIOSGraphics*)m_Graphics;
    if ( graphics->isRenderViewReady() )
    {
        MainGameLoop* gameLoop = (MainGameLoop*)m_GameLoop;
        gameLoop->Start();
    }
}

- (void)ResizeView
{
    MainGameLoop* gameLoop = (MainGameLoop*)m_GameLoop;
    gameLoop->PushMessage( MainGameLoop::MSG_WINDOW_SET, NULL );
}

- (void)TouchBegan:(CGPoint)point
{
    int* touchParams = new int[4];
    touchParams[0] = TouchEvent::TOUCH_DOWN;
    touchParams[1] = 0;
    touchParams[2] = (int)point.x;
    touchParams[3] = (int)point.y;
    
    MainGameLoop* gameLoop = (MainGameLoop*)m_GameLoop;
    gameLoop->PushMessage( MainGameLoop::MSG_TOUCH_EVENT, touchParams );
    
    NSLog( @"touch passed" );
}

- (void)TouchMoved:(CGPoint)point
{
    int* touchParams = new int[4];
    touchParams[0] = TouchEvent::TOUCH_DRAG;
    touchParams[1] = 0;
    touchParams[2] = (int)point.x;
    touchParams[3] = (int)point.y;
    
    MainGameLoop* gameLoop = (MainGameLoop*)m_GameLoop;
    gameLoop->PushMessage( MainGameLoop::MSG_TOUCH_EVENT, touchParams );
}

- (void)TouchEnded:(CGPoint)point
{
    int* touchParams = new int[4];
    touchParams[0] = TouchEvent::TOUCH_UP;
    touchParams[1] = 0;
    touchParams[2] = (int)point.x;
    touchParams[3] = (int)point.y;
    
    MainGameLoop* gameLoop = (MainGameLoop*)m_GameLoop;
    gameLoop->PushMessage( MainGameLoop::MSG_TOUCH_EVENT, touchParams );
}

@end
