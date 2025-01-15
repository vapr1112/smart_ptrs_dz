#include "unique_ptr.h"
#include "shared_ptrs.h"



int main()
{
	setlocale(LC_ALL, "rus");

	int value = 10, value_2 = 25;

	unique_ptrs <int> ptr{ &value };

	shared_ptrs <int> ptr_2{& value_2};

	shared_ptrs <int> ptr_3{ &value_2 };

	try
	{
		ptr.set_ptr(new int(15));

		ptr.print();

		cout << *ptr;

		cout << "\n" << *ptr_2 << "\n";

		cout << ptr_2.get_count();
	}

	catch (const del_error& del)
	{
		cout << del.what();
	}

	return 0;
}