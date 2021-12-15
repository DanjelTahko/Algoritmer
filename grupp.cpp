#include <iostream>
#include <vector>
#include <time.h>
#include <unistd.h>
#include <algorithm>
#include <chrono>
using namespace std;
using namespace std::chrono;


class Time {
  
    public:

        std::chrono::time_point<std::chrono::high_resolution_clock> start;
        std::chrono::time_point<std::chrono::high_resolution_clock> stop;

        void startCount() {
            start = high_resolution_clock::now();
            cout << "Sorting list.." << endl;
        }

        void stopCount() {
            stop = high_resolution_clock::now();
        }

        void getTime() {

            int milli, seconds;
            Time::stopCount();
            auto duration = duration_cast<milliseconds>(stop - start);
            milli = duration.count();
            seconds = duration.count() / 1000;
            cout << "\n* " << seconds << " seconds (" << milli << " milliseconds)\n" << endl;
        }
};

void menu() {

    cout << "======== MENU ========" << endl;
    cout << "1. Change array size"   << endl;
    cout << "2. Create sorted array" << endl;
    cout << "3. Bubble sort"         << endl;
    cout << "4. Cocktail sort"       << endl;
    cout << "5. Tims bubble sort"    << endl;
    cout << "6. Heap sort"           << endl;
    cout << "7. Quicksort"           << endl;
    cout << "8. Check all "          << endl;
    cout << "9. Quit"                << endl;
    cout << "======================\n"     << "->";
}

void swap(int *xp, int *yp) {
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void bubbleSort(vector<int> array, int size) {
	int i, j;
	for (i = 0; i < size-1; i++) {	
        for (j = 0; j < size-i-1; j++) {
            if (array[j] > array[j+1]) {
                swap(&array[j], &array[j+1]);
            }
        }
    }
}

void timsBubbleSort(vector<int> array, int size) {
    int unsorted = 1;
    while (unsorted) {
        unsorted = 0;
        for (int i = 0; i < size -1; i++) {
            if (array[i] > array[i+1]) {
                swap(&array[i], &array[i+1]);
                unsorted = 1;
            }
        }
    }
}

void cocktailSort(vector<int> array, int size) {
    bool swapped = true;
    int start = 0;
    int end = size -1;
    while (swapped) {
        swapped = false;
        for (int i = start; i < end; i++) {
            if (array[i] > array[i+1]) {
                swap(&array[i], &array[i+1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
        swapped = false;
        --end;
        for (int i = end - 1; i >= start; --i) {
            if (array[i] > array[i+1]) {
                swap(&array[i], &array[i+1]);
                swapped = true;
            }
        }
        ++start;
    }
    //cout << array[10] << array[100] << array[1000] << array[10000] << array[size] << endl;
}

void basicSort(vector<int>array, int size) {
    sort(array.begin(), array.end());
}

void heapify(vector<int>array, int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
  
    if (l < n && array[l] > array[largest])
        largest = l;
  
    if (r < n && array[r] > array[largest])
        largest = r;
  
    if (largest != i) {
        swap(array[i], array[largest]);
  
        heapify(array, n, largest);
    }
}
  
void heapSort(vector<int>array, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(array, n, i);
  
    for (int i = n - 1; i >= 0; i--) {
        swap(array[0], array[i]);
  
        heapify(array, i, 0);
    }
}

int partition(vector<int>array, int low, int high) {
    int pivot = array[high];
    int i = (low - 1);
    for (int j = low; j <= high-1; j++) {
        if (array[j] < pivot) {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    cout << array[i] << endl;
    swap(&array[i+1], &array[high]);
    return (i+1);
}

void quickSort(vector<int>array, int low, int high) {

    if (low < high) {
        int pi = partition(array, low, high);
        quickSort(array, low, pi -1);
        quickSort(array, pi+1, high);
    }
}

vector<int> createArray(int input) {
    vector<int> array;
    for (int i = 0; i < input;i++) {
        array.push_back((rand()%50)+1);
    }
    return array;
}

vector<int> createSortedArray(int input) {
    vector<int> array;
    for (int i = 0; i < input;i++) {
        array.push_back(i);
    }
    return array;
}

void checkAll(Time t, vector<int> array, int size) {

    t.startCount();
    basicSort(array, size);
    cout << "Basic sort =" << endl;
    t.getTime();

    t.startCount();
    bubbleSort(array, size);
    cout << "Bubble sort =" << endl;
    t.getTime();

    t.startCount();
    cocktailSort(array, size);
    cout << "Cocktail sort =" << endl;
    t.getTime();

    t.startCount();
    timsBubbleSort(array, size);
    cout << "Tims bubble sort =" << endl;
    t.getTime();

    t.startCount();
    heapSort(array, size);
    cout << "Heap sort =" << endl;
    t.getTime();

    int low = 0;
    int high = size -1;
    t.startCount();
    quickSort(array, low, high);
    cout << "Quicksort =" << endl;
    t.getTime();
}



int main() {

    Time t;
    vector<int>array;
    int size;
    string line;
    char choice;
    int low = 0;
    int high;

    while (1) {
        menu();
        cin >> choice;
        switch (choice) {
        case '1':
            cout << "Choose array size: ";
            cin >> size;
            array = createArray(size);
            break;
        case '2':
            cout << "Choose array size: ";
            cin >> size;
            array = createSortedArray(size);
            break;
        case '3':
            t.startCount();
            bubbleSort(array, size);
            t.getTime();
            break;
        case '4':
            t.startCount();
            cocktailSort(array, size);
            t.getTime();
            break;
        case '5':
            t.startCount();
            timsBubbleSort(array, size);
            t.getTime();
            break;
        case '6':
            t.startCount();
            heapSort(array, size);
            t.getTime();
            break;
        case '7':
            high = size -1;
            t.startCount();
            quickSort(array, low, high);
            t.getTime();
            break;
        case '8':
            checkAll(t, array, size);
            break;
        case '9':
            return 0;
        default:
            cout << "Invalid input" << endl;
            break;
        }
    }
    return 0;

}

/*
for (int i = 0; i < size; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
*/
