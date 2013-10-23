// AboutWindow.cpp
// Generated by Interface Elements (Window v2.2) on Jan 7 1999
// This is a user written class and will not be overwritten.

#include "AboutWindow.h"
#include "SlayerApp.h"

#include <TranslationKit.h>
#include <SupportKit.h>
#include <InterfaceKit.h>

AboutWindow::AboutWindow(void)
	: IEWindow("AboutWindow")
{
	BView *bgview = NULL; 

	if (Lock()) {
		BStringView *version = (BStringView *)FindView("AboutVersion");

		version->SetText(SLAYER_VERSION);

		bgview = (BView *)FindView("AboutBackground");
		
		// Load the background picture from resources
		// Using IE resources...
		size_t data_size;
		void *data = resourcehandler->FindResource("SLAYER_ABOUT", B_RAW_TYPE, &data_size);
		if (data) {
			BTranslatorRoster *roster = BTranslatorRoster::Default();
			if (roster) {
				BMemoryIO *dataIO = new BMemoryIO(data, data_size);
				BBitmapStream *dstIO = new BBitmapStream;
				if (roster->Translate(dataIO, NULL, NULL, dstIO, B_TRANSLATOR_BITMAP)
					!= B_NO_ERROR) printf("Error during translation");
				
				BBitmap *bits = NULL;
				dstIO->DetachBitmap(&bits);
				if (!bits->IsValid()) {
					printf("Not a valid bitmap");
				}
				else {
					//bgview->SetFlags(bgview->Flags() | B_DRAW_ON_CHILDREN);
					bgview->SetViewColor(B_TRANSPARENT_COLOR);
					// set text so that it shows the background picture
					BView *child = bgview->ChildAt(0);
					uchar green = 255;
					for (; child; child = child->NextSibling()) {
						child->SetDrawingMode(B_OP_OVER); 
						child->SetHighColor(255,green > 0 ? green : 0,0);

						green -= 20;
					}
					
					// now comes the ugly part... coding round the BeOS bugs :(
					// I don't wanna comment this shit..
					BMessage arc;
					bgview->Archive(&arc);
					RemoveChild(bgview);
					bgview = (BView *)instantiate_object(&arc);
					AddChild(bgview);
					bgview->SetViewBitmap(bits, bits->Bounds(), Bounds());
				}		
				delete bits;
				delete dataIO;
				delete dstIO;
				
			}
			else printf("No translator roster\n");
		}
		else printf("Couldn't find raw picture data\n");

		Unlock();
	}
	Show();
}


AboutWindow::~AboutWindow(void)
{
}
