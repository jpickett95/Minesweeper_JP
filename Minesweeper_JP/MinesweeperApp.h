#pragma once
#include "wx/wx.h"
#include "MinesweeperWindow.h"

class MinesweeperApp : public wxApp
{
public:
	MinesweeperApp();
	~MinesweeperApp();

private:
	MinesweeperWindow* mFrame = nullptr;

public:
	virtual bool OnInit(); // for wxWidgets
};

