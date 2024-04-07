#include <iostream>
#include <assert.h>
#include <map>
#include <cmath>

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

// Will generate an infinite stream.
class generator {
	int comparisons_limit, previously_inserted, instruction, i, largest_group_index;

public:
	generator() : comparisons_limit(0), previously_inserted(0), instruction(0) {}

	int operator()() { switch (instruction) {
		beginning: case 0:
		largest_group_index =
			std::pow(2, comparisons_limit) - 1 // 0, 1, 3, 7, 15, ...
			- previously_inserted // The more were inserted, the less we can insert now.
			+ 1 // Since when searching the index inself will not be considered.
		;

		for (i = largest_group_index; i > previously_inserted; i--) {
			instruction = __LINE__; return i - 1; case __LINE__:;
		}

		comparisons_limit++;
		previously_inserted = largest_group_index;
		default:
		goto beginning;
	} }
};

template<class t> struct optional {
	t value;
	bool present;
	optional() : present(false) {}
	optional(t value) : value(value), present(true) {}
	t operator()() { return value; }
};

// Will take a limit and skip elements over the limit.
// Returns optional<int>() when done.
class limited_generator {
	generator g;
	const int limit;
	int count;
public:
	limited_generator(int limit) : limit(limit), count(0) {}

	optional<int> operator() () {
		if (count == limit) return optional<int>();
		for (;;) {
			int n = g();
			if (n < limit) {
				count++;
				return optional<int>(n);
			}
		}
	}
};
