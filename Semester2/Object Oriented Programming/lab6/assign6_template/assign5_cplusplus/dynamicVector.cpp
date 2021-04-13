#include "dynamicVector.h"
#include "tape.h"
#include <iostream>

DynamicVector::DynamicVector(int capacity)
{
	this->size = 0;
	this->capacity = capacity;
	this->elements = new TElem[capacity];
}

DynamicVector::DynamicVector(const DynamicVector& copy_vector)
{
	this->size = copy_vector.size;
	this->capacity = copy_vector.capacity;
	this->elements = new TElem[this->capacity];
	for (int i = 0; i < this->size; i++)
		this->elements[i] = copy_vector.elements[i];
}

DynamicVector::~DynamicVector()
{
	delete[] this->elements;
}

DynamicVector& DynamicVector::operator=(const DynamicVector& new_vector)
{
	if (this == &new_vector)
		return *this;
	this->size = new_vector.size;
	this->capacity = new_vector.capacity;

	delete[] this->elements;
	this->elements = new TElem[this->capacity];
	for (int i = 0; i < this->size; i++)
		this->elements[i] = new_vector.elements[i];
	return *this;
}

TElem& DynamicVector::get_position(int position)
{
	return this->elements[position];
}

void DynamicVector::resize(double factor)
{
	this->capacity *= static_cast<int>(factor);

	TElem* new_elements = new TElem[this->capacity];
	for (int i = 0; i < this->size; i++)
		new_elements[i] = this->elements[i];

	delete[] this->elements;
	this->elements = new_elements;
}

int DynamicVector::get_size() const
{
	return this->size;
}

int DynamicVector::add(const TElem& e)
{
	if (this->size == this->capacity)
		this->resize();
	if (this->search(e.get_title()) == -1)
	{
		this->elements[this->size] = e;
		this->size++;
		return 1;
	}
	else
		return 0;
}

int DynamicVector::update(const TElem& element)
{
	std::string new_filmedAt, new_footagePreview;
	int position = search(element.get_title());
	if (position != -1)
	{
		new_filmedAt = element.get_filmedAt();
		new_footagePreview = element.get_footagePreview();
		this->elements[position].set_filmedAt(new_filmedAt);
		this->elements[position].set_creationDate(element.get_creationDate());
		this->elements[position].set_accessCount(element.get_accessCount());
		this->elements[position].set_footagePreview(new_footagePreview);
		return 1;
	}
	else
		return 0;
}

int DynamicVector::remove(const std::string& title)
{
	int position = search(title);
	if (position != -1)
	{
		for (int i = position; i < this->size - 1; i++)
		{
			this->elements[i] = this->elements[i + 1];
		}
		this->size--;
		return 1;
	}
	else
		return 0;
}

int DynamicVector::search(const std::string& title)
{
	for (int i = 0; i < this->size; i++)
	{
		if (this->elements[i].get_title() == title)
			return i;
	}
	return -1;
}
