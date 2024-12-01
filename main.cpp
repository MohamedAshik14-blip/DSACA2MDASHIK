#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <algorithm>

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
