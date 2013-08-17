//
//  TWMetadataSearcher.h
//  TagsWorkflow
//
//  Created by Daniel Shannon on 3/27/13.
//  Copyright (c) 2013 Daniel Shannon. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface TWMetadataSearcher : NSObject {
    NSMetadataQuery *tagSearcher;
	NSDictionary *COLOR_DICT;
}

- (void)getSystemTagsMatching:(NSString *)query;

@property NSString *query;

@end
