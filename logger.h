#pragma once
#include <iostream>
#include <fstream>
#include <mutex>
#include <string>
#include <memory>

class Logger {
private:
    static std::unique_ptr<Logger> instance;
    static std::mutex init_mtx;
    static std::mutex write_mtx;
    std::ofstream logFile;

    // 생성자
    Logger(const std::string& filename) {
        logFile.open(filename, std::ios::trunc);
        logFile << "[Init] Logger started." << std::endl;
    }

public:
    // 소멸자
    ~Logger() {
        logFile << "[Shutdown] Logger closed." << std::endl;
        logFile.close();
    }

    // Singleton 접근 함수
    static Logger* getInstance(const std::string& filename = "Test/output2.txt") {
        std::lock_guard<std::mutex> lock(init_mtx);
        if (!instance) {
            instance.reset(new Logger(filename));
        }
        return instance.get();
    }

    // 로그 기록
    void log(const std::string& message) {
        std::lock_guard<std::mutex> lock(write_mtx);
        logFile << message << std::endl;
    }
};

// static 멤버 정의
std::unique_ptr<Logger> Logger::instance;
std::mutex Logger::init_mtx;
std::mutex Logger::write_mtx;
