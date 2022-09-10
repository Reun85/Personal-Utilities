#pragma once


#include "File.h"
#include "Date.h"


namespace Reun::Utils {
    struct ProfileResult
    {
        std::string Name;
        long long Start, End;
        size_t ThreadID;
    };

    struct InstrumentationSession
    {
        std::string Name;
    };

    class Instrumentor
    {
    private:
        mutable char* directorypath;
        InstrumentationSession* m_CurrentSession;
        std::ofstream m_OutputStream;
        int m_ProfileCount;
        long long m_lastrecordedtime;
        std::mutex mutexoutputstream;
    public:
        Instrumentor()
            : m_CurrentSession(nullptr), m_ProfileCount(0), directorypath(new char[31]), m_lastrecordedtime(0)
        {
            memcpy(directorypath, "../Timers/", 10);
            GetCurrentDateHourMin(&directorypath[10]);
            directorypath[29] = '/';
            directorypath[30] = '\0';
            UtilsCreateDirectories(directorypath);
        }
        ~Instrumentor()
        {
            delete[] directorypath;
        }

        void BeginSession(const std::string& name, const char* filepath = "results.json")
        {
            const uint64 directorypathsize = strlen(directorypath);
            const uint64 filepathsize = strlen(filepath);
            char* filename = new char[directorypathsize + filepathsize + 1];
            memcpy(filename, directorypath, directorypathsize);
            memcpy(&filename[directorypathsize], filepath, filepathsize);
            filename[directorypathsize + filepathsize] = '\0';
            
            m_OutputStream.open(filename);
            delete[] filename;
            WriteHeader();
            m_ProfileCount = 0;
            m_CurrentSession = new InstrumentationSession{ name };
        }

        void EndSession()
        {
            WriteFooter();
            m_OutputStream.close();
            delete m_CurrentSession;
            m_CurrentSession = nullptr;
            m_ProfileCount = 0;
        }

        void WriteProfile(const ProfileResult& result)
        {
            std::scoped_lock<std::mutex> guard(mutexoutputstream);
            if (m_ProfileCount++ > 0)
                m_OutputStream << ",";

            std::string name = result.Name;
            std::replace(name.begin(), name.end(), '"', '\'');

            m_OutputStream << "{";
            m_OutputStream << "\"cat\":\"function\",";
            m_OutputStream << "\"dur\":" << (result.End - result.Start) << ',';
            m_OutputStream << "\"name\":\"" << name << "\",";
            m_OutputStream << "\"ph\":\"X\",";
            m_OutputStream << "\"pid\":0,";
            m_OutputStream << "\"tid\":" << result.ThreadID << ",";
            m_OutputStream << "\"ts\":" << result.Start;
            m_OutputStream << "}";

            m_OutputStream.flush();
        }

        void WriteHeader()
        {
            m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
            m_OutputStream.flush();
        }

        void WriteFooter()
        {
            m_OutputStream << "]}";
            m_OutputStream.flush();
        }
        long long getTimeNow()
        {
#if 0
            long long ret;
            ret = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count();
            if (ret == m_lastrecordedtime)
            {
                m_lastrecordedtime++;
            }
            else
            {
                m_lastrecordedtime = ret;
            }
            return m_lastrecordedtime;

#else
            return std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count();
#endif
        }

        long long getTimeNowEnd()
        {
            return std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count();
        }
        static Instrumentor& Get()
        {
            static Instrumentor instance;
            return instance;
        }
    };

    class InstrumentationTimer//NOT PERFECT a few extra operations happen
    {
    public:
        InstrumentationTimer(const char* name)
            : m_Name(name), m_Stopped(false), m_startTimePoint(Instrumentor::Get().getTimeNow())
        {
            //m_StartTimepoint = std::chrono::high_resolution_clock::now();
            //m_startTimePoint = ;
        }

        ~InstrumentationTimer()
        {
            if (!m_Stopped)
                Stop();
        }

        void Stop()
        {
            //auto endTimepoint = std::chrono::high_resolution_clock::now();

            //long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
            //long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();
            long long end = Instrumentor::Get().getTimeNowEnd();

            size_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
            Instrumentor::Get().WriteProfile({ m_Name, m_startTimePoint, end, threadID });

            m_Stopped = true;
        }
    private:
        const char* m_Name;
        //std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
        long long m_startTimePoint;
        bool m_Stopped;
    };
}