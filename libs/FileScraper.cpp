#include "../include/FileScraper.h"


namespace Scraper {
    /////////////////////////////////////////////////////////////
    // File Scraper Class Implementation (public methods)
    /////////////////////////////////////////////////////////////

    FileScraper::FileScraper(const Dir& directory, const int& id) {
        if (!std::filesystem::exists(directory.pathToDir)) {
            throw std::invalid_argument("Directory does not contain a path!");
        }
            
        m_dirToScrape = directory;
        m_workerID    = id;
    }

    bool FileScraper::collect(const int& timeout) {
        auto start = std::chrono::high_resolution_clock::now();

        std::string path = m_dirToScrape.pathToDir;
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            std::string filePath  = entry.path();
            std::string fileName  = getLastToken(filePath, "/");
            std::string name      = evaluateRegex(fileName, std::regex("(\\w*)"));
            std::string suffix    = evaluateRegex(fileName, std::regex("(\\.[a-z]*$)"));
            if (suffix.empty()) {
                continue;
            }

            std::string location     = path;
            float       size_of_file = entry.file_size();
            m_scrapedFiles.push_back(File(name, suffix, location, size_of_file));
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

    /////////////////////////////////////////////////////////////
    // File Scraper Class Implementation (private methods)
    /////////////////////////////////////////////////////////////

    std::string FileScraper::evaluateRegex(const std::string input, const std::regex regex) const {
        std::smatch match;
        std::regex_search(input, match, regex);
        
        return match.str(1);
    }

    std::string FileScraper::getLastToken(const std::string input, const std::string delimiter) const {
        int start = 0;
        int end   = input.find(delimiter);
        while (end != std::string::npos) {
            start = end + delimiter.length();
            end   = input.find(delimiter, start);
        }

        return input.substr(start, end);
    }
}