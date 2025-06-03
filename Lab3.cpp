#include <iostream>
#include <cmath>
#include <vector>
#include <locale>

using namespace std;

// Абстрактный класс Точка
class Point {
protected:
    double x, y;
public:
    Point(double xCoord = 0, double yCoord = 0) : x(xCoord), y(yCoord) {}
    virtual ~Point() {}

    // Чисто виртуальные методы делают класс абстрактным
    virtual void draw() const = 0;
    virtual void erase() const = 0;
    
    virtual void move(double dx, double dy) {
        x += dx;
        y += dy;
        cout << "Точка перемещена в (" << x << ", " << y << ")\n";
    }
    
    double getX() const { return x; }
    double getY() const { return y; }
    
    virtual void rotate(double angle) = 0;
};

class Line : public virtual Point {
protected:
    double x2, y2;
public:
    Line(double x1, double y1, double x2, double y2) 
        : Point(x1, y1), x2(x2), y2(y2) {}
    
    void draw() const override {
        cout << "Рисуем линию из (" << x << ", " << y 
             << ") в (" << x2 << ", " << y2 << ")\n";
    }
    
    void erase() const override {
        cout << "Стираем линию из (" << x << ", " << y 
             << ") в (" << x2 << ", " << y2 << ")\n";
    }
    
    void move(double dx, double dy) override {
        Point::move(dx, dy);
        x2 += dx;
        y2 += dy;
    }
    
    void rotate(double angle) override {
        double midX = (x + x2) / 2;
        double midY = (y + y2) / 2;
        
        double rad = angle * M_PI / 180.0;
        double cosA = cos(rad);
        double sinA = sin(rad);
        
        // Перенос в начало координат
        double x1 = x - midX;
        double y1 = y - midY;
        
        // Поворот
        double x1new = x1 * cosA - y1 * sinA;
        double y1new = x1 * sinA + y1 * cosA;
        
        double x2new = (x2 - midX) * cosA - (y2 - midY) * sinA;
        double y2new = (x2 - midX) * sinA + (y2 - midY) * cosA;
        
        // Обратный перенос
        x = x1new + midX;
        y = y1new + midY;
        x2 = x2new + midX;
        y2 = y2new + midY;
        
        cout << "Линия повернута на " << angle << " градусов\n";
    }
};

class Square : public virtual Point {
protected:
    double side;
public:
    Square(double x, double y, double s) : Point(x, y), side(s) {}
    
    void draw() const override {
        cout << "Рисуем квадрат в (" << x << ", " << y 
             << ") со стороной " << side << "\n";
    }
    
    void erase() const override {
        cout << "Стираем квадрат в (" << x << ", " << y 
             << ") со стороной " << side << "\n";
    }
    
    void rotate(double angle) override {
        cout << "Квадрат повернут на " << angle << " градусов\n";
    }
    
    double getSide() const { return side; }
};

class Rhombus : public virtual Point {
protected:
    double diagonal1, diagonal2;
public:
    Rhombus(double x, double y, double d1, double d2) 
        : Point(x, y), diagonal1(d1), diagonal2(d2) {}
    
    void draw() const override {
        cout << "Рисуем ромб в (" << x << ", " << y 
             << ") с диагоналями " << diagonal1 << " и " << diagonal2 << "\n";
    }
    
    void erase() const override {
        cout << "Стираем ромб в (" << x << ", " << y 
             << ") с диагоналями " << diagonal1 << " и " << diagonal2 << "\n";
    }
    
    void rotate(double angle) override {
        cout << "Ромб повернут на " << angle << " градусов\n";
    }
};

class Rectangle : public virtual Point {
protected:
    double width, height;
public:
    Rectangle(double x, double y, double w, double h) 
        : Point(x, y), width(w), height(h) {}
    
    void draw() const override {
        cout << "Рисуем прямоугольник в (" << x << ", " << y 
             << ") с шириной " << width << " и высотой " << height << "\n";
    }
    
    void erase() const override {
        cout << "Стираем прямоугольник в (" << x << ", " << y 
             << ") с шириной " << width << " и высотой " << height << "\n";
    }
    
    void rotate(double angle) override {
        cout << "Прямоугольник повернут на " << angle << " градусов\n";
    }
};

class Parallelogram : public virtual Square {
protected:
    double angle;
public:
    Parallelogram(double x, double y, double s, double a) 
        : Point(x, y), Square(x, y, s), angle(a) {}
    
    void draw() const override {
        cout << "Рисуем параллелограмм в (" << x << ", " << y 
             << ") со стороной " << side << " и углом " << angle << "\n";
    }
    
    void erase() const override {
        cout << "Стираем параллелограмм в (" << x << ", " << y 
             << ") со стороной " << side << " и углом " << angle << "\n";
    }
    
    void rotate(double rotAngle) override {
        angle += rotAngle;
        if (angle >= 360) angle -= 360;
        cout << "Параллелограмм повернут. Новый угол: " << angle << " градусов\n";
    }
};

void testPolymorphism() {
    vector<Point*> shapes;
    
    shapes.push_back(new Line(0, 0, 10, 10));
    shapes.push_back(new Square(5, 5, 10));
    shapes.push_back(new Rhombus(3, 3, 8, 6));
    shapes.push_back(new Rectangle(2, 2, 10, 5));
    shapes.push_back(new Parallelogram(1, 1, 7, 45));
    
    for (auto shape : shapes) {
        shape->draw();
        shape->move(2, 2);
        shape->rotate(30);
        shape->erase();
        cout << "----------------------------------\n";
    }
    
    for (auto shape : shapes) {
        delete shape;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    testPolymorphism();
    return 0;
}
