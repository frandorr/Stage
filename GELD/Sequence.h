#ifndef SEQUENCE_H_
#define SEQUENCE_H_

//STL
#include <list>
#include <stack>


//User
#include "Utils.h"
#include "SuffixArray.h"
#include "Alphabet.h"
#include "Word.h"
#include "WordList.h"
#include <memory>



using namespace std;

/*A Sequence is a class that represents the sequence to be compressed.
Its build over a SuffixArray for better performance*/

class SubSequence;

class Sequence : public std::enable_shared_from_this<Sequence>
{
private:
	SuffixArray* sArray_;
	char* sequence_;
	int* intSequence_;
	Alphabet *alph_;
	int size_;

	std::vector<int> delimiterPos_;
	//Methods

public:
	list<int>* getSubSeqOccPos(const SubSequence* word, int sArrayStartIndex, int sArrayEndIndex ) const;
	Sequence();
	~Sequence();
	int* toInt() const;
	void readFromFile(const char * filename);
	void createFromInt(int* intSeq, int size);

	std::shared_ptr<Sequence> getShared();


 	unordered_set< shared_ptr<Word> > * maximalRepeats();
 	void createWordsFromLimits(int seqIndex, int length, unordered_set<shared_ptr<Word> > *result);
 	void getSeparatorPos(list<int> &separator, int seqIndex,int length);

	list< pair<int,int> >* wordPosPairList(shared_ptr<Word> u, shared_ptr<Word> v) const;
  WordList* obtainWordsInside(list<std::pair<int,int> >* posPairs, int uSize);

  shared_ptr<Word> createSubWord(shared_ptr<Word> w, int start, int end);


  int groupNumber(int pos) const;
	// Getters
	int getSize() const;
	char* getSequence() const;
	int* getIntSequence() const;
	Alphabet * getAlphabet() const;
	SuffixArray* getSArray() const;

	//Overload[]
	int& operator[](int idx);
	const int& operator[](int idx) const;

	// Print
	friend ostream& operator<<(ostream& cout, const Sequence &seq);

};

#endif /* SEQUENCE_H_*/
