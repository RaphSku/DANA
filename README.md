# ARCHIVED

# DANA
Datafile TrANsport Amplifier (DANA)

## Goal
File Aggregration Tool which allows you to control the flow of data/file transportation, e.g. segregation of data files by the file types (json, txt, csv, xml).

## How to Use
1. Define which directories should be "scraped", the FileScheduler will deploy FileScrapers which will scan these directories.
```cpp
Dir fileDir1("./dir1/");
Dir fileDir2("./dir2/");
```
2. Define which Sinks should exist, these sinks represent entities which are responsible for the segregation of the files. Sinks are classified by their Sink Handler. In this version of the code, there are only two sink handlers available, for csv and txt files.
```cpp
SinkHandles::TXTSinkHandle txtSinkHandle("./dir_txt/");
Sinks::Sink txtSink(txtSinkHandle);

SinkHandles::CSVSinkHandle csvSinkHandle("./csv_txt/");
Sinks::Sink csvSink(csvSinkHandle);
```
3. That's basically everything to set the FileScheduler up, we only have to register the directories and the sinks. The FileScheduler is a Singleton, so we only have to call getInstance instead of the constructor. It is the single source of truth which decides which FileScraper gets deployed and which sink gets activated.
```cpp
auto fs = Scheduler::FileScheduler::getInstance();
fs->registerDirs({fileDir1, fileDir2});
fs->registerSinks({txtSink, csvSink});
```
4. Next, we have to define the timeout, the timeout is defined in seconds and is relevant for the FileScrapers, when the FileScrapers need longer than this timeout, it will be recorded in the generated log file, named "deployed_filescrapers". The method `run` will kickstart the FileScheduler and will start with the scraping and segregation of the files.
```cpp
int timeout  = 10;
bool success = fs->run(timeout); 
```
