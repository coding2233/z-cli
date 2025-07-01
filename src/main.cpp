#include <iostream>
#include <string>

#include "cli_app.h"

int main(int argc,char* args[])
{
    if(argc < 2)
    {
        return -1;
    }

    CliApp cli_app(argc,args);
    return 0;
}