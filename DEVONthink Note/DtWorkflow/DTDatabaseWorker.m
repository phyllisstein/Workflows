//
//  DTDatabaseWorker.m
//  DtWorkflow
//
//  Created by Daniel Shannon on 5/26/13.
//  Copyright (c) 2013 Daniel Shannon. All rights reserved.
//

#import <Alfred/Alfred.h>
#import "DTDatabaseWorker.h"

#pragma mark-
#pragma mark Private interface

@interface DTDatabaseWorker ()

- (NSArray *)_fuzzyChildrenForGroup:(DEVONthinkRecord *)g;

@end



#pragma mark -
#pragma mark Implementation

@implementation DTDatabaseWorker

@synthesize workingGroup = _workingGroup;

- (id)initWithDB:(DEVONthinkDatabase *)myDB andQuery:(NSString *)q
{
    self = [super init];
    if (self != nil)
    {
        _db = myDB;
        _path = [q componentsSeparatedByString:@"→"];
        _workingGroup = nil;

        _query = [_path lastObject];
    }

    return self;
}

- (NSArray *)_fuzzyChildrenForGroup:(DEVONthinkRecord *)g
{
    SBElementArray *raw_children = [g children];
    NSMutableArray *children = [NSMutableArray new];
    for (DEVONthinkRecord *ch in raw_children)
    {
        NSString *c_name = [ch name];
        if ([ch type] == DEVONthinkDtypGroup && ![c_name isEqualToString:@"Trash"] &&
            ![c_name isEqualToString:@"Tags"] && ![c_name isEqualToString:@"Mobile Sync"])
        {
            [children addObject:ch];
        }
    }
    if ([self.query isEqualToString:@""])
    {
        return children;
    }
    else
    {
        AWWorkflow *aw = [[AWWorkflow alloc] init];
        NSArray *res = [aw fuzzySearchFor:self.query in:children withKeyBlock:^NSString *(id o) {
            DEVONthinkRecord *obj = (DEVONthinkRecord *)o;
            return [obj name];
        }];
        return res;
    }
}

- (NSArray *)workingGroupChildren
{
    return [self _fuzzyChildrenForGroup:self.workingGroup];
}

- (NSArray *)rootChildren
{
    return [self _fuzzyChildrenForGroup:[self.db root]];
}

- (NSString *)pathWithoutQuery
{
    NSUInteger z = [self.path count] - 1;
    NSRange y = NSMakeRange(0, z);
    return [[[self.path subarrayWithRange:y] componentsJoinedByString:@"→"] stringByAppendingString:@"→"];
}

- (DEVONthinkRecord *)findGroupByName:(NSString *)name
{
    DEVONthinkRecord *found = nil;
    NSMutableArray *matches = [NSMutableArray new];
    for (DEVONthinkRecord *r in [self.db parents])
    {
        if ([r type] == DEVONthinkDtypGroup && [[r name] isEqualToString:name])
        {
            [matches addObject:r];
        }
    }
    if ([matches count] < 1)
    {
        found = nil;
    }
    else if ([matches count] == 1)
    {
        found = matches[0];
    }
    else
    {
        for (NSString *above in [self.path reverseObjectEnumerator])
        {
            for (DEVONthinkRecord *r in matches)
            {
                for (DEVONthinkRecord *parent in [r parents])
                {
                    if ([above isEqualToString:[parent name]])
                    {
                        found = r;
                        break;
                    }
                }
            }
        }
    }

    return found;
}






# pragma mark -
# pragma mark Getters and setters

- (DEVONthinkRecord *)workingGroup
{
    NSString *working;
    if ([self.path count] < 3)                                      // self.path = [db]→[] || [db]→foo
    {
        _workingGroup = nil;
        return _workingGroup;
    }
    else
    {
        working = [self.path objectAtIndex:[self.path count]-2];    // self.path = [db]→[grp]→[] || [db]→[grp1]→[grp2]→q || etc.
        _workingGroup = [self findGroupByName:working];
        return _workingGroup;
    }
}

- (void)setWorkingGroup:(DEVONthinkRecord *)workingGroup
{
    return;
}

@end
