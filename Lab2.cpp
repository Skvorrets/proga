#include <iostream>
#include <iomanip>

using namespace std;

class vect {
public:
    int dim;
    double* b;
    int num;
    static int count;

    vect(int d) : dim(d), num(++count) {
        b = new double[dim];
        for (int i = 0; i < dim; i++) b[i] = 0.0;
    }

    vect(const vect& v) : dim(v.dim), num(++count) {
        b = new double[dim];
        for (int i = 0; i < dim; i++) b[i] = v.b[i];
    }

    ~vect() {
        delete[] b;
    }

    vect& operator=(const vect& v) {
        if (this != &v) {
            delete[] b;
            dim = v.dim;
            b = new double[dim];
            for (int i = 0; i < dim; i++)
                b[i] = v.b[i];
        }
        return *this;
    }

    vect operator+(const vect& v) const {
        vect res(dim);
        for (int i = 0; i < dim; i++)
            res.b[i] = b[i] + v.b[i];
        return res;
    }

    vect operator-(const vect& v) const {
        vect res(dim);
        for (int i = 0; i < dim; i++)
            res.b[i] = b[i] - v.b[i];
        return res;
    }

    vect operator-() const {
        vect res(dim);
        for (int i = 0; i < dim; i++)
            res.b[i] = -b[i];
        return res;
    }

    double operator*(const vect& v) const {
        double sum = 0.0;
        for (int i = 0; i < dim; i++)
            sum += b[i] * v.b[i];
        return sum;
    }

    vect operator*(double k) const {
        vect res(dim);
        for (int i = 0; i < dim; i++)
            res.b[i] = b[i] * k;
        return res;
    }

    vect& operator=(double val) {
        for (int i = 0; i < dim; i++)
            b[i] = val;
        return *this;
    }

    void print() const {
        for (int i = 0; i < dim; i++)
            cout << b[i] << " ";
        cout << endl;
    }
};

int vect::count = 0;

class matr {
public:
    int dim;
    double* a;
    int num;
    static int count;

    matr(int d) : dim(d), num(++count) {
        a = new double[dim * dim];
        for (int i = 0; i < dim * dim; i++) a[i] = 0.0;
    }

    matr(const matr& m) : dim(m.dim), num(++count) {
        a = new double[dim * dim];
        for (int i = 0; i < dim * dim; i++)
            a[i] = m.a[i];
    }

    ~matr() {
        delete[] a;
    }

    matr& operator=(const matr& m) {
        if (this != &m) {
            delete[] a;
            dim = m.dim;
            a = new double[dim * dim];
            for (int i = 0; i < dim * dim; i++)
                a[i] = m.a[i];
        }
        return *this;
    }

    matr operator+(const matr& m) const {
        matr res(dim);
        for (int i = 0; i < dim * dim; i++)
            res.a[i] = a[i] + m.a[i];
        return res;
    }

    matr operator-(const matr& m) const {
        matr res(dim);
        for (int i = 0; i < dim * dim; i++)
            res.a[i] = a[i] - m.a[i];
        return res;
    }

    matr operator-() const {
        matr res(dim);
        for (int i = 0; i < dim * dim; i++)
            res.a[i] = -a[i];
        return res;
    }

    double operator*(const matr& m) const {
        double sum = 0.0;
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                double s = 0.0;
                for (int k = 0; k < dim; k++) {
                    s += a[i * dim + k] * m.a[k * dim + j];
                }
                sum += s;
            }
        }
        return sum;
    }

    matr operator*(double k) const {
        matr res(dim);
        for (int i = 0; i < dim * dim; i++)
            res.a[i] = a[i] * k;
        return res;
    }

    double operator*(const vect& v) const {
        double sum = 0.0;
        for (int i = 0; i < dim; i++) {
            double s = 0.0;
            for (int j = 0; j < dim; j++) {
                s += a[i * dim + j] * v.b[j];
            }
            sum += s;
        }
        return sum;
    }

    matr& operator=(double val) {
        for (int i = 0; i < dim * dim; i++)
            a[i] = val;
        return *this;
    }

    void print() const {
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                cout << setw(8) << a[i * dim + j] << " ";
            }
            cout << endl;
        }
    }
};

int matr::count = 0;

int main() {
    // Создаем векторы и матрицы
    cout << "Результат умножения матрицы m1 на вектор v1: " << endl;
    vect v1(3), v2(3);
    v1.b[0] = 1; v1.b[1] = 2; v1.b[2] = 3;
    v2.b[0] = 4; v2.b[1] = 5; v2.b[2] = 6;

    matr m1(3), m2(3);
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            m1.a[i * 3 + j] = i + j;
            m2.a[i * 3 + j] = (i + 1) * (j + 1);
        }

    double result = m1 * v1;
    cout << result << endl;

    // Удаление матриц
    cout << "Деструктор матрицы m1" << endl;
    matr m3 = m1 + m2;
    cout << "Деструктор матрицы m3" << endl;
    matr m4 = m1 - m2;
    cout << "Деструктор матрицы m4" << endl;
    matr m5 = -m1;
    cout << "Деструктор матрицы m5" << endl;
    double scalar_prod_m1_m2 = m1 * m2;
    cout << "Результат умножения матриц m1 и m2: " << scalar_prod_m1_m2 << endl;

    // Создаются векторы
    cout << "Деструктор вектора v1" << endl;
    vect v3 = v1 + v2;
    cout << "Деструктор вектора v3" << endl;
    vect v4 = v1 - v2;
    cout << "Деструктор вектора v4" << endl;
    vect v5 = -v1;
    cout << "Деструктор вектора v5" << endl;
    double scalar_prod_v1_v2 = v1 * v2;
    cout << "Результат скалярного произведения векторов v1 и v2: " << scalar_prod_v1_v2 << endl;

    return 0;
}
