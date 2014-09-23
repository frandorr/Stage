#ifndef LLArray_H_
#define LLArray_H_

#include <ctype.h>
#include <iostream>

#include "IO.h"
#include "Utils.h"

using namespace std;

/**
 * Linked List array: random access in O(1)
 */

//TODO should also do the parsing!

#define ESCAPE '\\'

typedef int elem;

class LLArray{
public:
	LLArray(elem* arr, int size, int alph_size, int* inv);
	/**
	 * delete elem array passed to constructor
	 */
	virtual ~LLArray();
	elem at(int pos);
	/**
	 * return the next position of pos
	 * equivalent a next(pos, 1)
	 */
	int next(int pos);

	/**
	 * return the position of pos+len.
	 * If the goes out of the array, returns -1
	 * O(len)
	 */
	int next(int pos, int len);
	/**
	 * return the prev position of pos
	 */
	int prev(int pos);

	// modifies the structure
	void set(int pos, elem e);
	void jump_backward(int from, int to);
	void jump_forward(int from, int to);

	elem* get_intern();

	/**
	 * print len caracters starting from start
	 * @return length of sequence printed
	 */
	int print(int start, int len, ostream* out = output, bool newline=true);

	/**
	 * print whole sequence
	 * @return length of sequence printed
	 */
	int print(ostream* out = output);

	/**
	 * print caracter to_translate
	 */
	void print(int to_translate, ostream* out = output);

	int* give_next_inter();

	int size();

	void reduce_size(int amount);
	int get_real_size();

	/**
	 * return true if the position pos_to_translate correpond to a terminal caracter
	 */
	bool is_terminal(int to_translate);

	/** PRE: must correspond to a terminal
	 * return the caracter corresponding to the identifier in the position pos_to_translate
	 */
	char translate(int pos_to_translate);

private:
	elem* arr;
	int *next_;
	int *prev_;
	int alph_size;
	int* inv_alphabet;
	int seq_size;
	int real_size;

	int* real_to_abs;
	int *abs_to_real;

};

#endif /*LLArray_H_*/
