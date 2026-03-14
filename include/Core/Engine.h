#include <iostream>

namespace SuperEngine
{
    class Engine
    {
    private:
        bool isRunning = true;

    public:
        void Run();
        inline void Stop() { isRunning = false; }
        Engine()
        {
            std::cout << "Engine started.\n";
        }

        ~Engine()
        {
            std::cout << "Engine terminated.\n";
        }
    };
}