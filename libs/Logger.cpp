#include "../include/Logger.h"


namespace Logging {
    /////////////////////////////////////////////////////////////
    // BaseLogger Class Implementation (public methods)
    /////////////////////////////////////////////////////////////

    BaseLogger::BaseLogger() {

    }
    
    void BaseLogger::log(const std::vector<std::string> messages) {

    }

    /////////////////////////////////////////////////////////////
    // TableLogger Class Implementation (public methods)
    /////////////////////////////////////////////////////////////

    TableLogger::TableLogger() {

    }
    
    TableLogger::TableLogger(std::string pathToLogFile, int ncols, int columnWidth, std::vector<std::string> columnLabels)
        : pathToLogFile(pathToLogFile), ncols(ncols), columnWidth(columnWidth), columnLabels(columnLabels) {
        
        if (!std::filesystem::exists(pathToLogFile)) {
            std::ofstream new_file(pathToLogFile);
        }

        add_hline();
        add_line(columnLabels);
        add_hline();
    }

    void TableLogger::log(const std::vector<std::string> messages) {
        add_line(messages);
    }

    /////////////////////////////////////////////////////////////
    // TableLogger Class Implementation (private methods)
    /////////////////////////////////////////////////////////////

    void TableLogger::add_hline() {
        int total_width = ncols * columnWidth + ncols - 2;

        std::string tmp;
        tmp = std::string(total_width, '-');
        logFile.open(pathToLogFile, std::ios::app);
        logFile << tmp << "\n";
        logFile.close();
    }

    void TableLogger::add_line(const std::vector<std::string> labels) {
        std::vector<std::string> columns;
        int index       = 0;
        std::string tmp = "";
        for (auto& label : labels) {
            int leftSpace = columnWidth - label.size();
            int margin     = int(leftSpace / 2);
            if (index == labels.size() - 1) {
                columns.push_back(std::string(margin, ' ') + label + std::string(int(margin - 1), ' '));
                break;
            }
            if (label.size() % 2 == 0 && leftSpace % 2 == 0) {
                columns.push_back(std::string(margin, ' ') + label + std::string(int(margin - 1), ' ') + "|");
            } else if (label.size() % 2 != 0 && leftSpace % 2 == 0) {
                columns.push_back(std::string(margin, ' ') + label + std::string(margin, ' ') + "|");
            } else if (label.size() % 2 == 0 && leftSpace % 2 != 0) {
                columns.push_back(std::string(int(margin + 1), ' ') + label + std::string(margin, ' ') + "|");
            } else if (label.size() % 2 != 0 && leftSpace % 2 != 0) {
                columns.push_back(std::string(margin, ' ') + label + std::string(margin, ' ') + "|");
            }
            index++;
        }

        for (auto& item : columns) {
            tmp += item;
        }

        logFile.open(pathToLogFile, std::ios::app);
        logFile << tmp << "\n";
        logFile.close();
    }

    void TableLogger::set_logFile(std::string pathToLogFile) {
        pathToLogFile = pathToLogFile;
    }

    void TableLogger::change_settings(int ncols, int columnWidth) {
        ncols        = ncols;
        columnWidth  = columnWidth;
    }
}