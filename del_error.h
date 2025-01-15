#pragma once
#include <exception>
#include <iostream>

using namespace std;

class del_error : public exception
{
private:
	string messege;
public:
	del_error()noexcept = default;

	del_error(string mes) : messege{mes}{}

	virtual const char* what() const noexcept final override { return messege.c_str(); }

	virtual ~del_error() = default;

};

