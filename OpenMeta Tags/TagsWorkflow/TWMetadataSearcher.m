//
//  TWMetadataSearcher.m
//  TagsWorkflow
//
//  Created by Daniel Shannon on 3/27/13.
//  Copyright (c) 2013 Daniel Shannon. All rights reserved.
//

#include <uuid/uuid.h>
#import "TWMetadataSearcher.h"

@implementation TWMetadataSearcher

- (id)init
{
	self = [super init];
	if (self != nil)
	{
		COLOR_DICT = @{@"0": @"None", @"1": @"Gray", @"2": @"Green", @"3": @"Purple", @"4": @"Blue", @"5": @"Yellow", @"6": @"Red", @"7": @"Orange", @"8": @"Gray"};
	}
	return self;
}

- (void)getSystemTagsMatching:(NSString *)query
{
    tagSearcher = [[NSMetadataQuery alloc] init];
    self.query = query;
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(tagGatherComplete:) name:NSMetadataQueryDidFinishGatheringNotification object:tagSearcher];

    NSPredicate *searchPredicate;
    if (query == nil)
	{
        searchPredicate = [NSPredicate predicateWithFormat:@"_kMDItemUserTags LIKE[c] \"*\""];
    } else {
        query = [NSString stringWithFormat:@"*%@*", query];
        searchPredicate = [NSPredicate predicateWithFormat:@"_kMDItemUserTags LIKE[c] %@", query];
    }
    [tagSearcher setPredicate:searchPredicate];
    NSSortDescriptor *sorter;
    sorter = [[NSSortDescriptor alloc] initWithKey:@"com.apple.metadata:_kMDItemUserTags" ascending:YES];
    [tagSearcher setSortDescriptors:[NSArray arrayWithObject:sorter]];

    NSArray *searchScope;
    searchScope = [NSArray arrayWithObjects:NSMetadataQueryUserHomeScope, NSMetadataQueryLocalComputerScope, nil];
    [tagSearcher setSearchScopes:searchScope];

    [tagSearcher startQuery];
}

- (void)tagGatherComplete:sender
{
    [tagSearcher stopQuery];

    NSUInteger c = [tagSearcher resultCount];
    NSUInteger i;

    NSString *output = @"<?xml version=\"1.0\" ?><items>";

    if (self.query == nil) {
        output = [output stringByAppendingString:@"<item valid=\"no\"><title>Enter a Tag</title><subtitle>Tag the Finder selection with '...'</subtitle><icon>icon.png</icon></item>"];
    } else {
        output = [output stringByAppendingFormat:@"<item valid=\"yes\" arg=\"finder &quot;%@&quot;\"><title>Enter a Tag</title><subtitle>Tag the Finder selection with '%@'</subtitle><icon>icon.png</icon></item>", self.query, self.query];
    }

    if (self.query != nil) {
        for (i = 0; i < c; i++) {
            NSMetadataItem *aResult =[tagSearcher resultAtIndex:i];
            NSString *thePath = [aResult valueForAttribute:@"kMDItemPath"];
            NSString *name = [thePath lastPathComponent];
            output = [output stringByAppendingFormat:@"<item valid=\"yes\" arg=\"open &quot;%@&quot;\"><title>%@</title><subtitle>%@</subtitle><icon type=\"fileicon\">%@</icon></item>", thePath, name, thePath, thePath];
        }
    }

//    for (i = 0; i < c; i++) {
//        NSMetadataItem *aResult = [tagSearcher resultAtIndex:i];
//        NSDictionary *tags = [aResult valuesForAttributes:[NSArray arrayWithObjects:@"_kMDItemUserTags", @"kOMUserTags", nil]];
//        for (NSString *tag in [tags objectForKey:@"_kMDItemUserTags"]) {
//			NSArray *tag_parts = [tag componentsSeparatedByString:@"\n"];
//            if ([usableTags indexOfObject:tag_parts] == NSNotFound)
//			{
//				[usableTags addObject:tag_parts];
//            }
//        }
//    }
	NSMutableArray *usableTags = [[NSMutableArray alloc] initWithCapacity:c];
	for (NSMetadataItem *aResult in [tagSearcher results])
	{
		NSString *tag = [[aResult valuesForAttributes:@[@"_kMDItemUserTags"]] objectForKey:@"_kMDItemUserTags"];
		NSArray *tag_parts = [tag componentsSeparatedByString:@"\n"];
		if ([usableTags indexOfObject:tag_parts] == NSNotFound)
		{
			[usableTags addObject:tag_parts];
		}
	}

	NSString *iconsPath = [[NSBundle mainBundle] bundlePath];
	iconsPath = [iconsPath stringByAppendingPathComponent:@"icons"];
    for (NSArray *aTag in usableTags)
	{
		NSString *iPath = [iconsPath stringByAppendingPathComponent:[COLOR_DICT objectForKey:aTag[1]]];
		iPath = [iPath stringByAppendingPathExtension:@"png"];
        output = [output stringByAppendingFormat:@"<item valid=\"yes\" arg=\"finder &quot;%@&quot;\" autocomplete=\"%@\"><title>%@</title><subtitle></subtitle><icon>%@</icon></item>", aTag[0], aTag[0], aTag[0], iPath];
    }
    output = [output stringByAppendingString:@"</items>"];

    printf("%s\n", [output UTF8String]);
    exit(0);
}

@end
