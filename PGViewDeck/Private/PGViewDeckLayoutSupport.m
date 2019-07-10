//
//  PGViewDeckTransitionCoordinator.m
//  Pods
//
//  Created by Michael Ochs on 7/9/16.
//
//

#import "PGViewDeckLayoutSupport.h"

#import "IIEnvironment+Private.h"
#import "PGViewDeckController.h"

NS_ASSUME_NONNULL_BEGIN

@interface PGViewDeckLayoutSupport ()

@property (nonatomic, assign) PGViewDeckController *viewDeckController; // this is not weak as it is a required link! If the corresponding view deck controller will be removed, this class can no longer fullfill its purpose!

@end

@implementation PGViewDeckLayoutSupport

- (instancetype)init {
    NSAssert(NO, @"Please use initWithViewDeckController: instead.");
    return self;
}

- (instancetype)initWithViewDeckController:(PGViewDeckController *)viewDeckController {
    NSParameterAssert(viewDeckController);
    self = [super init];

    _viewDeckController = viewDeckController;

    return self;
}

static inline CGSize PGViewDeckSanitizeContentSize(const CGSize size) {
    if (size.width == 0.0 || size.height == 0.0) {
        return CGSizeMake(320.0, 480.0);
    } else {
        return size;
    }
}

- (CGSize)sizeForSide:(PGViewDeckSide)side inContainer:(UIView *)containerView {
    switch (side) {
        case PGViewDeckSideNone:
            return containerView.bounds.size;
        case PGViewDeckSideLeft: {
            CGSize size = PGViewDeckSanitizeContentSize(self.viewDeckController.leftViewController.preferredContentSize);
            size.height = CGRectGetHeight(containerView.bounds);
            return size;
        }
        case PGViewDeckSideRight: {
            CGSize size = PGViewDeckSanitizeContentSize(self.viewDeckController.rightViewController.preferredContentSize);
            size.height = CGRectGetHeight(containerView.bounds);
            return size;
        }
    }
}

- (CGRect)frameForSide:(PGViewDeckSide)side openSide:(PGViewDeckSide)openSide {
    UIView *containerView = self.viewDeckController.view;
    
    CGSize size = [self sizeForSide:side inContainer:containerView];
    CGRect frame = (CGRect){ .origin = CGPointZero, .size = size };
    if (side == PGViewDeckSideRight) {
        frame.origin.x = CGRectGetWidth(containerView.bounds) - CGRectGetWidth(frame);
    }
    if (side != PGViewDeckSideNone && side != openSide) {
        // calculate closed frame
        if (side == PGViewDeckSideLeft) {
            frame.origin.x -= CGRectGetWidth(frame);
        } else { // PGViewDeckSideRight
            frame.origin.x += CGRectGetWidth(frame);
        }
    }

    // parallax center
    if (side == PGViewDeckSideNone && openSide != PGViewDeckSideNone) {
        CGSize maxSize = [self sizeForSide:openSide inContainer:containerView];
        CGFloat xOffset = (openSide == PGViewDeckSideLeft ? maxSize.width * 0.1 : -maxSize.width * 0.1);
        frame.origin.x += xOffset;
    }

    return frame;
}

@end

NS_ASSUME_NONNULL_END
