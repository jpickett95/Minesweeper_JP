#pragma once
#include "wx/wx.h"

class MinesweeperWindow : public wxFrame
{
public:
	MinesweeperWindow();
	~MinesweeperWindow();

public:
	int mFieldWidth = 10;
	int mFieldHeight = 10;
	wxButton **btn;

	void OnButtonClicked(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

