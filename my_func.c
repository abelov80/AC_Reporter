#include <my_func.h>

float f1(float x)
{
    return 0.6 * x + 3;
}

float df1(float x)
{
    return 0.6;
}

float f2(float x)
{
    return pow(x - 2, 3) - 1;
}

float df2(float x)
{
    return 3 * pow(x -2, 2);
}

float f3(float x)
{
    return 3 / x;
}

float df3(float x)
{
    return -3 / pow(x, 2);
}

float f1_2(float x)
{
	return f1(x) - f2(x);
}

float df1_2(float x)
{
    return df1(x) - df2(x);
}

float f1_3(float x)
{
	return f1(x) - f3(x);
}

float df1_3(float x)
{
    return df1(x) - df3(x);
}

float f2_3(float x)
{
	return f2(x) - f3(x);
}

float df2_3(float x)
{
    return df2(x) - df3(x);
}

float rootPresent(float (*f)(float), float xl, float xr)
{
    if(f(xl) * f(xr) >= 0) // если знак одинаковый, то корней нет
	    return NAN;
    return 1;
}

float rootFindLineSearch(float (*f)(float), float xl, float xr, float eps)
{
    if(rootPresent(f, xl, xr) != 1)
    {
        printf("No root find\n");
	    return NAN;
    }
	float x, minx = xl,	nextstep;
	nextstep = fabs(xr - xl) / (1 / eps); //разбиваем на отрезки интервал
	int stepcount = 0;
	for(x = xl; x < xr; x += nextstep, stepcount++)
	{
		if(fabs(f(x)) < fabs(f(minx)))
			minx = x;
	}
	printf("Find root for %d steps\n", stepcount); //статистика
	return minx;	
}

float rootFindDiv2(float (*f)(float), float xl, float xr, float eps)
{
    if(rootPresent(f, xl, xr) != 1)
    {
        printf("No root find\n");
	    return NAN;
    }
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
		if(f(xl) * f(xm) < 0) //если знак отличается
			xr = xm;
		else
			xl = xm;
	}
    printf("Find root for %d steps\n", stepcount); //статистика
	return (xl + xr) / 2;
}

float rootFindChord(float (*f)(float), float xl, float xr, float eps)
{
    if(rootPresent(f, xl, xr) != 1)
    {
        printf("No root find\n");
	    return NAN;
    }
	int stepcount = 0;
	while(fabs(xr - xl) > eps)
	{
		xl = xr - (xr - xl) * f(xr) / (f(xr) - f(xl));
		xr = xl - (xl - xr) * f(xl) / (f(xl) - f(xr));
		stepcount++;
	}
	printf("Find root for %d steps\n", stepcount);
	return xr;
}