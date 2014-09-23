#ifndef SUBSEQUENCE_H_
#define SUBSEQUENCE_H_

#include "Utils.h"

using namespace std;

class Sequence;

class SubSequence
{
private:
	// The mother sequence
	shared_ptr<Sequence> motherSequence_;
	int startPos_;
	int size_;

public:
	SubSequence(shared_ptr<Sequence> motherSeq, const int start, const int end);
	~SubSequence();

	int* extractRangeFromSequence(const shared_ptr<Sequence> motherSeq, const int start, const int end) const;
	char* extractRangeFromCharSequence(const shared_ptr<Sequence> motherSeq, const int start, const int end) const;

	bool isInvalid() const;

	// Getters
	int getSize() const;
	int* getSubSequence() const;
	//Operators overloading
	bool operator==(const SubSequence& other) const;
	// Print
	friend ostream& operator<<(ostream& cout, const SubSequence &seq);

};

#endif /* SEQUENCE_H_*/
