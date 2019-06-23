cmake_minimum_required(VERSION 2.8.9)
project (CSVReader)

add_executable(
        CSVReader.h;
        CSVReader.cpp;
        Row.h;
        Row.cpp;
        Table.h;
        Table.cpp;
        CSVData.h;
        CSVData.cpp;
        main.cpp;
)