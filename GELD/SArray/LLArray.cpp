#include "LLArray.h"


/**
 * Linked List array: random access in O(1)
 */

//TODO should also do the parsing!

LLArray::LLArray(elem* arr, int size, int alph_size, int* inv){
	this->arr = arr;
	seq_size = size;
	real_size = size;
	this->alph_size = alph_size;
	next_ = new int[seq_size+1];
	prev_ = new int[seq_size+2];
	for(int i=0; i<seq_size+2;i++) prev_[i] = i-1;
	for(int i=0;i<seq_size+1;i++) next_[i] = i+1;
	inv_alphabet = inv;
	real_to_abs = new int[seq_size+2];
	abs_to_real = new int[seq_size+2];
	for(int i=0; i<seq_size+2;i++) real_to_abs[i] = abs_to_real[i] = i;
}

/**
 * delete elem array passed to constructor
 */
LLArray::~LLArray(){
	delete[] next_;
	delete[] prev_;
	delete[] arr;
	delete[] real_to_abs;
	delete[] abs_to_real;

}

/**
 * recalculate the real to abs and abs to real arrays.
 */
void LLArray::reduce_size(int amount){
	int apos = 0;
	for(int rpos = 0; rpos != seq_size+1; rpos = next_[rpos]){
		abs_to_real[apos] = rpos;
		real_to_abs[rpos] = apos;
		apos++;
	}

	real_size -= amount;
	assert(real_size == apos-1);

}

int LLArray::get_real_size(){
	return real_size;
}
elem LLArray::at(int pos){
	return arr[pos];
}
void LLArray::set(int pos, elem e){
	arr[pos] = e;
}
void LLArray::jump_backward(int from, int to){
	//assert(from < seq_size+1);
	prev_[from] = to;
}
void LLArray::jump_forward(int from, int to){
	next_[from] = to;
}
int LLArray::next(int pos){
	return next_[pos];
}

/**
 * O(1)
 */
int LLArray::next(int pos, int len){
	/*int ipos = pos;
	for(int i = 0; i<len && ipos != seq_size+1; i++) ipos = next_[ipos];
	return ipos;
	assert (ipos == (real_to_abs[pos]+len > real_size ? seq_size+1 : abs_to_real[real_to_abs[pos]+len]));*/
	return real_to_abs[pos]+len > seq_size ? seq_size+1 : abs_to_real[real_to_abs[pos]+len];
}
int LLArray::prev(int pos){
	return prev_[pos];
}

elem* LLArray::get_intern(){
	return arr;
}

/**
 * print len caracters starting from start
 */
int LLArray::print(int start, int len, ostream *whereprint, bool newline){
	int c;
	for(c=0; c++<len-1; start = next(start)){
		print(at(start),whereprint); *output << ' ';
	}
	print(at(start),whereprint);
	if(newline)*whereprint << endl;
	return c;
}

/**
 * print whole sequence
 */
int LLArray::print(ostream* whereprint){
	int i;
	int c=0;
	for(i=0; next(i)<seq_size; i = next(i)){
		print(at(i),whereprint); *whereprint << ' ';
		c++;
	}
	print(at(i),whereprint); *whereprint << endl;
	return c+1;
}


/**
 * print caracter to_translate
 */
void LLArray::print(int to_translate, ostream* out){
	if (to_translate <= alph_size){
		if (isdigit(inv_alphabet[to_translate])) *out << ESCAPE;
		*out << (char) inv_alphabet[to_translate];
	}
	else *out << to_translate;
	//out << ' ';
}

/**
 * return true if the position pos_to_translate correpond to a terminal caracter
 */
bool LLArray::is_terminal(int pos_to_translate){
	return at(pos_to_translate) <= alph_size;
}

/** PRE: must correspond to a terminal
 * return the caracter corresponding to the identifier in the position pos_to_translate
 */
char LLArray::translate(int pos_to_translate){
	assert(is_terminal(pos_to_translate));
	return inv_alphabet[at(pos_to_translate)];
}

int* LLArray::give_next_inter(){
	//TODO: eliminate this method
	return next_;
}

int LLArray::size(){
	return seq_size;
}
