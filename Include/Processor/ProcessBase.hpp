// Copyright © 2020 christian@schladetsch.com

#pragma once

#include <string>
#include <sstream>
#include <ostream>

namespace Turtle1::Processor {

struct ProcessBase {
 protected:
    mutable bool _failed = false;
    mutable std::ostringstream _errorStream;

public:
    virtual ~ProcessBase() = default;

    virtual bool Run() noexcept = 0;

    virtual void Reset() noexcept {
        _failed = false;
        _errorStream.clear();
    }

    bool HasFailed() const { return _failed; }
    bool HasSucceeded() const { return !_failed; }
    string GetError() const { return _errorStream.str(); }

protected:
    bool Fail(const char* errorText) const noexcept {
        Fail() << errorText;
        return false;
    }

    std::ostringstream& Fail() const noexcept {
        _failed = true;
        return _errorStream;
    }

};

}  // namespace Turtle1

