//
//  LaserRemoteControl.m
//  SampleObjectiveC
//
//  Created by Zeheng Chen on 9/20/14.
//  Copyright (c) 2014 Leap Motion. All rights reserved.
//

#import "LaserRemoteControl.h"

#define DIRECTION_THRESHOLD_LEFT_RIGHT 10
#define DIRECTION_THRESHOLD_UP_DOWN 20

static LaserRemoteControl *sharedManager =nil;
static dispatch_queue_t serialQueue;



@interface LaserRemoteControl ()

@property(nonatomic)int leftCount;
@property(nonatomic)int rightCount;
@property(nonatomic)int upCount;
@property(nonatomic)int downCount;
@property(nonatomic)int onCount;
@property(nonatomic)int offCount;
@property(nonatomic)BOOL updateGesture;
@property(nonatomic)LaserGestureDirection direction;
@end

@implementation LaserRemoteControl

+(id)sharedManager{
    
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedManager = [[self alloc]init];
        serialQueue = dispatch_queue_create("com.laserGesture.queue", DISPATCH_QUEUE_SERIAL);
    });
    return sharedManager ;
}

-(instancetype)init{
    
    self = [super init];
    if (self) {
        
    }
    return self;
}

-(void)update{
    
    NSLog(@"Updating Gesture %ld",self.direction);
    
    
    //Do HTTP Post here.
    
    
    self.updateGesture = false;
    self.leftCount = 0 ;
    self.rightCount = 0;
    self.upCount = 0;
    self.downCount = 0;
    self.direction = LaserGestureDirectionNone;

}



-(void)updateSwipeGesture:(LaserGestureDirection)direction{
    
    dispatch_async(serialQueue, ^{
        switch (direction) {
            case LaserGestureDirectionUP:
                _upCount++;
                break;
            case LaserGestureDirectionDown:
                _downCount++;
                break;
            case LaserGestureDirectionLeft:
                _leftCount++;
                break;
            case LaserGestureDirectionRight:
                _rightCount++;
            default:
                break;
        }
        
        
        if (_upCount > DIRECTION_THRESHOLD_UP_DOWN) {
            _updateGesture = true;
            _direction = LaserGestureDirectionUP;
        }
        
        else if (_downCount > DIRECTION_THRESHOLD_UP_DOWN){
            _updateGesture = true;
            _direction = LaserGestureDirectionDown;
        }
        
        else if (_leftCount > DIRECTION_THRESHOLD_LEFT_RIGHT){
            _updateGesture = true;
            _direction = LaserGestureDirectionLeft;
        }
        
        else if (_rightCount > DIRECTION_THRESHOLD_LEFT_RIGHT){
            _updateGesture = true;
            _direction = LaserGestureDirectionRight;
        }
        
        dispatch_async(dispatch_get_main_queue(), ^{
            if (_updateGesture) {
                [self update];
            }
        });
    });
}




@end
