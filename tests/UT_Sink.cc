#include <gtest/gtest.h>
#include "../include/sinks/Sink.h"
#include "../include/sinks/SinkHandle.h"
#include <filesystem>
#include <fstream>


class SinkTest : public ::testing::Test {
    protected:
        void SetUp() override {
            std::string workDirectory = std::filesystem::current_path();
            m_targetDirectory         = workDirectory + "/../tests/test_dir";
            std::filesystem::create_directory(m_targetDirectory);

            std::ofstream file_1(m_targetDirectory + "/dummy_1.txt");
            std::ofstream file_2(m_targetDirectory + "/dummy_2.txt");
            std::ofstream file_3(m_targetDirectory + "/dummy_3.csv");
            std::ofstream file_4(m_targetDirectory + "/dummy_4.csv");
        }

        void TearDown() override {
            std::filesystem::remove_all(m_targetDirectory);

            std::string workDirectory   = std::filesystem::current_path();
            std::string targetDirectory = workDirectory + "/../tests";
            std::filesystem::remove(targetDirectory + "/dummy_1.txt");
            std::filesystem::remove(targetDirectory + "/dummy_2.txt");
            std::filesystem::remove(targetDirectory + "/dummy_3.csv");
            std::filesystem::remove(targetDirectory + "/dummy_4.csv");
        }

        std::string m_targetDirectory;
};

TEST_F(SinkTest, Initialisation_S01) {
    SinkHandles::TXTSinkHandle txtSinkHandle(m_targetDirectory + "/../");
    SinkHandles::CSVSinkHandle csvSinkHandle(m_targetDirectory + "/../");

    Sinks::Sink txtSink(txtSinkHandle);
    Sinks::Sink csvSink(csvSinkHandle);

    SUCCEED();
}

TEST_F(SinkTest, GetSinkType_S01) {
    SinkHandles::TXTSinkHandle txtSinkHandle(m_targetDirectory + "/../");
    SinkHandles::CSVSinkHandle csvSinkHandle(m_targetDirectory + "/../");

    Sinks::Sink txtSink(txtSinkHandle);
    Sinks::Sink csvSink(csvSinkHandle);

    SinkType txtSinkType = txtSink.getSinkType();
    SinkType csvSinkType = csvSink.getSinkType();

    ASSERT_EQ(txtSinkType, SinkType::TXT);
    ASSERT_EQ(csvSinkType, SinkType::CSV);

    SUCCEED();
}

TEST_F(SinkTest, DepositFiles_S01) {
    SinkHandles::TXTSinkHandle txtSinkHandle(m_targetDirectory + "/../");
    SinkHandles::CSVSinkHandle csvSinkHandle(m_targetDirectory + "/../");

    Sinks::Sink txtSink(txtSinkHandle);
    Sinks::Sink csvSink(csvSinkHandle);

    File file_1("dummy_1", ".txt", m_targetDirectory, 27355);
    File file_2("dummy_2", ".txt", m_targetDirectory, 23357.32);

    std::vector<File> txtFiles{file_1, file_2};
    txtSink.depositFiles(txtFiles);

    if (!std::filesystem::exists(m_targetDirectory + "/../" + "dummy_1.txt") && !std::filesystem::exists(m_targetDirectory + "/../" + "dummy_2.txt")) {
        FAIL();
    }
    if (std::filesystem::exists(m_targetDirectory + "/dummy_1.txt") && std::filesystem::exists(m_targetDirectory + "/dummy_2.txt")) {
        FAIL();
    }

    File file_3("dummy_3", ".csv", m_targetDirectory, 27457);
    File file_4("dummy_4", ".csv", m_targetDirectory, 297.25);

    std::vector<File> csvFiles{file_3, file_4};
    csvSink.depositFiles(csvFiles);

    if (!std::filesystem::exists(m_targetDirectory + "/../" + "/dummy_3.csv") && !std::filesystem::exists(m_targetDirectory + "/../" + "/dummy_4.csv")) {
        FAIL();
    }
    if (std::filesystem::exists(m_targetDirectory + "/dummy_3.csv") && std::filesystem::exists(m_targetDirectory + "/dummy_4.csv")) {
        FAIL();
    }

    SUCCEED();
}