#pragma once

#include "Singleton.h"

class NaiveSingleton : public Singleton<NaiveSingleton>
{
public:
    NaiveSingleton(const std::string value)
        : Singleton<NaiveSingleton>(value)
    {
    }
};

#define NAIVE_SINGLETON NaiveSingleton::GetSingleton()