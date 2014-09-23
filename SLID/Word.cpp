#include "Word.h"



/**
 * Itinialize father SubSequence class and assign occPos_
 */
Word::Word(const shared_ptr<Sequence> motherSeq, const int start, const int end, list<int> * occPos)
           : SubSequence(motherSeq, start, end)
{
  occPos_ = occPos;
}


/**
 * Delete occPos_ list
 */
Word::~Word()
{
  delete occPos_;
  occPos_ = NULL;
}



// Methods:


//Getters:

/**
 * get the word occs positions in Sequence
 * @return occPos_
 */
list<int> * Word::getOccPos() const
{
  return occPos_;
}


// Print

/**
 * Overload << operator to cout the SubSequence
 */
ostream& operator<<(ostream& cout, const Word &word)
{
  int* intS = word.getSubSequence();
  int size = word.getSize();

  cout << endl << "--- WORD ---" << endl;
  for(int i=0; i<size;i++)
  {
    cout << intS[i] << " ";
    // cout << toChar(intS[i]) << " ";
  }
  cout << endl;
  list<int>* occs = word.getOccPos();
  if(occs != NULL)
  {
    cout << endl << "--- POS IN SEQ ---" << endl;
    for(list<int>::iterator it = occs->begin(); it != occs->end(); ++it )
    {
      cout << *it << " ";
    }
    cout << endl;

  }
  return cout;
}
