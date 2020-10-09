// Copyright 2020 christian@schladetsch.com

#pragma once

#include <string>

namespace Turtle1 { namespace Processor {
struct ProcessBase {
 protected:
    mutable bool _failed = false;
    mutable std::string _error;

public:
    virtual bool Run() = 0;

    void Reset() {
        _failed = false;
        _error.clear();
    }

    bool HasFailed() const { return _failed; }
    bool HasSucceeded() const { return !_failed; }

protected:
    bool Fail(const char* errorText) const noexcept {
        _failed = true;
        _error = errorText;
        return false;
    }
};
}  // namespace Processor
}  // namespace Turtle1

