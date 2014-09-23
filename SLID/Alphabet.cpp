#include "Alphabet.h" 

/**
 * Create new bimap alphabet with (A,0),(C,1),(G,2), (T,3) key-values
 */
Alphabet::Alphabet()
{
  const char *eol = "$";
  const char *pipe = "|";

  string streol(eol);
  string strpipe(pipe);

  alphabet_ = new bm_type;
  insert(streol, 1);
  insert(strpipe,2);
}

/**
 * Delete alphabet_
 */
Alphabet::~Alphabet()
{
	delete alphabet_;
}

/**
 * Insert new <k,value> to the alphabet
 * @param  k key
 * @param  i value
 * @return value added or if already exist old value.
 */
void Alphabet::insert(key k, value i)
{
  alphabet_->insert(bm_type::value_type(k, i));
}


// Getters:


/**
 * Get Alphabet size
 * @return int size_
 */
int Alphabet::getSize() const
{
	return alphabet_->size();
}

/**
 * get value from a given key
 * @param  k key
 * @return   value
 */
value Alphabet::getValue(key k) const
{
  return alphabet_->left.find(k)->second;
}

/**
 * get key from a given value
 * @param  v value
 * @return   key
 */
key Alphabet::getKey(value v) const
{
  return alphabet_->right.find(v)->second;
}

/**
 * get the bimap data struct where the alphabet is buid in
 * @return bimap alphabet_
 */
bm_type * Alphabet::getAlphBiMap() const
{
  return alphabet_;
}

// Print
 
/**
 * Overload << operator to cout the Alphabet
 */
ostream& operator<<(ostream& cout, const Alphabet &alph) 
{
  bm_type* map = alph.getAlphBiMap();

  cout << "Printing alphabet..." << endl;

  for( left_const_it left_iter = map->left.begin(), iend = map->left.end();
       left_iter != iend; ++left_iter )
  {
    cout << left_iter->first << "-->" << left_iter->second << endl;
  }

  cout << endl;

  cout << "Printing inv alphabet..." << endl;

  for( right_const_it right_iter = map->right.begin(), iend = map->right.end();
       right_iter != iend; ++right_iter )
  {
    cout << right_iter->first << "-->" << right_iter->second << endl;
  }

  return cout;
}
