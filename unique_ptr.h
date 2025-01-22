#pragma once
#include <iostream>
#include "del_error.h"

using namespace std;

//уникальный указатель (можно создать лишь один указатель на один адрес)
template <class T>
class unique_ptrs
{
private:
	T* ptr;
public:
	unique_ptrs()noexcept = default;
	explicit unique_ptrs(T* ptr_p)noexcept : ptr{ ptr_p } 
	{
		ptr_p = nullptr;
		delete ptr_p;
	}
	unique_ptrs(const unique_ptrs& ptr) = delete;
	unique_ptrs(unique_ptrs&& ptr_p)
	{
		ptr = ptr_p.ptr;
		ptr_p.ptr = nullptr;
		delete ptr_p.ptr;
	}

	const T* get_ptr()const noexcept { return ptr; }
	//изменяет значение 
	void set_ptr(const T* value)noexcept 
	{
		*ptr = *value;
		delete value;
	}

	unique_ptrs& operator=(const unique_ptrs& ptr) = delete;

	unique_ptrs&& operator=(const unique_ptrs&& ptr_p)
	{
		ptr = ptr_p.ptr;
		delete ptr_p.ptr;
	}

	//очищает память
	void del() 
	{
		if (!ptr) throw del_error("\nуказатель указывает на пустое значение\n");
		delete ptr; 
	}

	//показывает значение указателя
	void print()const
	{
		if (!ptr) throw del_error("\nуказатель указывает на пустое значение\n");
		cout << *ptr;
	}

	T operator*()noexcept { return *ptr; }

	T* operator->()noexcept { return *ptr; }

	~unique_ptrs()noexcept = default;
};