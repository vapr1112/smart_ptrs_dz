#pragma once
#include <iostream>
#include "del_error.h"
#include <map>

using namespace std;

template <class T>
class shared_ptrs
{
private:
	T* ptr;
	//счетчик указателей
	static int count;
	static map <T*, int> ptrs;
public:
	shared_ptrs()noexcept = default;
	explicit shared_ptrs(T* ptr_p)noexcept : ptr{ ptr_p } 
	{ 
		ptrs[ptr]++;

		if (!ptrs.count(ptr))
		{
			ptrs[ptr] = 1;
		}

		else
		{
			ptrs[ptr]++;
		}
	}
	shared_ptrs(const shared_ptrs& ptr_p)noexcept;
	shared_ptrs(shared_ptrs&& ptr_p)noexcept;

	const T* get_ptr()const noexcept { return ptr; }
	//показывает количество указателей
	int get_count() { return ptrs[ptr]; }
	//изменяет значение 
	void set_ptr(const T* value)noexcept 
	{ 
		if (!ptr)
		{
			delete[] ptr;
		}
		ptr = value; 
	}
	shared_ptrs<T>& operator=(const shared_ptrs<T>& ptr_p)noexcept 
	{
		ptr = ptr_p.ptr; 
		ptrs[ptr]++;
	}
	//очищает память
	void del()
	{
		if (!ptr) throw del_error("\nуказатель указывает на пустое значение\n");
		delete[] ptr;
		ptrs[ptr]--;
	}
	//показывает значение указателя
	void print()const
	{
		if (!ptr) throw del_error("\nуказатель указывает на пустое значение\n");
		cout << *ptr;
	}

	T operator*()noexcept { return *ptr; }

	T* operator->()noexcept { return *ptr; }

	~shared_ptrs()noexcept
	{
		ptrs[ptr]--;
		if (ptrs[ptr] == 0)
		{
			delete[] ptr;
		}
	}

};

template <class T> int shared_ptrs<T>::count{0};

template <class T> map <T*, int> shared_ptrs<T>::ptrs;

template <class T> shared_ptrs<T>:: shared_ptrs(const shared_ptrs<T>& ptr_p)noexcept
{
	ptrs[ptr]++;
	ptr = ptr_p.ptr;
}

template <class T> shared_ptrs<T>::shared_ptrs(shared_ptrs&& ptr_p)noexcept
{
	ptrs[ptr]++;
	ptr = ptr_p.ptr;
	ptr_p.ptr = nullptr;
}