/*
 * DEVONthink.h
 */

#import <AppKit/AppKit.h>
#import <ScriptingBridge/ScriptingBridge.h>


@class DEVONthinkItem, DEVONthinkApplication, DEVONthinkColor, DEVONthinkDocument, DEVONthinkWindow, DEVONthinkAttributeRun, DEVONthinkCharacter, DEVONthinkParagraph, DEVONthinkText, DEVONthinkAttachment, DEVONthinkWord, DEVONthinkApplication, DEVONthinkDatabase, DEVONthinkRecord, DEVONthinkChild, DEVONthinkContent, DEVONthinkParent, DEVONthinkSelectedText, DEVONthinkTab, DEVONthinkTagGroup, DEVONthinkThinkWindow, DEVONthinkDocumentWindow, DEVONthinkSearchWindow, DEVONthinkViewerWindow, DEVONthinkPrintSettings;

enum DEVONthinkSavo {
	DEVONthinkSavoAsk = 'ask ' /* Ask the user whether or not to save the file. */,
	DEVONthinkSavoNo = 'no  ' /* Do not save the file. */,
	DEVONthinkSavoYes = 'yes ' /* Save the file. */
};
typedef enum DEVONthinkSavo DEVONthinkSavo;

enum DEVONthinkDAta {
	DEVONthinkDAtaCenter = 'DAa1',
	DEVONthinkDAtaJustified = 'DAa3',
	DEVONthinkDAtaLeft = 'DAa0',
	DEVONthinkDAtaNatural = 'DAa4',
	DEVONthinkDAtaRight = 'DAa2'
};
typedef enum DEVONthinkDAta DEVONthinkDAta;

enum DEVONthinkLkwh {
	DEVONthinkLkwhAll = 'all ' /* Search term in contents, all attributes and metadata. */,
	DEVONthinkLkwhComments = 'lkw5' /* Search term in comments. */,
	DEVONthinkLkwhContents = 'lkw1' /* Search term in contents. */,
	DEVONthinkLkwhMetaData = 'mtdt' /* Search term in metadata. */,
	DEVONthinkLkwhTitles = 'lkw2' /* Search term in titles. */,
	DEVONthinkLkwhURLs = 'lkw3' /* Search term in URLs. */
};
typedef enum DEVONthinkLkwh DEVONthinkLkwh;

enum DEVONthinkItyp {
	DEVONthinkItypAll = 'all ' /* All files */,
	DEVONthinkItypChat = 'ipt3' /* iChat logs */,
	DEVONthinkItypImage = 'imaA' /* Images */,
	DEVONthinkItypLocation = 'DTlo' /* Internet locations */,
	DEVONthinkItypMarkup = 'itp2' /* Markup files */,
	DEVONthinkItypPdfAndPostscript = 'itp7' /* PDF & PostScript documents */,
	DEVONthinkItypQuicktime = 'ipt5' /* Quicktime movies & sounds */,
	DEVONthinkItypRich = 'ctp2' /* Rich text documents */,
	DEVONthinkItypScript = 'ipt4' /* AppleScripts */,
	DEVONthinkItypSheet = 'tabl' /* Sheets (TSV, CSV, BiBTeX, ...) */,
	DEVONthinkItypSimple = 'ctp1' /* Simple text files */
};
typedef enum DEVONthinkItyp DEVONthinkItyp;

enum DEVONthinkWSrt {
	DEVONthinkWSrtFrequency = 'freq' /* Sorted by frequency */,
	DEVONthinkWSrtWeight = 'wght' /* Sorted by weight */
};
typedef enum DEVONthinkWSrt DEVONthinkWSrt;

enum DEVONthinkLkcp {
	DEVONthinkLkcpFuzzy = 'fuzz' /* Fuzzy search. */,
	DEVONthinkLkcpNoCase = 'noca' /* Case insensitive search. */,
	DEVONthinkLkcpNoUmlauts = 'noum' /* Diacritics insensitive search. */
};
typedef enum DEVONthinkLkcp DEVONthinkLkcp;

enum DEVONthinkTtyp {
	DEVONthinkTtypGroupTag = 'gtag' /* A "group" tag located outside of the tags group. */,
	DEVONthinkTtypNoTag = 'ntag' /* No tag (not a group or excluded from tagging). */,
	DEVONthinkTtypOrdinaryTag = 'otag' /* An "ordinary" tag located inside of the tags group. */
};
typedef enum DEVONthinkTtyp DEVONthinkTtyp;

enum DEVONthinkCtyp {
	DEVONthinkCtypHtml = 'html' /* HTML document */,
	DEVONthinkCtypRich = 'ctp2' /* Rich text */,
	DEVONthinkCtypSimple = 'ctp1' /* Simple text */
};
typedef enum DEVONthinkCtyp DEVONthinkCtyp;

enum DEVONthinkDtyp {
	DEVONthinkDtypBookmark = 'DTnx' /* A Internet or filesystem location */,
	DEVONthinkDtypFeed = 'feed' /* RSS, RDF or Atom feed */,
	DEVONthinkDtypGroup = 'DTgr' /* Group */,
	DEVONthinkDtypHtml = 'html' /* HTML document */,
	DEVONthinkDtypPDFDocument = 'pdf ' /* PDF document */,
	DEVONthinkDtypPicture = 'pict' /* Picture */,
	DEVONthinkDtypPlist = 'plis' /* Property list */,
	DEVONthinkDtypQuicktime = 'quti' /* QuickTime movie or sound */,
	DEVONthinkDtypRtf = 'rtf ' /* RTF document */,
	DEVONthinkDtypRtfd = 'rtfd' /* RTFD document */,
	DEVONthinkDtypScript = 'scpt' /* Script */,
	DEVONthinkDtypSheet = 'tabl' /* Sheet */,
	DEVONthinkDtypSmartGroup = 'DTsg' /* Smart group */,
	DEVONthinkDtypTxt = 'txt ' /* Text document */,
	DEVONthinkDtypUnknown = '****' /* An unknown file type */,
	DEVONthinkDtypWebarchive = 'wbar' /* Web Archive */,
	DEVONthinkDtypXml = 'xml ' /* XML document */
};
typedef enum DEVONthinkDtyp DEVONthinkDtyp;

enum DEVONthinkEnum {
	DEVONthinkEnumStandard = 'lwst' /* Standard PostScript error handling */,
	DEVONthinkEnumDetailed = 'lwdt' /* print a detailed report of PostScript errors */
};
typedef enum DEVONthinkEnum DEVONthinkEnum;



/*
 * Standard Suite
 */

// A scriptable object.
@interface DEVONthinkItem : SBObject

@property (copy) DEVONthinkRecord *properties;  // All of the object's properties.

- (void) closeSaving:(DEVONthinkSavo)saving savingIn:(NSURL *)savingIn;  // Close an object.
- (void) delete;  // Delete an object.
- (void) duplicateTo:(SBObject *)to withProperties:(DEVONthinkRecord *)withProperties;  // Copy object(s) and put the copies at a new location.
- (BOOL) exists;  // Verify if an object exists.
- (void) moveTo:(SBObject *)to;  // Move object(s) to a new location.
- (void) saveAs:(NSString *)as in:(NSURL *)in_;  // Save an object.
- (void) bold;  // Bold some text
- (void) italicize;  // Italicize some text
- (void) plain;  // Make some text plain
- (void) scrollToVisible;  // Scroll to and animate some text. Requires Mac OS X 10.6.
- (void) strike;  // Strike some text
- (void) unbold;  // Unbold some text
- (void) underline;  // Underline some text
- (void) unitalicize;  // Unitalicize some text
- (void) unstrike;  // Unstrike some text
- (void) ununderline;  // Ununderline some text
- (BOOL) addRowCells:(NSArray *)cells;  // Add new row to current sheet.
- (BOOL) deleteRowAtPosition:(NSInteger)position;  // Remove row at specified position from current sheet.
- (NSString *) getCellAtColumn:(NSInteger)column row:(NSInteger)row;  // Get content of cell at specified position of current sheet.
- (BOOL) setCellAtColumn:(NSInteger)column row:(NSInteger)row to:(NSString *)to;  // Set cell at specified position of current sheet.
- (DEVONthinkRecord *) convertImageRecord:(DEVONthinkRecord *)record rotateBy:(NSInteger)rotateBy to:(DEVONthinkRecord *)to;  // Returns a searchable PDF for an image record.
- (DEVONthinkRecord *) ocrFile:(NSString *)file attributes:(DEVONthinkRecord *)attributes rotateBy:(NSInteger)rotateBy to:(DEVONthinkRecord *)to;  // Returns a record with a searchable PDF.

@end

// An application's top level scripting object.
@interface DEVONthinkApplication : SBApplication

- (SBElementArray *) documents;
- (SBElementArray *) windows;

@property (readonly) BOOL frontmost;  // Is this the frontmost (active) application?
@property (copy, readonly) NSString *name;  // The name of the application.
@property (copy, readonly) NSString *version;  // The version of the application.

- (DEVONthinkDocument *) open:(NSURL *)x;  // Open an object.
- (void) print:(NSURL *)x printDialog:(BOOL)printDialog withProperties:(DEVONthinkPrintSettings *)withProperties;  // Print an object.
- (void) quitSaving:(DEVONthinkSavo)saving;  // Quit an application.
- (BOOL) addDownload:(NSString *)x automatic:(BOOL)automatic password:(NSString *)password referrer:(NSString *)referrer user:(NSString *)user;  // Add a URL to the download manager.
- (BOOL) backupDatabase:(DEVONthinkDatabase *)database to:(NSString *)to includingFiles:(BOOL)includingFiles;  // Backup a DEVONthink Pro database.
- (NSArray *) classifyRecord:(DEVONthinkRecord *)record;  // Get a list of classification proposals.
- (NSArray *) compareContent:(NSString *)content record:(DEVONthinkRecord *)record to:(DEVONthinkDatabase *)to;  // Get a list of similar records, either by specifying a record or a content (and database).
- (BOOL) compressDatabase:(DEVONthinkDatabase *)database to:(NSString *)to;  // Compress a DEVONthink Pro database into a Zip archive.
- (BOOL) consolidateRecord:(DEVONthinkRecord *)record;  // Move an external/indexed record (and its children) into the database.
- (DEVONthinkRecord *) convertRecord:(DEVONthinkRecord *)record in:(DEVONthinkRecord *)in_ to:(DEVONthinkCtyp)to;  // Convert a record to simple or rich text and create a new record afterwards.
- (NSString *) convertFeedToHTML:(NSString *)x baseURL:(NSString *)baseURL;  // Convert a RSS, RDF or Atom feed to HTML.
- (DEVONthinkDatabase *) createDatabase:(NSString *)x;  // Create a new DEVONthink Pro database.
- (DEVONthinkRecord *) createLocation:(NSString *)x in:(DEVONthinkDatabase *)in_;  // Create a hierarchy of groups if necessary.
- (DEVONthinkRecord *) createPDFDocumentFrom:(NSString *)x agent:(NSString *)agent in:(DEVONthinkRecord *)in_ name:(NSString *)name pagination:(BOOL)pagination password:(NSString *)password referrer:(NSString *)referrer user:(NSString *)user width:(NSInteger)width;  // Create a new PDF document with or without pagination from a web resource.
- (BOOL) createThumbnailFor:(DEVONthinkRecord *)for_;  // Create image/movie thumbnail (and image info/characteristic) for a record.
- (DEVONthinkRecord *) createWebDocumentFrom:(NSString *)x agent:(NSString *)agent in:(DEVONthinkRecord *)in_ name:(NSString *)name password:(NSString *)password referrer:(NSString *)referrer user:(NSString *)user;  // Create a new record (picture, PDF or web archive) from a web resource.
- (BOOL) deconsolidateRecord:(DEVONthinkRecord *)record;  // Move an internal/imported record (and its children) to the enclosing external folder in the filesystem. Creation/Modification dates, Spotlight comments and OpenMeta tags are immediately updated.
- (BOOL) deleteRecord:(DEVONthinkRecord *)record in:(DEVONthinkRecord *)in_;  // Delete all instances of a record from the database or one instance from the specified group.
- (BOOL) deleteThumbnailOf:(DEVONthinkRecord *)of;  // Delete existing image/movie/web thumbnail of a record.
- (BOOL) deleteWorkspace:(NSString *)x;  // Delete a workspace.
- (DEVONthinkRecord *) displayAuthenticationDialog:(NSString *)x;  // Display a dialog to enter a username and its password.
- (DEVONthinkRecord *) displayGroupSelector:(NSString *)x buttons:(NSArray *)buttons for:(DEVONthinkDatabase *)for_;  // Display a dialog to select a (destination) group.
- (NSString *) displayNameEditor:(NSString *)x defaultAnswer:(NSString *)defaultAnswer info:(NSString *)info;  // Display a dialog to enter a name.
- (NSString *) doJavaScript:(NSString *)x in:(DEVONthinkThinkWindow *)in_;  // Applies a string of JavaScript code to a think window.
- (NSString *) downloadMarkupFrom:(NSString *)x agent:(NSString *)agent encoding:(NSString *)encoding password:(NSString *)password post:(DEVONthinkRecord *)post referrer:(NSString *)referrer user:(NSString *)user;  // Download an HTML or XML page (including RSS, RDF or Atom feeds).
- (id) downloadURL:(NSString *)x agent:(NSString *)agent password:(NSString *)password post:(DEVONthinkRecord *)post referrer:(NSString *)referrer user:(NSString *)user;  // Download a URL.
- (id) downloadWebArchiveFrom:(NSString *)x agent:(NSString *)agent password:(NSString *)password referrer:(NSString *)referrer user:(NSString *)user;  // Download a web archive (including subresources like images, scripts, stylesheets etc).
- (DEVONthinkRecord *) duplicateRecord:(DEVONthinkRecord *)record to:(DEVONthinkRecord *)to;  // Duplicate a record.
- (BOOL) existsRecordAt:(NSString *)x in:(DEVONthinkDatabase *)in_;  // Check if at least one record exists at the specified location.
- (BOOL) existsRecordWithComment:(NSString *)x in:(DEVONthinkDatabase *)in_;  // Check if at least one record with the specified comment exists.
- (BOOL) existsRecordWithFile:(NSString *)x in:(DEVONthinkDatabase *)in_;  // Check if at least one record with the specified last path component exists.
- (BOOL) existsRecordWithPath:(NSString *)x in:(DEVONthinkDatabase *)in_;  // Check if at least one record with the specified path exists.
- (BOOL) existsRecordWithURL:(NSString *)x in:(DEVONthinkDatabase *)in_;  // Check if at least one record with the specified URL exists.
- (NSString *) exportRecord:(DEVONthinkRecord *)record to:(NSString *)to;  // Export a record (and its children).
- (id) getCachedDataForURL:(NSString *)x from:(DEVONthinkTab *)from;  // Get cached data for URL of a resource which is part of a loaded webpage and its DOM tree, rendered in a think tab/window.
- (NSArray *) getConcordanceOfRecord:(DEVONthinkRecord *)record sortedBy:(DEVONthinkWSrt)sortedBy;  // Get list of words of a record.
- (DEVONthinkDatabase *) getDatabaseWithId:(NSInteger)x;  // Get database with the specified id.
- (DEVONthinkDatabase *) getDatabaseWithUuid:(NSString *)x;  // Get database with the specified uuid.
- (NSArray *) getEmbeddedImagesOf:(NSString *)x baseURL:(NSString *)baseURL type:(NSString *)type;  // Get the URLs of all embedded images of an HTML page.
- (NSArray *) getEmbeddedObjectsOf:(NSString *)x baseURL:(NSString *)baseURL type:(NSString *)type;  // Get the URLs of all embedded objects of an HTML page.
- (NSArray *) getEmbeddedSheetsAndScriptsOf:(NSString *)x baseURL:(NSString *)baseURL type:(NSString *)type;  // Get the URLs of all embedded style sheets and scripts of an HTML page.
- (NSArray *) getFramesOf:(NSString *)x baseURL:(NSString *)baseURL;  // Get the URLs of all frames of an HTML page.
- (NSArray *) getItemsOfFeed:(NSString *)x baseURL:(NSString *)baseURL;  // Get the items of a RSS, RDF or Atom feed. Dictionaries contain title (text), link (text), date (text), calendarDate (date), description (text), content (text), author (text), html (item converted to HTML), tags (list) and enclosures (list)
- (NSArray *) getLinksOf:(NSString *)x baseURL:(NSString *)baseURL containing:(NSString *)containing type:(NSString *)type;  // Get the URLs of all links of an HTML page.
- (DEVONthinkRecord *) getRecordAt:(NSString *)x in:(DEVONthinkDatabase *)in_;  // Search for record at the specified location.
- (DEVONthinkRecord *) getRecordWithId:(NSInteger)x in:(DEVONthinkDatabase *)in_;  // Get record with the specified id.
- (DEVONthinkRecord *) getRecordWithUuid:(NSString *)x in:(DEVONthinkDatabase *)in_;  // Get record with the specified uuid.
- (DEVONthinkText *) getRichTextOf:(NSString *)x baseURL:(NSString *)baseURL;  // Get the rich text of an HTML page.
- (NSString *) getTextOf:(NSString *)x;  // Get the text of an HTML page.
- (NSString *) getTitleOf:(NSString *)x;  // Get the title of an HTML page.
- (BOOL) hideProgressIndicator;  // Hide a visible progress indicator.
- (DEVONthinkRecord *) import:(NSString *)x from:(NSString *)from name:(NSString *)name placeholders:(DEVONthinkRecord *)placeholders to:(DEVONthinkRecord *)to type:(DEVONthinkItyp)type;  // Import a file or folder (including its subfolders).
- (DEVONthinkRecord *) indicate:(NSString *)x to:(DEVONthinkRecord *)to type:(DEVONthinkItyp)type;  // Indicate ('index') a file or folder (including its subfolders). If no type is specified or the type is 'all', then links to unknown file types are created too.
- (BOOL) loadWorkspace:(NSString *)x;  // Load a workspace.
- (BOOL) logMessage:(NSString *)x info:(NSString *)info;  // Log info for a file or action to the Log panel of DEVONthink Pro.
- (NSArray *) lookupRecordsWithComment:(NSString *)x in:(DEVONthinkDatabase *)in_;  // Lookup records with specified comment.
- (NSArray *) lookupRecordsWithFile:(NSString *)x in:(DEVONthinkDatabase *)in_;  // Lookup records whose last path component is the specified file.
- (NSArray *) lookupRecordsWithPath:(NSString *)x in:(DEVONthinkDatabase *)in_;  // Lookup records with specified path.
- (NSArray *) lookupRecordsWithTags:(NSArray *)x any:(BOOL)any in:(DEVONthinkDatabase *)in_;  // Lookup records with all or any of the specified tags.
- (NSArray *) lookupRecordsWithURL:(NSString *)x in:(DEVONthinkDatabase *)in_;  // Lookup records with specified URL.
- (DEVONthinkRecord *) mergeRecords:(NSArray *)records in:(DEVONthinkRecord *)in_;  // Merge either a list of records as an RTF(D)/a PDF document or merge a list of not indexed groups/tags.
- (DEVONthinkRecord *) moveRecord:(DEVONthinkRecord *)record to:(DEVONthinkRecord *)to from:(DEVONthinkRecord *)from;  // Move all instances of a record or one instance from the specified group to a different group.
- (DEVONthinkDatabase *) openDatabase:(NSString *)x;  // Open an existing DEVONthink Pro database. To close a database, use the standard "close" command.
- (DEVONthinkTab *) openTabForIn:(DEVONthinkThinkWindow *)in_ record:(DEVONthinkRecord *)record referrer:(NSString *)referrer URL:(NSString *)URL;  // Open a new tab for the specified URL or record in a think window.
- (DEVONthinkThinkWindow *) openWindowForRecord:(DEVONthinkRecord *)record;  // Open a (new) viewer or document window for the specified record (use the 'close' command to close a window). Only recommended for viewer windows, use 'open tab for' for document windows.
- (BOOL) optimizeDatabase:(DEVONthinkDatabase *)database;  // Backup & optimize a DEVONthink Pro database.
- (DEVONthinkRecord *) pasteClipboardTo:(DEVONthinkRecord *)to;  // Create a new record with the contents of the clipboard.
- (BOOL) refreshRecord:(DEVONthinkRecord *)record;  // Refresh a record. Currently only supported by feeds.
- (DEVONthinkRecord *) replicateRecord:(DEVONthinkRecord *)record to:(DEVONthinkRecord *)to;  // Replicate a record.
- (BOOL) saveWorkspace:(NSString *)x;  // Save a workspace.
- (NSArray *) search:(NSString *)x age:(double)age comparison:(DEVONthinkLkcp)comparison in:(DEVONthinkRecord *)in_ label:(NSInteger)label locking:(BOOL)locking state:(BOOL)state unread:(BOOL)unread within:(DEVONthinkLkwh)within;  // Search records by string, label, state/flag, locking and/or age.
- (BOOL) showProgressIndicator:(NSString *)x cancelButton:(BOOL)cancelButton steps:(NSInteger)steps;  // Show a progress indicator or update an already visible indicator. You have to ensure that the indicator is hidden again via 'hide progress indicator' when the script ends or if an error occurs.
- (BOOL) startDownloads;  // Start queue of download manager.
- (BOOL) stepProgressIndicator:(NSString *)x;  // Go to next step of a progress.
- (BOOL) stopDownloads;  // Stop queue of download manager.
- (BOOL) synchronizeRecord:(DEVONthinkRecord *)record;  // Synchronize a record (and its children) by importing/indexing updated external files.
- (BOOL) synchronizeOpenMetaTagsOfRecord:(DEVONthinkRecord *)record;  // Synchronize OpenMeta tags of a record.
- (BOOL) updateThumbnailOf:(DEVONthinkRecord *)of;  // Update existing image/movie thumbnail (and image info/characteristic) of a record.
- (NSInteger) verifyDatabase:(DEVONthinkDatabase *)database;  // Verify a DEVONthink Pro database. Returns total number of errors and missing files.

@end

// A color.
@interface DEVONthinkColor : DEVONthinkItem


@end

// A document.
@interface DEVONthinkDocument : DEVONthinkItem

@property (readonly) BOOL modified;  // Has the document been modified since the last save?
@property (copy) NSString *name;  // The document's name.
@property (copy) NSString *path;  // The document's path.


@end

// A window.
@interface DEVONthinkWindow : DEVONthinkItem

@property NSRect bounds;  // The bounding rectangle of the window.
@property (readonly) BOOL closeable;  // Whether the window has a close box.
@property (copy, readonly) DEVONthinkDocument *document;  // The document whose contents are being displayed in the window.
@property (readonly) BOOL floating;  // Whether the window floats.
- (NSInteger) id;  // The unique identifier of the window.
@property NSInteger index;  // The index of the window, ordered front to back.
@property (readonly) BOOL miniaturizable;  // Whether the window can be miniaturized.
@property BOOL miniaturized;  // Whether the window is currently miniaturized.
@property (readonly) BOOL modal;  // Whether the window is the application's current modal window.
@property (copy) NSString *name;  // The full title of the window.
@property (readonly) BOOL resizable;  // Whether the window can be resized.
@property (readonly) BOOL titled;  // Whether the window has a title bar.
@property BOOL visible;  // Whether the window is currently visible.
@property (readonly) BOOL zoomable;  // Whether the window can be zoomed.
@property BOOL zoomed;  // Whether the window is currently zoomed.


@end



/*
 * Text Suite
 */

// This subdivides the text into chunks that all have the same attributes.
@interface DEVONthinkAttributeRun : DEVONthinkItem

- (SBElementArray *) attachments;
- (SBElementArray *) attributeRuns;
- (SBElementArray *) characters;
- (SBElementArray *) paragraphs;
- (SBElementArray *) words;

@property (copy) NSColor *color;  // The color of the first character.
@property (copy) NSString *font;  // The name of the font of the first character.
@property NSInteger size;  // The size in points of the first character.


@end

// This subdivides the text into characters.
@interface DEVONthinkCharacter : DEVONthinkItem

- (SBElementArray *) attachments;
- (SBElementArray *) attributeRuns;
- (SBElementArray *) characters;
- (SBElementArray *) paragraphs;
- (SBElementArray *) words;

@property (copy) NSColor *color;  // The color of the first character.
@property (copy) NSString *font;  // The name of the font of the first character.
@property NSInteger size;  // The size in points of the first character.


@end

// This subdivides the text into paragraphs.
@interface DEVONthinkParagraph : DEVONthinkItem

- (SBElementArray *) attachments;
- (SBElementArray *) attributeRuns;
- (SBElementArray *) characters;
- (SBElementArray *) paragraphs;
- (SBElementArray *) words;

@property (copy) NSColor *color;  // The color of the first character.
@property (copy) NSString *font;  // The name of the font of the first character.
@property NSInteger size;  // The size in points of the first character.


@end

// Rich (styled) text
@interface DEVONthinkText : DEVONthinkItem

- (SBElementArray *) attachments;
- (SBElementArray *) attributeRuns;
- (SBElementArray *) characters;
- (SBElementArray *) paragraphs;
- (SBElementArray *) words;

@property (copy) NSColor *color;  // The color of the first character.
@property (copy) NSString *font;  // The name of the font of the first character.
@property NSInteger size;  // The size in points of the first character.

- (BOOL) addDownloadAutomatic:(BOOL)automatic password:(NSString *)password referrer:(NSString *)referrer user:(NSString *)user;  // Add a URL to the download manager.
- (NSString *) convertFeedToHTMLBaseURL:(NSString *)baseURL;  // Convert a RSS, RDF or Atom feed to HTML.
- (DEVONthinkDatabase *) createDatabase;  // Create a new DEVONthink Pro database.
- (DEVONthinkRecord *) createLocationIn:(DEVONthinkDatabase *)in_;  // Create a hierarchy of groups if necessary.
- (DEVONthinkRecord *) createPDFDocumentFromAgent:(NSString *)agent in:(DEVONthinkRecord *)in_ name:(NSString *)name pagination:(BOOL)pagination password:(NSString *)password referrer:(NSString *)referrer user:(NSString *)user width:(NSInteger)width;  // Create a new PDF document with or without pagination from a web resource.
- (DEVONthinkRecord *) createWebDocumentFromAgent:(NSString *)agent in:(DEVONthinkRecord *)in_ name:(NSString *)name password:(NSString *)password referrer:(NSString *)referrer user:(NSString *)user;  // Create a new record (picture, PDF or web archive) from a web resource.
- (BOOL) deleteWorkspace;  // Delete a workspace.
- (DEVONthinkRecord *) displayAuthenticationDialog;  // Display a dialog to enter a username and its password.
- (DEVONthinkRecord *) displayGroupSelectorButtons:(NSArray *)buttons for:(DEVONthinkDatabase *)for_;  // Display a dialog to select a (destination) group.
- (NSString *) displayNameEditorDefaultAnswer:(NSString *)defaultAnswer info:(NSString *)info;  // Display a dialog to enter a name.
- (NSString *) doJavaScriptIn:(DEVONthinkThinkWindow *)in_;  // Applies a string of JavaScript code to a think window.
- (NSString *) downloadMarkupFromAgent:(NSString *)agent encoding:(NSString *)encoding password:(NSString *)password post:(DEVONthinkRecord *)post referrer:(NSString *)referrer user:(NSString *)user;  // Download an HTML or XML page (including RSS, RDF or Atom feeds).
- (id) downloadURLAgent:(NSString *)agent password:(NSString *)password post:(DEVONthinkRecord *)post referrer:(NSString *)referrer user:(NSString *)user;  // Download a URL.
- (id) downloadWebArchiveFromAgent:(NSString *)agent password:(NSString *)password referrer:(NSString *)referrer user:(NSString *)user;  // Download a web archive (including subresources like images, scripts, stylesheets etc).
- (BOOL) existsRecordAtIn:(DEVONthinkDatabase *)in_;  // Check if at least one record exists at the specified location.
- (BOOL) existsRecordWithCommentIn:(DEVONthinkDatabase *)in_;  // Check if at least one record with the specified comment exists.
- (BOOL) existsRecordWithFileIn:(DEVONthinkDatabase *)in_;  // Check if at least one record with the specified last path component exists.
- (BOOL) existsRecordWithPathIn:(DEVONthinkDatabase *)in_;  // Check if at least one record with the specified path exists.
- (BOOL) existsRecordWithURLIn:(DEVONthinkDatabase *)in_;  // Check if at least one record with the specified URL exists.
- (id) getCachedDataForURLFrom:(DEVONthinkTab *)from;  // Get cached data for URL of a resource which is part of a loaded webpage and its DOM tree, rendered in a think tab/window.
- (DEVONthinkDatabase *) getDatabaseWithUuid;  // Get database with the specified uuid.
- (NSArray *) getEmbeddedImagesOfBaseURL:(NSString *)baseURL type:(NSString *)type;  // Get the URLs of all embedded images of an HTML page.
- (NSArray *) getEmbeddedObjectsOfBaseURL:(NSString *)baseURL type:(NSString *)type;  // Get the URLs of all embedded objects of an HTML page.
- (NSArray *) getEmbeddedSheetsAndScriptsOfBaseURL:(NSString *)baseURL type:(NSString *)type;  // Get the URLs of all embedded style sheets and scripts of an HTML page.
- (NSArray *) getFramesOfBaseURL:(NSString *)baseURL;  // Get the URLs of all frames of an HTML page.
- (NSArray *) getItemsOfFeedBaseURL:(NSString *)baseURL;  // Get the items of a RSS, RDF or Atom feed. Dictionaries contain title (text), link (text), date (text), calendarDate (date), description (text), content (text), author (text), html (item converted to HTML), tags (list) and enclosures (list)
- (NSArray *) getLinksOfBaseURL:(NSString *)baseURL containing:(NSString *)containing type:(NSString *)type;  // Get the URLs of all links of an HTML page.
- (DEVONthinkRecord *) getRecordAtIn:(DEVONthinkDatabase *)in_;  // Search for record at the specified location.
- (DEVONthinkRecord *) getRecordWithUuidIn:(DEVONthinkDatabase *)in_;  // Get record with the specified uuid.
- (DEVONthinkText *) getRichTextOfBaseURL:(NSString *)baseURL;  // Get the rich text of an HTML page.
- (NSString *) getTextOf;  // Get the text of an HTML page.
- (NSString *) getTitleOf;  // Get the title of an HTML page.
- (DEVONthinkRecord *) importFrom:(NSString *)from name:(NSString *)name placeholders:(DEVONthinkRecord *)placeholders to:(DEVONthinkRecord *)to type:(DEVONthinkItyp)type;  // Import a file or folder (including its subfolders).
- (DEVONthinkRecord *) indicateTo:(DEVONthinkRecord *)to type:(DEVONthinkItyp)type;  // Indicate ('index') a file or folder (including its subfolders). If no type is specified or the type is 'all', then links to unknown file types are created too.
- (BOOL) loadWorkspace;  // Load a workspace.
- (BOOL) logMessageInfo:(NSString *)info;  // Log info for a file or action to the Log panel of DEVONthink Pro.
- (NSArray *) lookupRecordsWithCommentIn:(DEVONthinkDatabase *)in_;  // Lookup records with specified comment.
- (NSArray *) lookupRecordsWithFileIn:(DEVONthinkDatabase *)in_;  // Lookup records whose last path component is the specified file.
- (NSArray *) lookupRecordsWithPathIn:(DEVONthinkDatabase *)in_;  // Lookup records with specified path.
- (NSArray *) lookupRecordsWithURLIn:(DEVONthinkDatabase *)in_;  // Lookup records with specified URL.
- (DEVONthinkDatabase *) openDatabase;  // Open an existing DEVONthink Pro database. To close a database, use the standard "close" command.
- (BOOL) saveWorkspace;  // Save a workspace.
- (NSArray *) searchAge:(double)age comparison:(DEVONthinkLkcp)comparison in:(DEVONthinkRecord *)in_ label:(NSInteger)label locking:(BOOL)locking state:(BOOL)state unread:(BOOL)unread within:(DEVONthinkLkwh)within;  // Search records by string, label, state/flag, locking and/or age.
- (BOOL) showProgressIndicatorCancelButton:(BOOL)cancelButton steps:(NSInteger)steps;  // Show a progress indicator or update an already visible indicator. You have to ensure that the indicator is hidden again via 'hide progress indicator' when the script ends or if an error occurs.
- (BOOL) stepProgressIndicator;  // Go to next step of a progress.

@end

// Represents an inline text attachment.  This class is used mainly for make commands.
@interface DEVONthinkAttachment : DEVONthinkText

@property (copy) NSString *fileName;  // The path to the file for the attachment


@end

// This subdivides the text into words.
@interface DEVONthinkWord : DEVONthinkItem

- (SBElementArray *) attachments;
- (SBElementArray *) attributeRuns;
- (SBElementArray *) characters;
- (SBElementArray *) paragraphs;
- (SBElementArray *) words;

@property (copy) NSColor *color;  // The color of the first character.
@property (copy) NSString *font;  // The name of the font of the first character.
@property NSInteger size;  // The size in points of the first character.


@end



/*
 * Extended Text Suite
 */

// Represents an inline text attachment.  This class is used mainly for make commands.
@interface DEVONthinkAttachment (ExtendedTextSuite)

@property (copy) NSString *fileName;  // The path to the file for the attachment

@end

// This subdivides the text into chunks that all have the same attributes.
@interface DEVONthinkAttributeRun (ExtendedTextSuite)

- (SBElementArray *) attachments;
- (SBElementArray *) attributeRuns;
- (SBElementArray *) characters;
- (SBElementArray *) paragraphs;
- (SBElementArray *) words;

@property DEVONthinkDAta alignment;  // Alignment of the text.
@property (copy) NSColor *background;  // The background color of the first character.
@property double baselineOffset;  // Number of pixels shifted above or below the normal baseline.
@property (copy) NSColor *color;  // The foreground color of the first character.
@property double firstLineHeadIndent;  // Paragraph first line head indent of the text (always 0 or positive)
@property (copy) NSString *font;  // The name of the font of the first character.
@property double headIndent;  // Paragraph head indent of the text (always 0 or positive).
@property double lineSpacing;  // Line spacing of the text.
@property double maximumLineHeight;  // Maximum line height of the text.
@property double minimumLineHeight;  // Minimum line height of the text.
@property double paragraphSpacing;  // Paragraph spacing of the text.
@property NSInteger size;  // The size in points of the first character.
@property NSInteger superscript;  // The superscript level of the text.
@property double tailIndent;  // Paragraph tail indent of the text. If positive, it's the absolute line width. If 0 or negative, it's added to the line width.
@property (copy) NSString *text;  // The actual text content.
@property BOOL underlined;  // Is the first character underlined?
@property (copy) NSString *URL;  // Link of the text.

@end

// This subdivides the text into characters.
@interface DEVONthinkCharacter (ExtendedTextSuite)

- (SBElementArray *) attachments;
- (SBElementArray *) attributeRuns;
- (SBElementArray *) characters;
- (SBElementArray *) paragraphs;
- (SBElementArray *) words;

@property DEVONthinkDAta alignment;  // Alignment of the text.
@property (copy) NSColor *background;  // The background color of the first character.
@property double baselineOffset;  // Number of pixels shifted above or below the normal baseline.
@property (copy) NSColor *color;  // The foreground color of the first character.
@property double firstLineHeadIndent;  // Paragraph first line head indent of the text (always 0 or positive)
@property (copy) NSString *font;  // The name of the font of the first character.
@property double headIndent;  // Paragraph head indent of the text (always 0 or positive).
@property double lineSpacing;  // Line spacing of the text.
@property double maximumLineHeight;  // Maximum line height of the text.
@property double minimumLineHeight;  // Minimum line height of the text.
@property double paragraphSpacing;  // Paragraph spacing of the text.
@property NSInteger size;  // The size in points of the first character.
@property NSInteger superscript;  // The superscript level of the text.
@property double tailIndent;  // Paragraph tail indent of the text. If positive, it's the absolute line width. If 0 or negative, it's added to the line width.
@property (copy) NSString *text;  // The actual text content.
@property BOOL underlined;  // Is the first character underlined?
@property (copy) NSString *URL;  // Link of the text.

@end

// This subdivides the text into paragraphs.
@interface DEVONthinkParagraph (ExtendedTextSuite)

- (SBElementArray *) attachments;
- (SBElementArray *) attributeRuns;
- (SBElementArray *) characters;
- (SBElementArray *) paragraphs;
- (SBElementArray *) words;

@property DEVONthinkDAta alignment;  // Alignment of the text.
@property (copy) NSColor *background;  // The background color of the first character.
@property double baselineOffset;  // Number of pixels shifted above or below the normal baseline.
@property (copy) NSColor *color;  // The foreground color of the first character.
@property double firstLineHeadIndent;  // Paragraph first line head indent of the text (always 0 or positive)
@property (copy) NSString *font;  // The name of the font of the first character.
@property double headIndent;  // Paragraph head indent of the text (always 0 or positive).
@property double lineSpacing;  // Line spacing of the text.
@property double maximumLineHeight;  // Maximum line height of the text.
@property double minimumLineHeight;  // Minimum line height of the text.
@property double paragraphSpacing;  // Paragraph spacing of the text.
@property NSInteger size;  // The size in points of the first character.
@property NSInteger superscript;  // The superscript level of the text.
@property double tailIndent;  // Paragraph tail indent of the text. If positive, it's the absolute line width. If 0 or negative, it's added to the line width.
@property (copy) NSString *text;  // The actual text content.
@property BOOL underlined;  // Is the first character underlined?
@property (copy) NSString *URL;  // Link of the text.

@end

// Rich (styled) text
@interface DEVONthinkText (ExtendedTextSuite)

- (SBElementArray *) attachments;
- (SBElementArray *) attributeRuns;
- (SBElementArray *) characters;
- (SBElementArray *) paragraphs;
- (SBElementArray *) words;

@property DEVONthinkDAta alignment;  // Alignment of the text.
@property (copy) NSColor *background;  // The background color of the first character.
@property double baselineOffset;  // Number of pixels shifted above or below the normal baseline.
@property (copy) NSColor *color;  // The foreground color of the first character.
@property double firstLineHeadIndent;  // Paragraph first line head indent of the text (always 0 or positive)
@property (copy) NSString *font;  // The name of the font of the first character.
@property double headIndent;  // Paragraph head indent of the text (always 0 or positive).
@property double lineSpacing;  // Line spacing of the text.
@property double maximumLineHeight;  // Maximum line height of the text.
@property double minimumLineHeight;  // Minimum line height of the text.
@property double paragraphSpacing;  // Paragraph spacing of the text.
@property NSInteger size;  // The size in points of the first character.
@property NSInteger superscript;  // The superscript level of the text.
@property double tailIndent;  // Paragraph tail indent of the text. If positive, it's the absolute line width. If 0 or negative, it's added to the line width.
@property (copy) NSString *text;  // The actual text content.
@property BOOL underlined;  // Is the first character underlined?
@property (copy) NSString *URL;  // Link of the text.

@end

// This subdivides the text into words.
@interface DEVONthinkWord (ExtendedTextSuite)

- (SBElementArray *) attachments;
- (SBElementArray *) attributeRuns;
- (SBElementArray *) characters;
- (SBElementArray *) paragraphs;
- (SBElementArray *) words;

@property DEVONthinkDAta alignment;  // Alignment of the text.
@property (copy) NSColor *background;  // The background color of the first character.
@property double baselineOffset;  // Number of pixels shifted above or below the normal baseline.
@property (copy) NSColor *color;  // The foreground color of the first character.
@property double firstLineHeadIndent;  // Paragraph first line head indent of the text (always 0 or positive)
@property (copy) NSString *font;  // The name of the font of the first character.
@property double headIndent;  // Paragraph head indent of the text (always 0 or positive).
@property double lineSpacing;  // Line spacing of the text.
@property double maximumLineHeight;  // Maximum line height of the text.
@property double minimumLineHeight;  // Minimum line height of the text.
@property double paragraphSpacing;  // Paragraph spacing of the text.
@property NSInteger size;  // The size in points of the first character.
@property NSInteger superscript;  // The superscript level of the text.
@property double tailIndent;  // Paragraph tail indent of the text. If positive, it's the absolute line width. If 0 or negative, it's added to the line width.
@property (copy) NSString *text;  // The actual text content.
@property BOOL underlined;  // Is the first character underlined?
@property (copy) NSString *URL;  // Link of the text.

@end



/*
 * DEVONthink Pro Suite
 */

// DEVONthink Pro's top level scripting object.
@interface DEVONthinkApplication (DEVONthinkProSuite)

- (SBElementArray *) databases;
- (SBElementArray *) documentWindows;
- (SBElementArray *) searchWindows;
- (SBElementArray *) thinkWindows;
- (SBElementArray *) viewerWindows;

@property (readonly) BOOL cancelledProgress;  // Specifies if a process with a visible progress indicator should be cancelled.
@property (copy, readonly) DEVONthinkRecord *contentRecord;  // The record of the visible document in the frontmost think window.
@property (copy, readonly) DEVONthinkDatabase *currentDatabase;  // The currently used database.
@property (copy, readonly) DEVONthinkRecord *currentGroup;  // The (selected) group of the frontmost window of the current database. Returns root of current database if no current group exists.
@property (copy, readonly) DEVONthinkDatabase *inbox;  // The global inbox.
@property (copy, readonly) DEVONthinkRecord *incomingGroup;  // The default group for new notes. Either global inbox or incoming group of current database.
@property (copy, readonly) NSString *lastDownloadedURL;  // The actual URL of the last download.
@property (copy, readonly) NSArray *selection;  // The selected records of the frontmost viewer or search window or the record of the frontmost document window.
@property (copy, readonly) NSArray *workspaces;  // The names of all available workspaces.

@end

// A DEVONthink Pro database (supports the standard 'close' command).
@interface DEVONthinkDatabase : DEVONthinkItem

- (SBElementArray *) contents;
- (SBElementArray *) parents;
- (SBElementArray *) records;
- (SBElementArray *) tagGroups;

@property (copy) NSString *comment;  // The comment of the database.
@property (copy, readonly) DEVONthinkRecord *currentGroup;  // The (selected) group of the frontmost window. Returns root if no current group exists.
- (NSInteger) id;  // The scripting identifier of a database.
@property (copy, readonly) DEVONthinkRecord *incomingGroup;  // The default group for new notes. Might be identical to root.
@property (copy) NSString *name;  // The name of the database.
@property (copy, readonly) NSString *path;  // The POSIX path of the database.
@property (readonly) BOOL readOnly;  // Specifies if a database is read-only and can't be modified.
@property (copy, readonly) DEVONthinkRecord *root;  // The top level group of the database.
@property (copy, readonly) DEVONthinkRecord *syncGroup;  // The group for synchronizing.
@property (copy, readonly) DEVONthinkRecord *tagsGroup;  // The group for tags.
@property (copy, readonly) DEVONthinkRecord *trashGroup;  // The trash's group.
@property (copy, readonly) NSString *uuid;  // The unique and persistent identifier of a database for external referencing.


@end

// A DEVONthink Pro database record.
@interface DEVONthinkRecord : DEVONthinkItem

- (SBElementArray *) children;
- (SBElementArray *) parents;

@property (copy, readonly) NSDate *additionDate;  // Date when the record was added to the database.
@property (copy) NSString *aliases;  // Wiki aliases (separated by commas or semicolons) of a record.
@property (copy) NSString *attachedScript;  // POSIX path of script attached to a record.
@property (copy) NSArray *cells;  // The cells of a sheet.
@property (readonly) NSInteger characterCount;  // The character count of a record.
@property (copy, readonly) NSArray *columns;  // The column names of a sheet.
@property (copy) NSString *comment;  // The comment of a record.
@property (copy) NSDate *creationDate;  // The creation date of a record.
@property (copy) id data;  // The file data of a record. Currently only supported by PDF documents, images, rich texts and web archives.
@property (copy, readonly) DEVONthinkDatabase *database;  // The database of the record.
@property (copy) NSDate *date;  // The (creation/modification) date of a record.
@property (copy, readonly) NSArray *dimensions;  // The width and height of an image or PDF document in pixels.
@property (readonly) NSInteger dpi;  // The resultion of an image in dpi.
@property (copy, readonly) NSArray *duplicates;  // The duplicates of a record (only other instances, not including the record).
@property BOOL excludeFromClassification;  // Exclude group or record from classifying.
@property BOOL excludeFromSearch;  // Exclude group or record from searching.
@property BOOL excludeFromSeeAlso;  // Exclude record from see also.
@property BOOL excludeFromTagging;  // Exclude group from tagging.
@property (copy, readonly) NSString *filename;  // The proposed file name for a record.
@property (readonly) NSInteger height;  // The height of an image or PDF document in pixels.
- (NSInteger) id;  // The scripting identifier of a record. Optimizing or closing a database might modify this identifier.
@property (copy) id image;  // The image or PDF document of a record.
@property (readonly) BOOL indexed;  // Indexed or imported record.
@property double interval;  // Refresh interval of a feed. Currently overriden by preferences.
@property (copy, readonly) NSString *kind;  // The human readable kind of a record.
@property NSInteger label;  // Index of label (0-7) of a record.
@property (copy, readonly) NSString *location;  // The location in the database as a POSIX path (/ in names is replaced with \/).
@property BOOL locking;  // The locking of a record.
@property (copy, readonly) DEVONthinkRecord *metaData;  // The metadata of a record as a dictionary containing key-value pairs. Possible keys are currently kMDItemTitle, kMDItemHeadline, kMDItemSubject, kMDItemDescription, kMDItemCopyright, kMDItemComment, kMDItemURL, kMDItemKeywords, kMDItemCreator, kMDItemProdu
@property (copy, readonly) NSString *MIMEType;  // The (proposed) MIME type of a record.
@property (copy) NSDate *modificationDate;  // The modification date of a record.
@property (copy) NSString *name;  // The name of a record.
@property (readonly) NSInteger numberOfDuplicates;  // The number of duplicates of a record.
@property (readonly) NSInteger numberOfReplicants;  // The number of replicants of a record.
@property (copy, readonly) NSDate *openingDate;  // Date when a content was opened the last time or when a feed was refreshed the last time.
@property (readonly) NSInteger pageCount;  // The page count of a record. Currently only supported by PDF documents.
@property (copy, readonly) NSString *path;  // The POSIX file path of a record.
@property (copy) NSString *plainText;  // The plain text of a record.
@property (copy, readonly) NSString *referenceURL;  // The URL (x-devonthink-item://...) to reference/link back to a record. Append ?page= to specify the zero-based index of a page of a PDF document, ?time= to specify the time of a movie or ?search= to specify a string to search.
@property (copy) DEVONthinkText *richText;  // The rich text of a record (see text suite).
@property (readonly) double score;  // The score of the last comparison, classification or search (value between 0.0 and 1.0) or undefined otherwise.
@property (readonly) NSInteger size;  // The size of a record in bytes.
@property (copy) NSString *source;  // The HTML/XML source of a record if available or the record converted to HTML if possible.
@property BOOL state;  // The state/flag of a record.
@property BOOL stateVisibility;  // Obsolete.
@property (readonly) DEVONthinkTtyp tagType;  // The tag type of a record.
@property (copy) NSArray *tags;  // The tags of a record.
@property (copy) id thumbnail;  // The thumbnail of a record.
@property (readonly) DEVONthinkDtyp type;  // The type of a record.
@property BOOL unread;  // The unread flag of a record.
@property (copy) NSString *URL;  // The URL of a record.
@property (copy, readonly) NSString *uuid;  // The unique and persistent identifier of a record.
@property (readonly) NSInteger width;  // The width of an image or PDF document in pixels.
@property (readonly) NSInteger wordCount;  // The word count of a record.

- (DEVONthinkRecord *) createRecordWithIn:(DEVONthinkRecord *)in_;  // Create a new record.

@end

// A child record of a group.
@interface DEVONthinkChild : DEVONthinkRecord


@end

// A content record of a database.
@interface DEVONthinkContent : DEVONthinkRecord


@end

// A parent group of a record.
@interface DEVONthinkParent : DEVONthinkRecord


@end

// Represents a text selection.
@interface DEVONthinkSelectedText : DEVONthinkText


@end

// A tab of a think window (supports standard 'save', 'print' and 'close' commands).
@interface DEVONthinkTab : DEVONthinkItem

@property (copy, readonly) DEVONthinkRecord *contentRecord;  // The record of the visible document.
@property (readonly) NSInteger currentPage;  // Zero-based index of current PDF page.
@property (copy, readonly) DEVONthinkDatabase *database;  // The database of the tab.
- (NSInteger) id;  // The unique identifier of the tab.
@property (readonly) BOOL loading;  // Specifies if the current web page is still loading.
@property (readonly) NSInteger numberOfColumns;  // Number of columns of the current sheet.
@property (readonly) NSInteger numberOfRows;  // Number of rows of the current sheet.
@property (copy, readonly) id paginatedPDF;  // A printed PDF with pagination of the visible document.
@property (copy, readonly) id PDF;  // A PDF without pagination of the visible document retaining the screen layout.
@property NSInteger selectedColumn;  // Index (1-n) of selected column of the current sheet.
@property (copy, readonly) NSArray *selectedColumns;  // Indices (1-n) of selected columns of the current sheet.
@property NSInteger selectedRow;  // Index (1-n) of selected row of the current sheet.
@property (copy, readonly) NSArray *selectedRows;  // Indices (1-n) of selected rows of the current sheet.
@property (copy) DEVONthinkSelectedText *selectedText;  // The text container for the selection of the tab.
@property (copy, readonly) NSString *source;  // The HTML source of the current web page.
@property (copy) DEVONthinkText *text;  // The text container of the tab.
@property (copy, readonly) DEVONthinkThinkWindow *thinkWindow;  // The think window of the tab.
@property (copy) NSString *URL;  // The URL of the current web page.
@property (copy, readonly) id webArchive;  // Web archive of the current web page.


@end

// A tag of a database.
@interface DEVONthinkTagGroup : DEVONthinkRecord


@end

// A DEVONthink Pro document, viewer or search window (supports standard 'save', 'print' and 'close' commands).
@interface DEVONthinkThinkWindow : DEVONthinkWindow

- (SBElementArray *) tabs;

@property (copy, readonly) DEVONthinkRecord *contentRecord;  // The record of the visible document.
@property (readonly) NSInteger currentPage;  // Zero-based index of current PDF page.
@property (copy) DEVONthinkTab *currentTab;  // The selected tab of the think window.
@property (copy, readonly) DEVONthinkDatabase *database;  // The database of the window.
@property (readonly) BOOL loading;  // Specifies if the current web page is still loading.
@property (readonly) NSInteger numberOfColumns;  // Number of columns of the current sheet.
@property (readonly) NSInteger numberOfRows;  // Number of rows of the current sheet.
@property (copy, readonly) id paginatedPDF;  // A printed PDF with pagination of the visible document.
@property (copy, readonly) id PDF;  // A PDF without pagination of the visible document retaining the screen layout.
@property NSInteger selectedColumn;  // Index (1-n) of selected column of the current sheet.
@property (copy, readonly) NSArray *selectedColumns;  // Indices (1-n) of selected columns of the current sheet.
@property NSInteger selectedRow;  // Index (1-n) of selected row of the current sheet.
@property (copy, readonly) NSArray *selectedRows;  // Indices (1-n) of selected rows of the current sheet.
@property (copy) DEVONthinkSelectedText *selectedText;  // The text container for the selection of the window.
@property (copy, readonly) NSString *source;  // The HTML source of the current web page.
@property (copy) DEVONthinkText *text;  // The text container of the window.
@property (copy) NSString *URL;  // The URL of the current web page.
@property (copy, readonly) id webArchive;  // Web archive of the current web page.


@end

// A DEVONthink Pro document window.
@interface DEVONthinkDocumentWindow : DEVONthinkThinkWindow

@property (copy) DEVONthinkRecord *record;  // The record of the document.


@end

// A DEVONthink Pro search window.
@interface DEVONthinkSearchWindow : DEVONthinkThinkWindow

@property (copy) NSArray *results;  // The search results.
@property (copy, readonly) NSArray *selection;  // The selected results.


@end

// A DEVONthink Pro viewer window.
@interface DEVONthinkViewerWindow : DEVONthinkThinkWindow

@property (copy) DEVONthinkRecord *root;  // The top level group of the viewer.
@property (copy) NSArray *selection;  // The selected records.


@end



/*
 * Type Definitions
 */

@interface DEVONthinkPrintSettings : SBObject

@property NSInteger copies;  // the number of copies of a document to be printed
@property BOOL collating;  // Should printed copies be collated?
@property NSInteger startingPage;  // the first page of the document to be printed
@property NSInteger endingPage;  // the last page of the document to be printed
@property NSInteger pagesAcross;  // number of logical pages laid across a physical page
@property NSInteger pagesDown;  // number of logical pages laid out down a physical page
@property (copy) NSDate *requestedPrintTime;  // the time at which the desktop printer should print the document
@property DEVONthinkEnum errorHandling;  // how errors are handled
@property (copy) NSString *faxNumber;  // for fax number
@property (copy) NSString *targetPrinter;  // for target printer

- (void) closeSaving:(DEVONthinkSavo)saving savingIn:(NSURL *)savingIn;  // Close an object.
- (void) delete;  // Delete an object.
- (void) duplicateTo:(SBObject *)to withProperties:(DEVONthinkRecord *)withProperties;  // Copy object(s) and put the copies at a new location.
- (BOOL) exists;  // Verify if an object exists.
- (void) moveTo:(SBObject *)to;  // Move object(s) to a new location.
- (void) saveAs:(NSString *)as in:(NSURL *)in_;  // Save an object.
- (void) bold;  // Bold some text
- (void) italicize;  // Italicize some text
- (void) plain;  // Make some text plain
- (void) scrollToVisible;  // Scroll to and animate some text. Requires Mac OS X 10.6.
- (void) strike;  // Strike some text
- (void) unbold;  // Unbold some text
- (void) underline;  // Underline some text
- (void) unitalicize;  // Unitalicize some text
- (void) unstrike;  // Unstrike some text
- (void) ununderline;  // Ununderline some text
- (BOOL) addRowCells:(NSArray *)cells;  // Add new row to current sheet.
- (BOOL) deleteRowAtPosition:(NSInteger)position;  // Remove row at specified position from current sheet.
- (NSString *) getCellAtColumn:(NSInteger)column row:(NSInteger)row;  // Get content of cell at specified position of current sheet.
- (BOOL) setCellAtColumn:(NSInteger)column row:(NSInteger)row to:(NSString *)to;  // Set cell at specified position of current sheet.
- (DEVONthinkRecord *) convertImageRecord:(DEVONthinkRecord *)record rotateBy:(NSInteger)rotateBy to:(DEVONthinkRecord *)to;  // Returns a searchable PDF for an image record.
- (DEVONthinkRecord *) ocrFile:(NSString *)file attributes:(DEVONthinkRecord *)attributes rotateBy:(NSInteger)rotateBy to:(DEVONthinkRecord *)to;  // Returns a record with a searchable PDF.

@end

