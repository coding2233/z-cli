#include <iostream>
#include <string>

#include "cli_app.h"

int main(int argc,char* args[])
{
    CliApp cli_app;
    std::string read_line;
  
    if(argc < 2)
    {
        while(true)
        {
            std::cout<<"z-cli> ";
            read_line.clear();
            std::getline(std::cin,read_line);
            if("exit" == read_line)
            {
                break;
            }
            cli_app.Run(read_line);
        }
    }
    else 
    {
        for(int i = 1;i < argc;i++)
        {
            read_line.append(args[i]);
            if (i< argc-1) 
            {
                read_line.append(" ");
            }
        }
        cli_app.Run(read_line);
    }
   
    return 0;
}