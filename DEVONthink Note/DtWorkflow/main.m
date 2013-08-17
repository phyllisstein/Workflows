//
//  main.m
//  DtWorkflow
//
//  Created by Daniel Shannon on 5/26/13.
//  Copyright (c) 2013 Daniel Shannon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Alfred/Alfred.h>
#import "DEVONthink.h"
#import "DTDatabaseWorker.h"



int main(int argc, const char * argv[])
{

    @autoreleasepool
    {
        AWWorkflow *wf = [AWWorkflow workflow];

        DEVONthinkApplication *Dt = [SBApplication applicationWithBundleIdentifier:@"com.devon-technologies.thinkpro2"];
        NSArray *dbNames = [[Dt databases] arrayByApplyingSelector:@selector(name)];
        NSArray *dbIDs = [[Dt databases] arrayByApplyingSelector:@selector(uuid)];
        const NSDictionary *dbs = [[NSDictionary alloc] initWithObjects:dbIDs forKeys:dbNames];
        const NSString *dbIcon = [wf local:[@"icons" stringByAppendingPathComponent:@"db.png"]];
        const NSString *groupIcon = [wf local:[@"icons" stringByAppendingPathComponent:@"group.png"]];

        NSMutableArray *outObjects = [NSMutableArray new];
        NSString *argv1 = [NSString stringWithCString:argv[1] encoding:NSUTF8StringEncoding];
        if (argc == 1 || [argv1 isEqualToString:@""])
        {
            for (NSString *n in dbNames)
            {
                NSString *acp = [NSString stringWithFormat:@"%@→", n];
                NSString *st = [NSString stringWithFormat:@"Select a group in \"%@\"", n];
                AWFeedbackItem *i = [AWFeedbackItem itemWithObjectsAndKeys:@NO, @"valid", acp, @"autocomplete", n, @"title", st, @"subtitle", dbIcon, @"icon", nil];
                [outObjects addObject:i];
            }

            [wf flush:YES feedbackArray:outObjects];
            return 0;
        }
        else if (argc == 2)
        {
            NSString *q = argv1;
            NSArray *path = [q componentsSeparatedByString:@"→"];
            NSString *workingDB = path[0];
            NSString *queryID = [dbs objectForKey:workingDB];
            DEVONthinkDatabase *queryDB = [Dt getDatabaseWithUuid:queryID];
            DTDatabaseWorker *dbw = [[DTDatabaseWorker alloc] initWithDB:queryDB andQuery:q];

            NSArray *children = [dbw workingGroup] == nil ? [dbw rootChildren] : [dbw workingGroupChildren];

            if ([children count])
            {
                for (DEVONthinkRecord *g in children)
                {
                    NSString *n = [g name];
                    NSString *_path = [NSString stringWithFormat:@"%@%@→", [dbw pathWithoutQuery], n];
                    NSString *st = [NSString stringWithFormat:@"Create a note or select a group in \"%@\"", n];
                    AWFeedbackItem *i = [AWFeedbackItem itemWithObjectsAndKeys:@NO, @"valid", _path, @"autocomplete", n, @"title", st, @"subtitle", groupIcon, @"icon", nil];
                    [outObjects addObject:i];
                }
            }
            else if ([[dbw query] isEqualToString:@""] && [[dbw path] count] == 2)
            {
                NSString *t = [NSString stringWithFormat:@"Create a note in \"%@\"", [[queryDB incomingGroup] name]];
                AWFeedbackItem *i = [AWFeedbackItem itemWithObjectsAndKeys:@NO, @"valid", t, @"title", @"Type to create a note", @"subtitle", nil];
                [outObjects addObject:i];
            }
            else if ([[dbw query] isEqualToString:@""])
            {
                NSString *t = [NSString stringWithFormat:@"Create a note in \"%@\"", [[dbw workingGroup] name]];
                AWFeedbackItem *i = [AWFeedbackItem itemWithObjectsAndKeys:@NO, @"valid", t, @"title", @"Type to create a note", @"subtitle", nil];
                [outObjects addObject:i];
            }

            if ([outObjects count] == 0)
            {
                NSString *noteTitle;
                NSString *note = @"";
                DEVONthinkRecord *target = [dbw workingGroup] == nil ? [queryDB incomingGroup] : [dbw workingGroup];
                NSString *uuid = [queryDB uuid];
                NSString *q_name = [queryDB name];
                NSString *t_name = [target name];
                if (uuid == nil && q_name == nil && t_name == nil)
                {
                    uuid = @"Inbox";
                    q_name = @"Inbox";
                    t_name = @"Inbox";
                }
                if ([[dbw query] rangeOfString:@":"].location != NSNotFound)
                {
                    NSArray *splitNote = [[dbw query] componentsSeparatedByString:@":"];
                    noteTitle = [[splitNote objectAtIndex:0] stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]];
                    if ([splitNote count] == 2)
                    {
                        note = [[splitNote objectAtIndex:1] stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]];
                    }
                    else
                    {
                        for (NSInteger i = 1; i < [splitNote count]; i++)
                        {
                            note = [note stringByAppendingFormat:@" %@", [splitNote objectAtIndex:i]];
                        }
                    }
                }
                else
                {
                    noteTitle = [@"Alfred Note: " stringByAppendingString:[[NSDate date] descriptionWithLocale:[[NSUserDefaults standardUserDefaults] dictionaryRepresentation]]];
                    note = [dbw query];
                }

                NSString *arg = [NSString stringWithFormat:@"\"%@\" \"%@\" \"%@\" \"%@\" \"%@\"", uuid, q_name, t_name, noteTitle, note];
                AWFeedbackItem *i = [AWFeedbackItem itemWithObjectsAndKeys:@YES, @"valid", arg, @"arg", noteTitle, @"title", note, @"subtitle", nil];
                [outObjects addObject:i];
            }

            [wf flush:YES feedbackArray:outObjects];
        }
//        else
//        {
//            NSArray *arg_keys = @[@{@"name": @"uuid", @"has_arg": @YES, @"flag": @"u"},
//                                  @{@"name": @"name", @"has_arg": @YES, @"flag": @"n"},
//                                  @{@"name": @"group", @"has_arg": @YES, @"flag": @"g"},
//                                  @{@"name": @"title", @"has_arg": @YES, @"flag": @"t"},
//                                  @{@"name": @"note", @"has_arg": @YES, @"flag": @"N"},
//                                  @{@"name": @"path", @"has_arg": @YES, @"flag": @"p"}];
//            NSDictionary *args = [wf parseArguments:argv withKeys:arg_keys count:argc];
//            NSLog(@"args=%@", args);
//            NSLog(@"dbs=%@", dbs);
//            if (![[dbs objectForKey:[args objectForKey:@"name"]] isEqualToString:[args objectForKey:@"uuid"]])
//            {
//                printf("Name/UUID Mismatch for %s.\n", [[args objectForKey:@"name"] UTF8String]);
//            }
//
//            DEVONthinkDatabase *targetDB;
//            DEVONthinkRecord *targetGroup;
//            if ([[args objectForKey:@"name"] isEqualToString:@"Inbox"] && [[args objectForKey:@"group"] isEqualToString:@"Inbox"])
//            {
//                targetDB = [Dt inbox];
//                targetGroup = [targetDB incomingGroup];
//            }
//            else
//            {
//                targetDB = [Dt getDatabaseWithUuid:[args objectForKey:@"uuid"]];
//                DTDatabaseWorker *dbw = [[DTDatabaseWorker alloc] initWithDB:targetDB andQuery:nil];
//                targetGroup = [dbw findGroupByName:[args objectForKey:@"group"]];
//                if (targetGroup == nil)
//                {
//                    targetGroup = [targetDB incomingGroup];
//                }
//            }
//
//            DEVONthinkRecord *newRecord = [targetGroup createRecordWithIn:targetGroup];
//            newRecord.name = [args objectForKey:@"title"];
//            newRecord.unread = YES;
//            newRecord.plainText = [args objectForKey:@"note"];
//            [Dt openTabForIn:[[[Dt windows] objectAtIndex:0] get] record:newRecord referrer:nil URL:nil];
//        }
    }

    return 0;
}