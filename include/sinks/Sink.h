#pragma once
#ifndef SINK_H_

#include <vector>
#include <string>
#include <filesystem>

#include "../CustomTypes.h"
#include "./SinkHandle.h"

namespace Sinks {

    /////////////////////////////////////////////////////////////
    // Interface Definition of the Sink
    /////////////////////////////////////////////////////////////

    class InterfaceSink {
        public:
            virtual ~InterfaceSink() {}
            virtual void depositFiles(const std::vector<File>& files) = 0;
    };

    /////////////////////////////////////////////////////////////
    // Class Definition of the Sink
    /////////////////////////////////////////////////////////////

    class Sink : public InterfaceSink {
        public:
            Sink(SinkHandles::InterfaceSinkHandle& sinkHandle);
            
            void depositFiles(const std::vector<File>& files);
            SinkType getSinkType() const;

        private:
            SinkHandles::InterfaceSinkHandle& m_sinkHandle;
            SinkType                          m_sinkType;

            std::map<std::string, SinkType> filesuffixToSinkType{{".txt", SinkType::TXT},
                                                                 {".csv", SinkType::CSV}};
    };
}

#endif