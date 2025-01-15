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
	explicit unique_ptrs(T* ptr_p)noexcept : ptr{ ptr_p } {}
	unique_ptrs(const unique_ptrs& ptr) = delete;
	unique_ptrs(unique_ptrs&& ptr) = delete;

	const T* get_ptr()const noexcept { return ptr; }
	//�������� �������� 
	void set_ptr(const T* value)noexcept { *ptr = *value; }

	unique_ptrs& operator=(const unique_ptrs& ptr) = delete;

	//������� ������
	void del() 
	{
		if (!ptr) throw del_error("\n��������� ��������� �� ������ ��������\n");
		delete ptr; 
	}

	//���������� �������� ���������
	void print()const
	{
		if (!ptr) throw del_error("\n��������� ��������� �� ������ ��������\n");
		cout << *ptr;
	}

	T operator*()noexcept { return *ptr; }

	T* operator->()noexcept { return *ptr; }

	~unique_ptrs()noexcept = default;
};
