#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <set>
#include <string>
#include <memory>
#include <cctype>
#include <algorithm>
#include "Employee.h"


class CompareByAge {
public:
    bool operator()(const std::shared_ptr<Employee>& e1, const std::shared_ptr<Employee>& e2) const {
        return e1->getAge() < e2->getAge();
    }
};

class CompareBySalary {
public:
    bool operator()(const std::shared_ptr<Employee>& e1, const std::shared_ptr<Employee>& e2) const {
        return e1->getSalary() < e2->getSalary();
    }
};

void processTextFile(const std::string& filename) {
    std::unordered_map<char, std::set<std::string>> wordMap;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string word;
    while (file >> word) {
        word.erase(std::remove_if(word.begin(), word.end(), [](char c) {
            return !std::isalpha(c);
        }), word.end());

        if (!word.empty()) {
            char firstLetter = std::tolower(word[0]);
            wordMap[firstLetter].insert(word);
        }
    }

    file.close();

    if (wordMap.empty()) {
        std::cout << "No words found in the file." << std::endl;
        return;
    }

    std::cout << "Unique letters with words: ";
    for (const auto& entry : wordMap) {
        std::cout << entry.first << " ";
    }
    std::cout << std::endl;

    char choice;
    std::cout << "Enter a letter to view associated words: ";
    std::cin >> choice;
    choice = std::tolower(choice);

    if (wordMap.find(choice) != wordMap.end()) {
        std::cout << "Words for letter '" << choice << "':" << std::endl;
        for (const auto& word : wordMap[choice]) {
            std::cout << word<< std::endl;
        }
    } else {
        std::cout << "No words for letter '" << choice << "'." << std::endl;
    }
}










int main() {
    std::ifstream file("/Users/mohamedashiks/CLionProjects/DSACA2/data.csv");

    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::set<std::string> words;
    std::string line;

    while (std::getline(file, line)) {
        std::transform(line.begin(), line.end(), line.begin(), ::tolower);  
        std::stringstream ss(line);
        std::string word;

        while (ss >> word) {
            words.insert(word);
        }
    }

    file.close();

    std::cout << "Processed and organized words (Stage 2):" << std::endl;
    for (const auto& word : words) {
        std::cout << word << std::endl;
    }

    return 0;
}
