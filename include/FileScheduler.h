#pragma once
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
#include <thread>
#include "date.h"

#include "CustomTypes.h"
#include "FileScraper.h"
#include "Logger.h"
#include "./sinks/Sink.h"


namespace Scheduler {
    /////////////////////////////////////////////////////////////
    // Interface Definition of the File Scheduler
    /////////////////////////////////////////////////////////////

    class InterfaceFileScheduler {
        /* 
        Interface for the FileScheduler which should implement at least
        the run method with a specified timeout. 
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
            void registerSinks(const std::vector<Sinks::Sink> sinks);

            static FileScheduler* getInstance();
        
        protected:
            FileScheduler();
            ~FileScheduler();

        private:
            std::vector<File> startCollecting(const int& timeout);
            void deployFileScrapers();

            static FileScheduler* m_instance;

            std::deque<Dir>                         m_registeredDirs;
            std::map<int, Scraper::FileScraper>     m_fileScrapers;
            std::map<SinkType, Sinks::Sink>         m_sinks;
            std::map<int, int>                      m_numberOfTimeOuts;
            Logging::TableLogger                    m_logger;
    };
}

#endif