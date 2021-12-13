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

    cout << "===== MENU ====="   << endl;
    cout << "1. Basic sort"      << endl;
    cout << "2. Bubble sort"     << endl;
    cout << "3. Cocktail sort"   << endl;
    cout << "4. Tims bubble sort" << endl;
    cout << "4. Quit"            << endl;
    cout << "================\n" << "->";
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
                swap(array[i], array[i+1]);
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
}

void basicSort(vector<int>array, int size) {
    sort(array.begin(), array.end());
}

int main() {

    Time t;
    vector<int> array;

    for (int i = 0; i < 100000;i++) { // 100 tusen
        array.push_back((rand()%50)+1);
    }

    int size = array.size();
    string line;
    char choice;

    while (1) {
        menu();
        cin >> choice;
        switch (choice) {
        case '1':
            t.startCount();
            basicSort(array, size);
            t.getTime();
            break;
        case '2':
            t.startCount();
            bubbleSort(array, size);
            t.getTime();
            break;
        case '3':
            t.startCount();
            cocktailSort(array, size);
            t.getTime();
            break;
        case '4':
            t.startCount();
            timsBubbleSort(array, size);
            t.getTime();
            break;
        case '5':
            return 0;
        default:
            cout << "Invalid input" << endl;
            break;
        }
    }
    return 0;

}