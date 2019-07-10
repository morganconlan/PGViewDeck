//
//  PGViewDeckTransitionCoordinator.h
//  Pods
//
//  Created by Michael Ochs on 7/9/16.
//
//

#import <UIKit/UIKit.h>

#import "IIEnvironment.h"


NS_ASSUME_NONNULL_BEGIN

@class PGViewDeckController;
@interface PGViewDeckLayoutSupport : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithViewDeckController:(PGViewDeckController *)viewDeckController NS_DESIGNATED_INITIALIZER;

- (CGRect)frameForSide:(PGViewDeckSide)side openSide:(PGViewDeckSide)openSide;

@end

NS_ASSUME_NONNULL_END
