#include "MinesweeperWindow.h"

wxBEGIN_EVENT_TABLE(MinesweeperWindow, wxFrame) // (name of class event is for, base class)
	EVT_BUTTON(10001, OnButtonClicked)
wxEND_EVENT_TABLE()

MinesweeperWindow::MinesweeperWindow() : wxFrame(nullptr, wxID_ANY, "Minesweeper - Jonah Pickett", wxPoint(500,100), wxSize(800,600))
{
	btn = new wxButton * [mFieldWidth * mFieldHeight];
	wxGridSizer* grid = new wxGridSizer(mFieldWidth, mFieldHeight, 0, 0);

	for (int x = 0; x < mFieldWidth; x++) {
		for (int y = 0; y < mFieldHeight; y++) {
			btn[y * mFieldWidth + x] = new wxButton(this, 10000 + (y * mFieldWidth + x));
			grid->Add(btn[y * mFieldWidth + x], 1, wxEXPAND | wxALL);
		
			btn[y * mFieldWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MinesweeperWindow::OnButtonClicked, this);
		}
	}

	this->SetSizer(grid);
	grid->Layout();
}

MinesweeperWindow::~MinesweeperWindow()
{
	delete[] btn;
}

void MinesweeperWindow::OnButtonClicked(wxCommandEvent& evt)
{
	// Get coordinate of button in field array
	int x = (evt.GetId() - 10000) % mFieldWidth;
	int y = (evt.GetId() - 10000) / mFieldWidth;

	evt.Skip(); // tell system we are finished with event
}
