#include "Window/Window.h"
#include "Config/Config.h"
#include "Commands/Commands.h"
#include <windows.h>

class App : public wxApp {
public:
    virtual bool OnInit() {
        Window* App = new Window("VTRMNL");

        Commands* CommandList = new Commands(App);

        //App->PushCommand(&Commands::Echo);

        Config* cfg = new Config("C:/Cl/config.txt");
        cfg->NewConfigVariable("$variable", std::to_string(1));
        cfg->HandleConfigFile();

        
        return true;
    }
};

wxIMPLEMENT_APP(App);