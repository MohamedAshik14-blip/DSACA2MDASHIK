#include <gtest/gtest.h>
#include <unordered_map>
#include <set>
#include <memory>
#include <sstream>
#include <string>
#include <algorithm>
#include <fstream>
#include "Employee.h"



void loadCSVDataFromFile(const std::string& filename, std::unordered_map<std::string, std::set<std::shared_ptr<Employee>>>& indexMap) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    bool isFirstLine = true;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream lineStream(line);
        std::string name, city, department, ageStr, salaryStr;
        int age;
        float salary;


        if (isFirstLine) {
            isFirstLine = false;
            continue;
        }

        std::getline(lineStream, name, ',');
        std::getline(lineStream, ageStr, ',');
        std::getline(lineStream, city, ',');
        std::getline(lineStream, salaryStr, ',');
        std::getline(lineStream, department, ',');


        if (name.empty() || ageStr.empty() || city.empty() || salaryStr.empty() || department.empty()) {
            continue;
        }

        try {
            age = std::stoi(ageStr);
            salary = std::stof(salaryStr);
        } catch (const std::exception&) {
            continue;
        }


        std::transform(department.begin(), department.end(), department.begin(), ::tolower);


        auto emp = std::make_shared<Employee>(name, age, city, salary, department);


        indexMap[department].insert(emp);
    }

    file.close();
}


TEST(EmployeeTest, ConstructorTest) {
    Employee emp("John Doe", 30, "New York", 50000, "Engineering");

    EXPECT_EQ(emp.getName(), "John Doe");
    EXPECT_EQ(emp.getAge(), 30);
    EXPECT_EQ(emp.getCity(), "New York");
    EXPECT_EQ(emp.getSalary(), 50000);
    EXPECT_EQ(emp.getDepartment(), "Engineering");
}

TEST(CSVTest, LoadCSVTest) {
    std::unordered_map<std::string, std::set<std::shared_ptr<Employee>>> indexMap;

    std::string filename = "/Users/mohamedashiks/CLionProjects/DSACA2/data.csv";


    loadCSVDataFromFile(filename, indexMap);


    ASSERT_FALSE(indexMap.empty());
    EXPECT_GT(indexMap.size(), 0);


    EXPECT_EQ(indexMap["engineering"].size(), 38);
    EXPECT_EQ(indexMap["management"].size(), 26);
    EXPECT_EQ(indexMap["support"].size(), 43);
}




TEST(SearchTest, SearchByDepartment) {
    std::unordered_map<std::string, std::set<std::shared_ptr<Employee>>> indexMap;

    std::string filename = "/Users/mohamedashiks/CLionProjects/DSACA2/data.csv";


    loadCSVDataFromFile(filename, indexMap);


    std::string dept = "engineering";
    bool found = false;
    for (const auto& entry : indexMap[dept]) {
        if (entry->getDepartment() == dept) {
            found = true;
        }
    }

    EXPECT_TRUE(found);
}



