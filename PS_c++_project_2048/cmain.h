#pragma once

#include "wx/wx.h"

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

public:
	int chenar;
	int nFieldWidth = 25;
	int nFieldHeight = 25;
	wxButton** btn;
	char color[64];
	const wxColour* var = nullptr;
	const wxColour* oldvar = nullptr;


	void OnButtonClicked(wxCommandEvent& evt);
	void rclick(wxMouseEvent& evt);
	wxDECLARE_EVENT_TABLE();
};
