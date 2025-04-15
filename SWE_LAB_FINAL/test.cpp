#include <gtest/gtest.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
#include "pch.h"

// ==================== StudentManager (Singleton) ====================
class StudentManager {
private:
    static StudentManager* instance;
    std::vector<std::string> students;


    StudentManager() {}

public:
    
    StudentManager(const StudentManager&) = delete;
    StudentManager& operator=(const StudentManager&) = delete;

    static StudentManager* getInstance() {
        if (!instance) {
            instance = new StudentManager();
        }
        return instance;
    }

    void addStudent(const std::string& name) {
        students.push_back(name);
    }

    void removeStudent(const std::string& name) {
        auto it = std::find(students.begin(), students.end(), name);
        if (it != students.end()) {
            students.erase(it);
        }
        else {
            throw std::runtime_error("Student not found");
        }
    }

    void displayStudents() const {
        std::cout << "Student List:\n";
        for (const auto& student : students) {
            std::cout << "- " << student << "\n";
        }
    }

    size_t countStudents() const {  
        return students.size();
    }

    void clearStudents() {
        students.clear();
    }
};


StudentManager* StudentManager::instance = nullptr;

// ==================== Test Cases ====================
TEST(StudentManagerTest, SingletonInstanceShouldBeSame) {
    StudentManager* sm1 = StudentManager::getInstance();
    StudentManager* sm2 = StudentManager::getInstance();
    EXPECT_EQ(sm1, sm2);
}

TEST(StudentManagerTest, AddAndCountStudents) {
    StudentManager* manager = StudentManager::getInstance();
    manager->clearStudents();  
    manager->addStudent("Alice");
    manager->addStudent("Bob");
    EXPECT_EQ(manager->countStudents(), 2u);  
}

TEST(StudentManagerTest, RemoveStudentShouldWork) {
    StudentManager* manager = StudentManager::getInstance();
    manager->clearStudents();  
    manager->addStudent("Charlie");
    manager->addStudent("David");
    manager->removeStudent("Charlie");
    EXPECT_EQ(manager->countStudents(), 1u);  
}

TEST(StudentManagerTest, RemoveNonExistentStudentThrows) {
    StudentManager* manager = StudentManager::getInstance();
    manager->clearStudents();
    manager->addStudent("Eve");
    EXPECT_THROW(manager->removeStudent("NotExist"), std::runtime_error);
}

// ==================== Main Function ====================
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}