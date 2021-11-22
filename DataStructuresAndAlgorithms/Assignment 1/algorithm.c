#include "algorithm.h"

//
// Private
//
int partition(int *a, int lb, int ub) {
	int pivot = a[ub];
	int i = lb - 1;
	for (int j = lb; j < ub; j++) {
		if (a[j] <= pivot) {
			int temp = a[++i];
			a[i] = a[j];
			a[j] = temp;
		}
	}
	int temp = a[++i];
	a[i] = a[ub];
	a[ub] = temp;
	return i;
}

void quick_sort_impl(int *a, int lb, int ub) {
	if (lb >= 0 && ub >= 0 && lb < ub) {
		int pivot = partition(a, lb, ub);
		quick_sort_impl(a, lb, pivot - 1);
		quick_sort_impl(a, pivot + 1, ub);
	}
}
//
// Public
//
void bubble_sort(int *a, int n) {
	bool noChange = false;
	for (int i = 1; i < n; i++) {
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
                                         		
void insertion_sort(int *a, int n) {
	for (int i = 1; i < n; i++) {
		int temp = a[i];
		int j = i - 1;
		while (j >= 0 && a[j] > temp) {
			a[j+1] = a[j];
			j--;
		}
		a[j+1] = temp;
	}
}

void quick_sort(int *a, int n) {
	quick_sort_impl(a, 0, n - 1);
}

bool linear_search(const int *a, int n, int v) {
	for (int i = 0; i < n; i++) {
		if (a[i] == v) {
			return true;
		}
	}
	return false;
}

bool binary_search(const int *a, int n, int v) {	
	int roof = n-1;
	int floor = 0;
	int mid = (n-1)/2;
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