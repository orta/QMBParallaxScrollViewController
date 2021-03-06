//
//  QMBParallaxScrollViewController.h
//  QMBParallaxScrollView-Sample
//
//  Created by Toni Möckel on 02.11.13.
//  Copyright (c) 2013 Toni Möckel. All rights reserved.
//

@class QMBParallaxScrollViewController;

typedef NS_ENUM(NSUInteger, QMBParallaxState) {
    QMBParallaxStateVisible,
    QMBParallaxStateFullSize,
    QMBParallaxStateContentPeakSize,
    QMBParallaxStateHidden,
};

typedef NS_ENUM(NSUInteger, QMBParallaxGesture) {
    QMBParallaxGestureTopViewTap,
    QMBParallaxGestureScrollsDown,
    QMBParallaxGestureScrollsUp,
};

@protocol QMBParallaxScrollViewHolder <NSObject>

- (UIScrollView *)scrollViewForParallaxController;

@end

@protocol QMBParallaxScrollViewControllerDelegate <NSObject>

@optional

/**
 * Callback when the user tapped the top-view
 * sender is usually the UITapGestureRecognizer instance
 */
- (void) parallaxScrollViewController:(QMBParallaxScrollViewController *) controller didChangeGesture:(QMBParallaxGesture)newGesture oldGesture:(QMBParallaxGesture)oldGesture;

/**
 * Callback when the state changed to QMBParallaxStateFullSize, QMBParallaxStateVisible or QMBParallaxStateHidden
 */
- (void) parallaxScrollViewController:(QMBParallaxScrollViewController *) controller didChangeState:(QMBParallaxState) state;

/**
 * Callback when the top height changed
 */
- (void) parallaxScrollViewController:(QMBParallaxScrollViewController *) controller didChangeTopHeight:(CGFloat) height;

@end



@interface QMBParallaxScrollViewController : UIViewController<UIGestureRecognizerDelegate, UIScrollViewDelegate>

@property (nonatomic, strong) id<QMBParallaxScrollViewControllerDelegate> delegate;

@property (nonatomic, strong, readonly) UIViewController *topViewController;
@property (nonatomic, strong, readonly) UIViewController *bottomViewController;

@property (nonatomic, assign, readonly) CGFloat topHeight;
@property (nonatomic, assign) CGFloat maxHeight;

/**
 * Set the height of the border (margin from top) that has to be scrolled over to expand the background view.
 * Default: 1.3 * topHeight
 */
@property (nonatomic, assign) CGFloat maxHeightBorder;

/**
 * Set the height of the border (margin from top) that has to be scrolled under to minimize the background view
 * Default: fullHeight - 5.0f
 */
@property (nonatomic, assign) CGFloat minHeightBorder;

/**
 * To enable section support for UITableViews, default: true if UITableView is client scrollview
 * TODO: this option will disable decelerated scrolling (known bug)
 */
@property (nonatomic, assign) BOOL enableSectionSupport;

@property (nonatomic, readonly) QMBParallaxState state;

/**
 * The Parallax Scrollview that embeds the bottom (foreground) view
 */
@property (nonatomic, readonly) UIScrollView *parallaxScrollView;

/**
 * Use the scrollview delegate for custom actions
 */
@property (nonatomic, weak) id<UIScrollViewDelegate> scrollViewDelegate;

// inits
-(void)setupWithTopViewController:(UIViewController *)topViewController topHeight:(CGFloat)height bottomViewController:(UIViewController *)bottomViewController;

/// Observe a scrollview
- (void)observeScrollView:(UIScrollView *)scrollView;

// configs

/**
 * Config to enable or disable top-view tap control
 * Call will be responsed by QMBParallaxScrollViewControllerDelegate instance
 */
- (void)enableTapGestureTopView:(BOOL) enable;

- (void)presentFullTopViewController:(BOOL)show;

@end
