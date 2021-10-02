# Documentation

## Design Doc

The following classes should be implemented and how they interact with each other:
- FileScheduler
- Logger
- FileScraper
- FileHandler
- Processors

Relationships between classes: 
The FileScheduler is the central entry point to the application. The FileScheduler triggers the FileScrapper which returns the files in given directories. Afterwards, the FileScheduler delegates these files to the FileHandlers which extract the information out of these files and then propagate those to the Processor Units (PU). The FileScheduler reports the status of the FileHandler and the FileScraper, these information are given to the logger.

The FileScheduler is scraping different kind of files, e.g. csv, xml, ..., from given directory paths. Afterwards, the FileScheduler will register the files and split them accordingly depending on the type of the file. The files are ordered through deques and will be piped to the respective handler. The FileHandler is taking the files and will preprocess them and distribute them to the different kind of Processor Units. There are different kind of Processor Units, one Processor Unit (PU) does a statistical analysis of the given file, another one simply describes the attributes of the content of the file and so on. The PU write all the gained information into text files and will deposit them at the given location. All PUs can communicate with all FileHandler but the PUs are registered at the FileHandler, such that the FileHandler know which PUs are able to process the given file.

### FileScheduler Definition & Implementation

The FileScheduler should implement the following two methods:
- void setPaths(const Paths& path)
- bool run(int& timeout)
setPath is used in order to tell the FileScheduler where to look out for the files.
run will let the FileScheduler start scraping, registering files and pipe them into the respective deques. Also a timeout has to be specified, such that after the given timeout, the FileScheduler stops and returns a bool flag, whether the scraping run as intended or if a problem has occured.