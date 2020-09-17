cmake_minimum_required(VERSION 3.17)
project(productionScheduling)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(productionScheduling
        Component.h
        Constant.h
        Date.h
        main.cpp
        Order.h
        Product.h
        Unit.h Schedule.h ParseOrders.h QuickSort.h Utility.h BundleGenerator.h SmartSchedule.h ReportGen.h libs/args.hxx Args.h)
