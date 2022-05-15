#include "mcc_generated_files/mcc.h"
#include "cli.h"
/*
    Main application
*/
int main(void)
{
    /* Initializes MCU, drivers and middleware */
    SYSTEM_Initialize();

    while (1)
    {
        cliHandler();
    }
}
/**
    End of File
*/