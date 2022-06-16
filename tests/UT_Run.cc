#include <gtest/gtest.h>
#include "UT_Logger.cc"
#include "UT_FileScheduler.cc"
#include "UT_FileScraper.cc"


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}