#pragma once
#include <iostream>
#include "del_error.h"

using namespace std;

//���������� ��������� (����� ������� ���� ���� ��������� �� ���� �����)
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
	}
	unique_ptrs(const unique_ptrs& ptr) = delete;
	unique_ptrs(unique_ptrs&& ptr_p)
	{
		ptr = ptr_p.ptr;
		ptr_p.ptr = nullptr;
	}

	const T* get_ptr()const noexcept { return ptr; }
	//�������� �������� 
	void set_ptr( T* value)noexcept 
	{
		if (!ptr)
		{
			delete[] ptr;
		}
		ptr = value;
		value = nullptr;
	}

	unique_ptrs& operator=(const unique_ptrs& ptr) = delete;

	unique_ptrs&& operator=(const unique_ptrs&& ptr_p)
	{
		if (this != ptr_p)
		{
			if (!ptr_p.ptr)
			{
				delete[] ptr;
			}
			ptr = ptr_p.ptr;
			ptr_p.ptr = nullptr;
		}

	}

	//������� ������
	void del() 
	{
		if (!ptr) throw del_error("\n��������� ��������� �� ������ ��������\n");
		delete[] ptr; 
	}

	//���������� �������� ���������
	void print()const
	{
		if (!ptr) throw del_error("\n��������� ��������� �� ������ ��������\n");
		cout << *ptr;
	}

	T operator*()noexcept { return *ptr; }

	T* operator->()noexcept { return *ptr; }

	~unique_ptrs()noexcept { delete[] ptr; }
};