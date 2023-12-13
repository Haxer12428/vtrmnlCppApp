#define CPPHTTPLIB_OPENSSL_SUPPORT

#include "wx/wx.h"
#include "frame/frame.h"
#include "graph/graph.h"
#include "../engine/engine.h"


class application : public wxApp {
	virtual bool OnInit() {

		try {
			wxFrame* mainframe = new frame("Vtrmnl5");
		}
		catch (
			const std::exception& ex
			) {
			wxLogMessage(
				(std::string("Unknown error thrown, please restart application.\n(?) ") + ex.what()).c_str()
			);
		}

		return true; 
	}
};

wxIMPLEMENT_APP(application);