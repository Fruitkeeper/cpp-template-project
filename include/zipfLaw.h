#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <set>

// Function to read the book and return a vector of characters
std::vector<char> readBook(std::string fileName) {
    std::ifstream file(fileName);
    std::vector<char> result;

    if (!file) {
        std::cerr << "File could not be opened!" << std::endl;
        return result;
    }

    char ch;
    while (file.get(ch)) { // Read each character from the file
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
            result.push_back(ch); // Append alphabetic characters
        } else {
            result.push_back(' '); // Replace non-alphabetic characters with a space
        }
    }

    file.close();
    return result;
}

// Function to compute the word frequency from the vector of characters
std::map<std::string, int> computeWordFrequency(const std::vector<char>& book) {
    std::map<std::string, int> wordFrequency;
    std::stringstream ss(std::string(book.begin(), book.end())); // Convert vector to string
    std::string word;

    while (ss >> word) {
        ++wordFrequency[word]; // Increment the count for each word
    }

    return wordFrequency;
}

// Function to count the number of unique words using a set
int countUniqueWords(const std::vector<char>& book) {
    std::set<std::string> uniqueWords;
    std::stringstream ss(std::string(book.begin(), book.end())); // Convert vector to string
    std::string word;

    while (ss >> word) {
        uniqueWords.insert(word);
    }

    return uniqueWords.size();
}

// Function to sort word frequencies into a multimap by frequency
std::multimap<int, std::string> sortFrequencies(const std::map<std::string, int>& frequencies) {
    std::multimap<int, std::string> sortedFrequencies;

    for (const auto& pair : frequencies) {
        sortedFrequencies.insert({pair.second, pair.first});
    }

    return std::multimap<int, std::string>(sortedFrequencies.rbegin(), sortedFrequencies.rend());
}

// Function to output frequencies to a file for plotting
void outputFrequenciesToFile(const std::multimap<int, std::string>& sortedFrequencies, const std::string& filename) {
    std::ofstream outFile(filename);
    int rank = 1; // Start the rank at 1

    for (const auto& [freq, word] : sortedFrequencies) {
        outFile << rank << " " << freq << " " << word << "\n";
        ++rank;
    }

    outFile.close();
}

// Function to print the number of hapax legomena (words that occur only once)
void printHapaxLegomena(const std::multimap<int, std::string>& sortedFrequencies) {
    int hapaxCount = 0;

    for (const auto& [freq, word] : sortedFrequencies) {
        if (freq == 1) {
            ++hapaxCount;
            std::cout << word << "\n"; // Print some hapax legomena
        }
    }

    std::cout << "Total number of words that occur only once: " << hapaxCount << std::endl;
}

// Main function
int main() {
    std::string fileName = "pg2701.txt";
    std::vector<char> book = readBook(fileName);

    if (book.empty()) {
        return 1; 
    }

    // Compute word frequencies
    std::map<std::string, int> wordFrequency = computeWordFrequency(book);

    // Count and print the number of unique words
    int uniqueWordCount = countUniqueWords(book);
    std::cout << "Number of unique words: " << uniqueWordCount << std::endl;

    // Sort word frequencies
    std::multimap<int, std::string> sortedFrequencies = sortFrequencies(wordFrequency);

    // Output sorted frequencies to a file for plotting
    std::string outputFileName = "word_frequencies.txt";
    outputFrequenciesToFile(sortedFrequencies, outputFileName);
    std::cout << "Frequencies written to " << outputFileName << std::endl;

    // Print hapax legomena
    printHapaxLegomena(sortedFrequencies);

    return 0;
}
