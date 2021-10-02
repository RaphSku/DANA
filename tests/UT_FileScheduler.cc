#include <gtest/gtest.h>
#include "../include/FileScheduler.h"
#include "../include/FileScraper.h"
#include "../include/CustomTypes.h"


TEST(FileScheduler, BasicAssertions) {
  auto fs = Scheduler::FileScheduler::getInstance();

  std::string test_path = "./ut_file\\.txt";
  Dir test_dir(test_path);

  std::vector<Dir> directories;
  directories.push_back(test_dir);

  fs->registerDirs(directories);

  int timeout = 1;
  fs->run(timeout);

  SUCCEED();
}