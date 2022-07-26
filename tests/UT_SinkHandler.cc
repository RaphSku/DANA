#include <gtest/gtest.h>
#include "../include/sinks/SinkHandle.h"
#include <filesystem>


class SinkHandlerTest : public ::testing::Test {
    protected:
        void SetUp() override {

        }
};

TEST_F(SinkHandlerTest, Initialisation_S01) {
    /* Test the initialisation of the SinkHandler */
    SinkHandles::TXTSinkHandle txtSinkHandle("./");
    SinkHandles::CSVSinkHandle csvSinkHandle("./test1");

    SUCCEED();
}

TEST_F(SinkHandlerTest, GetMethods_S01) {
    /* Check whether the attributes are set correctly in
    the SinkHandler, this is crucial since the Sinks will
    rely on this information to be correct */
    SinkHandles::TXTSinkHandle txtSinkHandle("./");
    SinkHandles::CSVSinkHandle csvSinkHandle("./test1");

    std::string txtTargetLocation = txtSinkHandle.getTargetLocation();
    std::string csvTargetLocation = csvSinkHandle.getTargetLocation();

    ASSERT_EQ(txtTargetLocation, "./");
    ASSERT_EQ(csvTargetLocation, "./test1");

    SinkTypes::Types txtSinkType = txtSinkHandle.exposeSinkType();
    SinkTypes::Types csvSinkType = csvSinkHandle.exposeSinkType();

    ASSERT_EQ(txtSinkType, SinkTypes::Types::TXT);
    ASSERT_EQ(csvSinkType, SinkTypes::Types::CSV);

    SUCCEED();
}