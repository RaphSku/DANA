#include "../include/FileScheduler.h"


namespace Scheduler { 
    /////////////////////////////////////////////////////////////
    // File Scheduler Class Implementation (public methods)
    /////////////////////////////////////////////////////////////

    bool FileScheduler::run(int& timeout) {
        // for every dir in m_registeredDirs, a FileScraper should be deployed
        for (auto& dir : m_registeredDirs) {
            bool successfulInitialized = false;
            int id = 0;
            while (successfulInitialized) {
                if (m_fileScrapers.find(id) == m_fileScrapers.end()) {
                    Scraper::FileScraper fileScraper(dir, id);
                    m_fileScrapers.emplace(id, fileScraper);
                    m_numberOfTimeOuts.emplace(id, 0);
                    successfulInitialized = true;
                }
                id++;
            }
            
            std::string now = date::format("%F %T", std::chrono::system_clock::now());
            std::ofstream register_filescraper;
            register_filescraper.open ("../data/deployed_filescrapers.txt", std::ios::app);
            register_filescraper << now << " | " << "     " << id << "      " << " | " << "Registered" << "  | " 
                                 << "     " <<  0 << "    " 
                                 << " | " << "       " << 0 << "        ";
            register_filescraper.close();
        }

        for (auto& [id, scraper] : m_fileScrapers) {
            std::string now = date::format("%F %T", std::chrono::system_clock::now());
            std::ofstream register_filescraper;
            register_filescraper.open ("../data/deployed_filescrapers.txt", std::ios::app);
            register_filescraper << now << " | " << "     " << id << "      " << " | " << " Running  " << "  | " 
                                 << "     " <<  0 << "    " 
                                 << " | " << "       " << 0 << "        ";
            register_filescraper.close();

            auto start    = std::chrono::high_resolution_clock::now();
            bool timedOut = scraper.collect(timeout);
            auto end      = std::chrono::high_resolution_clock::now();
            auto time     = std::chrono::duration_cast<std::chrono::seconds>(end - start).count(); 

            if (timedOut) {
                if (m_numberOfTimeOuts.find(id) != m_numberOfTimeOuts.end()) {
                    m_numberOfTimeOuts[id]++;
                }
            }

            now = date::format("%F %T", std::chrono::system_clock::now());
            register_filescraper.open ("../data/deployed_filescrapers.txt", std::ios::app); 
            register_filescraper << now << " | " << "     " << id << "      " << " | " << " Finished " << "  | " 
                                 << "     " <<  m_numberOfTimeOuts[id] << "    " 
                                 << " | " << "       " << time << "        ";
            register_filescraper.close();

            std::deque<File> output = scraper.getFiles(); 
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

    std::unique_ptr<FileScheduler> FileScheduler::getInstance() {
        if (m_instance == nullptr) {
            m_instance = std::unique_ptr<FileScheduler>(new FileScheduler);
        }
        return std::move(m_instance);
    }

    /////////////////////////////////////////////////////////////
    // File Scheduler Class Implementation (protected methods)
    /////////////////////////////////////////////////////////////

    FileScheduler::FileScheduler() {
        std::string label_timestamp             = "        Timestamp          ";
        std::string label_idOfWorker            = "ID of Worker";
        std::string label_status                = "   Status  ";
        std::string label_timedOut              = "#Timed Out";
        std::string label_collectionTime = "Collection Time";

        std::ofstream register_filescraper;
        register_filescraper.open ("../data/deployed_filescrapers.txt");
        register_filescraper << label_timestamp << " | " << label_idOfWorker << " | " << label_status << " | " << label_timedOut
                             << " | " << label_collectionTime << "\n";
        register_filescraper << "---------------------------------------------------------------------------------------" << "\n";
        register_filescraper.close();
    }

    /////////////////////////////////////////////////////////////
    // File Scheduler Class Implementation (private methods)
    /////////////////////////////////////////////////////////////


    /////////////////////////////////////////////////////////////
    // File Scheduler Class Implementation (private variables)
    /////////////////////////////////////////////////////////////

    std::unique_ptr<FileScheduler> FileScheduler::m_instance = nullptr;
}