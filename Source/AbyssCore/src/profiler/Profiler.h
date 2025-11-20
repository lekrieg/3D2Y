//
// Created by lekrieg on 11/11/2025.
//

#ifndef PROFILER_H
#define PROFILER_H

#include <chrono>
#include <fstream>
#include <mutex>
#include <map>
#include <string>
#include <algorithm>
#include <thread>

#define PROFILING 1
#ifdef PROFILING
    #define PROFILE_SCOPE(name) \
        ProfilerTimer timer##__COUNTER__(name)
    #define PROFILE_FUNCTION() \
        PROFILE_SCOPE(__FUNCTION__)
#else
    #define PROFILE_SCOPE(name)
#endif

struct ProfileResult
{
    std::string name = "Default";
    long long start = 0;
    long long end = 0;
    size_t threadId = 0;
};

class Profiler
{
    std::string m_outputFile = "results.json";
    size_t m_profileCount = 0;
    std::ofstream m_outputStream;
    std::mutex m_lock;

    Profiler()
    {
        m_outputStream = std::ofstream(m_outputFile);
        WriteHeader();
    }

    void WriteHeader()
    {
        m_outputStream << R"({"otherData": {},"traceEvents":[)";
    }
    void WriteFooter()
    {
        m_outputStream << R"(]})";
    }

public:

    static Profiler& Instance()
    {
        static Profiler instance;
        return instance;
    }

    ~Profiler()
    {
        WriteFooter();
    }

    void WriteProfile(const ProfileResult& result)
    {
        std::lock_guard<std::mutex> lock(m_lock);

        if (m_profileCount++ > 0)
        {
            m_outputStream << ",";
        }

        std::string name = result.name;
        std::replace(name.begin(), name.end(), '"', '\'');

        m_outputStream << "{";
        m_outputStream << R"("cat":"function",)";
        m_outputStream << R"("dur":)" << (result.end - result.start) << ',';
        m_outputStream << R"("name":")" << name << "\",";
        m_outputStream << R"("ph":"X",)";
        m_outputStream << R"("pid":0,)";
        m_outputStream << R"("tid":)" << result.threadId << ",";
        m_outputStream << R"("ts":)" << result.start;
        m_outputStream << "}";
    }
};

class ProfilerTimer
{
    typedef std::chrono::time_point<std::chrono::high_resolution_clock> ClockType;
    ClockType m_startTimepoint;
    ProfileResult m_result;
    bool m_stopped = false;

public:

    explicit ProfilerTimer(const std::string& name) : m_result({name, 0, 0, 0})
    {
        Start();
    }

    ~ProfilerTimer()
    {
        Stop();
    }

    void Start()
    {
        static long long lastStartTime = 0;

        m_startTimepoint = std::chrono::high_resolution_clock::now();
        m_result.start = std::chrono::time_point_cast<std::chrono::microseconds>(m_startTimepoint).time_since_epoch().count();

        m_result.start += (m_result.start - lastStartTime ? 1 : 0);

        lastStartTime = m_result.start;

        m_stopped = false;
    }

    void Stop()
    {
        if (m_stopped)
        {
            return;
        }

        auto endTimepoint = std::chrono::high_resolution_clock::now();

        m_result.end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();
        m_result.threadId = std::hash<std::thread::id>{}(std::this_thread::get_id());
        Profiler::Instance().WriteProfile(m_result);

        m_stopped = true;
    }
};

#endif //PROFILER_H