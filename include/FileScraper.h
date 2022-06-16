#pragma once
#ifndef FILESCRAPER_H_
#define FILESCRAPER_H_

#include <iostream>
#include <deque>
#include <stdexcept>
#include <chrono>
#include <filesystem>
#include <regex>
#include <sstream>
#include <filesystem>

#include "CustomTypes.h"


namespace Scraper {
    /////////////////////////////////////////////////////////////
    // Interface Definition of the File Scraper
    /////////////////////////////////////////////////////////////

    class InterfaceFileScraper {
        public:
            virtual ~InterfaceFileScraper() {}
            virtual bool collect(const int& timeout) = 0;
            virtual std::deque<File> getFiles() const = 0;

        protected:
            std::deque<File> m_scrapedFiles;
            Dir              m_dirToScrape;
    };

    /////////////////////////////////////////////////////////////
    // Class Definition of the File Scraper
    /////////////////////////////////////////////////////////////

    class FileScraper : InterfaceFileScraper {
        public:
            FileScraper(const Dir& directory, const int& id);
            bool collect(const int& timeout) override;

            std::deque<File> getFiles() const override;
            int              getID() const;

        private:
            std::string evaluateRegex(const std::string input, const std::regex regex) const;
            std::string getLastToken(const std::string input, const std::string delimiter) const;     

            int m_workerID;
    };
}

#endif