#include "header.h"

int binary_search(int *numbers, int size, int x) {
	if (size == 0) return 0;
	if (size == 1) {
		if (x < *numbers) return 0;
		return 1;
	}

	int half = size / 2;
	int middle = numbers[half];
	if (x < middle) {
		return binary_search(numbers, half, x);
	} else {
		numbers += half;
		return half + binary_search(numbers, size - half, x);
	}
}

// Inserts x as first element of numbers.
void insert(int *numbers, int size, int x) {
	int before;
	int after = x;
	for (int i = 0; i < size; i++) {
		before = numbers[i];
		numbers[i] = after;

		after = before;
	}
	numbers[size] = after;
}

// Inserts x as nth element of numbers.
void insert(int *numbers, int size, int x, int offset) {
	numbers += offset;
	size -= offset;
	insert(numbers, size, x);
}

// Binary lookup and insertion.
void sorted_insert(int *numbers, int size, int x) {
	insert(numbers, size, x, binary_search(numbers, size, x));
}

std::ostream &indent(int n) { for (int i = 0; i < n; i++) cout << "\t"; return cout; }

int lookup(pair<int, int> *pairs, int key, int size) {
	for (int i = 0; i < size; i++) {
		pair<int, int> pair = pairs[i];
		int key_in_pair = pair.first;
		int value_in_pair = pair.second;
		if (key_in_pair == key)
			return value_in_pair;
	}
	assert(0);
}

void merge_insert_binary_insert(
	merge_insert_binary_insert_arguments _
) {
	int *numbers = _.numbers;
	int size = _.size;
	int depth = _.depth;
	bool debug = _.debug;
	int *more = _.more;
	//map<int, int> m = _.m;
	int the_odd = _.the_odd;
	bool odd = _.odd;
	int half = _.half;
	pair<int, int> *pairs = _.pairs;

	for (int i = 0; i < half; i++) numbers[i] = more[i];

	limited_generator g(half);

	for (int count = 0; ; count++) {
		optional<int> o = g();
		if (!o.present) break;
		int index = o.value;
		int element = lookup(pairs, more[index], half);
		sorted_insert(numbers, half + count, element);
	}

	if (odd) sorted_insert(numbers, half * 2, the_odd);
}

void merge_insert_sort_helper(merge_insert_sort_helper_arguments _) {
	int *numbers = _.numbers;
	int size = _.size;
	int depth = _.depth;
	bool debug = _.debug;

	if (debug) { indent(depth) << "begin" << endl; }

	if (size == 0 || size == 1) return;

	int half = size / 2; // Verify that rounds down.

	bool odd = (size % 2) == 1; int the_odd; if (odd) the_odd = numbers[size - 1];

	/* An example.
	int numbers[] = {3, 8, |  6, 4, | 5, 1, | 9, 7, | 2};
	less = {3, 4, 1, 7};
	more = {8, 6, 5, 9};

	m = map[int]int{8: 3, 6: 4, 5: 1, 9: 7}

	// After sorting more.
	more = {5, 6, 8, 9};

	m[more[0]] == 1;
	numbers = {1, 5, 6, 8, 9, ...};

	i: {0, 1, 2}
	i = 0
	m[more[1 + i]] = m[more[1 + 0]] = m[more[1]] = m[6] = 4
	sorted_insert(numbers, 5, 4);
	for (int i = 0; i < 4 - 1; i++) sorted_insert(numbers, 1 + 4 + i, m[more[1 + i]]);
	*/

	int *less = new int[half];
	int *more = new int[half];

	for (int i = 0; i < half; i++) {
		int a = numbers[i * 2];
		int b = numbers[(i * 2) + 1];

		less[i] = (a < b) ? a : b;
		more[i] = (a > b) ? a : b;
	}

	// Assume that there are no duplicate numbers.
	//map<int, int> m;

	pair<int, int> *pairs = new pair<int, int>[half];
	for (int i = 0; i < half; i++) {
		//m[more[i]] = less[i];
		pairs[i] = make_pair(more[i], less[i]);
	}

	if (debug) {
		indent(depth) << "less" << endl; for (int i = 0; i < half + odd; i++) indent(depth + 1) << less[i] << endl;
		indent(depth) << "more" << endl; for (int i = 0; i < half; i++) indent(depth + 1) << more[i] << endl;

		indent(depth) << "pairs" << endl;
		for (int i = 0; i < half; i++) {
			indent(depth + 1) << pairs[i].first << ": " << pairs[i].second << endl;
		}
		indent(depth) << "end" << endl;
	}

	// This loses information about pairing, that is why we use pairs.
	merge_insert_sort_helper((merge_insert_sort_helper_arguments){
		.numbers = more,
		.size = half,
		.depth = depth + 1,
		.debug = debug
	});

	merge_insert_binary_insert((merge_insert_binary_insert_arguments){
		.numbers = numbers,
		.size = size,
		.depth = depth,
		.debug = debug,
		.more = more,
		//.m = m,
		.pairs = pairs,
		.the_odd = the_odd,
		.odd = odd,
		.half = half,
	});

	delete[] less;
	delete[] more;
	delete[] pairs;
}

void merge_insert_sort(int *numbers, int size) {
	merge_insert_sort_helper((merge_insert_sort_helper_arguments){
		.numbers = numbers,
		.size = size,
		.depth = 0,
		.debug = 1,
	});
}
