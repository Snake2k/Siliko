/* clang -ObjC -fsyntax-only -fobjc-arc Delegate.h */

#import <Cocoa/Cocoa.h>

@interface SilikoDelegate : NSObject <NSApplicationDelegate>

@property (weak) IBOutlet NSTextField *input;
@property (weak) IBOutlet NSTextField *output;

-(IBAction) Calculate:(id)sender;

@end
