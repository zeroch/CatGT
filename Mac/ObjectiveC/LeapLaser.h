//
//  LeapLaser.h
//  SampleObjectiveC
//
//  Created by Zeheng Chen on 9/21/14.
//  Copyright (c) 2014 Leap Motion. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LeapObjectiveC.h"

@interface LeapLaser : NSObject<LeapListener>

-(void)run;

@end
