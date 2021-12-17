/* vim: set tabstop=4:softtabstop=4:shiftwidth=4:expandtab */
#include <iostream>
#include <vector>
#include <time.h>
#include <unistd.h>
#include <algorithm>
#include <chrono>
#include <span>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>
#include <random>
using namespace std;
using namespace std::chrono;


class Time {
    public:
        std::chrono::time_point<std::chrono::high_resolution_clock> start;
        std::chrono::time_point<std::chrono::high_resolution_clock> stop;

        void startCount() {
            start = high_resolution_clock::now();
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
            cout << seconds << " seconds (" << milli << " milliseconds)" << endl;
        }
};


void swap(int *xp, int *yp) {
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void bubbleSort(vector<int> &array, int size) {
	int i, j;
	for (i = 0; i < size-1; i++) {
        for (j = 0; j < size-i-1; j++) {
            if (array[j] > array[j+1]) {
                swap(&array[j], &array[j+1]);
            }
        }
    }
}

void timsBubbleSort(vector<int> &array, int size) {
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

void cocktailSort(vector<int> &array, int size) {
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

void basicSort(vector<int> &array, int size) {
    sort(array.begin(), array.end());
}

void heapify(vector<int> &array, int n, int i)
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

void heapSort(vector<int> &array, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(array, n, i);

    for (int i = n - 1; i >= 0; i--) {
        swap(array[0], array[i]);

        heapify(array, i, 0);
    }
}

int partition(vector<int> &array, int low, int high) {
    int pivot = array[high];
    int i = (low-1);
    for (int j = low; j <= high-1; j++) {
        if (array[j] <= pivot) {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i+1], &array[high]);
    return (i+1);
}

void quickSort(vector<int> &array, int low, int high) {

    if (low < high) {
        int pi = partition(array, low, high);
        quickSort(array, low, pi -1);
        quickSort(array, pi+1, high);
    }
}

void merge(vector<int> &array, int const left, int const mid, int const right)
{
	auto const subArrayOne = mid - left + 1;
	auto const subArrayTwo = right - mid;

	// Create temp arrays
	auto *leftArray = new int[subArrayOne],
		*rightArray = new int[subArrayTwo];

	// Copy data to temp arrays leftArray[] and rightArray[]
	for (auto i = 0; i < subArrayOne; i++)
		leftArray[i] = array[left + i];
	for (auto j = 0; j < subArrayTwo; j++)
		rightArray[j] = array[mid + 1 + j];

	auto indexOfSubArrayOne = 0, // Initial index of first sub-array
		indexOfSubArrayTwo = 0; // Initial index of second sub-array
	int indexOfMergedArray = left; // Initial index of merged array

	// Merge the temp arrays back into array[left..right]
	while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
		if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
			array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
			indexOfSubArrayOne++;
		}
		else {
			array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
			indexOfSubArrayTwo++;
		}
		indexOfMergedArray++;
	}
	// Copy the remaining elements of
	// left[], if there are any
	while (indexOfSubArrayOne < subArrayOne) {
		array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
		indexOfSubArrayOne++;
		indexOfMergedArray++;
	}
	// Copy the remaining elements of
	// right[], if there are any
	while (indexOfSubArrayTwo < subArrayTwo) {
		array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
	}

    delete[] leftArray;
    delete[] rightArray;
}

// begin is for left index and end is
// right index of the sub-array
// of arr to be sorted */
void mergeSort(vector<int> &array, int const begin, int const end)
{
	if (begin >= end)
		return; // Returns recursively

	auto mid = begin + (end - begin) / 2;
	mergeSort(array, begin, mid);
	mergeSort(array, mid + 1, end);
	merge(array, begin, mid, end);
}


void
insertionSort(span<int>arr)
{
	for (int i = 1; i < (int)arr.size(); i++) {
		if (arr[i] >= arr[i - 1]) continue;
		int j = i - 1;
		for (;;) {
			if (j == 0) break;
			if (arr[i] > arr[j-1]) break;
			j--;
		}
		rotate(arr.begin()+j, arr.begin()+i, arr.begin()+i+1);
	}
}

void
merge2(span<int> inA, span<int> inB, span<int> out)
{
	int left = 0;
	int right = 0;
	int lw = inA.size();
	int rw = inB.size();
	int ow = out.size();
//	printf("      lw = %d, rw = %d, ow = %d\n", lw, rw, ow);
	for (int outidx = 0; outidx < ow; outidx++) {
//		printf("         outidx = %d\n", outidx);
//		printf("         left = %d\n", left);
//		printf("         right = %d\n", right);
		if (left < lw && (right >= rw || inA[left] <= inB[right])) {
//			printf("            doing left\n");
			out[outidx] = inA[left];
//			printf("            out[outidx] = %d\n", out[outidx]);
			left++;
		} else {
//			printf("            doing right\n");
			out[outidx] = inB[right];
//			printf("            out[outidx] = %d\n", out[outidx]);
			right++;
		}
	}
}

void
hybridMergeSort(span<int>in)
{
	int n = in.size();
	auto A = in;
	auto temp = new int[n];
	auto B = span(temp, n);

	int width = 8;
	for (int i = 0; i < n; i += width) {
		insertionSort(span(A).subspan(i, min(width, n - i)));
	}

	for (; width < n; width *= 2) {
//		printf("width = %d\n", width);
		for (int i = 0; i < n; i += 2*width) {
//			printf("   i = %d\n", i);
			int llen = min(width, n-i);
			int rlen = max(0, min(width, n-(llen+i)));
//			printf("   l = %d\n", llen);
//			printf("   r = %d\n", rlen);
			merge2(A.subspan(i, llen), A.subspan(i+llen, rlen),
				B.subspan(i, llen+rlen));
		}
		auto foo = A;
		A = B;
		B = foo;
	}
	if (B.data() == in.data()) {
		memcpy(in.data(), A.data(), in.size_bytes());
	}
	delete[] temp;
}


#define UNIFORM 1
#define BINOMIAL 2

class randStuff {
    random_device rd;
    mt19937_64 gen;
    int max;
    uniform_int_distribution<> uid;
    binomial_distribution<> bd;
    int type = UNIFORM;

    public:

    randStuff() {
        gen.seed(rd());
    }

    void init(int type, int max) {
        this->type = type;
        this->max = max;
        switch (type) {
            case UNIFORM:
                uid = uniform_int_distribution<>(1, max);
                break;
            case BINOMIAL:
                bd = binomial_distribution<>(max, 0.5);
                break;
        }
    }

    void setMax(int max) {
        this->init(this->type, max);
        this->max = max;
    }
    int getMax() {
        return max;
    }

    int get() {
        switch (type) {
            case UNIFORM:
                return uid(gen);
            case BINOMIAL:
                return bd(gen);
        }
        return -1;
    }
};

vector<int> createArray(randStuff &r, int size) {
    vector<int> array;
    for (int i = 0; i < size;i++) {
        array.push_back(r.get());
    }
    return array;
}

vector<int> createSortedArray(randStuff& r, int size) {
    vector<int> array = createArray(r, size);
    sort(array.begin(), array.end());
    return array;
}

vector<int> almostSortedArray(randStuff &r, int size) {
    vector<int> array = createSortedArray(r, size);

    for (int j = 0; j < size;) {
        array[j] = r.get();
        j += 10;
    }

    return array;
}

vector<int> reverseSortedArray(randStuff &r, int size) {
    vector<int> array = createArray(r, size);
    sort(array.rbegin(), array.rend());
    return array;
}

void checkAll(Time t, vector<int> &array) {
    int size = array.size();
    vector<int> tmp;

    tmp = array;
    cout << "std::sort sort = ";
    t.startCount();
    basicSort(tmp, size);
    t.getTime();

    if (size <= 20000) {
        tmp = array;
        cout << "Bubble sort = ";
        t.startCount();
        bubbleSort(tmp, size);
        t.getTime();
    } else printf("skipping bubble sort\n");

    if (size <= 20000) {
        tmp = array;
	    cout << "Cocktail sort = ";
	    t.startCount();
	    cocktailSort(tmp, size);
	    t.getTime();
    } else printf("skipping cocktail sort\n");

    if (size <= 20000) {
        tmp = array;
	    cout << "Tims bubble sort = ";
        t.startCount();
	    timsBubbleSort(tmp, size);
	    t.getTime();
    } else printf("skipping tim's bubble sort\n");

    if (size <= 50000) {
        tmp = array;
        cout << "Heap sort = ";
        t.startCount();
        heapSort(tmp, size);
        t.getTime();
    } else printf("skipping heap sort\n");

    if (size <= 2000000) {
        int low = 0;
        int high = size -1;
        tmp = array;
        t.startCount();
        quickSort(tmp, low, high);
        cout << "Quicksort =" << endl;
        t.getTime();
    } else printf("skipping quicksort\n");

    tmp = array;
    cout << "Merge sort = ";
    t.startCount();
    mergeSort(tmp, 0, size - 1);
    t.getTime();

    cout << "hybrid merge sort = ";
    tmp = array;
    t.startCount();
    hybridMergeSort(tmp);
    t.getTime();
}



void menu() {
    cout
    << "======== MENU ========" << endl
    << "n. Change array size"   << endl
    << "m. Change the maximum element value"   << endl
    << "U. Use uniform distribution."   << endl
    << "B. Use binomial distribution."   << endl
    << "1. Create unsorted array" << endl
    << "2. Create sorted array" << endl
    << "3. Create reverse sorted array" << endl
    << "4. Create almost sorted array" << endl
    << "0. Check all "          << endl
    << "9. Quit"                << endl
    << "c. Cocktail sort"       << endl
    << "t. Tims bubble sort"    << endl
    << "h. Heap sort"           << endl
    << "q. Quicksort"           << endl
    << "M. Recursive Merge Sort"	<< endl
    << "a. hybridMergeSort"	<< endl
    << "b. c++ std::sort"	<< endl
    << "======================\n"
    << "-> ";
}


int main() {

    Time t;
    vector<int> array, tmp;
    int size = 1000;
    int max = 200;
    randStuff rands;
    rands.init(UNIFORM, max);

    string line;
    char choice;
    int low = 0;
    int high;


    while (1) {
        menu();
        cin >> choice;
        switch (choice) {
        case 'n':
            cout << "Choose array size: ";
            cin >> size;
            break;
        case 'm':
            cout << "Choose element max: ";
            cin >> max;
            rands.setMax(max);
            break;
        case 'U':
            rands.init(UNIFORM, max);
            break;
        case 'B':
            rands.init(BINOMIAL, max);
            break;
        case '1':
            cout << "Making unsorted array.\n";
            array = createArray(rands, size);
            break;
        case '2':
            cout << "Making sorted array.\n";
            array = createSortedArray(rands, size);
            break;
        case '3':
            cout << "Making reverse sorted array.\n";
            array = reverseSortedArray(rands, size);
            break;
        case '4':
            cout << "Making almost sorted array.\n";
            array = almostSortedArray(rands, size);
            break;
        case '0':
            checkAll(t, array);
            break;
        case '9':
            return 0;
        case 'c':
            tmp = array;
            t.startCount();
            cocktailSort(tmp, tmp.size());
            t.getTime();
            break;
        case 't':
            tmp = array;
            t.startCount();
            timsBubbleSort(tmp, tmp.size());
            t.getTime();
            break;
        case 'h':
            tmp = array;
            t.startCount();
            heapSort(tmp, tmp.size());
            t.getTime();
            break;
        case 'q':
            tmp = array;
            high = tmp.size() -1;
            t.startCount();
            quickSort(tmp, low, high);
            t.getTime();
            break;
        case 'M':
            tmp = array;
            t.startCount();
            mergeSort(tmp, 0, tmp.size() - 1);
            t.getTime();
            break;
        case 'a':
            tmp = array;
            t.startCount();
            hybridMergeSort(tmp);
            t.getTime();
            break;
        case 'b':
            tmp = array;
            t.startCount();
            basicSort(tmp, tmp.size());
            t.getTime();
            break;
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







