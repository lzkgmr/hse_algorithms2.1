#include <iostream>
#include <vector>
#include <algorithm>
#include <iostream>

void insertionSort(std::vector<int> &array, int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
        int k = array[i];
        int j = i - 1;
        while (j >= left && array[j] > k) {
            array[j + 1] = array[j];
            j -= 1;
        }
        array[j + 1] = k;
    }
}

void merge(std::vector<int> &nums, int left, int mid, int right) {
    std::vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        if (nums[i] <= nums[j]) {
            temp[k++] = nums[i++];
        } else {
            temp[k++] = nums[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = nums[i++];
    }

    while (j <= right) {
        temp[k++] = nums[j++];
    }
    std::copy(temp.begin(), temp.end(), nums.begin() + left);
}

void mergeSort(std::vector<int> &nums, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(nums, left, mid);
        mergeSort(nums, mid + 1, right);
        merge(nums, left, mid, right);
    }
}

void modMergeSort(std::vector<int> &nums, int left, int right) {
    if (left < right) {
        if (right - left <= 500) {
            insertionSort(nums, left, right);
            return;
        }

        int mid = left + (right - left) / 2;

        mergeSort(nums, left, mid);
        mergeSort(nums, mid + 1, right);
        merge(nums, left, mid, right);
    }
}

// void solve() {
//     int n;
//     std::cin >> n;
//     std::vector<int> array(n);
//     for (int i = 0; i < n; ++i) {
//         std::cin >> array[i];
//     }
//     mergeSort(array, 0, array.size() - 1);
//     for (auto n : array) {
//         std::cout << n << ' ';
//     }
// }

// int main() {
//     std::ios_base::sync_with_stdio(false);
//     std::cin.tie(nullptr);
//     std::cout.tie(nullptr);

//     solve();
// }