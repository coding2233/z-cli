#include <iostream>
#include <string>
#include <vector>

#include "cli_app.h"

int main(int argc,char* args[])
{
    CliApp cli_app;

    std::string action;
    std::vector<std::string> action_args;
  
    if(argc < 2)
    {
        std::string read_line;
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
        action = args[1];
        for(int i = 2;i < argc;i++)
        {
            action_args.push_back(args[i]);
        }
        cli_app.Run(action,action_args);
    }
   
    return 0;
}