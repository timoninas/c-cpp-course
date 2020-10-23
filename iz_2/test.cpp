#include <gtest/gtest.h>

extern "C" {
#include "errors.h"
#include "header.h"
#include "static.h"
#include "dynamic.h"
#include "reader.h"
}

TEST(check_valid_date, valid_date)
{
    EXPECT_EQ(1, 1);
}

int main(int argc, char **argv) 
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
