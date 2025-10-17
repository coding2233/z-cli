#ifndef __CLI_H__
#define __CLI_H__

#include <memory>
#include <string>
#include <iostream>
#include <vector>

#include "core/cli_core.h"
#include "cxxopts.hpp"

class Cli
{
    public:
        Cli(std::string name, std::string help_text = "") : options_(name, help_text), help_text_(help_text) {}
        virtual void SetupOptions() = 0;
        virtual bool Run(cxxopts::ParseResult result) = 0;
        virtual std::string GetHelpText() const { return help_text_; }
        cxxopts::Options& GetOptions() { return options_; }
    protected:
        cxxopts::Options options_;
        std::string help_text_;
};

#endif