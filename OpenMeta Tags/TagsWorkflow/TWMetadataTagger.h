//
//  TWMetadataTagger.h
//  TagsWorkflow
//
//  Created by Daniel Shannon on 5/24/13.
//  Copyright (c) 2013 Daniel Shannon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Finder.h"

@interface TWMetadataTagger : NSObject {
    NSArray *TAG_KEYS;
}

+ (NSArray *)getFinderSelection;

- (void)dieWithErrno:(int)e;
- (NSArray *)getCurrentTags;
- (void)tagFinderSelectionWith:(NSString *)tags;
- (void)clearTagsFromFinderSelection;
- (int)clearTagsFromPath:(NSString *)p;

@end
