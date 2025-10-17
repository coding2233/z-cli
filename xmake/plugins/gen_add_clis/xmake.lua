task("gen_add_clis")
    set_category("plugin")
    on_run(function ()
        local modules = {}
        for _, dir in ipairs(os.dirs("src/*")) do
            local module_name = path.basename(dir)
            if module_name ~= "core" and module_name ~= "generated" then
                table.insert(modules, module_name)
            end
        end

        local content = "// This file is generated automatically by xmake. Do not edit.\n\n"
        content = content .. "#include \"cli_app.h\"\n"
        for _, module_name in ipairs(modules) do
            local cli_name = module_name:gsub("-%", "_"):gsub(" ", "_")
            local cli_class_name = cli_name:sub(1,1):upper() .. cli_name:sub(2) .. "Cli"
            content = content .. "#include \"" .. module_name .. "/" .. cli_name .. "_cli.h\"\n"
        end

        content = content .. "\nvoid CliApp::AddClis()\n{\n"

        for _, module_name in ipairs(modules) do
            local cli_name = module_name:gsub("-%", "_"):gsub(" ", "_")
            local cli_class_name = cli_name:sub(1,1):upper() .. cli_name:sub(2) .. "Cli"
            local command_name = module_name
            content = content .. string.format("    AddCli<%s>(\"%s\");\n", cli_class_name, command_name)
        end

        content = content .. "}\n"

        os.tryrm("src/generated")
        os.mkdir("src/generated")
        io.writefile("src/generated/add_clis.cpp", content)
    end)
    set_menu {
        usage = "xmake gen_add_clis",
        description = "Generate the AddClis function for z-cli.",
        options = {}
    }
