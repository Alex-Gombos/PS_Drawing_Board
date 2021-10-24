#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Pixel Painting", wxPoint(30, 30), wxSize(800, 800))
{
	//constr
	//generate drawing matrix V

	wxInitAllImageHandlers();
	btn = new wxButton * [cMain::nFieldWidth * cMain::nFieldHeight];
	wxGridSizer* grid = new wxGridSizer(cMain::nFieldWidth, cMain::nFieldHeight, 0, 0);
	chenar=0;
	for (int x = 0; x < cMain::nFieldWidth; x++)
	{
		for (int y = 0; y < cMain::nFieldHeight; y++)
		{
			btn[y * (cMain::nFieldWidth) + x] = new wxButton(this, 10000 + (y * (cMain::nFieldWidth) + x));
			grid->Add(btn[y * (cMain::nFieldWidth) + x], 1, wxEXPAND | wxALL);
			btn[y * cMain::nFieldWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnButtonClicked, this);
			btn[y * cMain::nFieldWidth + x]->Bind(wxEVT_RIGHT_DOWN, &cMain::rclick, this);
			btn[y * cMain::nFieldWidth + x]->SetBackgroundColour(wxColour(*wxWHITE));
		}
	}
	this->SetSizer(grid);
	grid->Layout();
	//create a border around the drawing matrix and disable buttons
	for (int x = 0; x < cMain::nFieldWidth; x++) {
		btn[x * cMain::nFieldWidth + 0]->SetBackgroundColour(wxColour(*wxLIGHT_GREY));
		btn[x * cMain::nFieldWidth + 0]->Enable(false);
	}
	for (int y = 0; y < cMain::nFieldWidth; y++) {
		btn[0 * cMain::nFieldWidth + y]->SetBackgroundColour(wxColour(*wxLIGHT_GREY));
		btn[0 * cMain::nFieldWidth + y]->Enable(false);
	}
	for (int x = cMain::nFieldWidth-1; x >= 0 ; x--) {
		btn[x * cMain::nFieldWidth + nFieldHeight-1]->SetBackgroundColour(wxColour(*wxLIGHT_GREY));
		btn[x * cMain::nFieldWidth + nFieldHeight - 1]->Enable(false);
	}
	for (int y = cMain::nFieldWidth - 1; y >= 0; y--) {
		btn[(nFieldHeight-1) * cMain::nFieldWidth + y]->SetBackgroundColour(wxColour(*wxLIGHT_GREY));
		btn[(nFieldHeight-1) * cMain::nFieldWidth + y]->Enable(false);
	}

	//reset button
	btn[(nFieldHeight - 1) * cMain::nFieldWidth + nFieldHeight-1]->Enable(true);
	btn[(nFieldHeight - 1) * cMain::nFieldWidth + nFieldHeight-1]->SetLabel("R");

	//generate color picker

	for (int y = 1; y < cMain::nFieldHeight; y++) {
		switch (y) {
		case 1:
			btn[1 * cMain::nFieldWidth + y]->SetBackgroundColour(wxColour(*wxBLACK));
			break;
		case 2:
			btn[1 * cMain::nFieldWidth + y]->SetBackgroundColour(wxColour(*wxBLUE));
			break;
		case 3:
			btn[1 * cMain::nFieldWidth + y]->SetBackgroundColour(wxColour(*wxCYAN));
			break;
		case 4:
			btn[1 * cMain::nFieldWidth + y]->SetBackgroundColour(wxColour(*wxGREEN));
			break;
		case 5:
			btn[1 * cMain::nFieldWidth + y]->SetBackgroundColour(wxColour(*wxYELLOW));
			break;
		case 6:
			btn[1 * cMain::nFieldWidth + y]->SetBackgroundColour(wxColour(*wxLIGHT_GREY));
			break;
		case 7:
			btn[1 * cMain::nFieldWidth + y]->SetBackgroundColour(wxColour(*wxWHITE));
			break;
		case 8:
			btn[1 * cMain::nFieldWidth + y]->SetBackgroundColour(wxColour(*wxRED));
			break;
		}
	}
}
cMain::~cMain()
{
	//deconstr
	delete[]btn;
}

void cMain::OnButtonClicked(wxCommandEvent& evt)
{
	//get coordonates of clicked cell
	int x = (evt.GetId() - 10000) % cMain::nFieldWidth;
	int y = (evt.GetId() - 10000) / cMain::nFieldHeight;
	if (y == 1) {
		switch (x) {
		case 1:
			strcpy(cMain::color, "black");
			var = wxBLACK;
			break;
		case 2:
			strcpy(cMain::color, "blue");
			var = wxBLUE;
			break;
		case 3:
			strcpy(cMain::color, "cyan");
			var = wxCYAN;
			break;
		case 4:
			strcpy(cMain::color, "green");
			var = wxGREEN;
			break;
		case 5:
			strcpy(cMain::color, "yellow");
			var = wxYELLOW;
			break;
		case 6:
			strcpy(cMain::color, "grey");
			var = wxLIGHT_GREY;
			break;
		case 7:
			strcpy(cMain::color, "white");
			var = wxWHITE;
			break;
		case 8:
			strcpy(cMain::color, "red");
			var = wxRED;
			break;
		}
	}

	if (y != 1 && var!=nullptr) {
		btn[y * cMain::nFieldWidth + x]->SetBackgroundColour(wxColor(*var));
		btn[(nFieldWidth-2) * cMain::nFieldWidth + 0]->SetLabel(std::to_string(x));
		btn[(nFieldWidth-1) * cMain::nFieldWidth + 0]->SetLabel(std::to_string(y));

	}
	if (y == nFieldHeight - 1 && x == nFieldWidth - 1) {
		for (int i = 1; i < nFieldHeight - 1; i++) {
			for (int j = 2; j < cMain::nFieldWidth - 1; j++) {
				btn[j * cMain::nFieldWidth + i]->SetBackgroundColour(wxColor(*wxWHITE));
			}
		}
	}
}
void cMain::rclick(wxMouseEvent& evt)
{
	int x = (evt.GetId() - 10000) % cMain::nFieldWidth;
	int y = (evt.GetId() - 10000) / cMain::nFieldWidth;
	int c1, c2, c3, c4;
	chenar++;
	switch (chenar)
	{
	case 1:
		c1 = evt.GetId();
		btn[(nFieldWidth - 2) * cMain::nFieldWidth + 0]->SetLabel(std::to_string(x));
		btn[(nFieldWidth - 1) * cMain::nFieldWidth + 0]->SetLabel(std::to_string(y));
		btn[y * cMain::nFieldWidth + x]->SetBackgroundColour(wxColor(*wxRED));
		break;
	case 2:
		c2 = evt.GetId();
		btn[(nFieldWidth - 2) * cMain::nFieldWidth + 0]->SetLabel(std::to_string(x));
		btn[(nFieldWidth - 1) * cMain::nFieldWidth + 0]->SetLabel(std::to_string(y));
		btn[y * cMain::nFieldWidth + x]->SetBackgroundColour(wxColor(*wxRED));
		break;
	case 3:
		c3 = evt.GetId();
		btn[(nFieldWidth - 2) * cMain::nFieldWidth + 0]->SetLabel(std::to_string(x));
		btn[(nFieldWidth - 1) * cMain::nFieldWidth + 0]->SetLabel(std::to_string(y));
		btn[y * cMain::nFieldWidth + x]->SetBackgroundColour(wxColor(*wxRED));
		break;
	case 4:
		c4 = evt.GetId();
		btn[(nFieldWidth - 2) * cMain::nFieldWidth + 0]->SetLabel(std::to_string(x));
		btn[(nFieldWidth - 1) * cMain::nFieldWidth + 0]->SetLabel(std::to_string(y));
		btn[y * cMain::nFieldWidth + x]->SetLabel(std::to_string(chenar));
		chenar = 0;
		break;
	}
	if (chenar == 0) {
		for (int i = (c1 - 10000) % cMain::nFieldWidth; i <= (c2 - 10000) % cMain::nFieldWidth; i++) {
			for (int j = (c1 - 10000) / cMain::nFieldWidth; j <= (c3 = 10000) % cMain::nFieldWidth; j++) {
				btn[i * cMain::nFieldWidth + j]->SetLabel(std::to_string(i));
			}
		}
	}
	evt.Skip();
}
