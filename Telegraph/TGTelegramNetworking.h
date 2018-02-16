/*
 * This is the source code of eVITA for iOS v. 1.1
 * It is licensed under GNU GPL v. 2 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Peter Iakovlev, 2013.
 */

#import <Foundation/Foundation.h>

#import <SSignalKit/SSignalKit.h>
#import <MTProtoKit/MTRpcError.h>

typedef enum {
    TGRequestClassGeneric = 1,
    TGRequestClassDownloadMedia = 2,
    TGRequestClassUploadMedia = 4,
    TGRequestClassEnableUnauthorized = 8,
    TGRequestClassEnableMerging = 16,
    TGRequestClassHidesActivityIndicator = 64,
    TGRequestClassLargeMedia = 128,
    TGRequestClassFailOnServerErrors = 256,
    TGRequestClassFailOnFloodErrors = 512,
    TGRequestClassPassthroughPasswordNeeded = 1024,
    TGRequestClassIgnorePasswordEntryRequired = 2048,
    TGRequestClassFailOnServerErrorsImmediately = 4096,
} TGRequestClass;

#define TG_DEFAULT_DATACENTER_ID INT_MAX

#define TGUseModernNetworking true//defined(DEBUG)

#import <MTProtoKit/MTRequest.h>

@class MTContext;
@class MTProto;
@class MTRequest;
@class TLMetaRpc;
@class TLError;
@class MTDatacenterAddress;
@class TGNetworkWorker;
@class TGNetworkWorkerGuard;
@class MTNetworkUsageCalculationInfo;
@protocol TLObject;

typedef enum {
    TGNetworkMediaTypeTagGeneric = 0,
    TGNetworkMediaTypeTagImage = 1,
    TGNetworkMediaTypeTagVideo = 2,
    TGNetworkMediaTypeTagAudio = 3,
    TGNetworkMediaTypeTagDocument = 4,
    TGNetworkMediaTypeTagCall = 5
} TGNetworkMediaTypeTag;

typedef enum {
    TGeVITANetworkUsageKeyDataIncomingWWAN = 0,
    TGeVITANetworkUsageKeyDataOutgoingWWAN = 1,
    TGeVITANetworkUsageKeyDataIncomingOther = 2,
    TGeVITANetworkUsageKeyDataOutgoingOther = 3,
    
    TGeVITANetworkUsageKeyMediaGenericIncomingWWAN = 4,
    TGeVITANetworkUsageKeyMediaGenericOutgoingWWAN = 5,
    TGeVITANetworkUsageKeyMediaGenericIncomingOther = 6,
    TGeVITANetworkUsageKeyMediaGenericOutgoingOther = 7,
    
    TGeVITANetworkUsageKeyMediaImageIncomingWWAN = 8,
    TGeVITANetworkUsageKeyMediaImageOutgoingWWAN = 9,
    TGeVITANetworkUsageKeyMediaImageIncomingOther = 10,
    TGeVITANetworkUsageKeyMediaImageOutgoingOther = 11,
    
    TGeVITANetworkUsageKeyMediaVideoIncomingWWAN = 12,
    TGeVITANetworkUsageKeyMediaVideoOutgoingWWAN = 13,
    TGeVITANetworkUsageKeyMediaVideoIncomingOther = 14,
    TGeVITANetworkUsageKeyMediaVideoOutgoingOther = 15,
    
    TGeVITANetworkUsageKeyMediaAudioIncomingWWAN = 16,
    TGeVITANetworkUsageKeyMediaAudioOutgoingWWAN = 17,
    TGeVITANetworkUsageKeyMediaAudioIncomingOther = 18,
    TGeVITANetworkUsageKeyMediaAudioOutgoingOther = 19,
    
    TGeVITANetworkUsageKeyMediaDocumentIncomingWWAN = 20,
    TGeVITANetworkUsageKeyMediaDocumentOutgoingWWAN = 21,
    TGeVITANetworkUsageKeyMediaDocumentIncomingOther = 22,
    TGeVITANetworkUsageKeyMediaDocumentOutgoingOther = 23,
    
    TGeVITANetworkUsageKeyCallIncomingWWAN = 24,
    TGeVITANetworkUsageKeyCallOutgoingWWAN = 25,
    TGeVITANetworkUsageKeyCallIncomingOther = 26,
    TGeVITANetworkUsageKeyCallOutgoingOther = 27,
} TGeVITANetworkUsageKey;

@interface TGTelegramNetworking : NSObject

+ (void)preload;
+ (TGTelegramNetworking *)instance;
+ (TGTelegramNetworking *)maybeInstance;

- (SMulticastSignalManager *)genericTasksSignalManager;

- (void)updatePts:(int)pts ptsCount:(int)ptsCount seq:(int)seq;
- (void)addUpdates:(id)updates;

- (MTContext *)context;
- (MTProto *)mtProto;

- (void)removeCredentialsForExtensions;
- (void)exportCredentialsForExtensions;

- (NSTimeInterval)globalTime;
- (NSTimeInterval)timeOffset;
- (NSTimeInterval)approximateRemoteTime;

- (void)loadCredentials;
- (void)start;
- (void)pause;
- (void)resume;

- (void)moveToDatacenterId:(NSInteger)datacenterId;
- (void)restartWithCleanCredentials;

- (void)clearExportedTokens;
- (void)mergeDatacenterAddress:(NSInteger)datacenterId address:(MTDatacenterAddress *)address;

- (void)performDeferredServiceTasks;

- (NSInteger)masterDatacenterId;
- (id)requestDownloadWorkerForDatacenterId:(NSInteger)datacenterId type:(TGNetworkMediaTypeTag)type completion:(void (^)(TGNetworkWorkerGuard *))completion;
- (id)requestDownloadWorkerForDatacenterId:(NSInteger)datacenterId type:(TGNetworkMediaTypeTag)type isCdn:(bool)isCdn completion:(void (^)(TGNetworkWorkerGuard *))completion;
- (void)cancelDownloadWorkerRequestByToken:(id)token;

- (void)addRequest:(MTRequest *)request;

// legacy
- (void)switchBackends;

- (NSObject *)performRpc:(TLMetaRpc *)rpc completionBlock:(void (^)(id<TLObject> response, int64_t responseTime, MTRpcError *error))completionBlock progressBlock:(void (^)(int length, float progress))progressBlock requiresCompletion:(bool)requiresCompletion requestClass:(int)requestClass;
- (NSObject *)performRpc:(TLMetaRpc *)rpc completionBlock:(void (^)(id<TLObject> response, int64_t responseTime, MTRpcError *error))completionBlock progressBlock:(void (^)(int length, float progress))progressBlock requiresCompletion:(bool)requiresCompletion requestClass:(int)requestClass datacenterId:(int)datacenterId;
- (NSObject *)performRpc:(TLMetaRpc *)rpc completionBlock:(void (^)(id<TLObject> response, int64_t responseTime, MTRpcError *error))completionBlock progressBlock:(void (^)(int length, float progress))progressBlock quickAckBlock:(void (^)())quickAckBlock requiresCompletion:(bool)requiresCompletion requestClass:(int)requestClass datacenterId:(int)datacenterId;

- (void)cancelRpc:(id)token;

- (bool)isNetworkAvailable;
- (bool)isConnecting;
- (bool)isUpdating;

- (bool)_isReadyToBeSuspended;

- (void)wakeUpWithCompletion:(void (^)())completion;

- (SSignal *)downloadWorkerForDatacenterId:(NSInteger)datacenterId type:(TGNetworkMediaTypeTag)type;
- (SSignal *)downloadWorkerForDatacenterId:(NSInteger)datacenterId type:(TGNetworkMediaTypeTag)type isCdn:(bool)isCdn;
- (SSignal *)requestSignal:(TLMetaRpc *)rpc;
- (SSignal *)requestSignal:(TLMetaRpc *)rpc continueOnServerErrors:(bool)continueOnServerErrors;
- (SSignal *)requestSignal:(TLMetaRpc *)rpc continueOnServerErrors:(bool)continueOnServerErrors failOnFloodErrors:(bool)failOnFloodErrors;
- (SSignal *)requestSignal:(TLMetaRpc *)rpc continueOnServerErrors:(bool)continueOnServerErrors failOnFloodErrors:(bool)failOnFloodErrors failOnServerErrorsImmediately:(bool)failOnServerErrorsImmediately;
- (SSignal *)requestSignal:(TLMetaRpc *)rpc requestClass:(int)requestClass;
- (SSignal *)requestSignalWithResponseTimestamp:(TLMetaRpc *)rpc;
- (SSignal *)requestSignal:(TLMetaRpc *)rpc worker:(TGNetworkWorkerGuard *)worker;

- (NSString *)extractNetworkErrorType:(id)error;

- (MTNetworkUsageCalculationInfo *)dataUsageInfo;
- (MTNetworkUsageCalculationInfo *)mediaUsageInfoForType:(TGNetworkMediaTypeTag)type;
- (NSString *)cellularUsageResetPath;
- (NSString *)wifiUsageResetPath;

@end

@interface MTRequest (LegacyTL)

- (void)setBody:(TLMetaRpc *)body;

@end
