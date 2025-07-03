#include <iostream>
#include <string>

#include "cli_app.h"

int main(int argc,char* args[])
{
    CliApp cli_app(argc,args);
    if(argc < 2)
    {
        std::string read_line;
        while(true)
        {
            std::cout<<"z-cli> ";
            std::getline(std::cin,read_line);
            if("exit" == read_line)
            {
                break;
            }
            cli_app.Run(read_line);
        }
    }
   
    return 0;
}