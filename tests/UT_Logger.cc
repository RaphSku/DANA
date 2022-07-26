#include <gtest/gtest.h>
#include "../include/Logger.h"
#include <filesystem>


class TableLoggerTest : public ::testing::Test {
    protected:
        TableLoggerTest() {
            std::string workDirectory = std::filesystem::current_path();
            m_currentPath             = workDirectory + "/../tests/ut_file.txt";
            m_tableLogger             = Logging::TableLogger(m_currentPath, 5, 35, {"Timestamp", "ID of Worker", "Status", "#Timed Out", "Collection Time"});
        }

        ~TableLoggerTest() {
            std::filesystem::remove(m_currentPath);
        }

        std::string          m_currentPath;
        Logging::TableLogger m_tableLogger;
};

TEST_F(TableLoggerTest, Initialisation_S01) {
    /* Test if the logger is initialised correctly with its
    designated header format */
    if (!std::filesystem::exists(m_currentPath)) {
        FAIL();
    }

    std::ifstream logFile(m_currentPath);
    int index = 0;
    for (std::string line; getline(logFile, line);) {
        switch (index) {
            case 0:
                ASSERT_EQ(line, "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
                break;
            case 1:
                ASSERT_EQ(line, "             Timestamp             |            ID of Worker           |               Status              |             #Timed Out            |          Collection Time         ");
                break;
            case 2:
                ASSERT_EQ(line, "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
                break;
        };
        index++;
    }

    std::filesystem::remove(m_currentPath);

    SUCCEED();
}

TEST_F(TableLoggerTest, Logging_S01) {
    /* Test if the logger logs the message correctly */
    m_tableLogger.log({"2022-08-12 0:247925", "0", "Ready", "100", "1257"});

    std::ifstream logFile(m_currentPath);
    int index = 0;
    for (std::string line; getline(logFile, line);) {
        if (index == 3) {
            ASSERT_EQ(line, "        2022-08-12 0:247925        |                 0                 |               Ready               |                100                |               1257              ");
        }
        index++;
    }

    SUCCEED();
}