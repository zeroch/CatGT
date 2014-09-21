//
//  LaserRemoteControl.m
//  SampleObjectiveC
//
//  Created by Zeheng Chen on 9/20/14.
//  Copyright (c) 2014 Leap Motion. All rights reserved.
//

#import "LaserRemoteControl.h"
#import <Foundation/NSStream.h>


#define DIRECTION_THRESHOLD_LEFT_RIGHT 10
#define DIRECTION_THRESHOLD_UP_DOWN 10
#define POWER_THREDSHOLD_ON_OFF 30

NSString *const directionUp = @"UP";
NSString *const directionDown = @"DOWN";
NSString *const directionLeft = @"A";
NSString *const directionRight = @"B";
NSString *const powerOn = @"C";
NSString *const powerOff = @"D";

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
@property(nonatomic)BOOL updatePower;
@property(nonatomic)LaserGestureDirection direction;
@property(nonatomic,strong)NSInputStream *inputStream;
@property(nonatomic,strong)NSOutputStream *outputStream;
@property(nonatomic)NSString *previousSend;
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
        [self initNetworkCommunication];
    }
    return self;
}

- (void)initNetworkCommunication {
    CFReadStreamRef readStream;
    CFWriteStreamRef writeStream;
    CFStreamCreatePairWithSocketToHost(NULL, (CFStringRef)@"198.74.55.55",4321, &readStream, &writeStream);
    //bridge Core Foundation's socket stream to IOS by doing a bridge casting.
    self.inputStream = (__bridge NSInputStream *)readStream;
    self.outputStream = (__bridge NSOutputStream *)writeStream;
    [_inputStream setDelegate:self];
    [_outputStream setDelegate:self];
    [self.inputStream scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    [self.outputStream scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    [self.inputStream open];
    [self.outputStream open];
}

-(void)reset{
    self.updateGesture = false;
    self.leftCount = 0 ;
    self.rightCount = 0;
    self.upCount = 0;
    self.downCount = 0;
    self.direction = LaserGestureDirectionNone;
    self.onCount = 0;
    self.offCount = 0;
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
                //Do TCP Socket here.
                [self sendGestureToServer:self.direction];
                [self reset];
            }
        });
    });
}

-(void)sendGestureToServer:(LaserGestureDirection)control{
    
    NSString *response ;
    
    switch (control) {
        case LaserGestureDirectionNone:
            response = nil;
            break;
        case LaserGestureDirectionDown:
            response = directionDown ;
            break;
        case LaserGestureDirectionUP:
            response = directionUp ;
            break;
        case LaserGestureDirectionLeft:
            response = directionLeft ;
            break;
        case LaserGestureDirectionRight:
            response = directionRight ;
        default:
            break;
    }
    if (response!=_previousSend) {

    NSData *data =[[NSData alloc] initWithData:[response dataUsingEncoding:NSASCIIStringEncoding]];
        NSLog(@"%@",response);
    _previousSend = response;
    [self.outputStream write:[data bytes] maxLength:[data length]];
    }
}

-(void)sendPowerCommandToServer{
    NSString *response;
    if (self.onCount > self.offCount) {
        response = powerOn;
    }
    else{
        response = powerOff;
    }
    
    
    if (response!=_previousSend) {
        NSData *data =[[NSData alloc] initWithData:[response dataUsingEncoding:NSASCIIStringEncoding]];
        NSLog(@"%@",response);
        _previousSend = response;
        
        [self.outputStream write:[data bytes] maxLength:[data length]];
        
        [self reset];
    }
}

-(void)updateOnAnOffLaser:(BOOL)toggle{
    
    dispatch_async(serialQueue, ^{
        if (toggle) {
            self.onCount++;
            if (self.onCount > POWER_THREDSHOLD_ON_OFF) {
                _updatePower = true;
            }
        }
        else{
            self.offCount++;
            if (self.offCount > POWER_THREDSHOLD_ON_OFF) {
                _updatePower = true;
            }
        }
        dispatch_async(dispatch_get_main_queue(), ^{
            if (_updatePower) {
                [self sendPowerCommandToServer];
            }
        });
    });
}

@end
