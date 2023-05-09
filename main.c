#include <stdio.h>
#include <math.h>

/* Функции, задающие кривые */
float f1(float x)
{
    return 0.6 * x + 3;
}

float f2(float x)
{
    return pow(x - 2, 3) - 1;
}

float f3(float x)
{
    return 3 / x;
}

float f1_2(float x)
{
	return f1(x) - f2(x);
}

float f1_3(float x)
{
	return f1(x) - f3(x);
}

float f2_3(float x)
{
	return f2(x) - f3(x);
}


// Метод нахождения корня "Линейный поиск"
float rootFindLineSearch(float (*f)(float), float xl, float xr, float eps)
{
	float x, minx = xl,	nextstep;
	nextstep = fabs(xr - xl) / (1 / eps); //разбиваем на отрезки интервал
	int stepcount = 0;
	for(x = xl; x < xr; x += nextstep, stepcount++)
	{
		if(fabs(f(x)) < fabs(f(minx)))
			minx = x;
	}
	float result = f(minx);
    result = floor(fabs(result));
	if(result == 0)
	{
		printf("Find root for %d steps\n", stepcount); //статистика
		return minx;
	}
	printf("No root find\n");
	return NAN;
}

// выделение знака числа
float signF(float value)
{
    return value / fabs(value);
}

// Метод нахождения корня "Деление отрезка пополам"
float rootFindDiv2(float (*f)(float), float xl, float xr, float eps)
{
	int stepcount = 0; //число шагов
	float xm;
	while(fabs(xr-xl) > eps)
	{ //вещественный модуль разницы
		stepcount++;
		xm = (xl + xr) / 2; // середина отрезка
		if(f(xr) == 0)
		{ // нашли решение на правой границе
			printf("Find root for %d steps\n", stepcount);
			return xr;
		}
		if(f(xl) == 0)
		{ // нашли решение на левой границе
			printf("Find root for %d steps\n", stepcount);
			return xl;
		}
		if(signF(f(xl)) != signF(f(xm))) //если знак отличается
			xr = xm;
		else
			xl = xm;
	}
    
	printf("Find root for %d steps\n", stepcount); //статистика
	return (xl + xr) / 2;
}

// Метод нахождения корня "Хорды"
float rootFindChord(float (*f)(float), float xl, float xr, float eps) {
	int stepcount = 0;
	while(fabs(xr - xl) > eps)
	{
		xl = xr - (xr - xl) * f(xr) / (f(xr) - f(xl));
		xr = xl - (xl - xr) * f(xl) / (f(xl) - f(xr));
		stepcount++;
	}
	printf("\nFind root for %d steps\n", stepcount);
	return xr;
}

/*
// Метод деления отрезка пополам
double bisection(double (*f)(double), double a, double b, double eps) {
    double c;
    while (b - a >= eps) {
        c = (a + b) / 2;
        if (f(c) == 0)
            return c;
        else if (f(a) * f(c) < 0)
            b = c;
        else
            a = c;
    }
    return (a + b) / 2;
}

// Метод хорд (секущих)
double chord(double (*f)(double), double a, double b, double eps) {
    double fa = f(a), fb = f(b), c;
	unsigned int flagReload = 1000000;
    while (fabs(b - a) >= eps) {
        c = a - fa * (b - a) / (fb - fa);
        if (f(c) == 0)
            return c;
        else if (f(a) * f(c) < 0) {
            b = c;
            fb = f(c);
        } else {
            a = c;
            fa = f(c);
        }
		flagReload--;
		if(!flagReload) {
			printf("Function chord hangs. break..\n");
			break;
		}
    }
    return a - fa * (b - a) / (fb - fa);
}

// Метод Ньютона
double newton(double (*f)(double), double (*df)(double), double x0, double eps) {
    double x1 = x0 - f(x0) / df(x0);
    while (fabs(x1 - x0) >= eps) {
        x0 = x1;
        x1 = x0 - f(x0) / df(x0);
    }
    return x1;
}

// Комбинированный метод (хорд и касательных)
double combined(double (*f)(double), double (*df)(double), double a, double b, double eps) {
    double fa = f(a), fb = f(b), c;
    while (fabs(b - a) >= eps) {
        c = a - fa * (b - a) / (fb - fa);
        if (f(c) == 0)
            return c;
        else if (f(a) * f(c) < 0) {
            b = c;
            fb = f(c);
        } else {
            double dfc = df(c);
            if (dfc == 0)
                return c;
            else if (dfc > 0)
                b = c;
            else
                a = c;
        }
    }
    return a - fa * (b - a) / (fb - fa);
}

// Функция, вычисляющая площадь фигуры
double area(double (*f1)(double), double (*f2)(double), double (*f3)(double), double a, double b, double eps1, double eps2) {
    printf("start bisection function\n");
	double x1 = bisection(f1, a, b, eps1);
	printf("start chord function\n");
    double x2 = chord(f2, a, b, eps1);
	printf("start newton function\n");
    double x3 = newton(f3, f3, b, eps1);
	printf("start combined x4 function\n");
    double x4 = combined(f1, f1, a, b, eps1);
	printf("start combined x5 function\n");
    double x5 = combined(f2, f2, a, b, eps1);
	printf("start combined x6 function\n");
    double x6 = combined(f3, f3, a, b, eps1);
	printf("start fabs s1 function\n");
    double s1 = fabs(x2 - x1) * (f1(x1) + f2(x1)) / 2;
	printf("start fabs s2 function\n");
    double s2 = fabs(x4 - x3) * (f1(x3) + f3(x3)) / 2;
	printf("start fabs s3 function\n");
    double s3 = fabs(x6 - x5) * (f2(x5) + f3(x5)) / 2;
	printf("start fabs s4 function\n");
    double s4 = fabs(b - a) * (f1(a) + f1(b)) / 2;
	printf("start fabs s5 function\n");
    double s5 = fabs(b - a) * (f2(a) + f2(b)) / 2;
	printf("start fabs s6 function\n");
    double s6 = fabs(b - a) * (f3(a) + f3(b)) / 2;
    double s = s1 + s2 + s3 - s4 - s5 - s6;
    double h = (b - a) / 1000;
    double x, sum = 0;
	printf("start cycle\n");
    for (int i = 0; i < 1000; i++) {
        x = a + i * h;
        sum += (f1(x) - f2(x)) * (f1(x) - f3(x)) * (f2(x) - f3(x));
    }
    return s + sum * h / 2;
}*/

int main() {
    /*double a = -7, b = 4, eps = 1e-3;
    double s = area(f1, f2, f3, a, b, eps, eps);
    printf("The area of the figure is %lf\n", s);*/
    printf("Linear search root: %f\n", rootFindLineSearch(f1_2, 1, 5, 1e-3));
	printf("Div2 root: %f\n", rootFindDiv2(f1_2, 1, 5, 1e-3));
    return 0;
}