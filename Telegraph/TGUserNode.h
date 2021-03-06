/*
 * This is the source code of eVITA for iOS v. 1.1
 * It is licensed under GNU GPL v. 2 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Peter Iakovlev, 2013.
 */

#import <LegacyComponents/SGraphNode.h>

#import <LegacyComponents/LegacyComponents.h>

@interface TGUserNode : SGraphNode

@property (nonatomic, strong) TGUser *user;

- (id)initWithUser:(TGUser *)user;

@end
