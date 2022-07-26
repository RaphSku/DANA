#include "../include/sinks/SinkHandle.h"

namespace SinkHandles {

    /////////////////////////////////////////////////////////////
    // TXTSinkHandle Class Implementation (public methods)
    /////////////////////////////////////////////////////////////

    TXTSinkHandle::TXTSinkHandle(const std::string targetLocation) : m_targetLocation(targetLocation) {

    }

    std::string TXTSinkHandle::getTargetLocation() const {
        return m_targetLocation;
    }

    SinkType TXTSinkHandle::exposeSinkType() const {
        return m_sinkType;
    }

    /////////////////////////////////////////////////////////////
    // CSVSinkHandle Class Implementation (public methods)
    /////////////////////////////////////////////////////////////

    CSVSinkHandle::CSVSinkHandle(const std::string targetLocation) : m_targetLocation(targetLocation) {

    }

    std::string CSVSinkHandle::getTargetLocation() const {
        return m_targetLocation;
    }

    SinkType CSVSinkHandle::exposeSinkType() const {
        return m_sinkType;
    }
}