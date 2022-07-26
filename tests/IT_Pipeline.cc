#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>

#include "../include/CustomTypes.h"
#include "../include/FileScheduler.h"
#include "../include/FileScraper.h"
#include "../include/sinks/Sink.h"
#include "../include/sinks/SinkHandle.h"


class PipelineTest : public ::testing::Test {
    protected:
        void SetUp() override {
            std::string workDirectory   = std::filesystem::current_path();
            m_fileDirectory = workDirectory + "/../tests/test_dir/";
            std::filesystem::create_directory(m_fileDirectory);

            std::ofstream file_1(m_fileDirectory + "/dummy_1.txt");
            std::ofstream file_2(m_fileDirectory + "/dummy_2.txt");
            std::ofstream file_3(m_fileDirectory + "/dummy_3.csv");
            std::ofstream file_4(m_fileDirectory + "/dummy_4.csv");

            m_targetTxtDirectory = workDirectory + "/../tests/target_dir_txt/";
            std::filesystem::create_directory(m_targetTxtDirectory);

            m_targetCsvDirectory = workDirectory + "/../tests/target_dir_csv/";
            std::filesystem::create_directory(m_targetCsvDirectory);
        }

        void TearDown() override {
            std::filesystem::remove_all(m_fileDirectory);
            std::filesystem::remove_all(m_targetTxtDirectory);
            std::filesystem::remove_all(m_targetCsvDirectory);
        }

        std::string m_targetTxtDirectory;
        std::string m_targetCsvDirectory;
        std::string m_fileDirectory;
};

TEST_F(PipelineTest, Pipeline_S01) {
    /* Test the whole pipeline, from getting the FileScheduler instance,
    registering the directories, registering the sinks, and running
    the deployment, collection and depositing of the scraped files */
    Dir fileDir(m_fileDirectory);
    
    SinkHandles::TXTSinkHandle txtSinkHandle(m_targetTxtDirectory);
    Sinks::Sink txtSink(txtSinkHandle);

    SinkHandles::CSVSinkHandle csvSinkHandle(m_targetCsvDirectory);
    Sinks::Sink csvSink(csvSinkHandle);

    auto fs = Scheduler::FileScheduler::getInstance();
    fs->registerDirs({fileDir});
    fs->registerSinks({txtSink, csvSink});
    int timeout  = 10;
    bool success = fs->run(timeout);
    ASSERT_EQ(success, true);

    ASSERT_EQ(std::filesystem::exists(m_targetTxtDirectory + "/dummy_1.txt"), true);
    ASSERT_EQ(std::filesystem::exists(m_targetTxtDirectory + "/dummy_2.txt"), true);
    ASSERT_EQ(std::filesystem::exists(m_targetCsvDirectory + "/dummy_3.csv"), true);
    ASSERT_EQ(std::filesystem::exists(m_targetCsvDirectory + "/dummy_4.csv"), true);

    SUCCEED();
}