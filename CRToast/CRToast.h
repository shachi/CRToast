//
//  CRToast
//  CRNotificationDemo
//
//

#import <Foundation/Foundation.h>
#import "CRToastManager.h"
@import UIKit;

@class CRToastSwipeGestureRecognizer, CRToastTapGestureRecognizer;
/**
 CRToastInteractionType defines the types of interactions that can be injected into a CRToastIneractionResponder.
 */

typedef NS_OPTIONS(NSInteger, CRToastInteractionType) {
    CRToastInteractionTypeSwipeUp           = 1 << 0,
    CRToastInteractionTypeSwipeLeft         = 1 << 1,
    CRToastInteractionTypeSwipeDown         = 1 << 2,
    CRToastInteractionTypeSwipeRight        = 1 << 3,
    CRToastInteractionTypeTapOnce           = 1 << 4,
    CRToastInteractionTypeTapTwice          = 1 << 5,
    CRToastInteractionTypeTwoFingerTapOnce  = 1 << 6,
    CRToastInteractionTypeTwoFingerTapTwice = 1 << 7,
    
    //An interaction responder with a CRToastInteractionTypeSwipe interaction type will fire on all swipe interactions
    CRToastInteractionTypeSwipe             = (CRToastInteractionTypeSwipeUp    |
                                               CRToastInteractionTypeSwipeLeft  |
                                               CRToastInteractionTypeSwipeDown  |
                                               CRToastInteractionTypeSwipeRight),
    
    //An interaction responder with a CRToastInteractionTypeTap interaction type will fire on all tap interactions
    CRToastInteractionTypeTap               = (CRToastInteractionTypeTapOnce            |
                                               CRToastInteractionTypeTapTwice           |
                                               CRToastInteractionTypeTwoFingerTapOnce   |
                                               CRToastInteractionTypeTwoFingerTapTwice),
    
    //An interaction responder with a CRToastInteractionTypeAll interaction type will fire on all swipe and tap interactions
    CRToastInteractionTypeAll               = (CRToastInteractionTypeSwipe, CRToastInteractionTypeTap)
};

OBJC_EXTERN NSString *NSStringFromCRToastInteractionType(CRToastInteractionType interactionType);

/**
 CRToastInteractionResponder is a container object to configure responses to user interactions with a notification. A collection of interaction responders can be included in the
 options for any given notification or in defaults.
 */

@interface CRToastInteractionResponder : NSObject

/**
 Creates an interaction responder for a given interaction type.
 @param interactionType The kind of interaction that will trigger the responder
 @param automaticallyDismiss A BOOL indiciating if the notification should automatically be dismissed on the interaction being observed. If YES the configured notification dismisall
 animation will begin immidiately upon encountering the interaction.
 @param block A block of code to be called immidiately upon the interaction being encountered. The block will be provided the specific CRToastInteractionType that resulted in the
 block firing
 */

+ (instancetype)interactionResponderWithInteractionType:(CRToastInteractionType)interactionType
                                   automaticallyDismiss:(BOOL)automaticallyDismiss
                                                  block:(void (^)(CRToastInteractionType interactionType))block;
@end

///--------------------
/// @name Notification Option Types
///--------------------

/**
 `CRToastType` defines the height of the notification. `CRToastTypeStatusBar` covers the status bar, `CRToastTypeNavigationBar` covers the status bar
 and navigation bar
 */

typedef NS_ENUM(NSInteger, CRToastType){
    CRToastTypeStatusBar,
    CRToastTypeNavigationBar,
    CRToastTypeCustom
};

/**
 `CRToastPresentationType` defines whether a notification will cover the contents of the status/navigation bar or whether the content will be pushed
 out by the notification.
 */

typedef NS_ENUM(NSInteger, CRToastPresentationType){
    CRToastPresentationTypeCover,
    CRToastPresentationTypePush
};

/**
 `CRToastAnimationDirection` defines the direction of the notification. A direction can be specified for both notification entrance and exit.
 */

typedef NS_ENUM(NSInteger, CRToastAnimationDirection) {
    CRToastAnimationDirectionTop,
    CRToastAnimationDirectionBottom,
    CRToastAnimationDirectionLeft,
    CRToastAnimationDirectionRight
};

/**
 `CRToastAnimationType` defines the timing function used for the notification presentation.
 */

typedef NS_ENUM(NSInteger, CRToastAnimationType) {
    CRToastAnimationTypeLinear,
    CRToastAnimationTypeSpring,
    CRToastAnimationTypeGravity
};

/**
  `CRToastState` defines the current state of the CRToast. Used for internal state management in the manager 
 */
typedef NS_ENUM(NSInteger, CRToastState){
    CRToastStateWaiting,
    CRToastStateEntering,
    CRToastStateDisplaying,
    CRToastStateExiting,
    CRToastStateCompleted
};

///--------------------
/// @name Option Keys
///--------------------

/**
 These are the keys that define the options that can be set for a notifaction. All primitive types mentioned should
 be wrapped as `NSNumber`s or `NSValue`s
 */

/**
 The notification type for the notification. Expects type `CRToastType`.
 */

OBJC_EXTERN NSString *const kCRToastNotificationTypeKey;

/**
 The preferred height for the notificaiton, this will only be used for notifications with CRToastTypeCustom set for kCRToastNotificationTypeKey
 */

OBJC_EXTERN NSString *const kCRToastNotificationPreferredHeightKey;

/**
 The presentation type for the notification. Expects type `CRToastPresentationType`.
 */

OBJC_EXTERN NSString *const kCRToastNotificationPresentationTypeKey;

/**
 Indicates whether the notification should slide under the staus bar, leaving it visible or not.
 Making this YES with `kCRToastNotificationTypeKey` set to `CRToastTypeStatusBar` isn't sensible and will look
 odd. Expects type `BOOL`.
 */

OBJC_EXTERN NSString *const kCRToastUnderStatusBarKey;

/**
 The animation in type for the notification. Expects type `CRToastAnimationType`.
 */

OBJC_EXTERN NSString *const kCRToastAnimationInTypeKey;

/**
 The animation out type for the notification. Expects type `CRToastAnimationType`.
 */

OBJC_EXTERN NSString *const kCRToastAnimationOutTypeKey;

/**
 The animation in direction for the notification. Expects type `CRToastAnimationDirection`.
 */

OBJC_EXTERN NSString *const kCRToastAnimationInDirectionKey;

/**
 The animation out direction for the notification. Expects type `CRToastAnimationDirection`.
 */

OBJC_EXTERN NSString *const kCRToastAnimationOutDirectionKey;

/**
 The animation in time interval for the notification. Expects type `NSTimeInterval`.
 */

OBJC_EXTERN NSString *const kCRToastAnimationInTimeIntervalKey;

/**
 The notification presentation timeinterval of type for the notification. This is how long the notification
 will be on screen after its presentation but before its dismissal. Expects type `NSTimeInterval`.
 */

OBJC_EXTERN NSString *const kCRToastTimeIntervalKey;

/**
 The animation out timeinterval for the notification. Expects type `NSTimeInterval`.
 */

OBJC_EXTERN NSString *const kCRToastAnimationOutTimeIntervalKey;

/**
 The spring damping coefficient to be used when `kCRToastAnimationInTypeKey` or `kCRToastAnimationOutTypeKey` is set to
 `CRToastAnimationTypeSpring`. Currently you can't define separate damping for in and out. Expects type `CGFloat`.
 */


OBJC_EXTERN NSString *const kCRToastAnimationSpringDampingKey;

/**
 The initial velocity coefficient to be used when `kCRToastAnimationInTypeKey` or `kCRToastAnimationOutTypeKey` is set to
 `CRToastAnimationTypeSpring`. Currently you can't define initial velocity for in and out. Expects type `CGFloat`.
 */

OBJC_EXTERN NSString *const kCRToastAnimationSpringInitialVelocityKey;

/**
 The gravity magnitude coefficient to be used when `kCRToastAnimationInTypeKey` or `kCRToastAnimationOutTypeKey` is set to
 `CRToastAnimationTypeGravity`. Currently you can't define gravity magnitude for in and out. Expects type `CGFloat`.
 */

OBJC_EXTERN NSString *const kCRToastAnimationGravityMagnitudeKey;

/**
 The main text to be shown in the notification. Expects type `NSString`.
 */

OBJC_EXTERN NSString *const kCRToastTextKey;

/**
 The font to be used for the `kCRToastTextKey` value . Expects type `UIFont`.
 */

OBJC_EXTERN NSString *const kCRToastFontKey;

/**
 The text color to be used for the `kCRToastTextKey` value . Expects type `UIColor`.
 */

OBJC_EXTERN NSString *const kCRToastTextColorKey;

/**
 The text alignment to be used for the `kCRToastTextKey` value . Expects type `NSTextAlignment`.
 */

OBJC_EXTERN NSString *const kCRToastTextAlignmentKey;

/**
 The shadow color to be used for the `kCRToastTextKey` value . Expects type `UIColor`.
 */

OBJC_EXTERN NSString *const kCRToastTextShadowColorKey;

/**
 The shadow offset to be used for the `kCRToastTextKey` value . Expects type `CGSize`.
 */

OBJC_EXTERN NSString *const kCRToastTextShadowOffsetKey;

/**
 The max number of lines to be used for the `kCRToastTextKey` value . Expects type `NSInteger`.
 */

OBJC_EXTERN NSString *const kCRToastTextMaxNumberOfLinesKey;

/**
 The subtitle text to be shown in the notification. Expects type `NSString`.
 */

OBJC_EXTERN NSString *const kCRToastSubtitleTextKey;

/**
 The font to be used for the `kCRToastSubtitleTextKey` value . Expects type `UIFont`.
 */

OBJC_EXTERN NSString *const kCRToastSubtitleFontKey;

/**
 The text color to be used for the `kCRToastSubtitleTextKey` value . Expects type `UIColor`.
 */

OBJC_EXTERN NSString *const kCRToastSubtitleTextColorKey;

/**
 The text alignment to be used for the `kCRToastSubtitleTextKey` value . Expects type `NSTextAlignment`.
 */

OBJC_EXTERN NSString *const kCRToastSubtitleTextAlignmentKey;

/**
 The shadow color to be used for the `kCRToastSubtitleTextKey` value . Expects type `UIColor`.
 */

OBJC_EXTERN NSString *const kCRToastSubtitleTextShadowColorKey;

/**
 The shadow offset to be used for the `kCRToastSubtitleTextKey` value . Expects type `NSInteger`.
 */

OBJC_EXTERN NSString *const kCRToastSubtitleTextShadowOffsetKey;

/**
 The max number of lines to be used for the `kCRToastSubtitleTextKey` value . Expects type `NSInteger`.
 */

OBJC_EXTERN NSString *const kCRToastSubtitleTextMaxNumberOfLinesKey;

/**
 The status bar style for the navigation bar.  Expects type `UIStatusBarStyle`.
 */

OBJC_EXTERN NSString *const kCRToastStatusBarStyleKey;

/**
 The background color for the notification. Expects type `UIColor`.
 */

OBJC_EXTERN NSString *const kCRToastBackgroundColorKey;

/**
 The image to be shown on the left side of the notification. Expects type `UIImage`.
 */

OBJC_EXTERN NSString *const kCRToastImageKey;

/**
 The image content mode to use for `kCRToastImageKey` image. Exptects type `UIViewContentMode`
 */
OBJC_EXTERN NSString *const kCRToastImageContentModeKey;

/**
 BOOL setting whether the CRToast should show a loading indicator in the left image location.
 */
OBJC_EXTERN NSString *const kCRToastShowActivityIndicatorKey;

/**
 The activity indicator view style. Expects type `UIActivityIndicatorViewStyle`
 */
OBJC_EXTERN NSString *const kCRToastActivityIndicatorViewStyleKey;

/**
 An Array of Interaction Responders for the Notification. Expects type `NSArray` full of `CRToastInteractionResponders`
 */
OBJC_EXTERN NSString *const kCRToastInteractionRespondersKey;

/**
 BOOL setting whether the CRToast should force the user to interact with it, ignoring the `kCRToastTimeIntervalKey` key
 */
OBJC_EXTERN NSString *const kCRToastForceUserInteractionKey;

/**
 An BOOL setting whether the CRToast's should autorotate. Expects type `BOOL` defaults to `YES`
 */
OBJC_EXTERN NSString *const kCRToastAutorotateKey;

/**
 Key for the Identifier for a notification.
 */
OBJC_EXTERN NSString *const kCRToastIdentifierKey;

/**
 A BOOL setting whether the CRToast's should capture the screen behind the default UIWindow. Expects type `BOOL` defaults to `YES`
 */
OBJC_EXTERN NSString *const kCRToastCaptureDefaultWindowKey;

#pragma mark - CRToast Interface
@interface CRToast : NSObject <UIGestureRecognizerDelegate>

@property (nonatomic, strong) NSUUID *uuid;
@property (nonatomic, assign) CRToastState state;

//Top Level Properties

@property (nonatomic, strong) NSDictionary *options;
@property (nonatomic, copy) void(^completion)(void);
@property (nonatomic, copy) void(^appearance)(void);

//Interactions

@property (nonatomic, strong) NSArray *gestureRecognizers;

//Autorotate

@property (nonatomic, assign) BOOL autorotate;

//Views and Layout Data

@property (nonatomic, readonly) UIView *notificationView;
@property (nonatomic, readonly) CGRect notificationViewAnimationFrame1;
@property (nonatomic, readonly) CGRect notificationViewAnimationFrame2;
@property (nonatomic, readonly) UIView *statusBarView;
@property (nonatomic, readonly) CGRect statusBarViewAnimationFrame1;
@property (nonatomic, readonly) CGRect statusBarViewAnimationFrame2;
@property (nonatomic, strong) UIDynamicAnimator *animator;

//Read Only Convinence Properties Providing Default Values or Values from Options

@property (nonatomic, readonly) CRToastType notificationType;
@property (nonatomic, assign) CGFloat preferredHeight;
@property (nonatomic, readonly) CRToastPresentationType presentationType;
@property (nonatomic, readonly) BOOL displayUnderStatusBar;

@property (nonatomic, readonly) CRToastAnimationType inAnimationType;
@property (nonatomic, readonly) CRToastAnimationType outAnimationType;
@property (nonatomic, readonly) CRToastAnimationDirection inAnimationDirection;
@property (nonatomic, readonly) CRToastAnimationDirection outAnimationDirection;
@property (nonatomic, readonly) NSTimeInterval animateInTimeInterval;
@property (nonatomic, readonly) NSTimeInterval timeInterval;
@property (nonatomic, readonly) NSTimeInterval animateOutTimeInterval;

@property (nonatomic, readonly) CGFloat animationSpringDamping;
@property (nonatomic, readonly) CGFloat animationSpringInitialVelocity;
@property (nonatomic, readonly) CGFloat animationGravityMagnitude;

@property (nonatomic, readonly) NSString *text;
@property (nonatomic, readonly) UIFont *font;
@property (nonatomic, readonly) UIColor *textColor;
@property (nonatomic, readonly) NSTextAlignment textAlignment;
@property (nonatomic, readonly) UIColor *textShadowColor;
@property (nonatomic, readonly) CGSize textShadowOffset;
@property (nonatomic, readonly) NSInteger textMaxNumberOfLines;

@property (nonatomic, readonly) NSString *subtitleText;
@property (nonatomic, readonly) UIFont *subtitleFont;
@property (nonatomic, readonly) UIColor *subtitleTextColor;
@property (nonatomic, readonly) NSTextAlignment subtitleTextAlignment;
@property (nonatomic, readonly) UIColor *subtitleTextShadowColor;
@property (nonatomic, readonly) CGSize subtitleTextShadowOffset;
@property (nonatomic, readonly) NSInteger subtitleTextMaxNumberOfLines;
@property (nonatomic, readonly) UIStatusBarStyle statusBarStyle;
@property (nonatomic, readonly) UIColor *backgroundColor;
@property (nonatomic, readonly) UIImage *image;
@property (nonatomic, readonly) UIViewContentMode imageContentMode;
@property (nonatomic, readonly) UIActivityIndicatorViewStyle activityIndicatorViewStyle;
@property (nonatomic, readonly) BOOL showActivityIndicator;
@property (nonatomic, readonly) BOOL forceUserInteraction;

@property (nonatomic, readonly) CGVector inGravityDirection;
@property (nonatomic, readonly) CGVector outGravityDirection;

@property (nonatomic, readonly) CGPoint inCollisionPoint1;
@property (nonatomic, readonly) CGPoint inCollisionPoint2;
@property (nonatomic, readonly) CGPoint outCollisionPoint1;
@property (nonatomic, readonly) CGPoint outCollisionPoint2;

- (void)swipeGestureRecognizerSwiped:(CRToastSwipeGestureRecognizer*)swipeGestureRecognizer;
- (void)tapGestureRecognizerTapped:(CRToastTapGestureRecognizer*)tapGestureRecognizer;
- (void)initiateAnimator:(UIView *)view;

@end
