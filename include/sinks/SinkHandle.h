#pragma once
#ifndef SINKHANDLE_H_

#include <string>
 
#include "../CustomTypes.h"

namespace SinkHandles {

    /////////////////////////////////////////////////////////////
    // Interface Definition of the SinkHandle
    /////////////////////////////////////////////////////////////

    class InterfaceSinkHandle {
        public:
            virtual ~InterfaceSinkHandle() {}
            virtual std::string getTargetLocation() const = 0;
            virtual SinkType exposeSinkType() const = 0;
    };

    /////////////////////////////////////////////////////////////
    // Class Definition of the TXTSinkHandle
    /////////////////////////////////////////////////////////////

    class TXTSinkHandle : public InterfaceSinkHandle {
        public:
            TXTSinkHandle(const std::string targetLocation);

            std::string getTargetLocation() const;
            SinkType exposeSinkType() const;

        private:
            std::string m_targetLocation;
            SinkType    m_sinkType{SinkType::TXT};
    };

    /////////////////////////////////////////////////////////////
    // Class Definition of the CSVSinkHandle
    /////////////////////////////////////////////////////////////

    class CSVSinkHandle : public InterfaceSinkHandle {
        public:
            CSVSinkHandle(const std::string targetLocation);

            std::string getTargetLocation() const;
            SinkType exposeSinkType() const;

        private:
            std::string m_targetLocation;
            SinkType    m_sinkType{SinkType::CSV};
    };
}

#endif