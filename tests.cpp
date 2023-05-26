#include "header.h"

#include <map>

using std::map;

/*
Example of insertion sort.
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

{1, 2, 3, []} -42
{-42, 1, 2, 3}
*/
void test_insert() {
	int numbers[6] = {1, 2, 3, 4, 5};
	insert(numbers, 5, 10);
	for (int i = 0; i < 6; i++) {
		cout << numbers[i] << endl;
	}
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
	merge_insert_sort_helper((merge_insert_sort_helper_arguments){
		.numbers = numbers,
		.size = size,
		.depth = 0,
		.debug = 1,
	});
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
	test_merge_insert_sort_2();
}
