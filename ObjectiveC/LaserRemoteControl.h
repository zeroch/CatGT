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


extern NSString *const directionUp;
extern NSString *const directionDown;
extern NSString *const directionLeft;
extern NSString *const directionRight;
extern NSString *const powerOn;
extern NSString *const powerOff;


@interface LaserRemoteControl : NSObject <NSStreamDelegate>


+(id)sharedManager;

-(void)updateSwipeGesture:(LaserGestureDirection)direction;
-(void)updateOnAnOffLaser:(BOOL)toggle;

@end
