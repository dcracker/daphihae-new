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
    
//    [self.view setUserInteractionEnabled:YES];
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

@end
