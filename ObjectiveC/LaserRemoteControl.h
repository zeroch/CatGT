//
//  LaserRemoteControl.h
//  SampleObjectiveC
//
//  Created by Zeheng Chen on 9/20/14.
//  Copyright (c) 2014 Leap Motion. All rights reserved.
//

#import <Foundation/Foundation.h>


typedef NS_ENUM(NSInteger, LaserGestureDirection){
    LaserGestureDirectionUP,
    LaserGestureDirectionDown,
    LaserGestureDirectionLeft,
    LaserGestureDirectionRight,
    LaserGestureDirectionNone
};



@interface LaserRemoteControl : NSObject


+(id)sharedManager;

-(void)updateSwipeGesture:(LaserGestureDirection)direction;
-(void)updateOnAnOffLaser:(BOOL)toggle;


@end
