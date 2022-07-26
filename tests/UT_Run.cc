#include <gtest/gtest.h>
#include "UT_Logger.cc"
#include "UT_FileScheduler.cc"
#include "UT_FileScraper.cc"
#include "UT_Sink.cc"
#include "UT_SinkHandler.cc"
#include "IT_Pipeline.cc"


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}