#pragma once
#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <array>


namespace Logging {
    /////////////////////////////////////////////////////////////
    // Interface Definition of the Logger
    /////////////////////////////////////////////////////////////

    class InterfaceLogger {
        public:
            virtual ~InterfaceLogger() {}
            virtual void log(const std::vector<std::string> messages) = 0;
    };

    /////////////////////////////////////////////////////////////
    // Class Definition of the Logger
    /////////////////////////////////////////////////////////////

    class BaseLogger : public InterfaceLogger {
        public:
            BaseLogger();
            void log(const std::vector<std::string> messages) override;
    };

    /////////////////////////////////////////////////////////////
    // Class Definition of the TableLogger
    /////////////////////////////////////////////////////////////
    
    class TableLogger : public InterfaceLogger {
        public:
            TableLogger();
            TableLogger(const std::string pathToLogFile,const int ncols, const int columnWidth, const std::vector<std::string> columnLabels);
            void log(const std::vector<std::string> messages) override;
            void set_logFile(std::string pathToLogFile);
            void change_settings(int ncols, int columnWidth);

        private:
            void add_hline();
            void add_line(const std::vector<std::string> labels);

            std::ofstream            logFile;
            std::vector<std::string> columnLabels;
            std::string              pathToLogFile;
            int                      ncols;
            int                      columnWidth;
    };
}

#endif