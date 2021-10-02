#ifndef FILESCHEDULER_H_
#define FILESCHEDULER_H_

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include <memory>
#include <fstream>
#include <chrono>
#include "CustomTypes.h"
#include "FileScraper.h"
#include "date.h"


namespace Scheduler {
    /////////////////////////////////////////////////////////////
    // Interface Definition of the File Scheduler
    /////////////////////////////////////////////////////////////

    class InterfaceFileScheduler {
        /* 
        This Interface introduces the following methods and the following tasks:
            1) setPaths which sets the Paths for scraping
        */

        public:
            virtual ~InterfaceFileScheduler() {};
            virtual bool run(int& timeout) = 0;
    };

    /////////////////////////////////////////////////////////////
    // Interface Definition of the File Scheduler
    /////////////////////////////////////////////////////////////

    class FileScheduler : public InterfaceFileScheduler {
        /*
        Registers files from given paths and then runs either for a given timeout
        or forever and will scrape new files from the dictionaries
        and will update the pipelines which will distribute the files to the given
        handlers
        */

        public:
            bool run(int& timeout) override;
            void registerDirs(const std::vector<Dir> dirs);

            static std::unique_ptr<FileScheduler> getInstance();
        
        protected:
            FileScheduler();

        private:
            static std::unique_ptr<FileScheduler> m_instance;

            std::deque<Dir>                     m_registeredDirs;
            std::map<int, Scraper::FileScraper> m_fileScrapers;
            std::map<int, int>                  m_numberOfTimeOuts;
    };
}

#endif