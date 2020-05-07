#include <gtest/gtest.h>
#include "../include/span_nd.hpp"

class constrTest : public ::testing::Test
{
protected:
};

TEST_F(constrTest, size)
{
  std::array<int, 3*3*3> arr{};
  span_3d<int> span3d(arr.data(), arr.size(), {3, 3, 3});
  EXPECT_EQ(span3d.size(), arr.size());
}