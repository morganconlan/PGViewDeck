//
//  PGViewDeckController+PGViewDeckController_Private.h
//  Pods
//
//  Created by Michael Ochs on 5/26/16.
//
//

#import "PGViewDeckController.h"

NS_ASSUME_NONNULL_BEGIN

@class PGViewDeckLayoutSupport;
@interface PGViewDeckController (Private)

@property (nonatomic, readonly) PGViewDeckLayoutSupport *layoutSupport;

- (void)openSide:(PGViewDeckSide)side animated:(BOOL)animated notify:(BOOL)notify completion:(nullable void(^)(BOOL cancelled))completion;
- (void)closeSide:(BOOL)animated notify:(BOOL)notify completion:(nullable void(^)(BOOL cancelled))completion;

@end

NS_ASSUME_NONNULL_END
