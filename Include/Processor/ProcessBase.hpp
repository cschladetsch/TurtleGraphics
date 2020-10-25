// Copyright © 2020 christian@schladetsch.com

#pragma once

#include <string>
#include <sstream>

namespace TurtleGraphics::Processor {

struct ProcessBase {
protected:
    mutable bool _failed = false;
    mutable std::stringstream _errorStream;

public:
    virtual ~ProcessBase() = default;

    virtual bool Run() = 0;

    virtual void Reset() {
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
    std::ostream &ErrorStream() const {
        return _errorStream;
    }

    virtual bool Fail(const char* errorText) const {
        try {
            Fail() << errorText;
        } catch (const std::exception& e) {
            (void)e;
        }
        return false;
    }

    virtual std::ostream& Fail() const {
        _failed = true;
        return _errorStream;
    }
};

}  // namespace TurtleGraphics::Processor

