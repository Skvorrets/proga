#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// Класс Студент (только свойства, без методов)
class Student {
public:
    int id;
    string name;
    int age;
    double grade;
};

class StudentDatabase {
private:
    string filename;
    vector<Student> students;

    // Вспомогательная функция для разделения строки
    vector<string> splitString(const string &s, char delimiter) {
        vector<string> tokens;
        string token;
        istringstream tokenStream(s);
        while (getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

public:
    StudentDatabase(const string &fname = "students_db.txt") : filename(fname) {}

    // Добавить студента в систему (в вектор)
    void addStudent(const Student &student) {
        students.push_back(student);
        cout << "Студент " << student.name << " добавлен в систему." << endl;
    }

    // Сохранить всех студентов в файл
    void saveToFile() {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto &student : students) {
                file << student.id << " " << student.name << " " 
                     << student.age << " " << student.grade << endl;
            }
            file.close();
            cout << "Данные сохранены в файл " << filename << endl;
        } else {
            cerr << "Не удалось открыть файл для записи!" << endl;
        }
    }

    // Считать студентов из файла в вектор
    void readFromFile() {
        students.clear();
        ifstream file(filename);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                vector<string> tokens = splitString(line, ' ');
                if (tokens.size() == 4) {
                    Student student;
                    student.id = stoi(tokens[0]);
                    student.name = tokens[1];
                    student.age = stoi(tokens[2]);
                    student.grade = stod(tokens[3]);
                    students.push_back(student);
                }
            }
            file.close();
            cout << "Данные загружены из файла " << filename << endl;
        } else {
            cerr << "Не удалось открыть файл для чтения!" << endl;
        }
    }

    // Обновить данные студента по ID
    void updateStudent(int id, const Student &newData) {
        for (auto &student : students) {
            if (student.id == id) {
                student = newData;
                cout << "Данные студента с ID " << id << " обновлены." << endl;
                return;
            }
        }
        cerr << "Студент с ID " << id << " не найден!" << endl;
    }

    // Удалить студента по ID
    void deleteStudent(int id) {
        for (auto it = students.begin(); it != students.end(); ++it) {
            if (it->id == id) {
                students.erase(it);
                cout << "Студент с ID " << id << " удален." << endl;
                return;
            }
        }
        cerr << "Студент с ID " << id << " не найден!" << endl;
    }

    // Вывести всех студентов
    void printAllStudents() {
        if (students.empty()) {
            cout << "В базе данных нет студентов." << endl;
            return;
        }

        cout << "Список студентов:" << endl;
        cout << "ID\tИмя\tВозраст\tСредний балл" << endl;
        for (const auto &student : students) {
            cout << student.id << "\t" << student.name << "\t" 
                 << student.age << "\t" << student.grade << endl;
        }
    }
};

// Функция для ввода данных студента с консоли
Student inputStudent() {
    Student student;
    cout << "Введите ID студента: ";
    cin >> student.id;
    cout << "Введите имя студента: ";
    cin.ignore();
    getline(cin, student.name);
    cout << "Введите возраст студента: ";
    cin >> student.age;
    cout << "Введите средний балл студента: ";
    cin >> student.grade;
    return student;
}

int main() {
    StudentDatabase db;
    int choice;

    do {
        cout << "\nМеню:\n";
        cout << "1. Добавить студента\n";
        cout << "2. Сохранить в файл\n";
        cout << "3. Загрузить из файла\n";
        cout << "4. Обновить данные студента\n";
        cout << "5. Удалить студента\n";
        cout << "6. Показать всех студентов\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Student student = inputStudent();
                db.addStudent(student);
                break;
            }
            case 2:
                db.saveToFile();
                break;
            case 3:
                db.readFromFile();
                break;
            case 4: {
                int id;
                cout << "Введите ID студента для обновления: ";
                cin >> id;
                Student newData = inputStudent();
                db.updateStudent(id, newData);
                break;
            }
            case 5: {
                int id;
                cout << "Введите ID студента для удаления: ";
                cin >> id;
                db.deleteStudent(id);
                break;
            }
            case 6:
                db.printAllStudents();
                break;
            case 0:
                cout << "Выход из программы.\n";
                break;
            default:
                cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);

    return 0;
}
