#ifndef SUFFIXARRAY_H_
#define SUFFIXARRAY_H_

#include "SArray/SArray.h"
#include "Utils.h"
#include "IO.h"

using namespace std;

// Here all about the sequence: update, size, toString, toInt, read, etc

class SuffixArray
{
private:
	int* sequence_;
	int* sArray_;
	int* lcp_;
	int* inverse_;
	int size_;
	int maxAlph_;

	void makeSArray_();

public:
	SuffixArray(int* seq, int size, bool larsson, int maxAlph=-1);

	~SuffixArray();

	pair<int,int> search(int* s, int size);

	// Getters
	int getSize() const;
	int* getSArray() const;
	int* getLCP() const;



	int& operator[](int idx);
	const int& operator[](int idx) const;

	// Print
	friend ostream& operator<<(ostream& cout, SuffixArray &sArray);

};

#endif /* SUFFIXARRAY_H_*/
