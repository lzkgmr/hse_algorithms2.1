#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include "a2i.cpp"

class ArrayGenerator {
public:
    ArrayGenerator() {
        initializeBaseArrays();
        generateSubArrays();
    }

    std::vector<std::vector<int>> getRandomArrays() const {
        return randomArrays;
    }

    std::vector<std::vector<int>> getSortedArrays() const {
        return sortedArrays;
    }

    std::vector<std::vector<int>> getAlmostSorted() const {
        return almostSortedArrays;
    }

private:
    std::vector<std::vector<int>> randomArrays;
    std::vector<std::vector<int>> sortedArrays;
    std::vector<std::vector<int>> almostSortedArrays;
    std::mt19937 generator;

    void initializeBaseArrays()  {
        std::random_device rand_dev;
        generator = std::mt19937(rand_dev());
        std::uniform_int_distribution<> distr(1, 6000);

        randomArrays.emplace_back(generateRandomArray(10000, distr));
        sortedArrays.emplace_back(randomArrays[0]);
        almostSortedArrays.emplace_back(randomArrays[0]);

        std::stable_sort(sortedArrays[0].begin(), sortedArrays[0].end());
        reverseArray(sortedArrays[0]);

        std::stable_sort(almostSortedArrays[0].begin(), almostSortedArrays[0].end());
        reverseArray(almostSortedArrays[0]);
        introduceRandomSwaps(almostSortedArrays[0], distr, 10);
    }

    void generateSubArrays() {
        std::uniform_int_distribution<> distr(0, 10000 - 1);

        for (int size = 500; size <= 10000; size += 100) {
            int range = 10000 - size;
            int start = (range > 0) ? distr(generator) % range : 0;

            randomArrays.push_back(copySubArray(randomArrays[0], start, size));
            sortedArrays.push_back(copySubArray(sortedArrays[0], start, size));
            almostSortedArrays.push_back(copySubArray(almostSortedArrays[0], start, size));
        }
    }

    std::vector<int> generateRandomArray(int size, std::uniform_int_distribution<> &distr) {
        std::vector<int> array(size);
        for (int &val : array) {
            val = distr(generator);
        }
        return array;
    }

    void reverseArray(std::vector<int> &array)  {
        std::reverse(array.begin(), array.end());
    }

    void introduceRandomSwaps(std::vector<int> &array, std::uniform_int_distribution<> &distr, int swaps) {
        int n = array.size();
        for (int i = 0; i < swaps; ++i) {
            std::swap(array[distr(generator) % n], array[distr(generator) % n]);
        }
    }

    std::vector<int> copySubArray(const std::vector<int> &source, int start, int size) {
        return std::vector<int>(source.begin() + start, source.begin() + start + size);
    }
};

class SortTester {
public:
    long long testMergeSort(std::vector<int>& A) {
        auto start = std::chrono::high_resolution_clock::now();
        mergeSort(A, 0, static_cast<int>(A.size() - 1));
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long msec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        return msec;
    }

    long long testModMergeSort(std::vector<int>& A) {
        auto start = std::chrono::high_resolution_clock::now();
        modMergeSort(A, 0, static_cast<int>(A.size() - 1));
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long msec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        return msec;
    }
};

int main() {
    ArrayGenerator arrg = ArrayGenerator();
    auto random = arrg.getRandomArrays();
    auto sorted = arrg.getSortedArrays();
    auto almost = arrg.getAlmostSorted();
    auto tester = SortTester();

    std::vector<long long> result(almost.size());

    for (int j = 0; j < 20; ++j) {
        for (int i = 0; i < almost.size(); ++i) {
            result[i] += tester.testMergeSort(sorted[i]);
        }
    }

    for (int i = 0; i < almost.size(); ++i) {
        result[i] /= 20;
        std::cout << result[i] << ' ';
    }
}