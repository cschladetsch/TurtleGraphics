// Copyright © 2020 christian@schladetsch.com

#pragma once

#include <string>
#include <sstream>

namespace TurtleGraphics::Processor {

struct ProcessBase {
protected:
    mutable bool _failed = false;
    int _verbosity = 0;
    mutable std::stringstream _stream;

public:
    virtual ~ProcessBase() = default;

    virtual bool Run() = 0;

    virtual void Reset() {
        _failed = false;
        _stream.clear();
    }

    bool HasFailed() const noexcept { return _failed; }
    bool HasSucceeded() const noexcept { return !_failed; }

    string GetError() const noexcept {
        try {
            return _stream.str();
        }
        catch (...) {
            return "Internal error";
        }
    }

protected:
    std::ostream& GetStream() const {
        return _stream;
    }

    void NotImplemented(const char* str) const {
        Warn() << "Not Implemented: " << str;
    }

    virtual bool Fail(const char* errorText) const {
        try {
            Fail() << errorText;
        }
        catch (const std::exception& e) {
            (void)e;
        }
        return false;
    }

    std::ostream& GetStream(const char* file, int line, const char* header) const {
        return GetStream() << file << '(' << line << "): " << header << ": ";
    }

    std::ostream& Info() const {
        return GetStream() << "Info: ";
    }

    std::ostream& Warn() const {
        return GetStream() << "Warn: ";
    }

    virtual std::ostream& Fail() const {
        _failed = true;
        return GetStream() << "Fail: ";
    }

    virtual bool FailWithText(const char* errorText) const {
        Fail() << errorText;
        return false;
    }

    std::ostream& Info(const char *file, int line) const {
        return GetStream(file, line, "Info");
    }

    std::ostream& Warn(const char *file, int line) const {
        return GetStream(file, line, "Warn");
    }

    std::ostream& Fail(const char *file, int line) const {
        _failed = true;
        return GetStream(file, line, "Fail");
    }

    std::ostream& Fail(const char *file, int line, const char *text) const {
        _failed = true;
        return GetStream(file, line, "Fail") << text;
    }
};

#define TURTLE_INFO() \
    Info(__FILE__, __LINE__)

#define TURTLE_WARN() \
    Warn(__FILE__, __LINE__)

#define TURTLE_FAIL() \
    Fail(__FILE__, __LINE__)

#define TURTLE_FAIL_1(text) \
    Fail(__FILE__, __LINE__, text)

#define TURTLE_VERBOSE(verbosity) \
    Info(__FILE__, __LINE__, verbosity)

}  // namespace TurtleGraphics::Processor

