#include <gtest/gtest.h>
#include "../include/FileScraper.h"
#include <filesystem>
#include <fstream>


class FileScraperTest : public ::testing::Test {
    protected:
        FileScraperTest() {
            std::string workDirectory = std::filesystem::current_path();
            m_current_dir_path        = workDirectory + "/../tests/test_dir";
            std::filesystem::create_directory(m_current_dir_path);
            
            std::ofstream m_new_file_1(m_current_dir_path + "/log.txt");
            std::ofstream m_new_file_2(m_current_dir_path + "/properties.json");
            std::ofstream m_new_file_3(m_current_dir_path + "/finance.csv");

            m_directory = Dir(m_current_dir_path);
            m_id        = 0;
        }
        ~FileScraperTest() {
            std::filesystem::remove_all(m_current_dir_path);
        }

        std::string m_current_dir_path;
        int         m_id;
        Dir         m_directory;

        std::ofstream m_new_file_1;
        std::ofstream m_new_file_2;
        std::ofstream m_new_file_3;
};

TEST_F(FileScraperTest, Initialisation_S01) {
    /* Test the initialisation of the FileScraper */
    auto filescraper = Scraper::FileScraper(m_directory, m_id);

    SUCCEED();
}

TEST_F(FileScraperTest, RetrievingID_S01) {
    /* Test if the id matches the set id */
    auto filescraper = Scraper::FileScraper(m_directory, m_id);
    int  id          = filescraper.getID();

    ASSERT_EQ(m_id, id);
    SUCCEED();
}

TEST_F(FileScraperTest, Collection_S01) {
    /* Test whether the collection scrapes the correct files with their
    appropriate attributes like file suffix */
    auto filescraper = Scraper::FileScraper(m_directory, m_id);

    int timeout            = 1000;
    bool timedOut          = filescraper.collect(timeout);
    std::deque<File> files = filescraper.getFiles();
    
    ASSERT_EQ(files.size(), 3);
    ASSERT_EQ(files.at(0).name, "log");
    ASSERT_EQ(files.at(0).suffix, ".txt");
    ASSERT_EQ(files.at(1).name, "properties");
    ASSERT_EQ(files.at(1).suffix, ".json");
    ASSERT_EQ(files.at(2).name, "finance");
    ASSERT_EQ(files.at(2).suffix, ".csv");
    SUCCEED();
}