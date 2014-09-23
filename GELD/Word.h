#ifndef WORD_H_
#define WORD_H_

//STL

//Boost

//User
#include "Utils.h"
#include "SubSequence.h"



using namespace std;

/*An WordList is a class that represents a list of words */


class Word: public SubSequence
{
private:
	// occs pos in the sequence
	list< int >* occPos_;


public:
	Word(const shared_ptr<Sequence> motherSeq, const int start, const int end, list<int>* occPos);
	~Word();

	// Getters

	list <int > * getOccPos() const;


	// Print
	friend ostream& operator<<(ostream& cout, const Word &w);

};

#endif /* WORDLIST_H_*/
