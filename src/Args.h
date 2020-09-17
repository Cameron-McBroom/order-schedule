#pragma once

#include <iostream>
#include "Constant.h"
#include "BundleGenerator.h"
#include "ReportGen.h"

class Args {
public:
    static void noArgMessage() {
        std::cout << "You have not entered any commands, or options.\n"
                  << "Default no args, will schedule any orders in the" << Const::ORDERS_PATH << " directory\n"
                  << "Press any key to continue, or enter -h or --help for more options\n";
    }

    static void showUsage(char **argv) {
        std::cerr << "Usage: " << argv[0] << " <option(s)> SOURCES\n"
        << "Options:\n"
        << "\tNo arguments results in program scheduling new bundles in the bundle directory\n"
        << "\t-h,--help"<< std::setw(60) <<std::right <<"Show this help message\n"
        << "\t-b,--bundle"<< std::setw(60)<<std::right <<"Create new bundle and save to orders path\n"
        << "\t-r,--report"<< std::setw(60) <<"BUNDLE NAME\tSpecify the order bundle path\n"
        << "\t-rs,--re-schedule"<< std::setw(60) << "BUNDLE NAME\tSpecify the order bundle path\n"
                  << std::endl;
    }

    static int checkArgOpts(int argc, char **argv) {
        for (int i = 1; i < argc; ++i) {
            std::string arg(argv[i]);
            if (arg == "-h" || arg == "--help") {
                showUsage(argv);
                return 0;
            }

            if (arg == "--bundle" || arg == "-b") {
                std::cout << "Making new bundle of orders, saving to: " << Const::ORDERS_PATH << std::endl;
                BundleGenerator()();
                return 0;
            }

            if (arg == "--report" || arg == "-r") {
                if (i + 1 < argc) {
                    std::string path(argv[i + 1]);
                    if (util::fileExists(path)) {
                        ReportGen::gen(path);
                        return 0;
                    } else {
                        std::cerr << "file path does not exist\n";
                        return 1;
                    }
                } else {
                    std::cerr << "--report option requires a file path to schedule\n";
                    return 1;
                }
            }

            if (arg == "--re-schedule" || arg == "-rs") {
                std::cout << "Re-scheduling all reports in the " << Const::ORDERS_PATH << " directory\n";
                ReportGen().reScheduleAll();
                return 0;
            }
        }
        return 1;
    }
};