#include "godmode.h"
#include "unittype.h"
#include "power.h"
#include "pxi.h"

void main(int argc, char** argv)
{
    (void) argv; // unused for now
    
    // running from FIRM0 partition?
    if (IS_SIGHAX && !argc)
        GodModeFirm0();
    
    // Screen on
    ScreenOn();

    // Run the main program
    if (GodMode() == GODMODE_EXIT_REBOOT) Reboot();
    else PowerOff();
}
