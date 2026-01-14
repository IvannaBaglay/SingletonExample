#include "NaiveSingleton.h"
#include "ThreadSafeChildSingleton.h"

#include <iostream>
#include <thread>

void ThreadFoo() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    NaiveSingleton* singleton = NaiveSingleton::GetSingletonPtr("FOO");
    std::cout << singleton->GetString() << "\n";
}

void ThreadBar() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    NaiveSingleton* singleton = NaiveSingleton::GetSingletonPtr("BAR");
    std::cout << singleton->GetString() << "\n";
}

void ThreadFooSafe() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    ThreadSafeChildSingleton* singleton = ThreadSafeChildSingleton::GetSingletonPtr("FOO");
    std::cout << singleton->GetString() << "\n";
}

void ThreadBarSafe() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    ThreadSafeChildSingleton* singleton = ThreadSafeChildSingleton::GetSingletonPtr("BAR");
    std::cout << singleton->GetString() << "\n";
}

int main() {

    std::cout << "If you see the same value, then singleton was reused (yay!\n" <<
        "If you see different values, then 2 singletons were created (booo!!)\n\n" <<
        "RESULT:\n";
    std::thread t1(ThreadFoo);
    std::thread t2(ThreadBar);

    std::thread t3(ThreadFooSafe);
    std::thread t4(ThreadBarSafe);

    t1.join();
    t2.join();

    t3.join();
    t4.join();

    return 0;
}
