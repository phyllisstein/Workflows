//
//  TWFlagger.h
//  TagsWorkflow
//
//  Created by Daniel Shannon on 5/24/13.
//  Copyright (c) 2013 Daniel Shannon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <sys/xattr.h>
#import "TWMetadataTagger.h"

@interface TWFlagger : NSObject {
    NSArray *COLORS;
    NSString *KEY;
}

- (void)printColorList;
- (void)setFinderColor:(NSUInteger)c;
- (NSData *)getFinderColorAtPath:(NSString *)p;

@end
