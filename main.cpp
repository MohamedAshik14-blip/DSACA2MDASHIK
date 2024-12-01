#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main() {
    std::ifstream file("/Users/mohamedashiks/CLionProjects/DSACA2/data.csv");

    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name, age, city, salary, department;

        std::getline(ss, name, ',');
        std::getline(ss, age, ',');
        std::getline(ss, city, ',');
        std::getline(ss, salary, ',');
        std::getline(ss, department, ',');

        std::cout << "Name: " << name << ", Age: " << age << ", City: " << city
                  << ", Salary: " << salary << ", Department: " << department << std::endl;
    }

    file.close();
    return 0;
}
