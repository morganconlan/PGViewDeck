//
//  PGViewDeckController.h
//  PGViewDeck
//
//  Copyright (C) 2011-2016, ViewDeck
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy of
//  this software and associated documentation files (the "Software"), to deal in
//  the Software without restriction, including without limitation the rights to
//  use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
//  of the Software, and to permit persons to whom the Software is furnished to do
//  so, subject to the following conditions:
// 
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.
//

#import <UIKit/UIKit.h>

#import "IIEnvironment.h"


// thanks to http://stackoverflow.com/a/8594878/742176

NS_ASSUME_NONNULL_BEGIN


FOUNDATION_EXPORT NSString* NSStringFromPGViewDeckSide(PGViewDeckSide side);


@class PGViewDeckController;

/**
 The delegate of a `PGViewDeckController` is used to inform the delegate of changes
 the view deck controller is undergoing, like opening or closing sides.
 */
@protocol PGViewDeckControllerDelegate <NSObject>
@optional

/// @name Open and Close Sides

/**
 Tells the delegate that the specified side will open.

 If this delegate method is not implemented, view deck will always open the side.

 @param viewDeckController The view deck controller informing the delegate.
 @param side               The side that will open. Either `PGViewDeckSideLeft` or `PGViewDeckSideRight`.

 @return `YES` if the View Deck Controller should open the side in question, `NO` otherwise.
 */
- (BOOL)viewDeckController:(PGViewDeckController *)viewDeckController willOpenSide:(PGViewDeckSide)side;

/**
 Tells the delegate that the specified side did open.

 @param viewDeckController The view deck controller informing the delegate.
 @param side               The side that did open. Either `PGViewDeckSideLeft` or `PGViewDeckSideRight`.
 */
- (void)viewDeckController:(PGViewDeckController *)viewDeckController didOpenSide:(PGViewDeckSide)side;

/**
 Tells the delegate that the specified side will close.
 
 If this delegate method is not implemented, view deck will always close the side.

 @param viewDeckController The view deck controller informing the delegate.
 @param side               The side that will close. Either `PGViewDeckSideLeft` or `PGViewDeckSideRight`.
 
 @return `YES` if the View Deck Controller should close the side in question, `NO` otherwise.
 */
- (BOOL)viewDeckController:(PGViewDeckController *)viewDeckController willCloseSide:(PGViewDeckSide)side;

/**
 Tells the delegate that the specified side did close.
 
 If this delegate method is not implemented, view deck will always start panning.

 @param viewDeckController The view deck controller informing the delegate.
 @param side               The side that did close. Either `PGViewDeckSideLeft` or `PGViewDeckSideRight`.
 */
- (void)viewDeckController:(PGViewDeckController *)viewDeckController didCloseSide:(PGViewDeckSide)side;


/// @name Interactive Transitions

/**
 Asks the delegate whether panning (and therefore an interactive side change) should
 start or not.

 This method is only triggered if `-[PGViewDeckController isPanningEnabled]` returns
 `YES`.

 @param viewDeckController The view deck controller informing the delegate.
 @param side               The side that will open interactively.
 @return `YES` if view deck should start the interactive transition, `NO` if the
         transition should be cancelled.
 */
- (BOOL)viewDeckController:(PGViewDeckController *)viewDeckController shouldStartPanningToSide:(PGViewDeckSide)side NS_SWIFT_NAME(viewDeckController(_:shouldStartPanningTo:));

@end


@protocol PGViewDeckTransitionAnimator, PGViewDeckTransitionContext;

/**
 The `PGViewDeckController` is the hart of ViewDeck. It is the main view controller
 controlls the content and whether or not a side bar is presented.
 
 The `PGViewDeckController` is a container view controller that uses the view controller
 hierarchy to display it's content. You always need to define a center view controller.
 This is the view controller that is visible in the center of the `PGViewDeckController`
 and has the same size. You can optionally set a left view controller and / or a
 right view controller that slides in from the left or right side either programatically
 or through a user action.
 
 # Controlling the size of a side view controller
 
 A side view controller always has the same height as the view deck controller
 itself. You can control the width of the view controller by setting `preferredContentSize`
 on your left or right content view controller, similar like you do when presenting
 a view controller as a popover.
 
 # Customizing the appearance
 
 By default side view controllers can slide in from the left or the right and while
 sliding in, a dimm view will be faded in between the center view controller and
 the side view controller to give it a nice iOS like look and feel. However this
 might not be suitable for all cases. You have multiple ways of customizing this
 appearance. The current methods of customization are listed under 'Customizing
 Transitions'. If you feel the current options are not suitable for you, please
 file an issue at https://github.com/ViewDeck/ViewDeck
 */
@interface PGViewDeckController : UIViewController


/// @name Initializing a View Deck Controller

/**
 Initialises an instance of `PGViewDeckController` with the given view controller
 as the center view controller.
 
 When using this method, the receiver has no left or right view controller after
 initialization and you need to set these manually via `setLeftViewController:`
 or `setRightViewController:`.
 
 @see initWithCenterViewController:leftViewController:
 @see initWithCenterViewController:rightViewController:
 @see initWithCenterViewController:leftViewController:rightViewController:

 @param centerController The view controller that should be responsible for the
                         view in the center of the view deck controller.

 @return A newly initialized instance of `PGViewDeckController`.
 */
- (instancetype)initWithCenterViewController:(UIViewController*)centerController;

/**
 Initialises an instance of `PGViewDeckController` with the given center and left
 view controller.

 When using this method, the receiver has no right view controller after
 initialization and you need to set this manually via `setRightViewController:`
 if you want to add one.

 @param centerController The view controller that should be responsible for the
                         view in the center of the view deck controller.
 @param leftController   The view controller that should be responsible for the
                         view on the left side of the view deck controller.

 @return A newly initialized instance of `PGViewDeckController`.
 */
- (instancetype)initWithCenterViewController:(UIViewController*)centerController leftViewController:(nullable UIViewController*)leftController;

/**
 Initialises an instance of `PGViewDeckController` with the given center and
 right view controller.

 When using this method, the receiver has no left view controller after
 initialization and you need to set this manually via `setLeftViewController:`
 if you want to add one.

 @param centerController The view controller that should be responsible for the
                         view in the center of the view deck controller.
 @param rightController  The view controller that should be responsible for the
                         view on the right side of the view deck controller.

 @return A newly initialized instance of `PGViewDeckController`.
 */
- (instancetype)initWithCenterViewController:(UIViewController*)centerController rightViewController:(nullable UIViewController*)rightController;

/**
 Initialises an instance of `PGViewDeckController` with the given center, left,
 and right view controller.
 
 @note This is the designated initializer.

 @param centerController The view controller that should be responsible for the
                         view in the center of the view deck controller.
 @param leftController   The view controller that should be responsible for the
                         view on the left side of the view deck controller.
 @param rightController  The view controller that should be responsible for the
                         view on the right side of the view deck controller.

 @return A newly initialized instance of `PGViewDeckController`.
 */
- (instancetype)initWithCenterViewController:(UIViewController*)centerController leftViewController:(nullable UIViewController*)leftController rightViewController:(nullable UIViewController*)rightController NS_DESIGNATED_INITIALIZER;

- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;


/// @name Managing the Delegate

@property (nonatomic, weak) id<PGViewDeckControllerDelegate> delegate;


/// @name Maintaining the Content View Controllers

/**
 The view controller that is responsible for the view in the center of the view
 deck controller.
 */
@property (nonatomic) UIViewController* centerViewController;

/**
 The view controller that is responsible for the view on the left side of the
 view deck controller.
 
 @warning Setting this view controller while is is already on screen will
          trigger an exception.
 */
@property (nonatomic, nullable) UIViewController* leftViewController;

/**
 The view controller that is responsible for the view on the right side of the
 view deck controller.

 @warning Setting this view controller while is is already on screen will
          trigger an exception.
 */
@property (nonatomic, nullable) UIViewController* rightViewController;


/// @name Managing Transitions

/**
 The side of the view deck controller that is currently open or `PGViewDeckSideNone`
 if no side is currently open and the center view controller is the only
 controller that the view deck controller is currently showing.
 
 @see openSide:animated:
 @see openSide:animated:completion:
 */
@property (nonatomic) PGViewDeckSide openSide;

/**
 Opens the passed in side.
 
 Opening a side that is already open does nothing.
 
 @note You can only switch between no view controller (`PGViewDeckSideNone`) or
       either the left (`PGViewDeckSideLeft`) or right (`PGViewDeckSideRight`)
       view controller. You can not switch directly from left to right without
       dismissing the open side first.
 
 @see closeSide:
 @see closeSide:animated:completion:

 @param side     The side you want to open.
 @param animated `YES` if you want to animate the transition, `NO` otherwise.
 */
- (void)openSide:(PGViewDeckSide)side animated:(BOOL)animated;


/**
 Opens the passed in side.
 
 Opening a side that is already open does nothing.
 
 @note You can only switch between no view controller (`PGViewDeckSideNone`) or
 either the left (`PGViewDeckSideLeft`) or right (`PGViewDeckSideRight`)
 view controller. You can not switch directly from left to right without
 dismissing the open side first.
 
 @see closeSide:
 @see closeSide:animated:
 
 @param side     The side you want to open.
 @param animated `YES` if you want to animate the transition, `NO` otherwise.
 @param completion Completion block that will be called when the animation completed
 */
- (void)openSide:(PGViewDeckSide)side animated:(BOOL)animated completion:(nullable void(^)(BOOL cancelled))completion;


/**
 Closes the currently open side.
 
 Closing a side when no side is open does nothing.

 @see closeSide:animated:completion:
 @see openSide:animated:

 @param animated `YES` if you want to animate the transition, `NO` otherwise.
 */
- (void)closeSide:(BOOL)animated;

/**
 Closes the currently open side.
 
 Closing a side when no side is open does nothing.
 
 @see closeSide:animated:
 @see openSide:animated:
 
 @param animated `YES` if you want to animate the transition, `NO` otherwise.
 @param completion Completion block that will be called when the animation completed
 */
- (void)closeSide:(BOOL)animated completion:(nullable void(^)(BOOL cancelled))completion;


- (void)toggleLeftSideAnimated:(BOOL)animated;

/// @name Customizing Transitions

/**
 Controls whether panning (and therefore interactive transitions) are enabled or
 disabled all together. Defaults to `YES`.
 
 If you want more control on a case by case basis, leave this property enabled and
 implement the methods provided by the delegate.
 
 @note If this property is disabled, the gesture recognizers itself will be completely
       deactivated, therefore the above mentioned delegate methods will not be called.
 */
@property (nonatomic, getter=isPanningEnabled) BOOL panningEnabled;

/**
 Creates and returns an object that conforms to `PGViewDeckTransitionAnimator` and
 is ready to handle the animation for the passed in transition.
 
 This method is ment to be subclassed if you want to add your own custom animator.
 If you want to customize the animation only in some cases, make sure to call super
 in all the other cases, otherwise calling super is not required.

 @param context The `PGViewDeckTransitionContext` that this animator should use.

 @return A fully configured animator object.
 */
- (id<PGViewDeckTransitionAnimator>)animatorForTransitionWithContext:(id<PGViewDeckTransitionContext>)context;

/**
 Creates and returns a view that can be used as decoration view between the center
 view controller's view and a side view.

 This method is ment to be subclassed if you want to add your own custom decoration
 view or if you want to disable decoration views alltogether. If you want to customize
 the decoration view only in some cases, make sure to call super in all the other
 cases, otherwise calling super is not required.

 @param context The `PGViewDeckTransitionContext` that this decoration view is used in.

 @return A fully configured decoration view.
 */
- (nullable UIView *)decorationViewForTransitionWithContext:(id<PGViewDeckTransitionContext>)context;

@end

// You should NOT change the gesture recognizers. These are only available for reference
// in case you want to link them with other gesture recognizers.
@interface PGViewDeckController (GestureRecognizer)

/**
 The gesture recognizer that is used to slide in the left view controller.
 
 @note Do not alter this gesture recognizer. This property should only be used to
       link this gesture recognizer with other gesture recognizers.
 */
@property (nonatomic, readonly) UIGestureRecognizer *leftEdgeGestureRecognizer;

/**
 The gesture recognizer that is used to slide in the right view controller.

 @note Do not alter this gesture recognizer. This property should only be used to
       link this gesture recognizer with other gesture recognizers.
 */
@property (nonatomic, readonly) UIGestureRecognizer *rightEdgeGestureRecognizer;

@end

NS_ASSUME_NONNULL_END
