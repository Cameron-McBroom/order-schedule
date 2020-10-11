#include <iostream>
#include <vector>

#include "src/ReportGen.h"
#include "src/Constant.h"
#include "src/Args.h"


int main(int argc, char **argv)
{
    srand(time(NULL));
    if (argc == 1) {
        // Let user know there are options
        Args::noArgMessage();

        // Let user decide whether to run default program
        std::string opt;
        std::getline(std::cin, opt);
        if (opt == "--help" || opt == "-h")
            Args::showUsage(argv);
        else {
            std::cout << "Scheduling any new reports in the " << Const::ORDERS_PATH << " directory\n";
            ReportGen().makeReports();
            return 0;
        }
    }
    return Args::checkArgOpts(argc, argv);

}

