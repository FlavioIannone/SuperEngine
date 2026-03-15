#pragma once

namespace SuperEngine
{
    template <typename T>
    class IDManager
    {
    private:
        inline static std::atomic<uint64_t> m_nextID = 0;

    public:
        static uint64_t GetNext() { return m_nextID++; }
    };
}