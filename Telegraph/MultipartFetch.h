#import <Foundation/Foundation.h>
#import <SSignalKit/SSignalKit.h>

#import "TelegramCloudMediaResource.h"
#import "TGTelegramNetworking.h"

SSignal *multipartFetch(id<eVITACloudMediaResource> resource, NSNumber *size, NSRange range, TGNetworkMediaTypeTag mediaTypeTag);
