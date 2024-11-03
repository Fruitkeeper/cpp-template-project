#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <map>

// Function to read the book into a vector of characters
std::vector<char> readBook(const std::string& fileName) {
    std::ifstream file(fileName);
    std::vector<char> result;

    if (!file) {
        std::cerr << "File could not be opened!" << std::endl;
        return result;
    }

    char ch;
    while (file.get(ch)) {
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
            result.push_back(ch);
        } else {
            result.push_back(' ');
        }
    }

    return result;
}

// Function to process the characters into words
std::vector<std::string> getWords(const std::vector<char>& book) {
    std::istringstream iss(std::string(book.begin(), book.end()));
    std::vector<std::string> words;
    std::string word;

    while (iss >> word) {
        words.push_back(word);
    }

    return words;
}

// Function to count word frequencies using std::vector, std::sort and std::count
std::vector<std::pair<std::string, int>> countWordFrequencies(std::vector<std::string>& words) {
    std::sort(words.begin(), words.end()); 
    std::vector<std::pair<std::string, int>> wordFrequencies;
    auto it = words.begin();

    while (it != words.end()) {
        int count = std::count(it, words.end(), *it);
        wordFrequencies.push_back({*it, count});
        it = std::find_if(it, words.end(), [&it](const std::string& s) { return s != *it; });
    }

    // Sort by frequency in descending order
    std::sort(wordFrequencies.begin(), wordFrequencies.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });

    return wordFrequencies;
}

// Main function for testing
int main() {
    std::string fileName = "pg2701.txt";
    std::vector<char> book = readBook(fileName);

    if (book.empty()) {
        return 1; 
    }

    std::vector<std::string> words = getWords(book);
    std::vector<std::pair<std::string, int>> wordFrequencies = countWordFrequencies(words);

    // Print the word frequencies
    for (const auto& [word, count] : wordFrequencies) {
        std::cout << word << ": " << count << std::endl;
    }

    return 0;
}
