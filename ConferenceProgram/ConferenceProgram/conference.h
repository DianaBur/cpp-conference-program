#pragma once
#include <string>
#include <vector>

struct Time {
    int hours;
    int minutes;
};

struct Presentation {
    Time start;
    Time end;
    std::string lastName;
    std::string firstName;
    std::string middleName;
    std::string topic;
};

// ������� ��� ������ � �������
int getDuration(const Presentation& p);
int compareByDurationDesc(const Presentation* a, const Presentation* b);
int compareByAuthorAndTopic(const Presentation* a, const Presentation* b);

// ������� ����������
void heapSort(std::vector<Presentation*>& array, int (*compare)(const Presentation*, const Presentation*));
void mergeSort(std::vector<Presentation*>& array, int (*compare)(const Presentation*, const Presentation*));