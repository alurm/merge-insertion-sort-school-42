#include <iostream>
#include <assert.h>
#include <map>

using std::cout;
using std::endl;
using std::map;
using std::multimap;
using std::make_pair;
using std::pair;

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

/*
{} {1, 5, 3, 2}
{} 1 {5, 3, 2}
{1} {5, 3, 2}
{1} 5 {3, 2}
{1, [5]} {3, 2}
1 < 5 ? insert : continue
{1, 5} {3, 2}
{1, 5} 3 {2}
{1, 5, [3]} {2}
5 < 3 ? insert : continue
{1, [3], 5} {2}
1 < 3 ? insert : continue
{1, 3, 5} {2}
{1, 3, 5} 2 {}
{1, 3, 5, [2]} {}
5 < 2 ? : continue
{1, 3, [2], 5} {}
3 < 2 ? : continue
{1, [2], 3, 5} {}
1 < 2 ? insert
{1, 2, 3, 5} {}

{1, 2, 3, 4, 5, 6, 7, 8} 4.5
{1, 2, 3} 4 {5, 6, 7, 8} 4.5
4 < 4.5 ? (4.5 < 5 ? insert : ...)
4 {5, 6, 7, 8} 4.5
*/
/*
{1, 2, 3, []} -42
{-42, 1, 2, 3}
*/
// Debil nazval. Unless?
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

void insert(int *numbers, int size, int x, int offset) {
	numbers += offset;
	size -= offset;
	insert(numbers, size, x);
}

/*int insert_at(int *numbers, int size, int x, int offset) {
	numbers += offset;
}*/

void test_insert() {
	int numbers[6] = {1, 2, 3, 4, 5};
	insert(numbers, 5, 10);
	for (int i = 0; i < 6; i++) {
		cout << numbers[i] << endl;
	}
}

// Binary insertion sort.
void sorted_insert(int *numbers, int size, int x) {
	insert(numbers, size, x, binary_search(numbers, size, x));
}

void test_insert_at() {
	int numbers[6] = {1, 2, 3, 4, 5};
	insert(numbers, 5, 10, 2);
	for (int i = 0; i < 6; i++) {
		cout << numbers[i] << endl;
	}
}

void test_binary_search() {
	int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	int size = sizeof numbers / sizeof *numbers;
	cout << binary_search(numbers, size, 0) << endl;
	cout << binary_search(numbers, size, 10) << endl;
	cout << binary_search(numbers, size, 5) << endl;
}

void test_insert_at_binary_search_helper(int insertee) {
	int numbers[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	int size = sizeof numbers / sizeof *numbers;
	size--;
	cout << "insertee: " << insertee << endl;
	cout << "at: " << binary_search(numbers, size, insertee) << endl;
	sorted_insert(numbers, size, insertee);
	insert(numbers, size, insertee, binary_search(numbers, size, insertee));
	for (int i = 0; i < 10; i++) {
		cout << numbers[i] << endl;
	}
	cout << endl;
}

void test_insert_at_binary_search() {
	test_insert_at_binary_search_helper(-25);
	test_insert_at_binary_search_helper(5);
	test_insert_at_binary_search_helper(1);
	test_insert_at_binary_search_helper(10);
	test_insert_at_binary_search_helper(9);
	test_insert_at_binary_search_helper(0);
}

namespace test_sorted_insert {

struct test_type {
	int *numbers;
	int size;
	int insertee;
	int *output;
} table[] = {
	{
		(int[1]){},
		0,
		5,
		(int[1]){5},
	},
	{
		(int[2]){1},
		1,
		0,
		(int[2]){0, 1},
	},
	{
		(int[2]){1},
		1,
		2,
		(int[2]){1, 2},
	},
	{
		(int[5]){1, 2, 4, 8},
		4,
		7,
		(int[5]){1, 2, 4, 7, 8},
	},
};

void test() {
	int table_size = sizeof table / sizeof *table;
	for (int i = 0; i < table_size; i++) {
		test_type t = table[i];
		sorted_insert(t.numbers, t.size, t.insertee);
		for (int j = 0; j < t.size + 1; j++) {
			assert(t.numbers[j] == t.output[j]);
		}
	}
}

}

void test_sequence_of_adders_to_power_of_two() {
	int goal = 1;
	int before = 0;
	int group_size = 0;
	for (int i = 0; i < 10; i++) {
		goal = goal * 2;
		before = group_size;
		group_size = goal - before;

		cout << group_size << endl;
	}
}

std::ostream &indent(int n) { for (int i = 0; i < n; i++) cout << "\t"; return cout; }

struct indexed {
	int value;
	int index;
};

#if 0
void merge_insert_sort_helper_pairs(indexed *numbers, int size, int depth, bool debug) {

	if (debug) { indent(depth) << "begin" << endl; }

	if (size == 0 || size == 1) return;
	
	int half = size / 2;

	bool odd = (size % 2) == 1; indexed the_odd; if (odd) the_odd = numbers[size - 1];

	indexed *less = new indexed[half];
	indexed *more = new indexed[half];

	for (int i = 0; i < half; i++) {
		indexed a = numbers[i * 2];
		indexed b = numbers[(i * 2) + 1];

		less[i] = (a < b) ? a : b;
		more[i] = (a > b) ? a : b;
	}

	if (debug) {
		indent(depth) << "less" << endl; for (int i = 0; i < half + odd; i++) indent(depth + 1) << less[i] << endl;
		indent(depth) << "more" << endl; for (int i = 0; i < half; i++) indent(depth + 1) << more[i] << endl;
	}

	// Information about pairings is lost here. May be preserved by storing indicies with the numbers.
	merge_insert_sort_helper_pairs(
		more,
		half,
		depth + 1,
		debug
	);

	/*// This is incorrect because we don't know what this is paired to.
	numbers[0] = less[0];

	for (int i = 0; i < half; i++) {
		numbers[i + 1] = more[i];
	}

	for (int i = 0; i < half + odd; i++) {
		sorted_insert(numbers, half + 1 + i, less[i]);
	}*/

	for (int i = 0; i < half; i++) numbers[i] = more[i];

	for (int i = 0; i < half; i++) sorted_insert(numbers, half + i, less[i]);

	if (odd) sorted_insert(numbers, half * 2, the_odd);

	/*int goal = 1;
	int before = 0;
	int group_size = 0;
	for (int i = 0; i < 10; i++) {
		goal = goal * 2;
		before = group_size;
		group_size = goal - before;

		...
	}*/

	delete[] less;
	delete[] more;
}
#endif

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

struct merge_insert_sort_helper_arguments { int *numbers; int size; int depth; bool debug; };

struct merge_insert_binary_insert_arguments {
	int *numbers; int size; int depth; bool debug;
	int *more;
	//map<int, int> m;
	pair<int, int> *pairs;
	int the_odd;
	bool odd;
	int half;
};

void merge_insert_binary_insert(
	merge_insert_binary_insert_arguments _
) {
	int *numbers = _.numbers; int size = _.size; int depth = _.depth; bool debug = _.debug; int *more = _.more; /*map<int, int> m = _.m;*/ int the_odd = _.the_odd; bool odd = _.odd; int half = _.half; pair<int, int> *pairs = _.pairs;

	/*// This is incorrect because we don't know what this is paired to.
	numbers[0] = less[0];

	for (int i = 0; i < half; i++) {
		numbers[i + 1] = more[i];
	}

	for (int i = 0; i < half + odd; i++) {
		sorted_insert(numbers, half + 1 + i, less[i]);
	}*/

	/*
	for (int i = 0; i < half; i++) numbers[i] = more[i];
	for (int i = 0; i < half; i++) sorted_insert(numbers, half + i, less[i]);
	if (odd) sorted_insert(numbers, half * 2, the_odd);
	*/

	//numbers[0] = m[more[0]];
	numbers[0] = lookup(pairs, more[0], half);
	for (int i = 0; i < half; i++) numbers[1 + i] = more[i];

	//for (int i = 0; i < half - 1; i++) sorted_insert(numbers, 1 + half + i, m[more[1 + i]]);

	int goal = 1;
	int before = 0;
	int group_size = 0;

	int offset = 0;
	if (debug) indent(depth) << "begin" << endl;
	while (offset < half - 1) {
		goal *= 2; before = group_size; group_size = goal - before;

		int shift = (half - 1) - (offset + group_size);
		if (shift > 0) shift = 0;
		if (debug) indent(depth) << "group size: " << group_size << endl;
		for (int i = 0; i < group_size && (offset + i < half - 1); i++) {
			//int final_index = 1 + offset + i;
			int final_index = 1 + offset + (group_size - 1 - i) + shift;
			if (debug) indent(depth) << final_index << endl;
			sorted_insert(
				numbers,
				1 + half + offset + i,
				//m[more[final_index]]
				lookup(pairs, more[final_index], half)
			);
		}
		offset += group_size;
	}
	if (debug) indent(depth) << "end" << endl;
	
	if (odd) sorted_insert(numbers, half * 2, the_odd);
}

void merge_insert_sort_helper(merge_insert_sort_helper_arguments _) {
	int *numbers = _.numbers; int size = _.size; int depth = _.depth; bool debug = _.debug;

	if (debug) { indent(depth) << "begin" << endl; }

	if (size == 0 || size == 1) return;
	
	int half = size / 2; // Verify that rounds down.

	bool odd = (size % 2) == 1; int the_odd; if (odd) the_odd = numbers[size - 1];

	/* Example.
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
			indent(depth + 1) << "key: " << pairs[i].first << endl;
			indent(depth + 1) << "value: " << pairs[i].second << endl;
		}
	}

	// Information about pairings is lost here. May be preserved by storing indicies with the numbers.
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
		.debug = 0,
	});
}

void test_merge_insert_sort() {
	int numbers[] = {3, 4, 6, 8, 5, 1, 9, 7, 2};
	int size = sizeof numbers / sizeof *numbers;
	//indent(0) << "numbers" << endl; for (int i = 0; i < size; i++) { indent(1) << numbers[i] << endl; }
	merge_insert_sort(numbers, size);
	for (int i = 0; i < size; i++) {
		cout << numbers[i] << endl;
	}
}

void test_merge_insert_sort_2() {
	int numbers[] = {54, 69, 25, 30, 81, 78, 63, 28, 38, 50, 93, 40, 85, 95, 32, 66, 64, 13, 36, 44, 5, 21, 89, 82, 58, 55, 8, 79, 68, 75, 10, 80, 73, 49, 41, 76, 46, 42, 56, 100, 65, 91, 57, 35, 90, 48, 86, 18, 98, 72, 37, 96, 52, 24, 6, 84, 71, 15, 12, 27, 2, 23, 53, 92, 94, 11, 26, 45, 88, 87, 60, 34, 47, 62, 33, 77, 29, 74, 17, 19, 31, 51, 83, 4, 22, 16, 39, 9, 67, 61, 3, 70, 97, 99, 14, 7, 59, 1, 20, 43,};
	int size = sizeof numbers / sizeof *numbers;
	//indent(0) << "numbers" << endl; for (int i = 0; i < size; i++) { indent(1) << numbers[i] << endl; }
	merge_insert_sort(numbers, size);
	for (int i = 0; i < size; i++) {
		cout << numbers[i] << endl;
	}
}

void test_merge_insert_sort_3() {
	int numbers[] = {4, 3, 2, 1};
	int size = sizeof numbers / sizeof *numbers;
	//indent(0) << "numbers" << endl; for (int i = 0; i < size; i++) { indent(1) << numbers[i] << endl; }
	merge_insert_sort(numbers, size);
	for (int i = 0; i < size; i++) {
		cout << numbers[i] << endl;
	}
}

void test_merge_insert_sort_4() {
	enum {
		size = 10000,
	};
	int numbers[size];// = {4, 3, 2, 1};
	for (int i = 0; i < size; i++) numbers[i] = i;
	//int size = sizeof numbers / sizeof *numbers;
	//indent(0) << "numbers" << endl; for (int i = 0; i < size; i++) { indent(1) << numbers[i] << endl; }
	merge_insert_sort(numbers, size);
	for (int i = 0; i < size; i++) {
		cout << numbers[i] << endl;
	}
}

void test_multimap() {
	typedef multimap<int, int> t;

	t m;
	m.insert(make_pair(1, 2));
	m.insert(make_pair(1, 3));
	m.insert(make_pair(1, 4));
	m.insert(make_pair(1, 2));
	m.insert(make_pair(1, 2));
	m.insert(make_pair(42, 99));

	std::pair<t::iterator, t::iterator> range = m.equal_range(1);
	t::iterator begin = range.first;
	t::iterator end = range.second;
	for (
		t::iterator current = begin;
		current != end;
		current++
	) {
		cout << "key: " << current->first << endl;
		cout << "value: " << current->second << endl;
	}
}

int main() {
	test_merge_insert_sort_4();
}
