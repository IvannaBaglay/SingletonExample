#pragma once

#include "ThreadSafeSingleton.h"

class ThreadSafeChildSingleton : public ThreadSafeSingleton<ThreadSafeChildSingleton>
{
public:
    ThreadSafeChildSingleton(const std::string value)
        : ThreadSafeSingleton<ThreadSafeChildSingleton>(value)
    {
    }
};

#define THREADSAFE_SINGLETON ThreadSafeChildSingleton::GetSingleton()