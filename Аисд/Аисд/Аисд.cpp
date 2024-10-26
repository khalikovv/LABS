#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <fstream>
#include <iomanip>

using namespace std;

// Функция для обмена элементов
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Функция для вывода массива
void printArray(const vector<int>& arr) {
    for (int i = 0; i < arr.size(); ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}


// Генерация отсортированного массива
vector<int> generateSortedArray(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = i; // Отсортированный по возрастанию
    }
    return arr;
}

// Генерация почти отсортированного массива (90/10)
vector<int> generateNearlySortedArray(int size, unsigned seed) {
    vector<int> arr = generateSortedArray(size);
    srand(seed);
    int numSwaps = size / 10;
    for (int i = 0; i < numSwaps; ++i) {
        int idx1 = rand() % size;
        int idx2 = rand() % size;
        swap(arr[idx1], arr[idx2]);
    }
    return arr;
}

// Генерация массива, отсортированного в обратном порядке
vector<int> generateReversedArray(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = size - i; // Отсортированный по убыванию
    }
    return arr;
}

// Генерация случайного массива с заданным сидом
vector<int> generateRandomArray(int size, unsigned seed) {
    srand(seed);
    vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 100; // Заполняем случайными числами от 0 до 99
    }
    return arr;
}

// Сохранение результатов в файл с фиксированной точностью
void saveResults(ofstream& outFile, int size, double time, const string& sortType, const string& arrayType) {
    outFile << sortType << "," << arrayType << "," << size << ",";
    outFile << fixed << setprecision(6) << time << endl;
}



// Сортировка выбором
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

// Сортировка вставками
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}


// Функции для случайной сортировки (Bogosort)
bool isSorted(const vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }
    return true;
}

void shuffle(vector<int>& arr) {
    random_shuffle(arr.begin(), arr.end());
}

void bogosort(vector<int>& arr) {
    while (!isSorted(arr)) {
        shuffle(arr);
    }
}

// Функция для слияния двух подмассивов
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> leftArr(n1), rightArr(n2);

    for (int i = 0; i < n1; ++i)
        leftArr[i] = arr[left + i];
    for (int i = 0; i < n2; ++i)
        rightArr[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        }
        else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

// Функция сортировки слиянием
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}


// Функция для выбора опорного элемента из середины на индексах
int medianOfThree(vector<int>& arr, int left, int right) {
    int mid = left + (right - left) / 2;
    if (arr[left] > arr[mid])
        swap(arr[left], arr[mid]);
    if (arr[left] > arr[right])
        swap(arr[left], arr[right]);
    if (arr[mid] > arr[right])
        swap(arr[mid], arr[right]);
    return arr[mid];
}

// Функция для разбиения массива и возврата индекса опорного элемента
int partition(vector<int>& arr, int left, int right) {
    int pivot = medianOfThree(arr, left, right);
    int i = left + 1;
    int j = right - 1;

    while (true) {
        while (i <= right && arr[i] < pivot) i++;
        while (j >= left && arr[j] > pivot) j--;

        if (i >= j) break;
        swap(arr[i], arr[j]);
        i++;
        j--;
    }
    swap(arr[i], arr[right - 1]); // Помещаем pivot на место
    return i;
}

// Оптимизированная быстрая сортировка 
void quickSort(vector<int>& arr, int left, int right) {
    while (left < right) {
        int pivotIndex = partition(arr, left, right);

        // Рекурсивно сортируем меньший подмассив, а больший используем в цикле
        if (pivotIndex - left < right - pivotIndex) {
            quickSort(arr, left, pivotIndex - 1);
            left = pivotIndex + 1;
        }
        else {
            quickSort(arr, pivotIndex + 1, right);
            right = pivotIndex - 1;
        }
    }
}

// Сортировка Шелла (Shell Sort)
void shellSort(vector<int>& arr) {
    int n = arr.size();

    // Начинаем с большого шага и уменьшаем его
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // Сортировка вставками для элементов, разделенных шагом gap
        for (int i = gap; i < n; ++i) {
            int temp = arr[i]; // текущий элемент
            int j;

            // Сдвигаем элементы, которые больше текущего, на шаг gap вправо
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap]; // Сдвиг
            }

            // Вставляем текущий элемент на правильное место
            arr[j] = temp;
        }
    }
}

//сортировка пузырьком
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}
// пирамедальная сортировка
void heapify(vector<int>& arr, int n, int i) {
    int largest = i; // Инициализируем наибольший элемент как корень
    int left = 2 * i + 1; // Левый дочерний элемент
    int right = 2 * i + 2; // Правый дочерний элемент

    // Если левый дочерний элемент больше корня
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // Если правый дочерний элемент больше наибольшего элемента
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // Если наибольший элемент не корень
    if (largest != i) {
        swap(arr[i], arr[largest]);

        // Рекурсивно преобразуем в кучу затронутое поддерево
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();

    // Построение кучи (перегруппируем массив)
    for (int i = n / 2 - 1; i >= 0; --i)
        heapify(arr, n, i);

    // Извлечение элементов из кучи по одному
    for (int i = n - 1; i > 0; --i) {
        // Перемещаем текущий корень в конец
        swap(arr[0], arr[i]);

        // Вызываем процедуру heapify на уменьшенной куче
        heapify(arr, i, 0);
    }
}
// Сортировка Шелла с использованием последовательности Хиббарда
void shellSortHibbard(vector<int>& arr) {
    int n = arr.size();
    vector<int> gaps;

    // Генерируем последовательность Хиббарда: 2^k - 1
    for (int k = 1; (1 << k) - 1 < n; ++k) {
        gaps.push_back((1 << k) - 1); // 1 << k - это 2^k
    }
    reverse(gaps.begin(), gaps.end()); // Начинаем с больших промежутков

    // Сортировка с использованием промежутков Хиббарда
    for (int gap : gaps) {
        for (int i = gap; i < n; ++i) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}
// Сортировка Шелла с использованием последовательности Пратта
void shellSortPratt(vector<int>& arr) {
    int n = arr.size();
    vector<int> gaps;

    // Генерируем последовательность Пратта: 2^i * 3^j
    for (int i = 1; i < n; i *= 2) {
        for (int j = i; j < n; j *= 3) {
            gaps.push_back(j);
        }
    }
    sort(gaps.begin(), gaps.end(), greater<int>()); // Сортируем в обратном порядке

    // Сортировка с использованием промежутков Пратта
    for (int gap : gaps) {
        for (int i = gap; i < n; ++i) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}





/// Функция для выбора сортировки
void chooseSort(vector<int>& arr, int sortType) {
    switch (sortType) {
    case 1: selectionSort(arr); break;
    case 2: insertionSort(arr); break;
    case 3: bogosort(arr); break;
    case 4: mergeSort(arr, 0, arr.size() - 1); break;
    case 5: quickSort(arr, 0, arr.size() - 1); break;
    case 6: shellSort(arr); break;
    case 7: bubbleSort(arr); break;
    case 8: heapSort(arr); break;
    case 9: shellSortHibbard(arr); break;
    case 10: shellSortPratt(arr); break;
    default: cout << "Неверный выбор\n";
    }
}


// Функция для загрузки сида из файла
unsigned loadSeed() {
    ifstream file("seed.txt");
    unsigned seed;
    if (file.is_open()) {
        file >> seed;
        file.close();
    }
    else {
        seed = time(0); // Если файла нет, используем текущее время как сид
        ofstream outFile("seed.txt");
        outFile << seed;
        outFile.close();
    }
    return seed;
}

// Главная функция
int main() {
    setlocale(LC_ALL, "ru");
    unsigned seed = loadSeed();
    int arrayType, sortType;
    string arrayTypeStr, sortTypeStr;

    // Массив размеров, по которым будем тестировать сортировку
    vector<int> sizes = { 1000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000 };

    cout << "Выберите тип массива:\n";
    cout << "1. Отсортированный\n";
    cout << "2. Почти отсортированный (90/10)\n";
    cout << "3. Случайный\n";
    cout << "4. Отсортированный в обратном порядке\n";
    cin >> arrayType;
    vector<int> arr;

    // Определяем тип массива
    switch (arrayType) {
    case 1:
        arrayTypeStr = "Отсортированный";
        break;
    case 2:
        arrayTypeStr = "Почти отсортированный (90/10)";
        break;
    case 3:
        arrayTypeStr = "Случайный";
        break;
    case 4:
        arrayTypeStr = "Отсортированный в обратном порядке";
        break;
    default:
        cout << "Неверный выбор\n";
        return 1;
    }
    //Сгенерированный массив
    /*cout << "Сгенерированный массив: ";
    printArray(arr);*/

    cout << "Выберите сортировку:\n";
    cout << "1. Сортировка выбором (Selection sort)\n";
    cout << "2. Сортировка вставками (Insertion sort)\n";
    cout << "3. Случайная сортировка (Bogosort)\n";
    cout << "4. Сортировка слиянием (Merge sort)\n";
    cout << "5. Быстрая сортировка (Quick sort)\n";
    cout << "6. Алгоритм сортировки Шелла (Shell sort)\n";
    cout << "7. Сортировка пузырьком (Bubble sort)\n";
    cout << "8. Пирамидальная сортировка (Heap sort)\n";
    cout << "9. Сортировка Хиббарда (Shell sort Hibbard)\n";
    cout << "10. Сортировка Пратта (Shell sort Pratt)\n";
    cin >> sortType;


    // Определяем название сортировки
    switch (sortType) {
    case 1: sortTypeStr = "Selection sort"; break;
    case 2: sortTypeStr = "Insertion sort"; break;
    case 3: sortTypeStr = "Bogosort"; break;
    case 4: sortTypeStr = "Merge sort"; break;
    case 5: sortTypeStr = "Quick sort"; break;
    case 6: sortTypeStr = "Shell sort"; break;
    case 7: sortTypeStr = "Bubble sort"; break;
    case 8: sortTypeStr = "Heap sort"; break;
    case 9: sortTypeStr = "Shell sort(Hibbard)"; break;
    case 10: sortTypeStr = "Shell sort(Pratt)"; break;
    default:
        cout << "Неверный выбор\n";
        return 1;
    }

    ofstream outFile("results.txt", ios::app);
    if (!outFile.is_open()) {
        cout << "Ошибка открытия файла для записи результатов.\n";
        return 1;
    }

    // Пробегаем по всем размерам из списка
    for (int size : sizes) {
        vector<int> arr;
        switch (arrayType) {
        case 1:
            arr = generateSortedArray(size);
            break;
        case 2:
            arr = generateNearlySortedArray(size, seed);
            break;
        case 3:
            arr = generateRandomArray(size, seed);
            break;
        case 4:
            arr = generateReversedArray(size);
            break;
        }

        vector<int> arrCopy = arr; // Копируем массив для сортировки

        // Замер времени начала сортировки
        auto start = chrono::high_resolution_clock::now();
        chooseSort(arrCopy, sortType);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;

        // Вывод времени сортировки
        cout << "Размер: " << size << ", Время сортировки: " << fixed << setprecision(6) << duration.count() << " секунд\n";

        //Показать отсортированный массив
        /*cout << "Отсортированный массив: ";
        printArray(arrCopy);*/

        // Сохранение результатов в файл
        saveResults(outFile, size, duration.count(), sortTypeStr, arrayTypeStr);
    }

    outFile.close();
    cout << "Результаты сохранены в файл results.txt\n";

    return 0;
}

