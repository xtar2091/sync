#include "CommanLine.h"

#include <boost/filesystem.hpp>
#include <fmt/format.h>

namespace
{
    class HelpInfoPrinter
    {
    public:
        HelpInfoPrinter();
        ~HelpInfoPrinter();

    public:
        bool show_help_info;
    };

    HelpInfoPrinter::HelpInfoPrinter()
    {
        show_help_info = true;
    }

    HelpInfoPrinter::~HelpInfoPrinter()
    {
        if (!show_help_info)
        {
            return;
        }
        fmt::print("usage: sync <sync_dir>\n");
    }
}

bool CommanLine::Check(int argc, char* argv[])
{
    HelpInfoPrinter printer;
    if (argc != 2) return false;
    boost::filesystem::path conf_path(argv[1]);
    if (!boost::filesystem::is_directory(conf_path)) return false;
    printer.show_help_info = false;
    return true;
}
