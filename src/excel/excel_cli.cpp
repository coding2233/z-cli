#include "excel_cli.h"

  std::string ExcelCli::GetName()
  {
    return "excel";
  }
  
  std::string ExcelCli::GetHelp()
  {
    return "ExcelCli";
  }

void ExcelCli::Run(int argc,char* args[])
{
    std::cout<< "ExcelCli"<<std::endl;
}

