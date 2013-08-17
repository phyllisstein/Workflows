//
//  AWFeedbackItem.h
//  AlfredWorkflow
//
//  Created by Daniel Shannon on 5/24/13.
//  Copyright (c) 2013 Daniel Shannon. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface AWFeedbackItem : NSObject {
    @private
    NSArray *tags_;
    NSDictionary *attrib_;
}

+ (id)itemWithObjectsAndKeys:(id)o, ... NS_REQUIRES_NIL_TERMINATION;
- (id)initWithObjects:(NSArray *)obj forKeys:(NSArray *)key;

- (NSString *)xml;


@property (copy) NSString      *title;
@property (copy) NSString      *subtitle;
@property (copy) NSString      *uid;
@property (copy) NSNumber      *valid;
@property (copy) NSString      *autocomplete;
@property (copy) NSString      *icon;
@property (copy) NSNumber      *fileicon;
@property (copy) NSNumber      *filetype;
@property (copy) NSString      *arg;
@property (copy) NSString      *type;

@end
