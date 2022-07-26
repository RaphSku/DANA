#include "../include/FileScheduler.h"


namespace Scheduler { 
    /////////////////////////////////////////////////////////////
    // File Scheduler Class Implementation (public methods)
    /////////////////////////////////////////////////////////////

    bool FileScheduler::run(int& timeout) {
        deployFileScrapers();
        std::vector<File> files = startCollecting(timeout);

        std::vector<std::thread> threads;
        for (auto& [sinkType, sink] : m_sinks) {
            threads.push_back(std::thread(&Sinks::Sink::depositFiles, sink, files));
        }

        for (auto& thread : threads) {
            thread.join();
        }

        return true;
    }

    void FileScheduler::registerDirs(const std::vector<Dir> dirs) {
        for (auto& dir : dirs) {
            if (dir.pathToDir.empty()) {
                continue;
            }
            m_registeredDirs.push_back(dir);
        }
    }

    void FileScheduler::registerSinks(const std::vector<Sinks::Sink> sinks) {
        for (auto& sink : sinks) {
            SinkTypes::Types sinkType = sink.getSinkType();
            if (m_sinks.find(sinkType) != m_sinks.end()) {
                std::string now                 = date::format("%F %T", std::chrono::system_clock::now());
                std::vector<std::string> fields = {now, std::string("Sink of type " + SinkTypes::toString(sinkType) + " could not be found!")};
                m_logger[LogTypes::ERROR].log(fields);
                continue;
            }
            m_sinks.emplace(std::make_pair(sinkType, sink));
        }
    }

    FileScheduler* FileScheduler::getInstance() {
        if (m_instance == nullptr) {
            m_instance = new FileScheduler();
        }
        return m_instance;
    }

    /////////////////////////////////////////////////////////////
    // File Scheduler Class Implementation (protected methods)
    /////////////////////////////////////////////////////////////

    FileScheduler::FileScheduler() {
        m_logger[LogTypes::FILESCRAPER] = Logging::TableLogger("./deployed_filescrapers.txt", 5, 35, {"Timestamp", "ID of Worker", "Status", "#Timed Out", "Collection Time"});
        m_logger[LogTypes::ERROR]       = Logging::TableLogger("./error_log.txt", 5, 35, {"Timestamp", "Error Message"});
    }

    FileScheduler::~FileScheduler() {
        delete m_instance;
    }

    /////////////////////////////////////////////////////////////
    // File Scheduler Class Implementation (private methods)
    /////////////////////////////////////////////////////////////

    void FileScheduler::deployFileScrapers() {
        std::vector<std::string> messages;
        for (auto& dir : m_registeredDirs) {
            int id = 0;
            if (m_fileScrapers.find(id) == m_fileScrapers.end()) {
                m_fileScrapers.emplace(id, Scraper::FileScraper(dir, id));
                m_numberOfTimeOuts.emplace(id, 0);
            }
            
            std::string now = date::format("%F %T", std::chrono::system_clock::now());
            messages        = {now, std::to_string(id), "Ready", "0", "0"};
            m_logger[LogTypes::FILESCRAPER].log(messages);
            id++;
        }
    }

    std::vector<File> FileScheduler::startCollecting(const int& timeout) {
        std::vector<std::string> messages;
        std::vector<File>        files;
        for (auto& [id, scraper] : m_fileScrapers) {
            std::string now = date::format("%F %T", std::chrono::system_clock::now());
            messages = {now, std::to_string(id), "Working", "0", "0"};
            m_logger[LogTypes::FILESCRAPER].log(messages);

            auto start    = std::chrono::high_resolution_clock::now();
            bool timedOut = scraper.collect(timeout);
            auto end      = std::chrono::high_resolution_clock::now();
            auto time     = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(); 

            if (timedOut) {
                if (m_numberOfTimeOuts.find(id) != m_numberOfTimeOuts.end()) {
                    m_numberOfTimeOuts[id]++;
                }
            }

            now      = date::format("%F %T", std::chrono::system_clock::now());
            messages = {now, std::to_string(id), "Terminated", std::to_string(m_numberOfTimeOuts[id]), std::to_string(time)};
            m_logger[LogTypes::FILESCRAPER].log(messages);

            std::deque<File> output = scraper.getFiles(); 
            for (auto& file : output) {
                files.push_back(file);
            }
        }

        return files;
    }


    /////////////////////////////////////////////////////////////
    // File Scheduler Class Implementation (private variables)
    /////////////////////////////////////////////////////////////

    FileScheduler* FileScheduler::m_instance = nullptr;
}