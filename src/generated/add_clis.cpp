// This file is generated automatically by xmake. Do not edit.

#include "cli_app.h"
#include "excel/excel_cli.h"
#include "fanyi/fanyi_cli.h"
#include "json/json_cli.h"
#include "update/update_cli.h"

void CliApp::AddClis()
{
    AddCli<ExcelCli>("excel");
    AddCli<FanyiCli>("fanyi");
    AddCli<JsonCli>("json");
    AddCli<UpdateCli>("update");
}
