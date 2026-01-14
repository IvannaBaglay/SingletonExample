#pragma once
#pragma once
#include <assert.h>
#include <string>
#include <stdexcept>
#include <mutex>

// thread-safe singleton template
template <typename T> class ThreadSafeSingleton
{

public:
    static T& GetSingleton();
    static T* GetSingletonPtr();

    static T& GetSingleton(const std::string value);
    static T* GetSingletonPtr(const std::string value);


    const std::string GetString()
    {
        return m_Value;
    }

    ThreadSafeSingleton(const T&) = delete;
    ThreadSafeSingleton(const T&&) = delete;
    T& operator=(const T&) = delete;

protected:
    ThreadSafeSingleton(const std::string value)
        : m_Value(value)
    {
        if (ms_Singleton) {
            //throw std::runtime_error("Singleton instance already exists!");
            return;
        }
        int offset = (int)(T*)1 - (int)(Singleton<T>*)(T*)1; // to avoid multiple inheritance issues
        ms_Singleton = (T*)(this + offset);
    }
    ~ThreadSafeSingleton()
    {
        assert(ms_Singleton);
        ms_Singleton = nullptr;
    }
private:

    static T* ms_Singleton;
    std::string m_Value;

    static std::mutex m_Mutex;
};

template <typename T> T* ThreadSafeSingleton<T>::ms_Singleton = nullptr;
template <typename T> std::mutex ThreadSafeSingleton<T>::m_Mutex;

template <typename T>
T& ThreadSafeSingleton<T>::GetSingleton()
{
    std::lock_guard<std::mutex> lock(m_Mutex);
    if (ms_Singleton == nullptr) {
        ms_Singleton = new T("void");
    }
    return *ms_Singleton;
}

template <typename T>
T* ThreadSafeSingleton<T>::GetSingletonPtr()
{
    std::lock_guard<std::mutex> lock(m_Mutex);
    if (ms_Singleton == nullptr) {
        ms_Singleton = new T("void");
    }
    return ms_Singleton;
}

template <typename T>
T& ThreadSafeSingleton<T>::GetSingleton(const std::string value)
{
    std::lock_guard<std::mutex> lock(m_Mutex);
    if (ms_Singleton == nullptr) {
        ms_Singleton = new T(value);
    }
    return *ms_Singleton;
}

template <typename T>
T* ThreadSafeSingleton<T>::GetSingletonPtr(const std::string value)
{
    std::lock_guard<std::mutex> lock(m_Mutex);
    if (ms_Singleton == nullptr) {
        ms_Singleton = new T(value);
    }
    return ms_Singleton;
}