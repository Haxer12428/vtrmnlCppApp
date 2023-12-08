#include <wx/wx.h>
#include "../Engine/Engine.h"
#include "Application/CMD/Cmd.h"


int _STATUS()
{
	return Engine::CPU::GetUsage();
}

int _MEMSTATUS()
{
	return Engine::Memory().GetUsed(Engine::Memory::MB);
}


class Application : public wxApp {
public:

	bool OnInit() {
		Engine::Config* Cfg = new Engine::Config("C:/Vtrmnl/5/config.txt");
		//wxLogMessage(Cfg->Desire("$Font", "Hack").c_str());
		//wxLogMessage(std::to_string(Engine::String::Find("asTHIS nigger", "THIS")).c_str());



		try {
			Cmd* Cl = new Cmd(
				"CL.UI Application", "C:\\Vtrmnl\\5"
			);
		}
		catch (
			const std::exception& ex
			) {
			wxLogMessage("Critical _SETUP error occured, please restart application. \n(?) This might be caused by application overriding corrupted config.cfg");
		}

		return true; 
	}
};

wxIMPLEMENT_APP(Application);