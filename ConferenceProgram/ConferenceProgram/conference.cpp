#include "conference.h"
#include <algorithm>

int getDuration(const Presentation& p) {
    return (p.end.hours * 60 + p.end.minutes) - (p.start.hours * 60 + p.start.minutes);
}

int compareByDurationDesc(const Presentation* a, const Presentation* b) {
    return getDuration(*b) - getDuration(*a);
}

int compareByAuthorAndTopic(const Presentation* a, const Presentation* b) {
    if (a->lastName != b->lastName) return a->lastName.compare(b->lastName);
    return a->topic.compare(b->topic);
}

// Реализация пирамидальной сортировки
void heapify(std::vector<Presentation*>& array, int size, int root, int (*compare)(const Presentation*, const Presentation*)) {
    int largest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;

    if (left < size && compare(array[left], array[largest]) > 0)
        largest = left;

    if (right < size && compare(array[right], array[largest]) > 0)
        largest = right;

    if (largest != root) {
        std::swap(array[root], array[largest]);
        heapify(array, size, largest, compare);
    }
}

void heapSort(std::vector<Presentation*>& array, int (*compare)(const Presentation*, const Presentation*)) {
    int size = static_cast<int>(array.size());
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(array, size, i, compare);

    for (int i = size - 1; i > 0; i--) {
        std::swap(array[0], array[i]);
        heapify(array, i, 0, compare);
    }
}

// Реализация сортировки слиянием
void merge(std::vector<Presentation*>& array, int left, int mid, int right, int (*compare)(const Presentation*, const Presentation*)) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<Presentation*> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = array[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = array[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (compare(L[i], R[j]) <= 0) {
            array[k] = L[i];
            i++;
        }
        else {
            array[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        array[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        array[k] = R[j];
        j++;
        k++;
    }
}

void mergeSortHelper(std::vector<Presentation*>& array, int left, int right, int (*compare)(const Presentation*, const Presentation*)) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortHelper(array, left, mid, compare);
        mergeSortHelper(array, mid + 1, right, compare);
        merge(array, left, mid, right, compare);
    }
}

void mergeSort(std::vector<Presentation*>& array, int (*compare)(const Presentation*, const Presentation*)) {
    mergeSortHelper(array, 0, static_cast<int>(array.size()) - 1, compare);
}