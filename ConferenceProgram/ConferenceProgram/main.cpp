#include <iostream>
#include <vector>
#include <algorithm>
#include "conference.h"
#include "file_reader.h"

void printPresentation(const Presentation& p) {
    std::cout << "Доклад: " << p.topic << "\n";
    std::cout << "Автор: " << p.lastName << " " << p.firstName << " " << p.middleName << "\n";
    std::cout << "Время: " << p.start.hours << ":" << (p.start.minutes < 10 ? "0" : "") << p.start.minutes
        << " - " << p.end.hours << ":" << (p.end.minutes < 10 ? "0" : "") << p.end.minutes
        << " (длительность: " << getDuration(p) << " мин)\n";
    std::cout << "----------------------------------------\n";
}

void filterByAuthor(const std::vector<Presentation>& presentations) {
    std::string lastName, firstName, middleName;
    std::cout << "Введите фамилию автора: ";
    std::cin >> lastName;
    std::cout << "Введите имя автора: ";
    std::cin >> firstName;
    std::cout << "Введите отчество автора: ";
    std::cin >> middleName;

    std::cout << "\nДоклады " << lastName << " " << firstName << " " << middleName << ":\n";
    bool found = false;
    for (const auto& p : presentations) {
        if (p.lastName == lastName && p.firstName == firstName && p.middleName == middleName) {
            printPresentation(p);
            found = true;
        }
    }
    if (!found) {
        std::cout << "Докладов не найдено.\n";
    }
}

void filterByDuration(const std::vector<Presentation>& presentations) {
    std::cout << "\nДоклады длительностью более 15 минут:\n";
    bool found = false;
    for (const auto& p : presentations) {
        if (getDuration(p) > 15) {
            printPresentation(p);
            found = true;
        }
    }
    if (!found) {
        std::cout << "Докладов не найдено.\n";
    }
}

void sortPresentations(std::vector<Presentation>& presentations) {
    std::vector<Presentation*> ptrs;
    for (auto& p : presentations) {
        ptrs.push_back(&p);
    }

    std::cout << "\nВыберите метод сортировки:\n";
    std::cout << "1. Пирамидальная сортировка (Heap sort)\n";
    std::cout << "2. Сортировка слиянием (Merge sort)\n";
    int method;
    std::cin >> method;

    std::cout << "\nВыберите критерий сортировки:\n";
    std::cout << "1. По убыванию длительности доклада\n";
    std::cout << "2. По возрастанию фамилии автора, затем по теме\n";
    int criterion;
    std::cin >> criterion;

    if (method == 1) {
        if (criterion == 1) {
            heapSort(ptrs, compareByDurationDesc);
        }
        else {
            heapSort(ptrs, compareByAuthorAndTopic);
        }
    }
    else {
        if (criterion == 1) {
            mergeSort(ptrs, compareByDurationDesc);
        }
        else {
            mergeSort(ptrs, compareByAuthorAndTopic);
        }
    }

    std::cout << "\nОтсортированные доклады:\n";
    for (const auto& p : ptrs) {
        printPresentation(*p);
    }
}

int main() {
    setlocale(LC_ALL, "ru");

    std::cout << "Программа конференции\n";
    std::cout << "Автор: Diana Burunova\n";

    std::vector<Presentation> presentations = readPresentationsFromFile("data.txt");

    if (presentations.empty()) {
        std::cout << "Не удалось загрузить данные или файл пуст.\n";
        return 1;
    }

    while (true) {
        std::cout << "\nМеню:\n";
        std::cout << "1. Показать все доклады\n";
        std::cout << "2. Фильтровать доклады по автору\n";
        std::cout << "3. Фильтровать доклады по длительности (>15 мин)\n";
        std::cout << "4. Сортировать доклады\n";
        std::cout << "5. Выход\n";
        std::cout << "Выберите действие: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "\nВсе доклады:\n";
            for (const auto& p : presentations) {
                printPresentation(p);
            }
            break;
        case 2:
            filterByAuthor(presentations);
            break;
        case 3:
            filterByDuration(presentations);
            break;
        case 4:
            sortPresentations(presentations);
            break;
        case 5:
            return 0;
        default:
            std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    }
}
