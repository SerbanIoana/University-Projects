#pragma once
#include <iterator>
#include <algorithm>


template <typename TElem>
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

	void add(const TElem& element);

	void update(int position, const TElem& element);

	void remove(int position);

	int get_size() const;
	
	TElem& get_position(int position);
	
	// assignment operator
	DynamicVector& operator = (const DynamicVector& new_vector);

	TElem& operator[] (int position);

private:
	void resize();
public:
	class iterator 
	{
	private:
		TElem* pointer = nullptr;
	public:
		iterator() = default;
		iterator(TElem* pointer_value ) : pointer{ pointer_value } {}
		TElem operator*();
		bool operator!=(const iterator& iterator_to_compare);
		typename iterator operator++();
		typename iterator operator++(int value);
		bool operator==(const iterator& iterator_to_compare);
	};

	public:
	typename iterator begin();
	typename iterator end();
};

//constructor
template <typename TElem>
inline DynamicVector<TElem>::DynamicVector(int capacity) : size{ 0 }, capacity{ capacity }
{
	elements = new TElem[capacity];
}

template <typename TElem>
inline DynamicVector<TElem>::DynamicVector(const DynamicVector& copy_vector)
{
	size = copy_vector.size;
	capacity = copy_vector.capacity;
	elements = new TElem[capacity];

	for (int i = 0; i < size; i++)
		elements[i] = copy_vector.elements[i];
}

template <typename TElem>
inline DynamicVector<TElem>::~DynamicVector()
{
	delete[] elements;
}

template <typename TElem>
inline void DynamicVector<TElem>::resize()
{
	capacity *= 2;

	TElem* new_elements = new TElem[capacity];
	for (int i = 0; i < size; i++)
		new_elements[i] = elements[i];

	delete[] elements;
	elements = new_elements;
}

template <typename TElem>
inline void DynamicVector<TElem>::add(const TElem& element)
{
	if (size == capacity)
	{
		resize();
	}
	elements[size++] = element;
}

template <typename TElem>
inline void DynamicVector<TElem>::update(int position, const TElem& element)
{
	elements[position] = element;
}

template <typename TElem>
inline void DynamicVector<TElem>::remove(int position)
{
	for (int i = position; i < size - 1; i++)
	{
		elements[i] = elements[i + 1];
	}
	size--;
}

template <typename TElem>
inline int DynamicVector<TElem>::get_size() const
{
	return size;
}

template <typename TElem>
inline TElem& DynamicVector<TElem>::get_position(int position)
{
	if (position >= size)
	{
		throw std::runtime_error("Invalid position!");
	}
	return elements[position];
}

template <typename TElem>
inline DynamicVector<TElem>& DynamicVector<TElem>::operator=(const DynamicVector& new_vector)
{
	if (this == &new_vector) {
		return *this;
	}
	this->capacity = new_vector.capacity;
	this->size = new_vector.size;
	delete[]this->elements;
	this->elements = new TElem[this->capacity];
	for (int i = 0; i < this->size; i++)
		this->elements[i] = new_vector.elements[i];
	return *this;
}

template <class TElem>
inline TElem& DynamicVector<TElem>::operator[](int position) {
	return elements[position];
}

//return the first position in elements
template <typename TElem>
inline typename DynamicVector<TElem>::iterator DynamicVector<TElem>::begin()
{
	return iterator{ this->elements };
}

//return the last position in elements
template <class TElem>
inline typename DynamicVector<TElem>::iterator DynamicVector<TElem>::end()
{
	return iterator{ elements + size };
}

template <class TElem>
inline TElem DynamicVector<TElem>::iterator::operator*()
{
	return *this->pointer;
}

template <class TElem>
inline bool DynamicVector<TElem>::iterator::operator!=(const iterator& iterator_to_compare)
{
	return this->pointer != iterator_to_compare.pointer;
}

template <class TElem>
inline typename DynamicVector<TElem>::iterator DynamicVector<TElem>::iterator::operator++()
{
	this->pointer++;
	return *this;
}

template <class TElem>
inline typename DynamicVector<TElem>::iterator DynamicVector<TElem>::iterator::operator++(int value)
{
	iterator new_iterator{ *this };
	this->pointer++;
	return *this;
}

template<typename TElem>
inline bool DynamicVector<TElem>::iterator::operator==(const iterator& iterator_to_compare)
{
	return !(this->pointer != iterator_to_compare.pointer);
}