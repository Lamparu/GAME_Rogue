#pragma once
#ifndef VECTOR_H
#define VECTOR_H

namespace Prog4_Rogue {

	template <class T>
	class Vector
	{
		friend class VectorIt<T>;
	private:
		T *data;
		int size;
		int cap;
		int GetPos(const int&) const;
	public:
		typedef VectorIt<T> Iterator;
		Iterator begin();
		Iterator end();
		Iterator find(const int&) const;
		Vector(int = 1);
		Vector(Vector&);
		Vector operator=(const Vector&);
		int GetCapacity() const;
		int GetSize() const;
		T& operator [](int);
		void push_back(T);
		void clear();
		void create(const int &i);
		void remove(const int &i);
		void resize(const int &n);
		~Vector<T>(void);

	};

	template <class T>
	class VectorIt
	{
		//friend class Vector<T>;
	private:
		T *cur;
	public:
		VectorIt() : cur(0) {}
		VectorIt(T *n) : cur(n) {}
		bool operator!=(const VectorIt&) const;
		bool operator==(const VectorIt&) const;
		T& operator *();
		T* operator ->();
		VectorIt<T>& operator ++();
	};

	template<class T>
	int Vector<T>::GetPos(const int &s) const
	{
		for (int i = 0; i < size; ++i)
			if (i == s)
				return i;
		return -1;
	}

	template<class T>
	Vector<T>::Iterator Vector<T>::begin()
	{
		return Iterator(data.get());
	}

	template<class T>
	Vector<T>::Iterator Vector<T>::end()
	{
		return Iterator(data.get() + size);
	}

	template<class T>
	Vector<T>::Iterator Vector<T>::find(const int &s) const
	{
		int i = getPos(s);
		if (i < 0)
			i = size;
		return Iterator(this->arr + i);
	}

	template <class  T>
	Vector<T>::Vector(int n)
	{
		create(n);
	}

	template <class  T>
	Vector<T>::~Vector(void)
	{
		delete[] data;
	}

	template <class  T>
	int Vector<T>::GetSize(void) const
	{
		return size;
	}

	template <class  T>
	T& Vector<T>::operator[](int i)
	{
		return data[i];
	}

	template <class T>
	Vector<T> Vector<T>::operator=(const Vector&a)
	{
		size = a.size;
		for (int i = 0; i != a.size; ++i) {
			this->date[i] = a.data[i];
		}
		return *this;
	}

	template<class T>
	bool VectorIt<T>::operator!=(const VectorIt &v) const
	{
		return cur != v.cur;
	}

	template <class T>
	bool VectorIt<T>::operator==(const VectorIt &v) const
	{
		return cur == v.cur;
	}

	template<class T>
	T & VectorIt<T>::operator*()
	{
		return *cur;
	}

	template<class T>
	T * VectorIt<T>::operator->()
	{
		return cur;
	}

	template<class T>
	VectorIt<T>& VectorIt<T>::operator++()
	{
		++cur;
		return *this;
	}

	template <class T>
	Vector<T>::Vector(Vector&a) {
		this->size = a.size;
		for (int i = 0; i != a.size; ++i) {
			this->date[i] = a.data[i];
		}
	}

	template <class T>
	void Vector<T>::push_back(T val) {
		T* newdata;
		if (size > cap) {
			cap = cap * 2;
			newdata = new T[cap];
			for (int i = 0; i < size; i++)
				newdata[i] = data[i];
			delete[] data;
			data = newdata;
		}
		data[size] = val;
		size++;
	}

	template <class  T>
	int Vector<T>::GetCapacity() const
	{
		return cap;
	}

	template <class  T>
	void Vector<T>::remove(const int &i)
	{
		T* newdata = new T[cap];
		bool f = false;

		for (int j = 0; j < this->size; j++)
		{
			if (j == i)
			{
				f = true;
			}
			if (f)
			{
				newdata[j - 1] = this->data[j];
			}
			else {
				newdata[j] = this->data[j];
			}
		}
		this->size -= 1;
		delete[] this->data;
		this->data = newdata;
	}

	template <class  T>
	void Vector<T>::resize(const int &n)
	{
		T* newdata = new T[n];
		this->cap = n;
		this->size = n > this->size ? this->size : n;
		for (int i = 0; i < this->size; i++)
		{
			newdata[i] = this->data[i];
		}
		delete[] this->data;
		this->data = newdata;
	}


	template <class  T>
	void Vector<T>::clear()
	{
		delete[] this->data;
		this->size = 0;
		this->cap = 1;
		this->data = new T[1];
	}

	template <class  T>
	void Vector<T>::create(const int &i) {
		if (this->data)
			delete[] data;
		size = 0;
		cap = i;
		data = new T[i];
	}
}
#endif