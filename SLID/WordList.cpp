#include "WordList.h"
#include <time.h>


WordList::WordList()
{

  sumListItemsSize_ = 0;
  sumSetItemsSize_ = 0;

  wordList_ = new list<shared_ptr<Word> >;
  wordSet_ = new set<shared_ptr<Word> >;
  size_ = 0;
}
/**
 * Itinialize WordList object from given list<shared_ptr<Word>>* and its size
 */
WordList::WordList(list<shared_ptr<Word> > * wordList)
{
  wordList_ = wordList;
  for(list<shared_ptr<Word> >::iterator it = wordList->begin(); it != wordList->end(); ++it)
  {
    wordSet_->insert(*it);
    sumListItemsSize_ += (*it)->getSize();
  }
  size_ = wordList->size();
}


/**
 * Delete wordList_ list
 */
WordList::~WordList()
{
  delete wordList_;
  wordList_ = NULL;
  delete wordSet_;
  wordSet_ = NULL;
}

/**
 * Insert a word in the wordList
 * @param w word to be inserted
 */
void WordList::insert(shared_ptr<Word> w)
{
  wordList_->push_back(w);
  int size = w->getSize();
  sumListItemsSize_ += size;
  //check if it's a new element or if it was already inside the set.
  if(wordSet_->insert(w).second) sumSetItemsSize_+= size;
  size_++;
}



/**
 * Set the occurences vector of the WordList
 * @param v vector of ocurrences
 */
void WordList::setOccsVec(vector<pair< shared_ptr<Word>, int> > v)
{
  wordOccsVec_ = v;
}

/**
 * find if there is another ptr pointing to same object, if exists return it
 * @param  w ptr to searching w
 * @return   ptr to existing one or NULL if it doesnt exist.
 */
shared_ptr<Word> WordList::find(const shared_ptr<Word>w) const
{
  list<shared_ptr<Word>>* wl = getWordList();
  for(list<shared_ptr<Word> >::iterator it = wl->begin(); it != wl->end(); ++it)
  {
    if(*(*it) == *w) return *it;
  }
  return NULL;
}

/**
 * clear the Wordlist
 */
void WordList::clear()
{
  wordList_->clear();
  wordSet_->clear();
  sumListItemsSize_ = 0;
  sumSetItemsSize_ = 0;
  size_ = 0;
}

/**
 * Cross all elements of WordList
 * @return list of words pairs representing cartesian product of elements
 */
list< std::pair<shared_ptr<Word> , shared_ptr<Word> > > WordList::crossAllWords() 
{

  clock_t t;
  t = clock();

  list< std::pair<shared_ptr<Word>,shared_ptr<Word> > > result;
  list < shared_ptr<Word> > * wordList = getWordList();
  for(list< shared_ptr<Word> >::iterator it1 = wordList->begin(); it1!= wordList->end(); ++it1)
  {
    for(list< shared_ptr<Word> >::iterator it2 = wordList->begin(); it2!= wordList->end(); ++it2)
    {
      std::pair<shared_ptr<Word>, shared_ptr<Word> > p = make_pair(*it1, *it2);
      result.push_back(p);
    }
  }
  t = clock() - t;

  this->clear();
  // printf ("crossAllWords: It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
  return result;
}


// list<int> WordList::listOfStartPos() const
// {
//   list<int> res;
//   for(list<shared_ptr<Word>>::iterator it = wordList_->begin(); it!=wordList_->end(); ++it)
//   {
//     res.push_back((*it)->start)
//   }
// }

/**
 * Sum all the words lenght of the wordlist
 * @return sum
 */
int WordList::sumWordsLengthWithRepeats() const
{
  // int res = 0;
  // for(set<shared_ptr<Word>>::iterator it = wordSet_->begin(); it != wordSet_->end(); ++it)
  // {
  //   res += (*it)->getSize();
  // }
  // return res;
  return sumListItemsSize_;
}

/**
 * Sum all the words length without repeating words
 * @return sum
 */
int WordList::sumWordsLengthWithoutRepeats() const
{
  // int res = 0;
  // for(list<shared_ptr<Word>>::iterator it = wordList_->begin(); it != wordList_->end(); ++it)
  // {
  //   res += (*it)->getSize();
  // }
  // return res;
  return sumSetItemsSize_;
}


//Getters:

/**
 * get the wordList
 * @return wordList_
 */
list<shared_ptr<Word> >* WordList::getWordList() const
{
  return wordList_;
}

/**
 * get the wordList size
 * @return size_
 */
int WordList::getSize() const
{
  return size_;
}

/**
 * get the wordSet
 * @return wordSet_
 */
set<shared_ptr<Word> >* WordList::getWordSet() const
{
  return wordSet_;
}

vector<pair< shared_ptr<Word>, int> > WordList::getWordVec() const
{
  return wordOccsVec_;
}

/**
 * get the word position in the WordList
 * @param  w word
 * @return   pos
 */
int WordList::wordPos(shared_ptr<Word> w) const
{
  for(unsigned int i=0; i<wordOccsVec_.size();i++)
  {
    if (wordOccsVec_[i].first == w) return i;
  }

  return -1;
  // return std::distance(wordOccsVec_.begin(), wordOccsVec_.find(w));

}

// Print

/**
 * Overload << operator to cout the WordList
 */
ostream& operator<<(ostream& cout, const WordList &wL)
{
  list<shared_ptr<Word>> * wordList = wL.getWordList();

  cout << "Printing Word List..." << endl;
  for(list<shared_ptr<Word> >::iterator it = wordList->begin(); it != wordList->end(); ++it)
  {
    cout << *(*it) << endl;
  }

  return cout;
}
