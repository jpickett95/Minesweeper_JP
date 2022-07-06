#include "MinesweeperWindow.h"

wxBEGIN_EVENT_TABLE(MinesweeperWindow, wxFrame) // (name of class event is for, base class)
	EVT_BUTTON(10001, OnButtonClicked)
wxEND_EVENT_TABLE()

MinesweeperWindow::MinesweeperWindow() : wxFrame(nullptr, wxID_ANY, "Minesweeper - Jonah Pickett", wxPoint(500,100), wxSize(800,600))
{
	btn = new wxButton * [mFieldWidth * mFieldHeight];
	wxGridSizer* grid = new wxGridSizer(mFieldWidth, mFieldHeight, 0, 0);

	mField = new int[mFieldWidth * mFieldHeight];

	wxFont font(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);

	for (int x = 0; x < mFieldWidth; x++) {
		for (int y = 0; y < mFieldHeight; y++) {
			btn[y * mFieldWidth + x] = new wxButton(this, 10000 + (y * mFieldWidth + x));
			btn[y * mFieldWidth + x]->SetFont(font);
			grid->Add(btn[y * mFieldWidth + x], 1, wxEXPAND | wxALL);
		
			btn[y * mFieldWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MinesweeperWindow::OnButtonClicked, this);
			mField[y * mFieldWidth + x] = 0;
		}
	}

	this->SetSizer(grid);
	grid->Layout();
}

MinesweeperWindow::~MinesweeperWindow()
{
	delete[] btn;
	delete[] mField;
}

void MinesweeperWindow::OnButtonClicked(wxCommandEvent& evt)
{
	// Get coordinate of button in field array
	int x = (evt.GetId() - 10000) % mFieldWidth;
	int y = (evt.GetId() - 10000) / mFieldWidth;

	if (mFirstClick) {
		int mines = 30;

		while (mines) {
			int rx = rand() % mFieldWidth;
			int ry = rand() % mFieldHeight;

			if (mField[ry * mFieldWidth + rx] == 0 && rx != x && ry != y) {
				mField[ry * mFieldWidth + rx] = -1;
				mines--;
			}
		}

		mFirstClick = false;
	}

	// Disable Button, preventing it from being pressed again
	btn[y * mFieldWidth + x]->Enable(false);

	// Check is player has hit a mine
	if (mField[y * mFieldWidth + x] == -1) {
		wxMessageBox("BOOOOOOM!!!!! - Game Over... :(");

		// Reset Game
		mFirstClick = true;
		for (int x = 0; x < mFieldWidth; x++) {
			for (int y = 0; y < mFieldHeight; y++) {
				mField[y * mFieldWidth + x] = 0;
				btn[y * mFieldWidth + x]->SetLabel("");
				btn[y * mFieldWidth + x]->Enable(true);
			}
		}
	}
	else {
		// Count Neighboring Mines
		int mineCount = 0;
		for (int i = -1; i < 2; i++)
			for (int j = -1; j < 2; j++) {
				if (x + i >= 0 && x + i < mFieldWidth && y + j >= 0 && y + j < mFieldHeight) {
					if (mField[(y + j) * mFieldWidth + (x + i)] == -1)
						mineCount++;
				}
			}

		// Update button labels to show mine count if > 0
		if (mineCount > 0) {
			btn[y * mFieldWidth + x]->SetLabel(std::to_string(mineCount));
		}
	}

	evt.Skip(); // tell system we are finished with event
}
