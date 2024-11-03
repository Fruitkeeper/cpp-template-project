#include <gtest/gtest.h>
#include <vector>
#include <map>
#include <fstream>
#include <cstdlib> // for rand()
#include <ctime> // For time()
#include "zipfLaw.h" 

using namespace std;

// Helper function to create a random test file with given content
void createRandomTestFile(const string& fileName, int numWords) {
    ofstream outFile(fileName);
    srand(time(0)); 

    const vector<string> sampleWords = {"Hello", "world", "test", "example", "random", "word"};
    for (int i = 0; i < numWords; ++i) {
        outFile << sampleWords[rand() % sampleWords.size()] << " ";
    }
    outFile.close();
}

// Test for the readBook function
TEST(WordFrequencyLibrary, ReadBookTest) {
    string testFileName = "random_test.txt";
    createRandomTestFile(testFileName, 100); // Create a file with 100 random words

    // Call the readBook function and check the result
    vector<char> result = readBook(testFileName);
    ASSERT_FALSE(result.empty()) << "readBook returned an empty vector.";
}
// Test for the computeWordFrequency function
TEST(WordFrequencyLibrary, ComputeWordFrequencyTest) {
    vector<char> book = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l', 'l', 'o'};
    map<string, int> frequencies = computeWordFrequency(book);
    EXPECT_EQ(frequencies["Hello"], 2);
    EXPECT_EQ(frequencies["world"], 1);
}
