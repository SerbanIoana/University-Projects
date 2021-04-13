#pragma once
#include "tape.h"

typedef Tape TElem;

class DynamicVector
{
private:
	TElem* elements;
	int size;
	int capacity;

public:
	// default constructor
	DynamicVector(int capacity = 10);
	// copy constructor
	DynamicVector(const DynamicVector& copy_vector);
	//destructor
	~DynamicVector();

	int add(const TElem& element);

	int update(const TElem& element);

	int remove(const std::string& title);

	int search(const std::string& title);

	// assignment operator
	DynamicVector& operator = (const DynamicVector& new_vector);

	TElem& get_position(int position);

	int get_size() const;

private:
	void resize(double factor = 2);

};