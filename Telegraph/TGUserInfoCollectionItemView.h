/*
 * This is the source code of eVITA for iOS v. 1.1
 * It is licensed under GNU GPL v. 2 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Peter Iakovlev, 2013.
 */

#import "TGCollectionItemView.h"

#import <LegacyComponents/LegacyComponents.h>

#import <LegacyComponents/ASWatcher.h>

@interface TGUserInfoCollectionItemView : TGCollectionItemView

@property (nonatomic) bool isVerified;

@property (nonatomic, strong) ASHandle *itemHandle;

- (void)setEditing:(bool)editing animated:(bool)animated;
- (void)setStatus:(NSString *)status active:(bool)active;

- (void)setFirstName:(NSString *)firstName lastName:(NSString *)lastName uidForPlaceholderCalculation:(int32_t)uidForPlaceholderCalculation;
- (void)setAvatarUri:(NSString *)avatarUri animated:(bool)animated synchronous:(bool)synchronous;
- (void)setAvatarImage:(UIImage *)avatarImage animated:(bool)animated;
- (void)setUpdatingAvatar:(bool)updatingAvatar animated:(bool)animated;
- (void)setDisableAvatarPlaceholder:(bool)disable;
- (void)setAvatarOffset:(CGSize)avatarOffset;
- (void)setNameOffset:(CGSize)nameOffset;
- (void)setShowCall:(bool)showCall;
- (void)setShowDisclosureIndicator:(bool)show;
- (void)setShowCameraIcon:(bool)show;

- (void)setPhoneNumber:(NSString *)phoneNumber;
- (void)setUsername:(NSString *)username;

- (void)setAvatarHidden:(bool)hidden animated:(bool)animated;
- (id)avatarView;
- (void)makeNameFieldFirstResponder;

@end
