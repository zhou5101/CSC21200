/****************************************************
implementation file for the hash table class.
*****************************************************/

#include "hashtbl.h"
#include <iostream>
using std::endl;
using std::ostream;
#include <string.h> /* for strcpy */
#include <algorithm> /* for find */
using std::find;
using std::swap;
#include <iomanip>
using std::setfill;
using std::setw;
#include <cassert>

#define R32 (rand()*100003 + rand())
#define R64 (((uint64_t)R32 << 32) + R32)
#define TLEN ((size_t)(1 << this->nBits))

namespace csc212
{
	/* First we implement our hash family */
	hashTbl::hash::hash(unsigned rangebits, const uint32_t* a,
					const uint64_t* alpha, const uint64_t* beta) {
		this->rangebits = rangebits;
		if (a) {
			for (size_t i = 0; i < aLen; i++) {
				this->a[i] = a[i] | 1; /* make sure it is odd. */
			}
		} else {
			for (size_t i = 0; i < aLen; i++) {
				this->a[i] = R32 | 1;
			}
		}
		this->alpha = ((alpha) ? *alpha : R64) | 1;
		this->beta = ((beta) ? *beta : R64);
		/* only keep the low order bits of beta: */
		this->beta &= ((uint64_t)-1)>>(64 - rangebits);
	}
	uint64_t hashTbl::hash::operator()(const string& x) const {
		assert(x.length() <= 4*aLen);
		/* TODO: write the hash function. */
		string c = x;
		while (c.length()%8 != 0)
			c.push_back(0);

		const uint32_t* s = reinterpret_cast<const uint32_t*>(c.c_str());

		uint64_t left = 0, right = 0;
		uint64_t index = 0, product = 0;

		size_t bound = c.length()/8;

		for (size_t i = 0; i < bound; i++) {
			left = a[2*i]+s[2*i];
			right = a[2*i + 1] + s[2*i + 1];
			product += left * right;
		}

		index = (alpha * product + beta) >> (64-rangebits);

		return index;
	}

	//constructors:
	hashTbl::hashTbl(unsigned nBits, const uint32_t* ha,
					const uint64_t* halpha, const uint64_t* hbeta) :
		nBits(nBits),h(nBits,ha,halpha,hbeta)
	{
		this->table = new list<val_type>[TLEN];
	}

	hashTbl::hashTbl(const hashTbl& H)
	{
		/* TODO: write this */
		/* NOTE: the underlying linked list class has a working
		 * assignment operator! */
		this->nBits = H.nBits;
		this->h = H.h;
		this->table = new list<val_type>[TLEN];
		for (size_t i = 0; i < TLEN; i++) {
				this->table[i] = H.table[i];
		}

	}

	//destructor:
	hashTbl::~hashTbl()
	{
		delete[] this->table;
		//NOTE: this will call the destructor of each of the linked lists,
		//so there isn't anything else that we need to worry about.
	}

	//operators:
	hashTbl& hashTbl::operator=(hashTbl H)
	{
		/* TODO: write this */
		this->nBits = H.nBits;
		this->h = H.h;
		swap(this->table, H.table);
		return *this;
	}

	ostream& operator<<(ostream& o, const hashTbl& H)
	{
		for (size_t i = 0; i < H.tableLength(); i++) {
			o << "[" << setfill('0') << setw(2) << i << "] |";
			for (list<val_type>::iterator j = H.table[i].begin();
					j != H.table[i].end(); j++) {
				o << *j << "|";
			}
			o << endl;
		}
		return o;
	}

	void hashTbl::insert(val_type x)
	{
		/* TODO: write this */
		//Remember to check for uniqueness before inserting.
			if (!search(x))
			{
				table[h(x)].push_front(x);
			}
		}

	void hashTbl::remove(val_type x)
	{
		/* TODO: write this */
		if (search(x)) {
			table[h(x)].remove(x);
		}
	}

	void hashTbl::clear()
	{
		for(size_t i=0; i<TLEN; i++)
			this->table[i].clear();
	}

	bool hashTbl::isEmpty() const
	{
		/* TODO: write this */
		for (size_t i=0; i < TLEN; i++)
			if (table[i].size() != 0) return false;
		return true; // just so it compiles...
	}

	bool hashTbl::search(val_type x) const
	{
		/* TODO: write this */
		for (size_t i=0; i < TLEN; i++)
			if (table[i].size() != 0)
				if(find(table[i].begin(), table[i].end(),x)!=table[i].end())
					return true;
		return false; // just so it compiles...
	}

	size_t hashTbl::countElements() const
	{
		/* TODO: write this */
		size_t i, total = 0;
		if (isEmpty())
			return total;
		for (i = 0; i < TLEN; i++) {
			if (table[i].size() != 0)
				total += table[i].size();
		}
		return total; // just so it compiles...
	}

	size_t hashTbl::tableLength() const
	{
		return TLEN;
	}

	size_t hashTbl::countCollisions() const
	{
		//just count the number of lists of length > 1
		size_t i,nCollisions=0;
		for(i=0; i<TLEN; i++)
			if(table[i].size() > 1)
				++nCollisions;
		return nCollisions;
	}

	size_t hashTbl::longestListLength() const
	{
		/* TODO: write this */
		size_t i, max = 0;
		for (i = 0; i < TLEN; i++) {
			if (table[i].size() > max)
				max = table[i].size();
		}
		return max; // just so it compiles...
	}
}