#include <iostream>
#include <atomic>
#include <algorithm>
#include <cstddef>
#include <string>
using namespace std;

template <typename T>
class CommonPointer
{
private:
	T* ptr;
	atomic_uint* count;
public:
	CommonPointer()
	{
		ptr = nullptr;
		count = nullptr;
	};
	explicit CommonPointer(T* ptr)
	{
		ptr = ptr;
		count = new atomic_uint(1);
	};
	CommonPointer(const CommonPointer& arg)
	{
		count = nullptr;
		*this = arg;
	};
	CommonPointer(CommonPointer&& arg)
	{
		count = nullptr;
		*this = std::move(arg);
	};
	~CommonPointer()
	{
		if (count == nullptr)
			return;
		else
		{
			count--;
			if (!count)
			{
				delete ptr;
				delete count;
			}
		}

	};
	auto operator=(const CommonPointer& arg)->CommonPointer&
	{
		if (this == &arg)
			return *this;

		(*this).~CommonPointer();

		ptr = arg.ptr;
		count = arg.count;
		(*count)++;

		return *this;
	};
	auto operator=(CommonPointer&& arg)->CommonPointer&
	{
		if (this == &arg)
			return *this;

		this->~CommonPointer();

		ptr = arg.ptr;
		count = arg.count;
		arg.count = nullptr;
		arg.ptr = nullptr;

		return *this;
	};
	operator bool() const
	{
		return ptr != nullptr;
	};
	auto operator*() const->T&
	{
		return *ptr;
	};
	auto operator->() const->T*
	{
		return ptr;
	};
	auto get()->T*
	{
		return ptr;
	};
	void reset()
	{
		*this = CommonPointer();
	};
	void resetTo(T* ptr)
	{
		*this = CommonPointer(ptr);
	};

	void swap(CommonPointer& swaper)
	{
		std::swap(ptr, swaper.ptr);
		std::swap(count, swaper.count);
	};

	auto getCount() const->size_t
	{
		if (count != nullptr)
			return *count;
		else
			return 0;
	};
};
