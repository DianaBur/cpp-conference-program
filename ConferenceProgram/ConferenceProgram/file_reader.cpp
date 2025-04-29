#include "file_reader.h"
#include "conference.h"
#include <fstream>
#include <sstream>
#include <string>

Time parseTime(const std::string& timeStr) {
    Time time;
    size_t colonPos = timeStr.find(':');
    time.hours = std::stoi(timeStr.substr(0, colonPos));
    time.minutes = std::stoi(timeStr.substr(colonPos + 1));
    return time;
}

std::vector<Presentation> readPresentationsFromFile(const std::string& filename) {
    std::vector<Presentation> presentations;
    std::ifstream file(filename);

    

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        Presentation p;
        std::string startTime, endTime;

        iss >> startTime >> endTime >> p.lastName >> p.firstName >> p.middleName;
        p.start = parseTime(startTime);
        p.end = parseTime(endTime);

        // Читаем тему доклада (остаток строки)
        std::getline(iss, p.topic);
        // Удаляем ведущие пробелы
        p.topic.erase(0, p.topic.find_first_not_of(" \t"));

        presentations.push_back(p);
    }

    return presentations;
}