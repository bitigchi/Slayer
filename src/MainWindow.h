// MainWindow.h
// Generated by Interface Elements (Window v2.1) on Jun 27 1998
// This is a user written class and will not be overwritten.

#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include "IEWindow.h"
#include "MainWindowDefs.h"
#include "TeamItem.h"
#include "TeamListView.h"
#include "ColumnListView/CLVEasyItem.h"

#include "Hashtable.h"
#include "RefreshThread.h"

bool saveitemstatus(CLVListItem *, void *);
bool postlistproc(CLVListItem *, void *);

class MainWindow : public IEWindow {
public:
	// true if window minimized
	bool minimized;

	TeamListView	*teamView;
	float    barPos;
	
	int32 team_amount;
	// TeamItemList *team_items_list;
	Hashtable *team_items_list;	
	BList RemoveList;

	// which iteration.. used in updating teams
	int32 iteration;

	// used to calculate CPU usage by thread / team
	bigtime_t total_CPU_diff;
	
	class RefreshThread *refreshThread;
						
	MainWindow(void);
	~MainWindow(void);
	
	virtual void AttachedToWindow();
	virtual void MessageReceived(BMessage *message);
	virtual void Quit();
	virtual void Minimize(bool minimize);
	virtual void WindowActivated(bool active);
		
	void UpdateTeams();
	void RemoveProcessItems(BList *);
	void SaveStatus();
	void DoKill();
	void DoPriority(int32 priority);
	void DoPriority();
	void DoSuspend();
	void DoResume();
	void SetButtonState();
	void SetPriorityState();
	void SetPriorityField(int32 priority);
	void SwitchColumn(int32 col_id, int32 menuid);
	void SetColumn(int32 col_mask);
	void FixArchive();
};

#endif
