#include "SubSequence.h"
#include "Sequence.h"

/**
 * Given a sequence, do the logic to find a a subsequence of it and construct
 * a SubSequence object. It's [start, end)
 * @param motherSeq
 * @param start, a start index of the subsequence
 * @param end, an end index, the closest to start
 */
SubSequence::SubSequence(shared_ptr<Sequence> motherSeq, const int start, const int end)
{
	motherSequence_ = motherSeq;
  startPos_ = start;
  size_ = end - start;

}

/**
 * delete subSequence. motherSeq is deleted in Sequence destructor
 */
SubSequence::~SubSequence()
{

}


/**
 * extract an int subsequence delimited by a range from the sequence
 * @param  motherSeq sequence from we extract
 * @param  start     start index
 * @param  end       end index
 * @return           return in subsequence
 */
int* SubSequence::extractRangeFromSequence(const shared_ptr<Sequence> motherSeq,
																					const int start, const int end) const
{
	int subSize = end-start;
	int* subSequence = new int[subSize];
  int* seq = motherSeq->getIntSequence();

  for(int i=0; i<subSize; i++)
  {
    subSequence[i] = seq[start+i];
  }
  return subSequence;
}

/**
 * given a range (start-end), extract the characters within this range from
 * the sequence
 * @param  motherSeq sequence
 * @param  start     
 * @param  end       
 * @return           characters in range
 */
char* SubSequence::extractRangeFromCharSequence(const shared_ptr<Sequence> motherSeq,
                                          const int start, const int end) const
{
  int subSize = end-start;
  char* subSequence = new char[subSize];
  char* seq = motherSeq->getSequence();

  for(int i=0; i<subSize; i++)
  {
    subSequence[i] = seq[start+i];
  }
  return subSequence;
}

/**
 * Say if a subsequence is invalid (if it has a pipe or a $ is invalid)
 * @return true if invalid
 */
bool SubSequence::isInvalid() const
{
  int end = startPos_ + size_ ;

  if (end > motherSequence_->getSize())
  {
    return true;
  }

  int * subSeq = getSubSequence();

  for(int i = 0; i<size_; i++)
  {
    int current = subSeq[i];
    if ((current == 1) || (current == 2))
    {
      return true;
    }
  }
  return false;
}

//Getters

/**
 * get the int representation of the subsequence
 * @return int* subSequence_
 */
int* SubSequence::getSubSequence() const
{
	return &(*motherSequence_)[startPos_] ;
}


/**
 * get the size of the subsequence
 * @return int size_
 */
int SubSequence::getSize() const
{
	return size_;

}

// Operators Overloading

/**
 * equality overloading. Be careful, just check if both has the same characters
 * in the same order, but no if they are in the same position of motherSequence.
 * Complexity: O(|left subSequence|)
 */
bool SubSequence::operator==(const SubSequence& other) const
{
  if((this->size_ != other.size_ ) ||
        (this->motherSequence_ != other.motherSequence_))
  {
    return false;
  }

  return (this->startPos_ == other.startPos_);
}

// Print

/**
 * Overload << operator to cout the SubSequence
 */
ostream& operator<<(ostream& cout, const SubSequence &seq)
{
  if(seq.startPos_ != -1)
  {
  	int* intS = seq.getSubSequence();
  	int size = seq.getSize();

    cout << "Printing int SubSequence..." << endl;
    for(int i=0; i<size;i++)
    {
    	cout << intS[i] << " ";
    } 
  }
  else
  {
    cout << "e ";
  }
  return cout;
}
