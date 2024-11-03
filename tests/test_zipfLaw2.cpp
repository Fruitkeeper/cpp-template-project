#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <map>
#include "zipfLaw2.h"

// Test for the readBook function
TEST(WordFrequencyLibrary, ReadBookTest) {
    // Create a test file
    std::string testFileName = "test.txt";
    std::ofstream testFile(testFileName);
    testFile << "Hello world! This is a test. Hello again.";
    testFile.close();

    // Read the book and test for content
    std::vector<char> result = readBook(testFileName);
    ASSERT_FALSE(result.empty()) << "readBook returned an empty vector.";
    EXPECT_EQ(result[0], 'H') << "First character should be 'H'.";
}
// Test for the countWordFrequencies function
TEST(WordFrequencyLibrary, CountWordFrequenciesTest) {
    std::vector<std::string> words = {"Hello", "world", "Hello", "test"};
    std::vector<std::pair<std::string, int>> frequencies = countWordFrequencies(words);
    ASSERT_EQ(frequencies.size(), 3) << "Expected 3 unique words in the frequency count.";

    EXPECT_EQ(frequencies[0].first, "Hello");
    EXPECT_EQ(frequencies[0].second, 2);
    EXPECT_EQ(frequencies[1].first, "test");
    EXPECT_EQ(frequencies[1].second, 1);
    EXPECT_EQ(frequencies[2].first, "world");
    EXPECT_EQ(frequencies[2].second, 1);
}

