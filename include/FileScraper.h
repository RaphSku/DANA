#ifndef FILESCRAPER_H_
#define FILESCRAPER_H_

#include <iostream>
#include <deque>
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
            int m_workerID;
    };
}

#endif