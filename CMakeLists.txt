cmake_minimum_required(VERSION 3.17)
project(productionScheduling)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(
        productionScheduling
        src/Component.h
        src/Constant.h
        src/Date.h
        main.cpp
        src/Order.h
        src/Product.h
        src/Unit.h
        src/Schedule.h
        src/ParseOrders.h
        src/QuickSort.h
        src/Utility.h
        src/BundleGenerator.h
        src/SmartSchedule.h
        src/ReportGen.h
        src/Args.h
        libs/csvfile.h)
