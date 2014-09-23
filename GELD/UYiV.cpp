#include "UYiV.h"

/**
 * Itinialize UYiV object from given word u and word v and a WordList y
 */
UYiV::UYiV(shared_ptr<Word> u, shared_ptr<Word> v, WordList* y, list <std::pair<int,int> > * wordPosPairs)
{
  u_ = u;
  v_ = v;
  y_ = y;
  wordPosPairs_ = wordPosPairs;
}


/**
 * Delete u_, v_ and y_
 */
UYiV::~UYiV()
{
  delete y_;
  y_ = NULL;
  delete wordPosPairs_;
  wordPosPairs_ = NULL;
}


//TODO: it's wrong.
// int UYiV::getEncoding() const
// {
//   int res = 0;
//   list<pair<int,int > > * wp = y_->getWordsPosPairs();
//   list<pair<int,int > >::iterator next;
//   next = boost::next(wp->begin());
//   for(list<pair<int,int > >::iterator it = wp->begin(); it!=wp->end(); it++)
//   {
//     if(next!=wp->end())
//     {
//       if(*it != *next)
//       {
//         res++;
//       }
//     next++;
//     }
//   }

//   return res;
  
// }


//Getters:

/**
 * get u context shared_ptr<Word>
 * @return u_
 */
shared_ptr<Word> UYiV::getU() const
{
  return u_;
}

/**
 * get v context shared_ptr<Word>
 * @return v_
 */
shared_ptr<Word> UYiV::getV() const
{
  return v_;
}

/**
 * get the insides Words from contexts u-v
 * @return WordList with insides
 */
WordList* UYiV::getYList() const
{
  return y_;
}

/**
 * get the list of ordered pairs from (pos(u), pos(v)) that we actually uses
 * @return wordPosPairs_
 */
list <std::pair<int,int> >* UYiV::getWordsPosPairs() const
{
  return wordPosPairs_;
}

// Print

/**
 * Overload << operator to cout the WordList
 */
ostream& operator<<(ostream& cout, const UYiV &uyv)
{
  shared_ptr<Word> u = uyv.getU();
  shared_ptr<Word> v = uyv.getV();
  WordList* y = uyv.getYList();


  cout << endl << "==== UYV ====" << endl << endl;
  cout << "--- U CONTEXT ---" << endl << *u << endl;
  cout << "--- V CONTEXT ---" << endl << *v << endl;
  cout << "--- Y LIST ---" << endl << *y << endl;
  cout << "--- WordPosPairs ---" << endl; 
  for(list <std::pair<int,int> >::iterator it = uyv.getWordsPosPairs()->begin();
                                          it != uyv.getWordsPosPairs()->end();++it)
  {
    cout << "(" << (*it).first << "," << (*it).second << ")" << " ";

  }  
  cout << endl;

  return cout;
}
