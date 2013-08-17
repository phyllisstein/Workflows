//
//  TWMetadataTagger.m
//  TagsWorkflow
//
//  Created by Daniel Shannon on 5/24/13.
//  Copyright (c) 2013 Daniel Shannon. All rights reserved.
//

#import "TWMetadataTagger.h"
#include <sys/xattr.h>

@implementation TWMetadataTagger

+ (NSArray *)getFinderSelection
{
    FinderApplication *Finder = [SBApplication applicationWithBundleIdentifier:@"com.apple.finder"];
    NSArray *sel = [[Finder selection] get];

    NSMutableArray *paths = [[NSMutableArray alloc] initWithCapacity:[sel count]];
    if ([sel count]) {
        for (FinderItem *anItem in sel) {
            [paths addObject:[NSURL URLWithString:[anItem URL]]];
        }
    } else {
        if ([[Finder FinderWindows] count]) {
            FinderFinderWindow *win = [[Finder FinderWindows] objectAtIndex:0];
            SBObject *target = [win target];
            FinderFolder *obj = [target get];
            [paths addObject:[NSURL URLWithString:[obj URL]]];
        } else {
            [paths addObject:[NSURL URLWithString:[[Finder desktop] URL]]];
        }
    }

    for (NSUInteger j = 0; j < [paths count]; j++) {
        NSString *p = [[paths objectAtIndex:j] path];
        [paths replaceObjectAtIndex:j withObject:p];
    }

    return paths;
}


- (id)init
{
    self = [super init];
    if (self != nil) {
        TAG_KEYS = [NSArray arrayWithObjects:@"org.openmetainfo:kOMUserTags", @"org.openmetainfo:kMDItemOMUserTags", @"com.apple.metadata:kOMUserTags", @"com.apple.metadata:kMDItemOMUserTags", @"com.apple.metadata:_kMDItemUserTags", nil];
        return self;
    } else {
        return nil;
    }
}

- (void)dieWithErrno:(int)e
{
    NSError *err = [NSError errorWithDomain:NSPOSIXErrorDomain code:e userInfo:nil];
    NSString *err_out = [NSString stringWithFormat:@"<?xml version=\"1.0\" ?><items><item valid=\"no\"><title>Error:</title><subtitle>%@</subtitle><icon>icon.png</icon></item></items>", [err localizedDescription]];
    printf("%s", [err_out UTF8String]);
    exit(1);
}

- (NSArray *)getCurrentTags
{
    NSArray *paths = [TWMetadataTagger getFinderSelection];
    NSMutableArray *t = [[NSMutableArray alloc] initWithCapacity:0];

    for (NSString *p in paths) {
        for (NSString *k in TAG_KEYS) {
            size_t kMaxDataSize = 4096;
            void *buff = malloc(kMaxDataSize);
            ssize_t data_size = getxattr([p UTF8String], [k UTF8String], buff, kMaxDataSize, 0, XATTR_NOFOLLOW);
            if (data_size > 0) {
                NSData *data = [NSData dataWithBytes:(const void *)buff length:data_size];
                NSError *e = nil;
                NSArray *pls = [NSPropertyListSerialization propertyListWithData:data options:kCFPropertyListImmutable format:NULL error:&e];
                for (NSString *tag in pls) {
                    if (![t containsObject:tag]) {
                        [t addObject:tag];
                    }
                }
            }
        }
    }

    return t;
}

- (void)tagFinderSelectionWith:(NSString *)tags
{
    NSMutableArray *t;
    if ([tags rangeOfString:@","].location != NSNotFound) {
        t = (NSMutableArray *)[tags componentsSeparatedByString:@","];
    } else {
        t = [NSMutableArray arrayWithObject:tags];
    }
    for (NSUInteger i = 0; i < [t count]; i++) {
        NSString *clean = [[t objectAtIndex:i] stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]];
        [t replaceObjectAtIndex:i withObject:clean];
    }

    NSArray *paths = [TWMetadataTagger getFinderSelection];
    [t addObjectsFromArray:[self getCurrentTags]];

    NSError *e = nil;
    if ([t count]) {
        NSData *send_me = [NSPropertyListSerialization dataWithPropertyList:t format:NSPropertyListBinaryFormat_v1_0 options:NSPropertyListImmutable error:&e];
        int check;
        NSMutableArray *names = [[NSMutableArray alloc] initWithCapacity:[t count]];
        for (NSString *p in paths) {
            for (NSString *k in TAG_KEYS) {
                check = setxattr([p UTF8String], [k UTF8String], [send_me bytes], [send_me length], 0, XATTR_NOFOLLOW);
            }
            [names addObject:[p lastPathComponent]];
        }

        NSString *oput = [NSString stringWithFormat:@"Tagged %@ \"%@\".", [names componentsJoinedByString:@", "], [t componentsJoinedByString:@", "]];
        printf("%s\n", [oput UTF8String]);

        exit(check);
    } else {
        [self clearTagsFromFinderSelection];
    }
}

- (void)clearTagsFromFinderSelection
{
    NSArray *paths = [TWMetadataTagger getFinderSelection];
    NSMutableArray *names = [[NSMutableArray alloc] initWithCapacity:[paths count]];
    int check;
    for (NSString *p in paths) {
        [names addObject:[p lastPathComponent]];
        check = [self clearTagsFromPath:p];
    }

    NSString *oput = [NSString stringWithFormat:@"Untagged %@.", [names componentsJoinedByString:@", "]];
    printf("%s\n", [oput UTF8String]);
}

- (int)clearTagsFromPath:(NSString *)p
{
    NSArray *t = [self getCurrentTags];
    if ([t count] < 1) {
        return -1;
    }

    int check;
    for (NSString *k in TAG_KEYS) {
        check = removexattr([p UTF8String], [k UTF8String], XATTR_NOFOLLOW);
    }

    return check;
}

@end
