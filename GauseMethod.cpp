#include <iostream>

using namespace std;

double* GausMethod(double** koefChysla, double* vilniyKoef, int n)
{
    double* x, max;
    int k, index;
    const double eps = 0.00001;  // точність до десятитичисячних
    x = new double[n];
    k = 0;
    while (k < n) {
        // Пошук рядка з максимальним koefChysla[i][k]
        max = abs(koefChysla[k][k]);
        index = k;
        for (int i = k + 1; i < n; i++) {
            if (abs(koefChysla[i][k]) > max) {
                max = abs(koefChysla[i][k]);
                index = i;
            }
        }
        // Перестановка рядків
        if (max < eps) {
            // нема нульових елементів по діагоналі
            cout << "Немає розвязку. Нульовий стовпчик.";
            return 0;
        }
        for (int j = 0; j < n; j++) {
            double temp = koefChysla[k][j];
            koefChysla[k][j] = koefChysla[index][j];
            koefChysla[index][j] = temp;
        }
        double temp = vilniyKoef[k];
        vilniyKoef[k] = vilniyKoef[index];
        vilniyKoef[index] = temp;
        // Нормалізація виразів
        for (int i = k; i < n; i++) {
            double temp = koefChysla[i][k];
            if (abs(temp) < eps) continue; // для нульового коефіцієнта пропустити
            for (int j = 0; j < n; j++) {
                koefChysla[i][j] = koefChysla[i][j] / temp;
            }
            vilniyKoef[i] = vilniyKoef[i] / temp;
            if (i == k)  continue; // рівняння не вираховує само себе
            for (int j = 0; j < n; j++) {
                koefChysla[i][j] = koefChysla[i][j] - koefChysla[k][j];
            }
            vilniyKoef[i] = vilniyKoef[i] - vilniyKoef[k];
        }
        k++;
    }
    // Обернена підстановка
    for (k = n - 1; k >= 0; k--) {
        x[k] = vilniyKoef[k];
        for (int i = 0; i < k; i++) {
            vilniyKoef[i] = vilniyKoef[i] - koefChysla[i][k] * x[k];
        }
    }
    return x;
}
// Вивід сиситеми рівнянь
void SystemOut(double** koefChysla, double* viliyKoef, int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << koefChysla[i][j] << "*X" << j + 1;
            if (j < n - 1)
                cout << " + ";
        }
        cout << " = " << viliyKoef[i] << endl;
    }
    return;
}
int main()
{
    double** koefChysla, * vilniyKoef, * x;
    int n;
    cout << "Введіть кількість виразів (число)= ";
    cin >> n;
    koefChysla = new double* [n];
    vilniyKoef = new double[n];
    for (int i = 0; i < n; i++) {
        cout << "Вираз #" << i + 1 << "\n";
        koefChysla[i] = new double[n];
        for (int j = 0; j < n; j++) {
            cout << "X" << j + 1 << " = ";
            cin >> koefChysla[i][j];
        }
        cout << "у[" << i + 1 << "]= ";
        cin >> vilniyKoef[i];
    }
    SystemOut(koefChysla, vilniyKoef, n);
    x = GausMethod(koefChysla, vilniyKoef, n);
    for (int i = 0; i < n; i++) {
        cout << "x[" << i + 1 << "]=" << x[i] << endl;
    }
    cin.get(); cin.get();
    return 0;
}