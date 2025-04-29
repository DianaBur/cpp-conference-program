#include <iostream>
#include <vector>
#include <algorithm>
#include "conference.h"
#include "file_reader.h"

void printPresentation(const Presentation& p) {
    std::cout << "������: " << p.topic << "\n";
    std::cout << "�����: " << p.lastName << " " << p.firstName << " " << p.middleName << "\n";
    std::cout << "�����: " << p.start.hours << ":" << (p.start.minutes < 10 ? "0" : "") << p.start.minutes
        << " - " << p.end.hours << ":" << (p.end.minutes < 10 ? "0" : "") << p.end.minutes
        << " (������������: " << getDuration(p) << " ���)\n";
    std::cout << "----------------------------------------\n";
}

void filterByAuthor(const std::vector<Presentation>& presentations) {
    std::string lastName, firstName, middleName;
    std::cout << "������� ������� ������: ";
    std::cin >> lastName;
    std::cout << "������� ��� ������: ";
    std::cin >> firstName;
    std::cout << "������� �������� ������: ";
    std::cin >> middleName;

    std::cout << "\n������� " << lastName << " " << firstName << " " << middleName << ":\n";
    bool found = false;
    for (const auto& p : presentations) {
        if (p.lastName == lastName && p.firstName == firstName && p.middleName == middleName) {
            printPresentation(p);
            found = true;
        }
    }
    if (!found) {
        std::cout << "�������� �� �������.\n";
    }
}

void filterByDuration(const std::vector<Presentation>& presentations) {
    std::cout << "\n������� ������������� ����� 15 �����:\n";
    bool found = false;
    for (const auto& p : presentations) {
        if (getDuration(p) > 15) {
            printPresentation(p);
            found = true;
        }
    }
    if (!found) {
        std::cout << "�������� �� �������.\n";
    }
}

void sortPresentations(std::vector<Presentation>& presentations) {
    std::vector<Presentation*> ptrs;
    for (auto& p : presentations) {
        ptrs.push_back(&p);
    }

    std::cout << "\n�������� ����� ����������:\n";
    std::cout << "1. ������������� ���������� (Heap sort)\n";
    std::cout << "2. ���������� �������� (Merge sort)\n";
    int method;
    std::cin >> method;

    std::cout << "\n�������� �������� ����������:\n";
    std::cout << "1. �� �������� ������������ �������\n";
    std::cout << "2. �� ����������� ������� ������, ����� �� ����\n";
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

    std::cout << "\n��������������� �������:\n";
    for (const auto& p : ptrs) {
        printPresentation(*p);
    }
}

int main() {
    setlocale(LC_ALL, "ru");

    std::cout << "��������� �����������\n";
    std::cout << "�����: Diana Burunova\n";

    std::vector<Presentation> presentations = readPresentationsFromFile("data.txt");

    if (presentations.empty()) {
        std::cout << "�� ������� ��������� ������ ��� ���� ����.\n";
        return 1;
    }

    while (true) {
        std::cout << "\n����:\n";
        std::cout << "1. �������� ��� �������\n";
        std::cout << "2. ����������� ������� �� ������\n";
        std::cout << "3. ����������� ������� �� ������������ (>15 ���)\n";
        std::cout << "4. ����������� �������\n";
        std::cout << "5. �����\n";
        std::cout << "�������� ��������: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "\n��� �������:\n";
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
            std::cout << "�������� �����. ���������� �����.\n";
        }
    }
}
