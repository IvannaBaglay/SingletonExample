#pragma once

#include <assert.h>
#include <stdexcept>
#include <string>

template <typename T> class Singleton
{
public:
    Singleton(const T&) = delete;
    Singleton(const T&&) = delete;
    T& operator=(const T&) = delete;

    static T& GetSingleton()
    {
        if (ms_Singleton == nullptr) {
            ms_Singleton = new T("void");
        }
        return *ms_Singleton;
    }

    static T* GetSingletonPtr()
    {
        if (ms_Singleton == nullptr) {
            ms_Singleton = new T("void");
        }
        return ms_Singleton;
    }

    static T& GetSingleton(const std::string value)
    {
        if (ms_Singleton == nullptr) {
            ms_Singleton = new T(value);
        }
        return *ms_Singleton;
    }
    static T* GetSingletonPtr(const std::string value)
    {
        if (ms_Singleton == nullptr) {
            ms_Singleton = new T(value);
        }
        return ms_Singleton;
    }

    const std::string GetString()
    {
        return m_Value;
    }

protected:
    Singleton(const std::string value)
        : m_Value(value)
    {
        if (ms_Singleton) {
            //throw std::runtime_error("Singleton instance already exists!"); // ??
            return;
        }
        int offset = (int)(T*)1 - (int)(Singleton<T>*)(T*)1; // to avoid multiple inheritance issues
        ms_Singleton = (T*)(this + offset);
    }

    ~Singleton()
    {
        assert(ms_Singleton);
        ms_Singleton = nullptr;
    }

private:
    static T* ms_Singleton;
    std::string m_Value;
};

template <typename T> T* Singleton<T>::ms_Singleton = nullptr;

