#include <gtest/gtest.h>
#include <cstring>
#include <string>

extern "C" {
#include "errors.h"
#include "header.h"
#include "static.h"
#include "dynamic.h"
#include "reader.h"
}

TEST(read_file_size, not_exist_file)
{
    char filename[] = "../test_files/file-1.txt";
    size_t rc = read_file_size(filename);
    EXPECT_EQ(rc, ERROR_OPEN_FILE);
}

TEST(read_file_size, empty_file)
{
    char filename[] = "../test_files/empty.txt";
    size_t rc = read_file_size(filename);
    EXPECT_EQ(rc, ERROR_EMPTY_FILE);
}

TEST(read_file_data, not_exist_file)
{
    char filename[] = "../test_files/file-1.txt";
    int rc = read_file_data(filename, NULL, 0);
    EXPECT_EQ(rc, ERROR_OPEN_FILE);
}

TEST(read_file_data, compare_with_expected)
{
    // Arrange
    char filename[] = "../test_files/test1.txt";
    char expected[] = "abcdef123\n ";
    size_t size = read_file_size(filename);
    char* file_content = (char*) malloc(sizeof(char) * size);

    // Act
    int rc = read_file_data(filename, file_content, &size);

    // Assert
    EXPECT_EQ(size, 10);
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(strncmp(file_content, expected, size), 0);

    free(file_content);
}


TEST(find_sequence, not_found_sequence)
{
    // Arrange
    char filename[] = "../test_files/test1.txt";
    size_t size = read_file_size(filename);
    char *file_content = (char *) malloc(sizeof(char) * size);
    read_file_data(filename, file_content, &size);

    // Assert
    EXPECT_NE(size, 0);
    EXPECT_EQ(file_content == NULL, 0);
    EXPECT_EQ(find_sequence(file_content, &size) == NULL, true);
    free(file_content);
}

TEST(find_sequence, sequence)
{
    // Arrange
    char filename[] = "../test_files/test2.txt";
    char expected[] = "<Ebbb>";
    size_t size = read_file_size(filename);
    char* file_content = (char*) malloc(sizeof(char) * size);
    read_file_data(filename, file_content, &size);

    // Act
    char* finded_sequence = find_sequence(file_content, &size);

    // Assert
    EXPECT_NE(size, 0);
    EXPECT_EQ(file_content == NULL, false);
    EXPECT_EQ(finded_sequence == NULL, 0);
    EXPECT_EQ(strcmp(expected, finded_sequence), 0);

    free(file_content);
    free(finded_sequence);
}

TEST(find_sequence_multi, not_found_sequence)
{
     // Arrange
     char filename[] = "../test_files/test1.txt";
     size_t size = read_file_size(filename);
     char *file_content = (char *) malloc(sizeof(char) * size);
     read_file_data(filename, file_content, &size);

     // Act
     char *finded_sequence = find_sequence_multi(file_content, &size);

     // Assert
     EXPECT_NE(size, 0);
     EXPECT_EQ(file_content == NULL, false);
     EXPECT_EQ(finded_sequence == NULL, 1);

     free(file_content);
     free(finded_sequence);
}

TEST(find_sequence_multi, sequence_multi)
{
     // Arrange
     char filename[] = "../test_files/test2.txt";
     char expected[] = "<Ebbb>";
     size_t size = read_file_size(filename);
     char* file_content = (char*) malloc(sizeof(char) * size);
     read_file_data(filename, file_content, &size);

     // Act
     char* finded_sequence = find_sequence_multi(file_content, &size);

     // Assert
     EXPECT_NE(size, 0);
     EXPECT_EQ(file_content == NULL, 0);
     EXPECT_NE(finded_sequence == NULL, 1);
     EXPECT_EQ(strcmp(expected, finded_sequence), 0);

     free(file_content);
     free(finded_sequence);
}

TEST(find_sequence, comapre_seq_n_multi)
{
    // Arrange
    char filename[] = "../test_files/test4.txt";
    size_t size = read_file_size(filename);
    char *file_content = (char *) malloc(sizeof(char) * size);
    read_file_data(filename, file_content, &size);

    // Act
    char *finded_sequence = find_sequence(file_content, &size);
    char *finded_sequence_multi = find_sequence_multi(file_content, &size);

    // Assert
    EXPECT_NE(size, 0);
    EXPECT_EQ(file_content == NULL, 0);
    EXPECT_EQ(strcmp(finded_sequence, finded_sequence_multi), 0);

    //free
    free(file_content);
    free(finded_sequence);
    free(finded_sequence_multi);
}

int main(int argc, char **argv) 
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
