#include "MinesweeperApp.h"

wxIMPLEMENT_APP(MinesweeperApp);

MinesweeperApp::MinesweeperApp()
{
}

MinesweeperApp::~MinesweeperApp()
{
}

bool MinesweeperApp::OnInit()
{
	mFrame = new MinesweeperWindow();
	mFrame->Show();
	return true;
}
