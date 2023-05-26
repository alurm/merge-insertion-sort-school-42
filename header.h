#include <iostream>
#include <assert.h>
#include <map>

using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
using std::multimap;

int binary_search(int *numbers, int size, int x);

void insert(int *numbers, int size, int x);
void insert(int *numbers, int size, int x, int offset);

void sorted_insert(int *numbers, int size, int x);

struct merge_insert_binary_insert_arguments {
	int *numbers; int size; int depth; bool debug;
	int *more;
	//map<int, int> m;
	pair<int, int> *pairs;
	int the_odd;
	bool odd;
	int half;
};
void merge_insert_binary_insert(merge_insert_binary_insert_arguments);

struct merge_insert_sort_helper_arguments { int *numbers; int size; int depth; bool debug; };
void merge_insert_sort_helper(merge_insert_sort_helper_arguments);

void merge_insert_sort(int *numbers, int size);
