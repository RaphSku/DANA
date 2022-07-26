#include <gtest/gtest.h>
#include "../include/sinks/SinkHandle.h"
#include <filesystem>


class SinkHandlerTest : public ::testing::Test {
    protected:
        void SetUp() override {

        }
};

TEST_F(SinkHandlerTest, Initialisation_S01) {
    SinkHandles::TXTSinkHandle txtSinkHandle("./");
    SinkHandles::CSVSinkHandle csvSinkHandle("./test1");

    SUCCEED();
}

TEST_F(SinkHandlerTest, GetMethods_S01) {
    SinkHandles::TXTSinkHandle txtSinkHandle("./");
    SinkHandles::CSVSinkHandle csvSinkHandle("./test1");

    std::string txtTargetLocation = txtSinkHandle.getTargetLocation();
    std::string csvTargetLocation = csvSinkHandle.getTargetLocation();

    ASSERT_EQ(txtTargetLocation, "./");
    ASSERT_EQ(csvTargetLocation, "./test1");

    SinkType txtSinkType = txtSinkHandle.exposeSinkType();
    SinkType csvSinkType = csvSinkHandle.exposeSinkType();

    ASSERT_EQ(txtSinkType, SinkType::TXT);
    ASSERT_EQ(csvSinkType, SinkType::CSV);

    SUCCEED();
}