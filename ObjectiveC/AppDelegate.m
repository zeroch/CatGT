/******************************************************************************\
* Copyright (C) 2012-2013 Leap Motion, Inc. All rights reserved.               *
* Leap Motion proprietary and confidential. Not for distribution.              *
* Use subject to the terms of the Leap Motion SDK Agreement available at       *
* https://developer.leapmotion.com/sdk_agreement, or another agreement         *
* between Leap Motion and you, your company or other organization.             *
\******************************************************************************/

//Modified by Zeheng Chen

#import "AppDelegate.h"
#import "LeapLaser.h"

@implementation AppDelegate

// Xcode 4.2 warns if we do not explicitly synthesize
@synthesize window = _window;
@synthesize LeapLaserController = _LeapLaserController; // must retain for notifications

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    _LeapLaserController = [[LeapLaser alloc]init];
    [_LeapLaserController run];
}

@end
