//
//  DTDatabaseWorker.h
//  DtWorkflow
//
//  Created by Daniel Shannon on 5/26/13.
//  Copyright (c) 2013 Daniel Shannon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DEVONthink.h"

@interface DTDatabaseWorker : NSObject

- (id)initWithDB:(DEVONthinkDatabase *)myDB andQuery:(NSString *)q;
- (DEVONthinkRecord *)findGroupByName:(NSString *)name;
- (NSArray *)workingGroupChildren;
- (NSArray *)rootChildren;
- (NSString *)pathWithoutQuery;

@property NSArray               *path;
@property DEVONthinkRecord      *workingGroup;
@property NSString              *query;
@property DEVONthinkDatabase    *db;

@end
