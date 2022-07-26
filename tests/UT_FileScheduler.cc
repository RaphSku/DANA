#include <gtest/gtest.h>
#include "../include/FileScheduler.h"
#include "../include/FileScraper.h"
#include "../include/CustomTypes.h"


class FileSchedulerTest : public ::testing::Test {
  protected:
    FileSchedulerTest() {
      std::string workDirectory = std::filesystem::current_path();
      m_targetDirectory         = workDirectory + "/../tests/test_dir";
      std::filesystem::create_directory(m_targetDirectory);
      
      std::string   pathToNewFile = m_targetDirectory + "/new_file.txt";
      std::ofstream newFile;
      newFile.open(pathToNewFile, std::ios::app);
      newFile << "Counter 14.24" << "\n";
      newFile << "Counter 42.24" << "\n";
      newFile.close();

      m_fileScheduler = Scheduler::FileScheduler::getInstance();
    }

    ~FileSchedulerTest() {
      std::filesystem::remove_all(m_targetDirectory);
      std::filesystem::remove("./deployed_filescrapers.txt");
    }

    std::string               m_targetDirectory;
    Scheduler::FileScheduler* m_fileScheduler;
};

TEST_F(FileSchedulerTest, Initialisation_S01) {
  auto fileScheduler = Scheduler::FileScheduler::getInstance();

  ASSERT_EQ(m_fileScheduler, fileScheduler);
  SUCCEED();
}

TEST_F(FileSchedulerTest, RegisterDirs_S01) {
  Dir directory_1("./test1.txt");
  Dir directory_2("./test2.txt");
  Dir directory_3("./test3.txt");

  std::vector<Dir> directories{directory_1, directory_2, directory_3};
  m_fileScheduler->registerDirs(directories);

  SUCCEED();
}

TEST_F(FileSchedulerTest, Run_S01) {
  Dir directory(m_targetDirectory);
  std::vector<Dir> directories{directory};

  m_fileScheduler->registerDirs(directories);

  int timeout = 1000;
  m_fileScheduler->run(timeout);

  std::ifstream file("./deployed_filescrapers.txt");
  int index = 0;
  for (std::string line; getline(file, line);) {
    switch (index) {
      case 3:
        ASSERT_GT(line.size(), 0);
        break;
      case 4:
        ASSERT_GT(line.size(), 0);
        break;
      case 5:
        ASSERT_GT(line.size(), 0);
        break;
    };
    index++;
  }

  if (index != 6)
    FAIL();

  SUCCEED();
}

TEST_F(FileSchedulerTest, RegisterSinks_S01) {
  SinkHandles::TXTSinkHandle txtSinkHandler("./");
  SinkHandles::CSVSinkHandle csvSinkHandler("./");
  
  Sinks::Sink txtSink(txtSinkHandler);
  Sinks::Sink csvSink(csvSinkHandler);

  std::vector<Sinks::Sink> sinks{txtSink, csvSink};
  m_fileScheduler->registerSinks(sinks);

  SUCCEED();
}