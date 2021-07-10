//
// Created by draven on 6/6/2021.
//

#pragma once

#include <Windows.h>
#include <string>
#include <format>

#include "xorstr.h"

#define DEBUG_ERROR(msg) debug::detail::debug_error(std::string(_(msg)) + " (" + _(__FILE__) + ":" + std::to_string(__LINE__) + ")")

namespace debug::detail
{
    inline void debug_error(const std::string &message)
    {
        MessageBox(nullptr, message.c_str(), _("Debug Error"), MB_OK | MB_ICONERROR);
    }

    inline void debug_info(const std::string &message)
    {
        MessageBox(nullptr, message.c_str(), _("Debug Info"), MB_OK);
    }
}

namespace dbg
{
    enum class LogLevel
    {
        Trace = 0,
        Debug = 1,
        Info = 2,
        Warn = 3,
        Error = 4,
        None = 5,
    };
    inline LogLevel logLevel = LogLevel::Trace;

    inline void logText(const std::string &text)
    {
        OutputDebugString((_("[modernwarfare-internal] ") + text).c_str());
    }

    template <class... Args>
    inline void error(const std::string_view format_str, const Args &... args)
    {
        if (logLevel > LogLevel::Error) {
            return;
        }
        std::string text = std::format(format_str, args...);
        logText("[error] " + text);
    }

    template <class... Args>
    inline void warn(const std::string_view format_str, const Args &... args)
    {
        if (logLevel > LogLevel::Warn) {
            return;
        }
        std::string text = std::format(format_str, args...);
        logText("[warn] " + text);
    }


    template <class... Args>
    inline void info(const std::string_view format_str, const Args &... args)
    {
        if (logLevel > LogLevel::Info) {
            return;
        }
        std::string text = std::format(format_str, args...);
        logText("[info] " + text);
    }

    template <class... Args>
    inline void debug(const std::string_view format_str, const Args &... args)
    {
        if (logLevel > LogLevel::Debug) {
            return;
        }
        std::string text = std::format(format_str, args...);
        logText("[debug] " + text);
    }

    template <class... Args>
    inline void trace(const std::string_view format_str, const Args &... args)
    {
        if (logLevel > LogLevel::Trace) {
            return;
        }
        std::string text = std::format(format_str, args...);
        logText("[trace] " + text);
    }
}