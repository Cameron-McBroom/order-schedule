#pragma once

#include <string>

#include "BundleGenerator.h"
#include "Schedule.h"
#include "SmartSchedule.h"
#include "libs/csvfile.h"

class ReportGen {
private:
    int lastReportIdx_;
    int lastBundleIdx_;
    void updateReportIdx();

public:
    ReportGen();
    void makeReports();
    void genBundleMakeReport();
    void reScheduleAll();

    template <typename ostream>
    static void gen(const std::string &path, ostream &out);

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
        std::string bundle = Const::ORDERS_PATH+Const::BUNDLE_NAME+idxString+".txt";
        std::ofstream txtReport(Const::REPORTS_PATH+Const::REPORT_NAME+idxString+".txt");
        csvfile csv(Const::REPORTS_PATH+Const::SCHEDULE_NAME+idxString+".csv");
        gen(bundle, txtReport);
        gen(bundle, csv);
        updateReportIdx();
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
        std::string bundle = Const::ORDERS_PATH+Const::BUNDLE_NAME+idxString+".txt";
        std::ofstream txtReport(Const::REPORTS_PATH+Const::REPORT_NAME+idxString+".txt");
        csvfile csv(Const::REPORTS_PATH+Const::SCHEDULE_NAME+idxString+".csv");
        gen(bundle, txtReport);
        gen(bundle, csv);
        updateReportIdx();
    }
}
template <typename ostream>
void ReportGen::gen(const std::string &path, ostream &out) {
    std::ifstream bundle(path);
    Schedule *orders;
    orders = new SmartSchedule(bundle);
    orders->createSchedule();
    orders->makeReport(out);
    delete orders;
    std::cout << "Generating Report For Bundle: " << path << std::endl;
}
