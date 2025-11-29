#include <iostream>
#include <stdexcept>
#include <algorithm>

class DynamicArray {
private:
    int* data;
    size_t size;

public:
    DynamicArray(size_t arraySize) : size(arraySize) {
        if (size > 0) {
            data = new int[size];
            for (size_t i = 0; i < size; ++i) {
                data[i] = 0;
            }
        } else {
            data = nullptr;
        }
    }

    DynamicArray(const DynamicArray& other) : size(other.size) {
        if (size > 0) {
            data = new int[size];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        } else {
            data = nullptr;
        }
    }

    ~DynamicArray() {
        delete[] data;
    }

    void print() const {
        std::cout << "Array [size: " << size << "]: ";
        for (size_t i = 0; i < size; ++i) {
            std::cout << data[i];
            if (i < size - 1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }

    void setValue(size_t index, int value) {
        if (index >= size) {
            throw std::out_of_range("Index is out of array bounds");
        }
        if (value < -100 || value > 100) {
            throw std::invalid_argument("Value must be in range from -100 to 100");
        }
        data[index] = value;
    }
    
    int getValue(size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index is out of array bounds");
        }
        return data[index];
    }

    void pushBack(int value) {
        if (value < -100 || value > 100) {
            throw std::invalid_argument("Value must be in range from -100 to 100");
        }

        size_t newSize = size + 1;
        int* newData = new int[newSize];

        for (size_t i = 0; i < size; ++i) {
            newData[i] = data[i];
        }

        newData[size] = value;
        delete[] data;
        data = newData;
        size = newSize;
    }

    DynamicArray add(const DynamicArray& other) const {
        size_t maxSize = (size > other.size) ? size : other.size;
        DynamicArray result(maxSize);

        for (size_t i = 0; i < maxSize; ++i) {
            int value1 = (i < size) ? data[i] : 0;
            int value2 = (i < other.size) ? other.data[i] : 0;
            int sum = value1 + value2;
            
            if (sum < -100) sum = -100;
            if (sum > 100) sum = 100;
            
            result.data[i] = sum;
        }

        return result;
    }

    DynamicArray subtract(const DynamicArray& other) const {
        size_t maxSize = (size > other.size) ? size : other.size;
        DynamicArray result(maxSize);

        for (size_t i = 0; i < maxSize; ++i) {
            int value1 = (i < size) ? data[i] : 0;
            int value2 = (i < other.size) ? other.data[i] : 0;
            int diff = value1 - value2;
            
            if (diff < -100) diff = -100;
            if (diff > 100) diff = 100;
            
            result.data[i] = diff;
        }

        return result;
    }

    size_t getSize() const {
        return size;
    }

    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            if (size > 0) {
                data = new int[size];
                for (size_t i = 0; i < size; ++i) {
                    data[i] = other.data[i];
                }
            } else {
                data = nullptr;
            }
        }
        return *this;
    }
};

class ExtendedDynamicArray : public DynamicArray {
public:
    // Constructors
    ExtendedDynamicArray(size_t arraySize) : DynamicArray(arraySize) {}
    ExtendedDynamicArray(const DynamicArray& other) : DynamicArray(other) {}

    // Calculate average value
    double calculateAverage() const {
        size_t currentSize = getSize();
        if (currentSize == 0) {
            throw std::runtime_error("Cannot calculate average for empty array");
        }
        
        double sum = 0.0;
        for (size_t i = 0; i < currentSize; ++i) {
            sum += getValue(i);
        }
        
        return sum / currentSize;
    }

    // Calculate median value
    double calculateMedian() {
        size_t currentSize = getSize();
        if (currentSize == 0) {
            throw std::runtime_error("Cannot calculate median for empty array");
        }
        
        // Create temporary array for sorting
        int* tempArray = new int[currentSize];
        for (size_t i = 0; i < currentSize; ++i) {
            tempArray[i] = getValue(i);
        }
        
        // Sort array
        std::sort(tempArray, tempArray + currentSize);
        
        double median;
        if (currentSize % 2 == 0) {
            // For even number of elements - average of two central elements
            median = (tempArray[currentSize / 2 - 1] + tempArray[currentSize / 2]) / 2.0;
        } else {
            // For odd number of elements - central element
            median = tempArray[currentSize / 2];
        }
        
        delete[] tempArray;
        return median;
    }

    // Find minimum element
    int findMin() const {
        size_t currentSize = getSize();
        if (currentSize == 0) {
            throw std::runtime_error("Cannot find minimum element in empty array");
        }
        
        int minValue = getValue(0);
        for (size_t i = 1; i < currentSize; ++i) {
            if (getValue(i) < minValue) {
                minValue = getValue(i);
            }
        }
        
        return minValue;
    }

    // Find maximum element
    int findMax() const {
        size_t currentSize = getSize();
        if (currentSize == 0) {
            throw std::runtime_error("Cannot find maximum element in empty array");
        }
        
        int maxValue = getValue(0);
        for (size_t i = 1; i < currentSize; ++i) {
            if (getValue(i) > maxValue) {
                maxValue = getValue(i);
            }
        }
        
        return maxValue;
    }

    // Method to print all statistical data
    void printStatistics() {
        std::cout << "Array statistics:" << std::endl;
        print();
        std::cout << "Minimum element: " << findMin() << std::endl;
        std::cout << "Maximum element: " << findMax() << std::endl;
        std::cout << "Average value: " << calculateAverage() << std::endl;
        std::cout << "Median value: " << calculateMedian() << std::endl;
    }
};

int main() {
    try {
        int size1, size2;
        
        std::cout << "Enter size of first array: ";
        std::cin >> size1;
        ExtendedDynamicArray arr1(size1);
        
        std::cout << "Enter " << size1 << " elements of first array (from -100 to 100):" << std::endl;
        for (int i = 0; i < size1; ++i) {
            int value;
            std::cin >> value;
            arr1.setValue(i, value);
        }
        
        std::cout << "Enter size of second array: ";
        std::cin >> size2;
        ExtendedDynamicArray arr2(size2);
        
        std::cout << "Enter " << size2 << " elements of second array (from -100 to 100):" << std::endl;
        for (int i = 0; i < size2; ++i) {
            int value;
            std::cin >> value;
            arr2.setValue(i, value);
        }
        
        std::cout << "\nFirst array: ";
        arr1.print();
        std::cout << "Second array: ";
        arr2.print();
        
        ExtendedDynamicArray sum = arr1.add(arr2);
        std::cout << "Addition result: ";
        sum.print();
        
        ExtendedDynamicArray diff = arr1.subtract(arr2);
        std::cout << "Subtraction result: ";
        diff.print();
        
        // Demonstration of new methods
        std::cout << "\n--- First array statistics ---" << std::endl;
        arr1.printStatistics();
        
        std::cout << "\n--- Second array statistics ---" << std::endl;
        arr2.printStatistics();
        
        char choice;
        std::cout << "\nDo you want to add elements to the end of first array? (y/n): ";
        std::cin >> choice;
        
        if (choice == 'y' || choice == 'Y') {
            int newValue;
            std::cout << "Enter value to add (from -100 to 100): ";
            std::cin >> newValue;
            arr1.pushBack(newValue);
            std::cout << "Array after addition: ";
            arr1.print();
            std::cout << "Updated statistics:" << std::endl;
            arr1.printStatistics();
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}