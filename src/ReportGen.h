#pragma once

#include <string>

#include "BundleGenerator.h"
#include "Schedule.h"
#include "SmartSchedule.h"

class ReportGen {
private:
    int lastReportIdx_;
    int lastBundleIdx_;
    void updateReportIdx();

public:
    ReportGen();
    static void gen(const std::string &path, std::ostream &out);
    void makeReports();
    void genBundleMakeReport();
    void reScheduleAll();
};

ReportGen::ReportGen() {
    lastBundleIdx_ = BundleGenerator::getLastBundleIdx();
    updateReportIdx();
}

void ReportGen::updateReportIdx() {
    std::size_t reportIdx = 0;
    std::string path = Const::REPORTS_PATH + Const::REPORT_NAME + ".txt";
    while (util::fileExists(path)) {
        reportIdx ++;
        path = Const::REPORTS_PATH + Const::REPORT_NAME + std::to_string(reportIdx) + ".txt";
    }
    lastReportIdx_ = reportIdx;
}

void ReportGen::makeReports() {
    while (lastReportIdx_ < lastBundleIdx_) {
        auto idxString = (lastReportIdx_ == 0 ? "" : std::to_string(lastReportIdx_));

        // Open corresponding bundle & report output file
        std::ifstream bundle(Const::ORDERS_PATH+ Const::BUNDLE_NAME+idxString+".txt");
        std::ofstream report(Const::REPORTS_PATH+Const::REPORT_NAME+idxString+".txt");

        Schedule *orders;
        orders = new SmartSchedule(bundle);
        orders->createSchedule();
        orders->makeReport(report);
        report.close();
        delete orders;
        std::cout << "Generating Report Number: " << lastReportIdx_ << std::endl;
        updateReportIdx();
    }
}

void ReportGen::genBundleMakeReport() {
    BundleGenerator()(); // generate new bundle
    lastBundleIdx_ = BundleGenerator::getLastBundleIdx();
    makeReports();
}

void ReportGen::reScheduleAll() {
    for (int i = 0; i < lastBundleIdx_; ++i) {
        // Check if it is 0
        auto idxString = (i == 0 ? "" : std::to_string(i));

        // Open corresponding bundle & report output file
        std::ifstream bundle(Const::ORDERS_PATH+Const::BUNDLE_NAME+idxString+".txt");
        std::ofstream report(Const::REPORTS_PATH+Const::REPORT_NAME+idxString+".txt");

        Schedule *orders;
        orders = new SmartSchedule(bundle);
        orders->createSchedule();
        orders->makeReport(report);
        report.close();
        delete orders;
        std::cout << "Generating Report Number: " << i << std::endl;
        updateReportIdx();
    }
}

void ReportGen::gen(const std::string &path, std::ostream &out = std::cout) {
    std::ifstream bundle(path);
    Schedule *orders;
    orders = new SmartSchedule(bundle);
    orders->createSchedule();
    orders->makeReport(out);
    delete orders;
    std::cout << "Generating Report For Bundle: " << path << std::endl;
}