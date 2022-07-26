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
            SinkTypes::Types getSinkType() const;

        private:
            SinkHandles::InterfaceSinkHandle& m_sinkHandle;
            SinkTypes::Types                  m_sinkType;

            std::map<std::string, SinkTypes::Types> filesuffixToSinkType{{".txt", SinkTypes::Types::TXT},
                                                                         {".csv", SinkTypes::Types::CSV}};
    };
}

#endif