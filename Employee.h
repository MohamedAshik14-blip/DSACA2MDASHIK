#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <iostream>

class Employee {
private:
    std::string name;
    int age;
    std::string city;
    float salary;
    std::string department;

public:

    Employee(const std::string& name, int age, const std::string& city, float salary, const std::string& department)
            : name(name), age(age), city(city), salary(salary), department(department) {}


    std::string getName() const { return name; }
    int getAge() const { return age; }
    std::string getCity() const { return city; }
    float getSalary() const { return salary; }
    std::string getDepartment() const { return department; }

bool operator<(const Employee& other) const {
        return name < other.name;
    }


    void display() const {
        std::cout << name << ", Age: " << age << ", City: " << city << ", Salary: " << salary << ", Department: " << department << std::endl;
    }

};

#endif
