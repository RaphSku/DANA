#include <stdexcept>
#include <chrono>
#include <filesystem>
#include <regex>
#include <sstream>

#include "../include/FileScraper.h"


namespace Scraper {
    /////////////////////////////////////////////////////////////
    // File Scraper Class Implementation (public methods)
    /////////////////////////////////////////////////////////////

    FileScraper::FileScraper(const Dir& directory, const int& id) {
        if (directory.pathToDir.empty()) {
            throw std::invalid_argument("Directory does not contain a path!");
        }
        m_dirToScrape = directory;
        m_workerID    = id;
    }

    bool FileScraper::collect(const int& timeout) {
        auto start = std::chrono::high_resolution_clock::now();

        std::string path = m_dirToScrape.pathToDir;
        for (auto& entry : std::filesystem::directory_iterator(path)) {
            std::stringstream ss;
            ss << entry;
            std::string entry_to_string;
            ss << entry_to_string;

            std::regex  name_rx("^\w*");
            std::smatch name_match;
            std::regex_search(entry_to_string, name_match, name_rx);
            std::string name         = name_match.str(1);

            std::regex  suffix_rx("\.[a-z]{3}$");
            std::smatch suffix_match;
            std::regex_search(entry_to_string, suffix_match, suffix_rx);
            std::string suffix       = suffix_match.str(1);
            if (suffix.empty()) {
                continue;
            }

            std::string location     = path;
            float       size_of_file = entry.file_size();
            File file(name, suffix, location, size_of_file);
            m_scrapedFiles.push_back(file);
        }

        auto end   = std::chrono::high_resolution_clock::now();
        auto clock = std::chrono::duration_cast<std::chrono::seconds>(end - start); 
        if (clock.count() >= timeout) {
            return true;
        }
        return false;
    }

    std::deque<File> FileScraper::getFiles() const {
        return m_scrapedFiles;
    }

    int FileScraper::getID() const {
        return m_workerID;
    }
}