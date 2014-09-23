#ifndef ALPHABET_H_
#define ALPHABET_H_

#include "Utils.h"

// Boost bimap
#include <boost/bimap.hpp>


using namespace std;

typedef std::string key;
typedef int value;
typedef boost::bimap< key, value > bm_type;
typedef bm_type::value_type value_type;
typedef bm_type::left_map::const_iterator left_const_it;
typedef bm_type::right_map::const_iterator right_const_it;

/*An Alphabet is a class that represents the symbols alphabet */

class Alphabet
{
private:
	bm_type * alphabet_; //boost bimap <key, value> 

	// SuffixArray* getSArray() const; //private? I don't use it outside Sequence class... actually I didn't need this.

public:
	Alphabet();
	~Alphabet();

	void insert(key k, value i);

	// Getters
	int getSize() const;
	bm_type * getAlphBiMap() const;

	value getValue(key k) const;
	key getKey(value v) const;


	// Print
	friend ostream& operator<<(ostream& cout, const Alphabet &alph);

};

#endif /* ALPHABET_H_*/
