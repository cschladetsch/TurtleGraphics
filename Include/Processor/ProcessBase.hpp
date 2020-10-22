// Copyright © 2020 christian@schladetsch.com

#pragma once

#include <string>
#include <sstream>

namespace TurtleGraphics::Processor {

struct ProcessBase {
 protected:
    mutable bool _failed = false;
    mutable std::ostringstream _errorStream;

public:
    virtual ~ProcessBase() = default;

    virtual bool Run() = 0;

    virtual void Reset() noexcept {
        _failed = false;
        _errorStream.clear();
    }

    bool HasFailed() const noexcept { return _failed; }
    bool HasSucceeded() const noexcept { return !_failed; }
    string GetError() const noexcept {
        try {
            return _errorStream.str();
        } catch (...) {
            return "Internal error";
        }
    }

protected:
    virtual bool Fail(const char* errorText) const noexcept {
        try {
            Fail() << errorText;
        } catch (std::exception& e) {
            (void)e;
        }
        return false;
    }

    std::ostringstream& Fail() const noexcept {
        _failed = true;
        return _errorStream;
    }
};

}  // namespace TurtleGraphics::Processor

