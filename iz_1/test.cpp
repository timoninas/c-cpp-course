#include <gtest/gtest.h>

extern "C" {
#include "cDate.h"
}

TEST(check_valid_date, valid_date)
{
    // Arrange
    cDate date = {29, 2, 2020};

    // Act
    int res = check_valid_date(date);

    // Assert
    EXPECT_EQ(res, 1);
}

TEST(check_valid_date, not_valid_date)
{
    // Arrange
    cDate date = {29, 2, 2021};

    // Act
    int res = check_valid_date(date);

    // Assert
    EXPECT_EQ(res, 0);
}

TEST(test_greater_date, greater)
{
    // Arrange
    cDate date1 = {29, 2, 2021};
    cDate date2 = {11, 2, 2021};

    // Act
    int res = greater_date(date1, date2);

    // Assert
    EXPECT_EQ(res, 1);
    //EXPECT_FALSE(ltr.sender == NULL);
}

TEST(test_greater_date, not_greater)
{
    // Arrange
    cDate date1 = {29, 2, 2021};
    cDate date2 = {11, 2, 2021};

    // Act
    int res = greater_date(date2, date1);

    // Assert
    EXPECT_EQ(res, -1);
}

TEST(test_greater_date, equal_date)
{
    // Arrange
    cDate date = {29, 2, 2021};

    // Act
    int res = greater_date(date, date);

    // Assert
    EXPECT_FALSE(res != 0);
}

TEST(test_sort, compare_sorted_arr)
{
    // Arrange
    int curr_num_dates = 0;
    int buff_dates = 1;
    cDate* dates = (cDate*)malloc(sizeof(cDate) * buff_dates);

    int curr_num_sort_dates = 0;
    int buff_sort_dates = 1;
    cDate* sort_dates = (cDate*)malloc(sizeof(cDate) * buff_sort_dates);

    cDate date1, date2, date3, date4;
    fill_cDate(&date1, 28, 12, 1984);
    fill_cDate(&date2, 27, 12, 1984);
    fill_cDate(&date3, 26, 1, 1984);
    fill_cDate(&date4, 26, 1, 1980);

    // Dates in sorted order

    sort_dates = add_date(sort_dates, date4, &curr_num_sort_dates, &buff_sort_dates);
    sort_dates = add_date(sort_dates, date3, &curr_num_sort_dates, &buff_sort_dates);
    sort_dates = add_date(sort_dates, date2, &curr_num_sort_dates, &buff_sort_dates);
    sort_dates = add_date(sort_dates, date1, &curr_num_sort_dates, &buff_sort_dates);

    // Dates in not sorted order
    dates = add_date(dates, date1, &curr_num_dates, &buff_dates);
    dates = add_date(dates, date2, &curr_num_dates, &buff_dates);
    dates = add_date(dates, date3, &curr_num_dates, &buff_dates);
    dates = add_date(dates, date4, &curr_num_dates, &buff_dates);
    
    // Act
    sort(dates, curr_num_dates, buff_dates);

    // Assert
    for (int i = 0; i < curr_num_dates; i++) {
    	EXPECT_EQ(greater_date(sort_dates[i], dates[i]), 0);
    }

    free(dates);
    free(sort_dates);
}

int main(int argc, char **argv) 
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
