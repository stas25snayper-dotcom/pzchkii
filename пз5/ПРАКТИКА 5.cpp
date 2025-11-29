#include <iostream>
#include <stdexcept>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>

class DynamicArray {
protected:
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

    virtual ~DynamicArray() {
        delete[] data;
    }

    void print() const {
        std::cout << "Массив [размер: " << size << "]: ";
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
            throw std::out_of_range("Индекс выходит за границы массива");
        }
        if (value < -100 || value > 100) {
            throw std::invalid_argument("Значение должно быть в диапазоне от -100 до 100");
        }
        data[index] = value;
    }

    int getValue(size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Индекс выходит за границы массива");
        }
        return data[index];
    }

    void pushBack(int value) {
        if (value < -100 || value > 100) {
            throw std::invalid_argument("Значение должно быть в диапазоне от -100 до 100");
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

    virtual DynamicArray* add(const DynamicArray& other) const = 0;

    virtual DynamicArray* subtract(const DynamicArray& other) const = 0;

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

    virtual void saveToFile() const = 0;

protected:
    std::string getCurrentDateTime() const {
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        
        std::stringstream ss;
        ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d_%H-%M-%S");
        return ss.str();
    }
};

class ArrTxt : public DynamicArray {
public:
    ArrTxt(size_t arraySize) : DynamicArray(arraySize) {}
    
    ArrTxt(const DynamicArray& other) : DynamicArray(other) {}

    DynamicArray* add(const DynamicArray& other) const override {
        size_t maxSize = (size > other.getSize()) ? size : other.getSize();
        ArrTxt* result = new ArrTxt(maxSize);

        for (size_t i = 0; i < maxSize; ++i) {
            int value1 = (i < size) ? data[i] : 0;
            int value2 = (i < other.getSize()) ? other.getValue(i) : 0;
            int sum = value1 + value2;
            
            if (sum < -100) sum = -100;
            if (sum > 100) sum = 100;
            
            result->data[i] = sum;
        }

        return result;
    }

    DynamicArray* subtract(const DynamicArray& other) const override {
        size_t maxSize = (size > other.getSize()) ? size : other.getSize();
        ArrTxt* result = new ArrTxt(maxSize);

        for (size_t i = 0; i < maxSize; ++i) {
            int value1 = (i < size) ? data[i] : 0;
            int value2 = (i < other.getSize()) ? other.getValue(i) : 0;
            int diff = value1 - value2;
            
            if (diff < -100) diff = -100;
            if (diff > 100) diff = 100;
            
            result->data[i] = diff;
        }

        return result;
    }

    void saveToFile() const override {
        std::string filename = getCurrentDateTime() + ".txt";
        std::ofstream file(filename);
        
        if (!file.is_open()) {
            throw std::runtime_error("Не удалось открыть файл для записи: " + filename);
        }
        
        file << "Массив [размер: " << size << "]:\n";
        for (size_t i = 0; i < size; ++i) {
            file << "Элемент " << i << ": " << data[i];
            if (i < size - 1) {
                file << "\n";
            }
        }
        
        file.close();
        std::cout << "Массив сохранен в файл: " << filename << std::endl;
    }
};

class ArrCSV : public DynamicArray {
public:
    ArrCSV(size_t arraySize) : DynamicArray(arraySize) {}
    
    ArrCSV(const DynamicArray& other) : DynamicArray(other) {}

    DynamicArray* add(const DynamicArray& other) const override {
        size_t maxSize = (size > other.getSize()) ? size : other.getSize();
        ArrCSV* result = new ArrCSV(maxSize);

        for (size_t i = 0; i < maxSize; ++i) {
            int value1 = (i < size) ? data[i] : 0;
            int value2 = (i < other.getSize()) ? other.getValue(i) : 0;
            int sum = value1 + value2;
            
            if (sum < -100) sum = -100;
            if (sum > 100) sum = 100;
            
            result->data[i] = sum;
        }

        return result;
    }

    DynamicArray* subtract(const DynamicArray& other) const override {
        size_t maxSize = (size > other.getSize()) ? size : other.getSize();
        ArrCSV* result = new ArrCSV(maxSize);

        for (size_t i = 0; i < maxSize; ++i) {
            int value1 = (i < size) ? data[i] : 0;
            int value2 = (i < other.getSize()) ? other.getValue(i) : 0;
            int diff = value1 - value2;
            
            if (diff < -100) diff = -100;
            if (diff > 100) diff = 100;
            
            result->data[i] = diff;
        }

        return result;
    }

    void saveToFile() const override {
        std::string filename = getCurrentDateTime() + ".csv";
        std::ofstream file(filename);
        
        if (!file.is_open()) {
            throw std::runtime_error("Не удалось открыть файл для записи: " + filename);
        }
        
        file << "Index,Value\n";
        for (size_t i = 0; i < size; ++i) {
            file << i << "," << data[i];
            if (i < size - 1) {
                file << "\n";
            }
        }
        
        file.close();
        std::cout << "Массив сохранен в файл: " << filename << std::endl;
    }
};

void saveArray(const DynamicArray& array) {
    array.saveToFile();
}

int main() {
    try {
        int size1, size2;
        
        std::cout << "Введите размер первого массива: ";
        std::cin >> size1;
        ArrTxt arr1(size1);
        
        std::cout << "Введите " << size1 << " элементов первого массива (от -100 до 100):" << std::endl;
        for (int i = 0; i < size1; ++i) {
            int value;
            std::cin >> value;
            arr1.setValue(i, value);
        }
        
        std::cout << "Введите размер второго массива: ";
        std::cin >> size2;
        ArrCSV arr2(size2);
        
        std::cout << "Введите " << size2 << " элементов второго массива (от -100 до 100):" << std::endl;
        for (int i = 0; i < size2; ++i) {
            int value;
            std::cin >> value;
            arr2.setValue(i, value);
        }
        
        std::cout << "\nПервый массив: ";
        arr1.print();
        std::cout << "Второй массив: ";
        arr2.print();
        
        // Используем указатели для результатов операций
        DynamicArray* sum = arr1.add(arr2);
        std::cout << "Результат сложения: ";
        sum->print();
        
        DynamicArray* diff = arr1.subtract(arr2);
        std::cout << "Результат вычитания: ";
        diff->print();
        
        // Демонстрация полиморфизма
        std::cout << "\nСохранение массивов в файлы..." << std::endl;
        
        DynamicArray* arrays[] = {&arr1, &arr2, sum, diff};
        
        for (int i = 0; i < 4; i++) {
            arrays[i]->saveToFile();
        }
        
        // Альтернативный способ через функцию
        std::cout << "\nСохранение через полиморфную функцию:" << std::endl;
        saveArray(arr1);
        saveArray(arr2);
        
        char choice;
        std::cout << "\nХотите добавить элементы в конец первого массива? (y/n): ";
        std::cin >> choice;
        
        if (choice == 'y' || choice == 'Y') {
            int newValue;
            std::cout << "Введите значение для добавления (от -100 до 100): ";
            std::cin >> newValue;
            arr1.pushBack(newValue);
            std::cout << "Массив после добавления: ";
            arr1.print();
            
            arr1.saveToFile();
        }
        
        // Освобождаем память
        delete sum;
        delete diff;
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}