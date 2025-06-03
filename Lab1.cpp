#include <iostream>
#include <string>

class Student {
public:
    Student(int id, double avg, const std::string& name)
        : id(id), AvgPoints(avg), name(name), next(nullptr) {
        count++;
    }


    Student* next;
    int id;
    double AvgPoints;
    std::string name;
    static int count;
};

int Student::count = 0;

class StudentList {
private:
    Student* head = nullptr;

public:
    void addToBeginning(int id, double avg, const std::string& name) {
        Student* newStudent = new Student(id, avg, name);
        newStudent->next = head;
        head = newStudent;
    }

    void addToEnd(int id, double avg, const std::string& name) {
        Student* newStudent = new Student(id, avg, name);
        if (!head) {
            head = newStudent;
            return;
        }
        Student* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newStudent;
    }

    void addAtIndex(int index, int id, double avg, const std::string& name) {
        if (index == 0) {
            addToBeginning(id, avg, name);
            return;
        }
        Student* newStudent = new Student(id, avg, name);
        Student* temp = head;
        for (int i = 0; i < index - 1 && temp; i++) temp = temp->next;
        if (!temp) {
            std::cout << "Некорректный индекс" << std::endl;
            delete newStudent;
            return;
        }
        newStudent->next = temp->next;
        temp->next = newStudent;
    }

    void removeAtBeginning() {
        if (!head) return;
        Student* temp = head;
        head = head->next;
        delete temp;
    }

    void removeAtIndex(int index) {
        if (index == 0) {
            removeAtBeginning();
            return;
        }
        Student* temp = head;
        for (int i = 0; i < index - 1 && temp; i++) temp = temp->next;
        if (!temp || !temp->next) {
            std::cout << "Некорректный индекс" << std::endl;
            return;
        }
        Student* toDelete = temp->next;
        temp->next = toDelete->next;
        delete toDelete;
    }

    void displayAll() const {
        for (Student* temp = head; temp; temp = temp->next) {
            std::cout << "ID: " << temp->id 
                      << ", Средний балл: " << temp->AvgPoints 
                      << ", Имя: " << temp->name << std::endl;
        }
    }
};

int main() {
    StudentList list;
    list.addToEnd(1, 12.5, "Vasya");
    list.addToEnd(2, 9.0, "Petya");
    list.addToBeginning(3, 15.0, "Misha");
    list.addAtIndex(1, 4, 10.0, "Sasha");

    std::cout << "Список студентов:" << std::endl;
    list.displayAll();

    list.removeAtIndex(2);

    std::cout << "\nСписок студентов после удаления:" << std::endl;
    list.displayAll();

    return 0;
}
