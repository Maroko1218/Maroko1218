#include "ui.h"
#include "io.h"
#include "analyze.h"

#include <stdbool.h>
#include <stdio.h>

//
// Private
//
static void ui_invalid_input()
{
	printf("info> bad input\n");
}

static void ui_exit()
{
	printf("info> bye\n");
}

static char ui_get_choice()
{
	char buf[3];

	printf("input> ");
	return read_line(buf, 3) ? buf[0] : 0;
}

static void ui_line(char c, int n)
{
	while (n-- > 0) {
		putchar(c);
	}
	putchar('\n');
}

static void ui_menu_options(const char *options[], int num_options)
{
	int i;

	for (i=0; i<num_options; i++) {
		printf("    %c) %s\n", 'a'+i, options[i]);
	}
}

static void ui_menu()
{
	const char *options[] = {
		"Menu",
		"Exit\n",
		"Bubble sort best case",
		"Bubble sort worst case",
		"Bubble sort average case\n",
		"Insertion sort best case",
		"Insertion sort worst case",
		"Insertion sort average case\n",
		"Quick sort best case",
		"Quick sort worst case",
		"Quick sort average case\n",
		"Linear search best case",
		"Linear search worst case",
		"Linear search average case\n",
		"Binary search best case",
		"Binary search worst case",
		"Binary search average case"
	};

	ui_line('=', MENU_WIDTH);
	ui_menu_options(options, sizeof(options) / sizeof(char *));
	ui_line('-', MENU_WIDTH);
}

static void list_times(const char *caller, result_t *results)
{
	ui_line('*', 63);
	int strlen = 0;
	for (int i = 0; caller[i] != '\0'; i++) {
		strlen++;
	}
	int adjustedWidth = (63 - strlen) / 2;
	for (int i = 0; i < adjustedWidth; i++) {
		putchar(' ');
	}
	printf("%s\n", caller);
	ui_line('~', 63);
	printf("%7s%14s%14s%14s%14s\n","size", "time T(s)", "T/nlogn", "T/n", "T/n^2");
	for (int i = 0; i < RESULT_ROWS; i++) {
		printf("%7d%14.8lf%14.8lf%14.8lf%14.8lf\n", results[i].size, results[i].time, results[i].time, results[i].time / results[i].size, results[i].time);
	}
	

}

//
// Public
//
void ui_run()
{
	bool running, show_menu;
	result_t result[RESULT_ROWS];
	show_menu = true;
	running = true;
	while (running) {
		if (show_menu) {
			show_menu = false;
			ui_menu();
		}
		switch (ui_get_choice()) {
			// House keeping
			case 'a':
				show_menu = true;
				break;
			case 'b':
				running = false;
				break;
			// Bubble sort
			case 'c':
				benchmark(bubble_sort_t, best_t, result, RESULT_ROWS);
				list_times("bubble sort: best\n", result);
				break;
			case 'd':
				benchmark(bubble_sort_t, worst_t, result, RESULT_ROWS);
				list_times("bubble sort: worst\n", result);
				break;
			case 'e':
				benchmark(bubble_sort_t, average_t, result, RESULT_ROWS);
				list_times("bubble sort: average\n", result);
				break;
			case 'f':
				benchmark(insertion_sort_t, best_t, result, RESULT_ROWS);
				list_times("insertion sort: best\n", result);
				break;
			case 'g':
				benchmark(insertion_sort_t, worst_t, result, RESULT_ROWS);
				list_times("insertion sort: worst\n", result);
				break;
			case 'h':
				benchmark(insertion_sort_t, average_t, result, RESULT_ROWS);
				list_times("insertion sort: average\n", result);
				break;
			case 'i':
				benchmark(quick_sort_t, best_t, result, RESULT_ROWS);
				list_times("quick sort: best\n", result);
				break;
			case 'j':
				benchmark(quick_sort_t, worst_t, result, RESULT_ROWS);
				list_times("quick sort: worst\n", result);
				break;
			case 'k':
				benchmark(quick_sort_t, average_t, result, RESULT_ROWS);
				list_times("quick sort: average\n", result);
				break;
			case 'l':
				benchmark(linear_search_t, best_t, result, RESULT_ROWS);
				list_times("linear search: best\n", result);
				break;
			case 'm':
				benchmark(linear_search_t, worst_t, result, RESULT_ROWS);
				list_times("linear search: worst\n", result);
				break;
			case 'n':
				benchmark(linear_search_t, average_t, result, RESULT_ROWS);
				list_times("linear search: average\n", result);
				break;
			case 'o':
				benchmark(binary_search_t, best_t, result, RESULT_ROWS);
				list_times("binary search: best\n", result);
				break;
			case 'p':
				benchmark(binary_search_t, worst_t, result, RESULT_ROWS);
				list_times("binary search: worst\n", result);
				break;
			case 'q':
				benchmark(binary_search_t, average_t, result, RESULT_ROWS);
				list_times("binary search: average\n", result);
				break;
			// Invalid input
			default:
				show_menu = false;
				ui_invalid_input();
				break;
		}
	}
	ui_exit();
}
