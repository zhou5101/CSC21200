/* This is the implementation file for the deque, where you will define how the
 * abstract functionality (described in the header file interface) is going to
 * be accomplished in terms of explicit sequences of C++ statements. */

#include "deque.h"
#include <stdio.h>
#include <cassert>

/* NOTE:
 * We will use the following "class invariants" for our data members:
 * 1. data points to a buffer of size cap.
 * 2. data[front_index,...,next_back_index-1] are the valid members of the
 *    deque, where the indexing is *circular*, and works modulo cap.
 * 3. the deque is empty iff front_index == next_back_index, and so we must
 *    resize the buffer *before* size == cap.  */

#ifndef INIT_CAP
#define INIT_CAP 4
#endif

deque::deque()
{
	/* setup a valid, empty deque */
	this->cap = INIT_CAP;
	this->data = new int[cap];
	this->front_index = 0;
	this->next_back_index = 0;
	/* NOTE: the choice of 0 is arbitrary; any valid index works. */
}
/* range constructor */
deque::deque(int* first, int* last)
{
	if (last <= first) return;
	this->cap = last - first + 1;
	this->data = new int[this->cap];
	this->front_index = 0;
	this->next_back_index = this->cap-1;
	for (size_t i = 0; i < this->cap-1; i++) {
		this->data[i] = first[i];
	}
}
/* l-value copy constructor */
deque::deque(const deque& D)
{
	/* TODO: write me.*/
	this->cap = D.cap;
	this->data = new int[cap];
	this->front_index = D.front_index;
	this->next_back_index = D.next_back_index;
	for (size_t i = 0; (i+D.front_index)%D.cap != D.next_back_index; i++) {
		size_t j =(i+D.front_index)%D.cap;
		this->data[j] = D.data[j];
	}
}
/* r-value copy constructor */
deque::deque(deque&& D)
{
	/* steal data from D */
	this->data = D.data;
	this->front_index = D.front_index;
	this->next_back_index = D.next_back_index;
	this->cap = D.cap;
	D.data = NULL;
}

deque& deque::operator=(deque RHS)
{
	/* TODO: write me.  See the r-value copy constructor for inspiration. */
	int* temp = this->data;
	this->data = RHS.data;
	RHS.data = temp;
	this->front_index = RHS.front_index;
	this->next_back_index = RHS.next_back_index;
	this->cap = RHS.cap;
	return *this;
}

deque::~deque()
{
	/* NOTE: to make the r-value copy more efficient, we allowed for the
	 * possibility of data being NULL. */
	if (this->data != NULL) delete[] this->data;
}

int deque::back() const
{
	/* for debug builds, make sure deque is nonempty */
	assert(!empty());
	/* TODO: write me. */
	return data[(next_back_index -1)%cap]; /* prevent compiler error. */
}

int deque::front() const
{
	/* for debug builds, make sure deque is nonempty */
	assert(!empty());
	/* TODO: write me. */
	return data[this->front_index]; /* prevent compiler error. */
}

size_t deque::capacity() const
{
	return this->cap - 1;
}

int& deque::operator[](size_t i) const
{
	assert(i < this->size());
	return this->data[(front_index + i) % cap];
}

size_t deque::size() const
{
	/* just compute number of elements between front and back, wrapping
	 * around modulo the size of the data array. */
	/* TODO: write me. */
	return (next_back_index - front_index) % cap; /* prevent compiler error. */
}

bool deque::empty() const
{
	return (next_back_index == front_index);
}

bool deque::needs_realloc()
{
	return ((next_back_index + 1) % cap == front_index);
}

void deque::push_front(int x)
{
	/* TODO: write me. */
	if (needs_realloc()||size() == capacity()) {
		int* newdata = new int[cap * 2];
		if (front_index > 0){
			for (size_t i = 0; (i+front_index)%cap != next_back_index; i++) {
				size_t j = (front_index+cap+i)%(2*cap);
				size_t k = (front_index+i)%cap;
				newdata[j] = data[k];
				}
			front_index += cap;
			}
		else{
			for(size_t i = 0; i+front_index!= next_back_index; i++){
				newdata[i+front_index] = data[i+front_index];
				}
			}
		delete[] data;
		data = newdata;
		cap *= 2;
		}
	front_index = (front_index-1)%cap;
	data[front_index] = x;
}

void deque::push_back(int x)
{
	/* TODO: write me. */
	if (needs_realloc()||size() == capacity()) {
		int* newdata = new int[cap * 2];
		if (front_index > 0){
			for (size_t i = 0; (i+front_index)%cap != next_back_index; i++) {
				size_t j = (front_index+cap+i)%(2*cap);
				size_t k = (front_index+i)%cap;
				newdata[j] = data[k];
				}
			front_index += cap;
			}
		else{
			for(size_t i = 0; i+front_index!= next_back_index; i++){
				newdata[i+front_index] = data[i+front_index];
				}
			}
		delete[] data;
		data = newdata;
		cap *= 2;
		}
	data[next_back_index] = x;
	next_back_index=(next_back_index+1)%cap;
}

int deque::pop_front()
{
	assert(!empty());
	/* TODO: write me. */
	front_index = (front_index+1)%cap;
	return 0; /* prevent compiler error. */
}

int deque::pop_back()
{
	assert(!empty());
	/* TODO: write me. */
	next_back_index = (next_back_index-1)%cap;
	return 0; /* prevent compiler error. */
}

void deque::clear()
{
	/* TODO: write me. */
	next_back_index = front_index = 0;
}

void deque::print(FILE* f) const
{
	for(size_t i=this->front_index; i!=this->next_back_index;
			i=(i+1) % this->cap)
		fprintf(f, "%i ",this->data[i]);
	fprintf(f, "\n");
}
