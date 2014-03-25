//
//  kkRenderView.m
//  Project-iOS
//
//  Created by Robin Kang on 2014. 3. 24..
//  Copyright (c) 2014년 KangRobin. All rights reserved.
//

#import "kkRenderView.h"

@implementation kkRenderView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
    }
    return self;
}


// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
    NSLog( @"draw" );
}


+ (Class)layerClass
{
    return [CAEAGLLayer class];
}

@end
