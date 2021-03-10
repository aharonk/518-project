//
//  main.cpp
//  algorithms
//
//  Created by Jeremy Mandelbaum on 2/20/21.
//
#include <iostream>
#include <algorithm>
#include "linkedList.cpp"
using namespace std;

//2

//fill array
int* fillArray(int SIZE){
    int* array = new int[SIZE];
    for (int i = 0; i <= SIZE; i++) {
       int n = rand() % 3 + i*3;
        srand(613);
        array[i] = n;
    }
    return array;
}

//fill linked list
LinkedList fillLL(int SIZE){
    LinkedList l;
    for (int i = 0; i < SIZE; i++) {
        int n = rand() % 3 + i*3;
         srand(613);
        l.newNode(n);
    }
    return l;
}

int recursiveBinarySearch(int arr[], int bottom, int top, int num) {
       if (bottom <= top) {
          int mid = (bottom + top)/2;
           //num is below the midpoint
           if (arr[mid] > num)
               return recursiveBinarySearch(arr, bottom, mid-1, num);
           //num is above midpoint
           else if (arr[mid] < num){
              return recursiveBinarySearch(arr, mid+1, top, num);
           } else if (arr[mid] == num)
                return mid;
       }
       return -1;
    }

int iterativeBinarySearch(int arr[], int top, int num) {
      int bottom = 0;

      while(bottom <= top) {
        int mid = (bottom+top)/2;
          //num is below midpoint
        if(arr[mid] > num)
          top = mid - 1;
          //num is above midpoint
        else if(arr[mid] < num)
          bottom = mid + 1;
        else
          return mid;
      }
      return -1;
    }

void testSpeed2(int size){
    //fill arrays up to given size
    int* nums = fillArray(size);
    LinkedList ll = fillLL(size);
    
    //time each individually
    clock_t iSeconds = clock();
    cout << "the results from the iterative search are " << iterativeBinarySearch(nums, size-1, 298) << "\nIt took " << clock() - iSeconds << " to find the solution\n" <<endl;
    
    clock_t rSeconds = clock();
    cout << "the results from the recursive search are " << recursiveBinarySearch(nums, 0, size, 298) << "\nIt took " << clock() - rSeconds << " to find the solution\n"<< endl;
    
    //delete nums to free up space
    delete nums;
    
    clock_t llSeconds = clock();
    cout << "the results from the linked type search are " << ll.binarySearch(ll.head, 298) << "\nIt took " << clock() - llSeconds << " to find the solution\n"<< endl;
    }

//4

//similiar to question 2 but wanted to keep everything self sufficient
int* fillArrayTest4(int SIZE){
    int* array = new int[SIZE];
    for (int i = 0; i <= SIZE; i++) {
       int n = rand() % 200;
        array[i] = n;
    }
    return array;
}

template <typename T>
void swap(T* a, T* b) {
    T placeholder = *a;
    *a = *b;
    *b = placeholder;
}

template <typename T>
int partition (T arr[], int bottom, int top) {
    T pivot = arr[top];
    int i = bottom - 1;
 
    for (int j = bottom; j < top; j++) {
        //current is smaller than or equal to pivot
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[top]);
    return i + 1;
}

template <typename T>
void quickSort(T arr[], int low, int high)
{
    if (low < high)
    {
        //find the partition
        int pIndex = partition(arr, low, high);
 
        //sorts elements before partition and after partition
        quickSort(arr, low, pIndex - 1);
        quickSort(arr, pIndex + 1, high);
    }
}

//bubble sort has little variablity in terms of overall efficiency
template <typename T>
void bubbleSort(T arr[], int size) {
   for (int i = 0; i < size - 1; i++) {
     bool swapped = false;
     for (int j = 0; j < size - (i - 1); j++) {
        if (arr[j] > arr[j + 1]) {
           swap(&arr[j], &arr[j + 1]);
           swapped = true;
        }
     }
     // If no elements swapped break
     if (swapped == false)
        break;
   }
}

//resonably comparative sort to bubble sort
//both n^2
template <typename T>
void testSelectionSort(T arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
        if (arr[j] < arr[minIndex])
            minIndex = j;
  
        swap(&arr[minIndex], &arr[i]);
    }
}

void heapify(int arr[], int n, int i)
{
    int largest = i; // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2
  
    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;
  
    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;
  
    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);
  
        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
  
    // One by one extract an element from heap
    for (int i = n - 1; i >= 0; i--) {
        // Move current root to end
        swap(arr[0], arr[i]);
  
        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

template <typename T>
void multilevelSort(T arr[], int SIZE){
    if (SIZE > 10)
        quickSort(arr, 0, SIZE);
    else
        bubbleSort(arr, SIZE);
}

template <typename T>
void multilevelSortComparision(T arr[], int SIZE){
    if (SIZE > 10)
        heapSort(arr, SIZE);
    else
        testSelectionSort(arr, SIZE);
}

void testSpeed4(int size){
    int* nums = fillArrayTest4(size);
    clock_t msSeconds = clock();
    multilevelSort(nums, size - 1);
    cout << clock() - msSeconds << " - The length of our sort" << endl;
    clock_t mscSeconds = clock();
    multilevelSortComparision(nums, size);
    cout << clock() - mscSeconds << " - The compared sort"<< endl;
}

//6
template <class T>
class Subset{
private: void subsetSum(T original[], T answers[], int originalSize, int answersSize, T sum, T currentIteration, T const targetSum){
   if (targetSum == sum) {
       //print current then move on to next case
       for (int i = 0; i < answersSize; i++)
          printf("%*d", 5, answers[i]);
            printf("\n");
      subsetSum(original, answers, originalSize, answersSize - 1, sum - original[currentIteration], currentIteration + 1, targetSum);
   }
   else {
      for (int i = currentIteration; i < originalSize; i++) {
         answers[answersSize] = original[i];
         subsetSum(original, answers, originalSize, answersSize + 1, sum + original[i], i + 1, targetSum);
      }
   }
}
public: void generateSubsets(T s[], int size, T targetSum){
   int* answers = (int*)malloc(size * sizeof(int));
   subsetSum(s, answers, size, 0, 0, 0, targetSum);
   //deallocates memory used by malloc
   free(answers);
}
};

int main(int argc, const char * argv[]) {
    
    //2
    testSpeed2(1000000);
    testSpeed2(10000000);
    testSpeed2(100000000);
    
    //4
    testSpeed4(7);
    testSpeed4(100);
    testSpeed4(10000);
    
    //6
    int set[] = { 5, 6, 12 , 54, 2 , 20 , 15 , 3};
       int size = sizeof(set) / sizeof(set[0]);
    Subset<int>* s = new Subset<int>;
    s->generateSubsets(set, size, 23);
    
    return 0;
}
