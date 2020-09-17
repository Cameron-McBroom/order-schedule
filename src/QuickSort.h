#pragma once

#include <vector>
#include <algorithm>

template <class T>
class QuickSort {
private:
    std::vector<T> values_;
    bool reversed_;

    int partition (int low, int high) {
        T pivot = values_[high];
        int i = (low - 1);

        for (int j = low; j <= high- 1; j++)
        {
            if (values_[j] <= pivot) {
                i++;
                std::swap(values_[i], values_[j]);
            }
        }
        std::swap(values_[i + 1], values_[high]);
        return (i + 1);
    }

    void quickSort(int low, int high)
    {
        if (low < high) {
            int pi = partition(low, high);
            quickSort(low, pi - 1);
            quickSort(pi + 1, high);
        }
    }

public:
    QuickSort(std::vector<T> values, bool reversed = false) : values_(values), reversed_(reversed) {}

    std::vector<T>& operator()() {
        quickSort(0, values_.size() - 1);
        if (reversed_) std::reverse(values_.begin(), values_.end());
        return values_;
    }
};