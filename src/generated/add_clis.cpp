// This file is generated automatically by xmake. Do not edit.

#include "cli_app.h"
#include "update/update_cli.h"
#include "json/json_cli.h"
#include "fanyi/fanyi_cli.h"
#include "excel/excel_cli.h"

void CliApp::AddClis()
{
    AddCli<UpdateCli>("update");
    AddCli<JsonCli>("json");
    AddCli<FanyiCli>("fy");
    AddCli<ExcelCli>("excel");
}
