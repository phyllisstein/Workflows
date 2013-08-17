//
//  main.m
//  TagsWorkflow
//
//  Created by Daniel Shannon on 3/26/13.
//  Copyright (c) 2013 Daniel Shannon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TWMetadataSearcher.h"
#import "TWMetadataTagger.h"
#import "TWFlagger.h"

int main(int argc, const char * argv[])
{

    @autoreleasepool {
        NSString *cmd;
        if (argc > 1) {
            cmd = [NSString stringWithCString:argv[1] encoding:NSUTF8StringEncoding];
        } else {
            cmd = nil;
        }

        if (cmd == nil) {
            TWMetadataSearcher *theSearcher = [[TWMetadataSearcher alloc] init];
            [theSearcher getSystemTagsMatching:nil];
			[[NSRunLoop mainRunLoop] run];
        } else if ([cmd isEqualToString:@"--search"] && argc == 2)  {
            TWMetadataSearcher *theSearcher = [[TWMetadataSearcher alloc] init];
            [theSearcher getSystemTagsMatching:nil];
            [[NSRunLoop mainRunLoop] run];
        } else if ([cmd isEqualToString:@"--search"] && argc == 3) {
            NSString *q = [[NSString alloc] initWithUTF8String:argv[2]];
            TWMetadataSearcher *theSearcher = [[TWMetadataSearcher alloc] init];
            [theSearcher getSystemTagsMatching:q];
            [[NSRunLoop mainRunLoop] run];
        } else if ([cmd isEqualToString:@"--tag"]) {
            TWMetadataTagger *theTagger = [[TWMetadataTagger alloc] init];
            NSString *target = [NSString stringWithCString:argv[2] encoding:NSUTF8StringEncoding];
            if ([target isEqualToString:@"finder"]) {
                NSString *q = [[NSString alloc] initWithUTF8String:argv[3]];
                [theTagger tagFinderSelectionWith:q];
            } else if ([target isEqualToString:@"open"]) {
                [[NSWorkspace sharedWorkspace] openFile:[NSString stringWithCString:argv[3] encoding:NSUTF8StringEncoding]];
            }
        } else if ([cmd isEqualToString:@"--clear"]) {
            NSString *target = [NSString stringWithCString:argv[2] encoding:NSUTF8StringEncoding];
            TWMetadataTagger *theTagger = [[TWMetadataTagger alloc] init];
            if ([target isEqualToString:@"finder"]) {
                [theTagger clearTagsFromFinderSelection];
            } else if ([target isEqualToString:@"open"]) {
                [theTagger clearTagsFromPath:[NSString stringWithCString:argv[3] encoding:NSUTF8StringEncoding]];
            }
        } else if ([cmd isEqualToString:@"--color"]) {
            TWFlagger *theFlagger = [[TWFlagger alloc] init];
            [theFlagger printColorList];
        } else if ([cmd isEqualToString:@"--setcolor"]) {
            NSString *arg = [NSString stringWithCString:argv[2] encoding:NSUTF8StringEncoding];
            TWFlagger *theFlagger = [[TWFlagger alloc] init];
            [theFlagger setFinderColor:[arg integerValue]];
        }
    }
    return 0;
}

