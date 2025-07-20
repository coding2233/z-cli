#include <iostream>
#include <string>
#include <vector>


#include "cli_app.h"

int main(int argc,char* args[])
{
    CliApp cli_app;
    return cli_app.Run(argc,args);
// #if _WIN32
//     SetConsoleOutputCP(CP_UTF8);
// #endif

    // return 0;
}