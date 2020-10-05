#pragma once

#include <string>

namespace T1 { namespace Processor {
    struct ProcessBase
    {
    protected:
        bool _failed;
        std::string _error;

    public:
        virtual bool Run() = 0;

        void Reset()
        {
            _failed = false;
            _error.clear();
        }

        bool HasFailed() const { return _failed; }
        bool HasSucceeded() const { return !_failed; }

    protected:
        bool Fail(const char* errorText)
        {
            _failed = true;
            _error = errorText;
        }
    };
} }

