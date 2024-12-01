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




void loadCSVData(const std::string& filename, std::unordered_map<std::string, std::set<std::shared_ptr<Employee>>>& indexMap) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    bool isFirstLine = true;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string name, city, department, ageStr, salaryStr;
        int age;
        float salary;

        if (isFirstLine) {
            isFirstLine = false;
            continue;
        }

        std::getline(ss, name, ',');
        std::getline(ss, ageStr, ',');
        std::getline(ss, city, ',');
        std::getline(ss, salaryStr, ',');
        std::getline(ss, department, ',');

        if (name.empty() || ageStr.empty() || city.empty() || salaryStr.empty() || department.empty()) {
            std::cerr << "Warning: Malformed line, skipping: " << line << std::endl;
            continue;
        }

        try {
            age = std::stoi(ageStr);
            salary = std::stof(salaryStr);
        } catch (const std::exception& e) {
            std::cerr << "Error converting age or salary in line: " << line << " (" << e.what() << ")" << std::endl;
            continue;
        }

        std::transform(department.begin(), department.end(), department.begin(), ::tolower);

        auto emp = std::make_shared<Employee>(name, age, city, salary, department);
        indexMap[department].insert(emp);
    }

    file.close();

    if (indexMap.empty()) {
        std::cout << "No employee data found in the CSV file." << std::endl;
    }
}

void searchData(std::unordered_map<std::string, std::set<std::shared_ptr<Employee>>>& indexMap) {
    int choice;
    std::cout << "Search by:\n";
    std::cout << "1. Department\n";
    std::cout << "2. City\n";
    std::cout << "3. Age (Categorized)\n";
    std::cout << "4. Salary (Categorized)\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    if (choice == 1) {
        std::cout << "Departments available:\n";
        std::cout << "1. Engineering\n";
        std::cout << "2. Management\n";
        std::cout << "3. Support\n";
        std::cout << "Enter department choice (1-3): ";
        int deptChoice;
        std::cin >> deptChoice;

        std::string deptName;
        switch (deptChoice) {
            case 1: deptName = "engineering"; break;
            case 2: deptName = "management"; break;
            case 3: deptName = "support"; break;
            default:
                std::cout << "Invalid choice." << std::endl;
                return;
        }

        if (indexMap.find(deptName) != indexMap.end()) {
            std::cout << "Employees in department '" << deptName << "':" << std::endl;
            for (const auto& emp : indexMap[deptName]) {
                std::cout << emp->getName() << ", Age: " << emp->getAge() << ", City: " << emp->getCity() << ", Salary: " << emp->getSalary() << std::endl;
            }
        } else {
            std::cout << "No data for department '" << deptName << "'." << std::endl;
        }
    } else if (choice == 2) {
        std::cout << "Cities available:\n";
        std::cout << "1. New York\n";
        std::cout << "2. Boston\n";
        std::cout << "3. Seattle\n";
        std::cout << "4. Chicago\n";
        std::cout << "5. San Francisco\n";
        std::cout << "6. Austin\n";
        std::cout << "Enter city choice (1-6): ";
        int cityChoice;
        std::cin >> cityChoice;

        std::string cityName;
        switch (cityChoice) {
            case 1: cityName = "New York"; break;
            case 2: cityName = "Boston"; break;
            case 3: cityName = "Seattle"; break;
            case 4: cityName = "Chicago"; break;
            case 5: cityName = "San Francisco"; break;
            case 6: cityName = "Austin"; break;
            default:
                std::cout << "Invalid choice." << std::endl;
                return;
        }

        bool found = false;
        for (const auto& entry : indexMap) {
            for (const auto& emp : entry.second) {
                if (emp->getCity() == cityName) {
                    std::cout << emp->getName() << ", Age: " << emp->getAge() << ", City: " << emp->getCity() << ", Salary: " << emp->getSalary() << ", Department: " << emp->getDepartment() << std::endl;
                    found = true;
                }
            }
        }

        if (!found) {
            std::cout << "No employees found in city '" << cityName << "'." << std::endl;
        }
    } else if (choice == 3) {
        int ageChoice;
        std::cout << "Enter age category:\n";
        std::cout << "1. 1-18\n";
        std::cout << "2. 18-25\n";
        std::cout << "3. 25-35\n";
        std::cout << "4. 35-45\n";
        std::cout << "5. 45-55\n";
        std::cout << "6. 60+\n";
        std::cin >> ageChoice;

        bool found = false;
        for (const auto& entry : indexMap) {
            for (const auto& emp : entry.second) {
                int age = emp->getAge();
                if ((ageChoice == 1 && age >= 1 && age <= 18) ||
                    (ageChoice == 2 && age > 18 && age <= 25) ||
                    (ageChoice == 3 && age > 25 && age <= 35) ||
                    (ageChoice == 4 && age > 35 && age <= 45) ||
                    (ageChoice == 5 && age > 45 && age <= 55) ||
                    (ageChoice == 6 && age > 60)) {
                    std::cout << emp->getName() << ", Age: " << age << ", City: " << emp->getCity() << ", Salary: " << emp->getSalary() << ", Department: " << emp->getDepartment() << std::endl;
                    found = true;
                }
            }
        }

        if (!found) {
            std::cout << "No employees found in this age category." << std::endl;
        }
    } else if (choice == 4) {
        int salaryChoice;
        std::cout << "Enter salary category:\n";
        std::cout << "1. <30k\n";
        std::cout << "2. 30k-50k\n";
        std::cout << "3. 50k-70k\n";
        std::cout << "4. 70k-100k\n";
        std::cout << "5. >100k\n";
        std::cin >> salaryChoice;

        bool found = false;
        for (const auto& entry : indexMap) {
            for (const auto& emp : entry.second) {
                float salary = emp->getSalary();
                if ((salaryChoice == 1 && salary < 30000) ||
                    (salaryChoice == 2 && salary >= 30000 && salary <= 50000) ||
                    (salaryChoice == 3 && salary > 50000 && salary <= 70000) ||
                    (salaryChoice == 4 && salary > 70000 && salary <= 100000) ||
                    (salaryChoice == 5 && salary > 100000)) {
                    std::cout << emp->getName() << ", Age: " << emp->getAge() << ", City: " << emp->getCity() << ", Salary: " << salary << ", Department: " << emp->getDepartment() << std::endl;
                    found = true;
                }
            }
        }

        if (!found) {
            std::cout << "No employees found in this salary category." << std::endl;
        }
    } else {
        std::cout << "Invalid search type." << std::endl;
    }
}


void listAllEmployees(const std::unordered_map<std::string, std::set<std::shared_ptr<Employee>>>& indexMap) {
    std::cout << "All Employees: \n";
    for (const auto& entry : indexMap) {
        for (const auto& emp : entry.second) {
            std::cout << emp->getName() << ", Age: " << emp->getAge() << ", City: " << emp->getCity() << ", Salary: " << emp->getSalary() << ", Department: " << emp->getDepartment() << std::endl;
        }
    }
}




int main() {
    std::unordered_map<std::string, std::set<std::shared_ptr<Employee>>> indexMap;

    int option;
    std::string filename;
    while (true) {
        std::cout << "\nMenu:\n";
        std::cout << "1. Process a text file and organize words (Stage 2)\n";
        std::cout << "2. Load CSV data and create an index (Stage 3)\n";
        std::cout << "3. Search and view indexed data (Stage 4)\n";
        std::cout << "4. List all employees\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> option;

        if (option == 1) {
            std::cout << "Enter the text file path: ";
            std::cin >> filename;
            processTextFile(filename);
        } else if (option == 2) {
            std::cout << "Enter the CSV file path: ";
            std::cin >> filename;
            loadCSVData(filename, indexMap);
        } else if (option == 3) {
            searchData(indexMap);
        } else if (option == 4) {
            listAllEmployees(indexMap);
        } else if (option == 5) {
            break;
        } else {
            std::cout << "Invalid choice. Try again." << std::endl;
        }
    }

    return 0;
}
