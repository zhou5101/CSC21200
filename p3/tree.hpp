/* Simple binary search tree. */  //check out "boost" c++ libraries for examples, for advance use of the template
#pragma once
#include <cstddef> /* for size_t */
#include <cassert>

/* here's how to make your own templates: just prefix the declaration with
 * "template" followed by a list of type parameters.  E.g. for a tree node
 * we might use the following.  Note that 'K' is a *type* variable, so we
 * can declare things of type 'K' in the template. */
template <typename K>
struct node {
	K data;
	node<K>* left;
	node<K>* right;
	node(K d=K(), node* l=NULL, node* r=NULL) : data(d),left(l),right(r) {} //node<K> constructor
}; // a 

template <typename K>
class tree {
public:
	/* basic stuff: constructors, destructors, assignment... */
	tree();
	tree(const tree<K>& T);
	tree<K>& operator=(tree<K> T);
	~tree();

	bool search(K x) const;
	void insert(K x);
	void remove(K x);
	void clear(); /* remove all elements */

	/* * * * * * * statistics * * * * * * */
	K max() const;         /* maximal value */
	K min() const;         /* minimal value */
	size_t size() const;   /* total number of nodes */
	size_t height() const; /* longest path from root to leaf. */
	size_t leaves() const; /* returns number of leaf nodes */

	/* NOTE: we include a function that retuns the location of the root
	 * node, but we do so *by value*, and furthermore we make the pointee
	 * const.  Hence, without really going out of one's way, the state of the
	 * tree should not be easily modified via non-member functions (none of
	 * the internal pointers can be changed).  However, one could still do
	 * something ridiculous, like calling delete on one of the nodes, I
	 * guess.  But note that such things are present in the STL as well.
	 * E.g., you can get a copy of a vector's pointer to its (nominally
	 * behind the scenes) array simply by storing &V[0]. */
	node<K>* const rootptr() const;
	/* NOTE: our main application for this feature is that it allows us
	 * to draw the tree in a variety of formats (see main.cpp).  It's not
	 * clear how useful this is in general for a BST, but I hope you find
	 * it to have educational value.  */
private:
	node<K>* root;
};

/* NOTE: you must include, one way or another, the implementation right
 * along with the header.  We will put our implementation here in the same
 * file (named *.hpp) below.  To understand why, think about the following
 * question: what object code could the compiler possibly generate by
 * compiling a bunch of template functions and structs??
 * TODO: make sure you have a satisfactory understanding of this before
 * moving on to ANY of the programming.
 * */


/* to avoid typing out the template params for every function: */
#define TK template <typename K>

/* * * * * * * * * * basic dynamic set operations * * * * * * * * * */
TK void insert(node<K>*& n, K x)
{
	/* TODO: write me */
}
TK bool search(const node<K>* const& n, K x)
{
	/* TODO: write me */
	return false; /* avoid compilation errors/warnings */
}
TK void remove(node<K>*& n, K x)
{
	/* TODO: write me */
}

/* the tree's member functions will just hand off to those acting on
 * nodes (see above): */
TK void tree<K>::insert(K x)
{
	::insert(this->root,x);
}
TK bool tree<K>::search(K x) const
{
	return ::search(this->root,x);
}
TK void tree<K>::remove(K x)
{
	::remove(this->root,x);
}


/* "function pointer" type for things that operate on nodes: */
template <typename K>
using nodeProcFunc = void (*)(node<K>*& n, void* pParams);
/* NOTE: the above says that any function which accepts a node<K>*
 * by reference and returns void counts as a "nodeProcFunc".  Before,
 * we did this with a typedef statement, but that's no longer possible
 * once templates are involved.  */
/* version for const input: */
template <typename K>
using c_nodeProcFunc = void (*)(const node<K>* const& n, void* pParams);

/* * * * * * * * * * tree traversal functions * * * * * * * * * */
TK void preorder(node<K>*& n, nodeProcFunc<K> f, void* pParams)
{
	/* TODO: write me */
}
TK void inorder(node<K>*& n, nodeProcFunc<K> f, void* pParams)
{
	/* TODO: write me */
}
TK void postorder(node<K>*& n, nodeProcFunc<K> f, void* pParams)
{
	/* TODO: write me */
}
/* * * * * * * * * * traversal functions (const) * * * * * * * * * */
TK void preorder(const node<K>* const& n, c_nodeProcFunc<K> f, void* pParams)
{
	/* TODO: write me */
	/* NOTE: text of this function should be the same as the non-const */
}
TK void inorder(const node<K>* const& n, c_nodeProcFunc<K> f, void* pParams)
{
	/* TODO: write me */
	/* NOTE: text of this function should be the same as the non-const */
}
TK void postorder(const node<K>* const& n, c_nodeProcFunc<K> f, void* pParams)
{
	/* TODO: write me */
	/* NOTE: text of this function should be the same as the non-const */
}


/* * * * * * * * * * clear(), destructor * * * * * * * * * */
TK tree<K>::~tree()
{
	/* TODO: write me */
}
TK void tree<K>::clear()
{
	/* TODO: write me */
	/* NOTE: can you do this via a traversal? */
}


/* * * * * * * * * * constructors, assignment * * * * * * * * * */
/* default constructor: make an empty tree: */
TK tree<K>::tree()
{
	this->root = NULL;
}
TK tree<K>::tree(const tree<K>& T)
{
	/* TODO: write me */
	/* NOTE: maybe use a function like this:
	 * TK node<K>* copySubtree(const node<K>* const& s);
	 * and then use it to set this->root...
	 * */
}
TK tree<K>& tree<K>::operator=(tree<K> T)
{
	/* TODO: write me */
	/* NOTE: the plan is to let the copy constructor do the real work
	 * and we'll just steal it here. */
	return *this;
}

/* * *  * * * * * * statistics * * * * * * * * */
TK size_t tree<K>::size() const
{
	/* TODO: write me */
	/* NOTE: you can make a function that acts on nodes like this:
	 * TK size_t size(const node<K>* const& n);
	 * Or perhaps solve this via a traversal + a small function that
	 * is of type c_nodeProcFunc...
	 * */
	return 0; /* avoid compiler errors/warnings */
}
TK size_t tree<K>::leaves() const
{
	/* TODO: write me.  See remarks above for size */
	return 0; /* avoid compiler errors/warnings */
}
TK size_t tree<K>::height() const
{
	/* TODO: write me.  Maybe write function like this to help:
	 * TK size_t height(const node<K>* const& n);
	 * NOTE: we use the convention that the empty tree has height -1.
	 * */
	return 0; /* avoid compiler errors/warnings */
}
TK K tree<K>::min() const
{
	assert(this->root != NULL);
	/* TODO: write me. */
	return K(); /* avoid compiler errors/warnings */
}
TK K tree<K>::max() const
{
	assert(this->root != NULL);
	/* TODO: write me. */
	return K(); /* avoid compiler errors/warnings */
}

/* expose constant pointer to root node, which enables interesting
 * applications (via tree traversals, for example). */
TK node<K>* const tree<K>::rootptr() const
{
	return this->root;
}
