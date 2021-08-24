/*
* About Google Test
* Prime: https://github.com/google/googletest/blob/master/docs/primer.md
* Advanced: https://github.com/google/googletest/blob/master/docs/advanced.md
*/

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::_;
using ::testing::Return;

namespace
{

TEST(TestSuitName, TestFunc_Condition_ExpectedBehavior) {
   EXPECT_EQ(1, 1);
   EXPECT_STREQ("hello", "hello");
}

class TestFixtureName : public ::testing::Test
{
protected:
   void SetUp() override {
      test_val_1 = 1;
      test_val_2 = 2;
   }

protected:
   int test_val_1;
   int test_val_2;
};

TEST_F(TestFixtureName, Value1_EqualBehaviorExpected) {
   EXPECT_EQ(test_val_1, 1);
}

TEST_F(TestFixtureName, Value2_EqualBehaviorExpected) {
   EXPECT_EQ(test_val_2, 2);
}

struct FooTestCase
{
   int input;
   int expect_output;
};

FooTestCase foo_test_cases[] = {
   //input expect_output
   { 0,    1 },
   { 1,    2 }
};

int foo(int input) {
   return input+ + 1;
}

struct FooTest : public testing::TestWithParam<FooTestCase> {};
INSTANTIATE_TEST_SUITE_P(InstantiationName, FooTest, ::testing::ValuesIn(foo_test_cases));

TEST_P(FooTest, Foo_OutputExpected) {
   auto testCase = GetParam();
   EXPECT_EQ(foo(testCase.input), testCase.expect_output);
}

class BarInterface
{
public:
   virtual ~BarInterface() = default;
   virtual void bar_0() = 0;
   virtual void bar_1(int x) = 0;
   virtual void bar_1_const(int x) const = 0;
   virtual void bar_2(int x, int y) = 0;
   virtual int bar_2_return(int x, int y) = 0;
};

class MockBar : public BarInterface
{
public:
   MOCK_METHOD(void, bar_0, (), (override));
   MOCK_METHOD(void, bar_1, (int), (override));
   MOCK_METHOD(void, bar_1_const, (int), (const, override));
   MOCK_METHOD(void, bar_2, (int, int), (override));
   MOCK_METHOD(int, bar_2_return, (int, int), (override));
};

TEST(MockTest, MockFunc_MockBehaviorExpected) {
   MockBar bar;

   EXPECT_CALL(bar, bar_0())
      .Times(1);
   bar.bar_0();

   EXPECT_CALL(bar, bar_1(1))
      .Times(1);
   bar.bar_1(1);

   EXPECT_CALL(bar, bar_1_const(_))
      .Times(1);
   bar.bar_1_const(2);

   EXPECT_CALL(bar, bar_2(1, _))
      .Times(1);
   bar.bar_2(1, 3);

   EXPECT_CALL(bar, bar_2_return(1, 2))
      .WillOnce(Return(10));
   int ret = bar.bar_2_return(1, 2);
   EXPECT_EQ(ret, 10);
}

}

