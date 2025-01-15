#pragma once
#include <iostream>
#include "del_error.h"

using namespace std;

template <class T>
class shared_ptrs
{
private:
	T* ptr;
	//������� ����������
	static int count;
public:
	shared_ptrs()noexcept = default;
	explicit shared_ptrs(T* ptr_p)noexcept : ptr{ ptr_p } { count++; }
	shared_ptrs(const shared_ptrs& ptr_p)noexcept;
	shared_ptrs(shared_ptrs&& ptr_p)noexcept;

	const T* get_ptr()const noexcept { return ptr; }
	//���������� ���������� ����������
	static int get_count() { return count; }
	//�������� �������� 
	void set_ptr(const T* value)noexcept { *ptr = *value; }
	shared_ptrs<T>& operator=(const shared_ptrs<T>& ptr_p)noexcept { *ptr = *ptr_p.ptr; }
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

	~shared_ptrs()noexcept = default;

};

template <class T> int shared_ptrs<T>::count{0};

template <class T> shared_ptrs<T>:: shared_ptrs(const shared_ptrs<T>& ptr_p)noexcept
{
	count++;
	*ptr = *ptr_p.ptr;
}

template <class T> shared_ptrs<T>::shared_ptrs(shared_ptrs&& ptr_p)noexcept
{
	count++;
	ptr = ptr_p.ptr;
	ptr_p.ptr = nullptr;
}