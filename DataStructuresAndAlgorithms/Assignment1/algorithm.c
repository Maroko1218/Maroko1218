#include "algorithm.h"

//
// Private
//

//
// Public
//
void bubble_sort(int *a, int n)
{
	bool noChange = false;
	for (int i = 0; i < n; i++) {
		noChange = true;
		for (int j = 0; j < n - i; j++) {
			if (a[j] > a[j+1]) {
				noChange = false;
				int temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
		if (noChange == true) {
			break;
		}
	}
}
                                         		
void insertion_sort(int *a, int n)
{
	for (int i = 1; i < n; i++) {
		if (a[i] >= a[i-1]) {
			continue;
		}
		for (int j = i-1; j >= 0; j--) {
			if (a[i] < a[j]) {
				int temp = a[i];
				for (int k = i; k > j; k--) {
					a[k] = a[k-1];
				}
				a[j] = temp;
			}	
		}
	}
}

void quick_sort(int *a, int n)
{
	// TODO: quick sort
}

bool linear_search(const int *a, int n, int v)
{
	for (int i = 0; i < n; i++) {
		if (a[i] == v) {
			return true;
		}
	}
	return false;
}

bool binary_search(const int *a, int n, int v)
{	
	int roof = n;
	int floor = 0;
	int mid = n/2;
	if (v > a[roof] || v < a[floor]) {
		return false;
	} 
	while (v != a[mid]) {
		if (roof == floor) {
			return false;
		}
		if (v < a[mid]) {
			roof = mid - 1;
		} else {
			floor = mid + 1;
		}
		mid = floor + ((roof - floor)/2); 
	}
	return true;
}
