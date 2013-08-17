//
//  TWFlagger.m
//  TagsWorkflow
//
//  Created by Daniel Shannon on 5/24/13.
//  Copyright (c) 2013 Daniel Shannon. All rights reserved.
//

#import "TWFlagger.h"

@implementation TWFlagger

- (id)init
{
    self = [super init];
    if (self != nil) {
        COLORS = [NSArray arrayWithObjects:@"None", @"Gray", @"Green", @"Purple", @"Blue", @"Yellow", @"Red", @"Orange", nil];
        KEY = @"com.apple.FinderInfo";
    }
    return self;
}

- (void)printColorList
{
    NSString *o = @"<?xml version=\"1.0\" ?><items>";
    for (int i = 0; i < [COLORS count]; i++) {
        NSString *c = [COLORS objectAtIndex:i];
        NSString *iconPath = [[NSBundle mainBundle] bundlePath];
        iconPath = [[iconPath stringByAppendingPathComponent:@"icons"] stringByAppendingPathComponent:c];
        iconPath = [iconPath stringByAppendingString:@".png"];
        o = [o stringByAppendingFormat:@"<item valid=\"yes\" arg=\"%i\" autocomplete=\"%@\"><title>%@</title><subtitle>Label the Finder selection '%@'</subtitle><icon>%@</icon></item>", i, c, c, c, iconPath];
    }
    o = [o stringByAppendingString:@"</items>"];

    printf("%s\n", [o UTF8String]);
    exit(0);
}

- (void)setFinderColor:(NSUInteger)c
{
    NSArray *paths = [TWMetadataTagger getFinderSelection];
    NSMutableArray *names = [[NSMutableArray alloc] initWithCapacity:[paths count]];
    NSString *o = @"";

    for (NSString *p in paths) {
        [names addObject:[p lastPathComponent]];

        NSMutableData *d = [[NSMutableData alloc] initWithData:[self getFinderColorAtPath:p]];
        NSRange want = NSMakeRange(9, 1);
        NSUInteger nc = c << 1;
        const void *cp = &nc;
        [d replaceBytesInRange:want withBytes:cp];

        int err = setxattr([p UTF8String], [KEY UTF8String], [d bytes], [d length], 0, XATTR_NOFOLLOW);
        if (err < 0) {
            NSError *e = [NSError errorWithDomain:NSPOSIXErrorDomain code:errno userInfo:nil];
            o = [o stringByAppendingFormat:@" %@: %@ ", [p lastPathComponent], [e localizedDescription]];
        }
    }
    if ([o length] > 0) {
        printf("Errors:%s\n", [o UTF8String]);
        exit(1);
    } else {
        o = [names componentsJoinedByString:@", "];
        NSString *op = [NSString stringWithFormat:@"Labeled %@ %@", o, [COLORS objectAtIndex:c]];
        printf("%s\n", [op UTF8String]);
        exit(0);
    }
    
}

- (NSData *)getFinderColorAtPath:(NSString *)p
{
    void *data = malloc(32);
    ssize_t dataSize;

    dataSize = getxattr([p UTF8String], [KEY UTF8String], data, 4096, 0, XATTR_NOFOLLOW);
    if (dataSize < 0) {
        data = memset(data, 0, 32);
        dataSize = 32;
    }
    return [NSData dataWithBytes:(const void *)data length:dataSize];
}

@end
