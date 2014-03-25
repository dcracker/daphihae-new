//
//  kkViewController.m
//  Project-iOS
//
//  Created by Robin Kang on 2014. 3. 20..
//  Copyright (c) 2014년 KangRobin. All rights reserved.
//


#import "kkViewController.h"
#import "kkRenderView.h"
#import "kkAppDelegate.h"

#include "iOSGraphics.h"

@interface kkViewController ()

@end

@implementation kkViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    
    kkAppDelegate* appDelegate = (kkAppDelegate*)[[UIApplication sharedApplication] delegate];
    
    m_viewRender = [[kkRenderView alloc] initWithFrame:self.view.frame];
    [self.view removeFromSuperview];
    [self setView:m_viewRender];
    CIOSGraphics* graphics = (CIOSGraphics*)appDelegate.m_Graphics;
    graphics->AttachRenderView( (__bridge void*)m_viewRender, [UIScreen mainScreen].scale, true );
    
    [self.view setUserInteractionEnabled:YES];
//    [self.view setMultipleTouchEnabled:YES];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)viewDidLayoutSubviews
{
    kkAppDelegate* appDelegate = (kkAppDelegate*)[[UIApplication sharedApplication] delegate];
    [appDelegate ResizeView];
}

- (BOOL)prefersStatusBarHidden
{
    return YES;
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    // for debug
    NSLog( @"touch began count: %d", touches.count );
    for ( int i=0; i < touches.count; i++ )
    {
        UITouch* touch = [touches.allObjects objectAtIndex:i];
        CGPoint gPos = [touch locationInView:nil];
        CGPoint lPos = [touch locationInView:self.view];
        NSLog( @"- %d pos(global): %f, %f, pos(local): %f, %f", i, gPos.x, gPos.y, lPos.x, lPos.y );
    }
    //--
    
    kkAppDelegate* appDelegate = (kkAppDelegate*)[[UIApplication sharedApplication] delegate];
    UITouch* touch = (UITouch*)touches.allObjects.firstObject;
    [appDelegate TouchBegan:[touch locationInView:nil]];
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    // for debug
    NSLog( @"touch moved count: %d", touches.count );
    for ( int i=0; i < touches.count; i++ )
    {
        UITouch* touch = [touches.allObjects objectAtIndex:i];
        CGPoint gPos = [touch locationInView:nil];
        CGPoint lPos = [touch locationInView:self.view];
        NSLog( @"- %d pos(global): %f, %f, pos(local): %f, %f", i, gPos.x, gPos.y, lPos.x, lPos.y );
    }
    //--
    
    kkAppDelegate* appDelegate = (kkAppDelegate*)[[UIApplication sharedApplication] delegate];
    UITouch* touch = (UITouch*)touches.allObjects.firstObject;
    [appDelegate TouchMoved:[touch locationInView:nil]];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    // for debug
    NSLog( @"touch ended count: %d", touches.count );
    for ( int i=0; i < touches.count; i++ )
    {
        UITouch* touch = [touches.allObjects objectAtIndex:i];
        CGPoint gPos = [touch locationInView:nil];
        CGPoint lPos = [touch locationInView:self.view];
        NSLog( @"- %d pos(global): %f, %f, pos(local): %f, %f", i, gPos.x, gPos.y, lPos.x, lPos.y );
    }
    //--
    
    kkAppDelegate* appDelegate = (kkAppDelegate*)[[UIApplication sharedApplication] delegate];
    UITouch* touch = (UITouch*)touches.allObjects.firstObject;
    [appDelegate TouchEnded:[touch locationInView:nil]];
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
    // for debug
    NSLog( @"touch cancelled count: %d", touches.count );
    for ( int i=0; i < touches.count; i++ )
    {
        UITouch* touch = [touches.allObjects objectAtIndex:i];
        CGPoint gPos = [touch locationInView:nil];
        CGPoint lPos = [touch locationInView:self.view];
        NSLog( @"- %d pos(global): %f, %f, pos(local): %f, %f", i, gPos.x, gPos.y, lPos.x, lPos.y );
    }
    //--
    
    // do nothing
}

@end
