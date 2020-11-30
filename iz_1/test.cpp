#include <gtest/gtest.h>

extern "C" {
#include "date.h"
}

TEST(check_valid_date, valid_date)
{
    // Arrange
    date_t date = {29, 2, 2020};

    // Act
    int res = check_valid_date(date);

    // Assert
    EXPECT_EQ(res, 1);
}

TEST(check_valid_date, not_valid_date)
{
    // Arrange
    date_t date = {29, 2, 2021};

    // Act
    int res = check_valid_date(date);

    // Assert
    EXPECT_EQ(res, 0);
}

TEST(test_greater_date, greater)
{
    // Arrange
    date_t date1 = {29, 2, 2021};
    date_t date2 = {11, 2, 2021};

    // Act
    int res = greater_date(date1, date2);

    // Assert
    EXPECT_EQ(res, 1);
    //EXPECT_FALSE(ltr.sender == NULL);
}

TEST(test_greater_date, equal_date)
{
    // Arrange
    date_t date = {29, 2, 2021};

    // Act
    int res = greater_date(date, date);

    // Assert
    EXPECT_EQ(res, 0);
}

TEST(test_swipe, swipe_values)
{
    // Arrange
    date_t date1 = {29, 2, 2021};
    date_t date2 = {11, 2, 2021};
    date_t tmp_date1 = {29, 2, 2021};
    date_t tmp_date2 = {11, 2, 2021};

    // Act
    swipe_date(&date1, &date2);
    int res1 = greater_date(date1, tmp_date2);
    int res2 = greater_date(date2, tmp_date1);

    // Assert
    EXPECT_EQ(res1, 0);
    EXPECT_EQ(res2, 0);
}

TEST(test_sort, compare_sorted_arr)
{
    // Arrange
    int curr_num_dates = 0;
    int buff_dates = 1;
    date_t* dates = (date_t*)malloc(sizeof(date_t) * buff_dates);

    int curr_num_sort_dates = 0;
    int buff_sort_dates = 1;
    date_t* sort_dates = (date_t*)malloc(sizeof(date_t) * buff_sort_dates);

    date_t date1, date2, date3, date4;
    fill_date(&date1, 28, 12, 1984);
    fill_date(&date2, 27, 12, 1984);
    fill_date(&date3, 26, 1, 1984);
    fill_date(&date4, 26, 1, 1980);

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
