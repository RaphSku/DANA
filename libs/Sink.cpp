#include "../include/sinks/Sink.h"

namespace Sinks {

    /////////////////////////////////////////////////////////////
    // Sink Class Implementation (public methods)
    /////////////////////////////////////////////////////////////

    Sink::Sink(SinkHandles::InterfaceSinkHandle& sinkHandle) : m_sinkHandle(sinkHandle), m_sinkType(sinkHandle.exposeSinkType()) {

    }
            
    void Sink::depositFiles(const std::vector<File>& files) {
        // filter files out, input is array of files with all endings, .txt, .csv
        std::vector<File> target_files;
        for (auto& file : files) {
            if (filesuffixToSinkType.at(file.suffix) == m_sinkType) {
                target_files.push_back(file);
            }
        }

        for (auto& file : target_files) {
            std::string filePrefix = file.name;
            std::string fileSuffix = file.suffix;
            std::string fileName   = filePrefix + fileSuffix;
            std::string pathToFile = file.location + "/" + fileName;
            std::filesystem::rename(pathToFile, m_sinkHandle.getTargetLocation() + fileName);
        }
    }

    SinkType Sink::getSinkType() const {
        return m_sinkType;
    }
}