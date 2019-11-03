

#include <gtest/gtest.h>
#include <Shared.hpp>

TEST(SharedPtr, FromPointer)
{
	int buff_int = 100;
	std::string buff_string = "tests";
	auto *ptr_int = new int(buff_int);
	auto *ptr_string = new std::string(buff_string);
	auto shared_ptr_int = SharedPtr<int>(ptr_int);
	auto shared_ptr_string = SharedPtr<std::string>(ptr_string);
	auto shared_ptr_null = SharedPtr<int>();
	auto shared_ptr_int_Copy = shared_ptr_int;
	EXPECT_EQ(shared_ptr_int_Copy.get(), ptr_int);
	EXPECT_EQ(shared_ptr_int_Copy.use_count(), 2);
	auto shared_ptr_int_Move = SharedPtr<int>(std::move(shared_ptr_int_Copy));
	EXPECT_EQ(shared_ptr_int_Move.get(), ptr_int);
	EXPECT_EQ(shared_ptr_int_Move.use_count(), 2);
	EXPECT_EQ(shared_ptr_int_Copy.get(), nullptr);
	EXPECT_EQ(static_cast<bool>(shared_ptr_int), true);
	EXPECT_EQ(static_cast<bool>(shared_ptr_string), true);
	EXPECT_EQ(static_cast<bool>(shared_ptr_null), false);
	EXPECT_EQ(shared_ptr_int.use_count(), 2);
	EXPECT_EQ(shared_ptr_string.use_count(), 1);
	EXPECT_EQ(shared_ptr_null.use_count(), 0);
	EXPECT_EQ(*shared_ptr_int, buff_int);
	EXPECT_EQ(*shared_ptr_string, buff_string);
	EXPECT_EQ(shared_ptr_int.get(), ptr_int);
	EXPECT_EQ(shared_ptr_string.get(), ptr_string);
	EXPECT_EQ(shared_ptr_null.get(), nullptr);
	EXPECT_EQ(shared_ptr_int.operator->(), ptr_int);
	EXPECT_EQ(shared_ptr_string->empty(), ptr_string->empty());
	EXPECT_EQ(shared_ptr_null.operator->(), nullptr);
	shared_ptr_int.swap(shared_ptr_null);
	EXPECT_EQ(shared_ptr_int.get(), nullptr);
	EXPECT_EQ(shared_ptr_null.get(), ptr_int);
	shared_ptr_int.reset(ptr_int);
	shared_ptr_null.reset();
	EXPECT_EQ(shared_ptr_int.get(), ptr_int);
	EXPECT_EQ(shared_ptr_null.get(), nullptr);
}