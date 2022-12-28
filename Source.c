#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
#include <Windows.h>

const double pi = 3.14;


double F1(double); // ������ ������� 
double F2(double); // ������ �������
void tabulation(double (*f)(double)); // ������������� �������
void calculate_y(double (*func)(double)); //������ � � ������� �������� F(x)
void print_func(double (*f)(double), double x0, double x1); //������ ������ ������
void menu();// ����( ����������������� ���������) 



void info() // ���������� 
{
    system("title FIO."); // ��������� ��������� ����
    setlocale(LC_ALL, "RUS"); // ����������� ���������
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // ��������� ����������� ������ ������
    SetConsoleTextAttribute(hConsole, 14); // ��������� ����� ������
}

int main() {
    info();

    menu();

    return 0;
}

void menu()
{
    while (1)
    {
        double (*func)(double); //��������� �� �������

        int choose;  //�������� �� ����� ������������ � ����

        do
        {
            system("cls");// ������ �������
            printf("\t\t�������� ������:\n");
            printf("1. 2sin(pi * x) + sin(3pi * x) /3x\n");
            printf("2. �������-�������� �������\n");
            printf("3. �����\n");
            scanf("%d", &choose);
        } while (choose < 1 && choose > 3);

        //�������� � ����� �������� ��������
        if (choose == 1)
            func = F1;
        else if (choose == 2)
            func = F2;
        else
            break; //������� �� ���������


        while (1)
        {
            do
            {
                system("cls");// ������ �������
                printf("1. ����� �������� �������\n");
                printf("2. ����� �������� ������� �� �������� ���������\n");
                printf("3. ��������� ������ �������\n");
                printf("4. �����\n");
                scanf("%d", &choose);

            } while (choose < 1 && choose > 4);
            system("cls");// ������ �������
            if (choose == 1)
            {
                calculate_y(func);
            }
            else if (choose == 2)
            {
                tabulation(func);
            }
            else if (choose == 3)
            {
                double x1, x2;
                printf("������� x1: ");
                scanf("%lf", &x1);

                printf("������� x2: ");
                scanf("%lf", &x2);

                print_func(func, x1, x2);
            }
            else if (choose == 4)
            {
                break;
            }

        }


    }
}



double F1(double x)
{
    if (x == 0)
        return 2 * sin(pi * x);

    return 2 * sin(pi * x) + sin(3 * pi * x) / (3 * x);
}

double F2(double x)
{
    if (x < 0)
    {
        return 1 + (3 + x) / (1 + x * x);
    }

    if (x < 1)
    {
        return sqrt(1 + (1 - x) * (1 - x));
    }

    if (x >= 1)
        return  (1 + x) / (1 + cos(x) * cos(x));
}



void calculate_y(double (*func)(double))
{
    double x;
    system("title ����� �������� �������");
    printf("\t\t����� �������� �������:\n");
    printf("������� x: ");
    scanf("%lf", &x);
    printf("F(%.2lf) = %.2lf\n", x, func(x));

    printf("��� ����������� ������� enter...\n");
    getchar();
    getchar();

}


void tabulation(double (*f)(double))
{
    system("title ������������� �������");
    double x1, x2, step;

    //������ ������������ ������� ��� ����������

    int t;

    printf("������� x1: ");
    scanf("%lf", &x1);

    printf("������� x2: ");
    scanf("%lf", &x2);

    printf("������� h: ");
    scanf("%lf", &step);

    do {
        system("cls");
        printf("�������� ��� ����������: ");
        printf("\n1.[%.1lf; %.1lf]", x1, x2);
        printf("\n2.[%.1lf; %.1lf)", x1, x2);
        printf("\n3.(%.1lf; %.1lf]", x1, x2);
        printf("\n4.(%.1lf; %.1lf)\n", x1, x2);
        scanf("%d", &t);
    } while (t <= 0 && t >= 5);   //���� ������� �� ��������� - ��������� ����


    //������� ������ �������, ���� ��� ������ 2 ��� 4 �����
    if (t == 2 || t == 4)
    {
        x2 -= step;
    }

    //������� ����� �������, ���� ��� ������ 3 ��� 4 �����
    if (t == 3 || t == 4)
    {
        x1 += step;
    }


    printf("X | ");
    for (double i = x1; i <= x2; i += step)
    {
        printf("%.2lf\t", i);
    }
    printf("\nY | ");

    for (double i = x1; i <= x2; i += step)
    {
        printf("%.2lf\t", f(i));
    }

    printf("\n��������� � ����? y/n\n");
    getchar();


    if (getchar() == 'y')
    {
        char path[30];
        printf("������� �������� �����.\n ������: output.txt\n");
        scanf("%s", path);

        FILE* fp;

        if ((fp = fopen(path, "w")) == NULL)
        {
            printf("�� ������� ������� ����");
        }
        else
        {
            fprintf(fp, "X | ");
            for (double i = x1; i <= x2; i += step)
            {
                fprintf(fp, "%.2lf\t", i);
            }
            fprintf(fp, "\nY | ");

            for (double i = x1; i <= x2; i += step)
            {
                fprintf(fp, "%.2lf\t", f(i));
            }

            printf("\n������ ������� ��������� � ����.\n");

        }
        fclose(fp);
    }


    printf("\n��� ����������� ������� enter...\n");
    getchar();
    getchar();
}


void print_func(double (*f)(double), double x0, double x1)
{
    system("title ������ �������");

    int screen_w = 100;
    int screen_y = 60;
    double max_y = f(x0);
    double min_y = f(x0);
    double step_x = (x1 - x0 + 1) / screen_w;

    for (double x = x0; x <= x1; x += step_x)
    {
        double fx = f(x);
        if (max_y < fx)
        {
            max_y = fx;
        }

        if (min_y > fx)
        {
            min_y = fx;
        }

    }

    double step_y = (max_y - min_y + 1) / screen_y;

    for (double y = max_y; y >= min_y; y -= step_y)
    {
        for (double x = x0; x < x1; x += step_x)
        {
            double fx = f(x);
            if (fx >= y && fx < (y + step_y))
            {
                printf("*");
            }
            else if (x == 0 || x > 0 && x - step_y < 0)
                printf("|");
            else if (y == 0 || y < 0 && y + step_y > 0)
                printf("-");
            else
                printf(" ");
        }
        printf("\n");
    }

    printf("��� ����������� ������� enter...\n");
    getchar();
    getchar();
}
