#include "my_func.h"

extern unsigned char flagShowStep;
extern unsigned char flagShowRootPoint;
extern unsigned char flagShowDebug;

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
    if(isnan(rootPresent(f, xl, xr)))
    {
		if(flagShowDebug)
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
	if(flagShowStep)
		printf("Find root for %d steps\n", stepcount); //статистика
	return minx;	
}

float rootFindDiv2(float (*f)(float), float xl, float xr, float eps)
{
    if(rootPresent(f, xl, xr) != 1)
    {
		if(flagShowDebug)
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
			if(flagShowStep)
				printf("Find root for %d steps\n", stepcount);
			return xr;
		}
		if(f(xl) == 0)
		{ // нашли решение на левой границе
			if(flagShowStep)
				printf("Find root for %d steps\n", stepcount);
			return xl;
		}
		if(f(xl) * f(xm) < 0) //если знак отличается
			xr = xm;
		else
			xl = xm;
	}
	if(flagShowStep)
    	printf("Find root for %d steps\n", stepcount); //статистика
	return (xl + xr) / 2;
}

float rootFindChord(float (*f)(float), float xl, float xr, float eps)
{
    if(rootPresent(f, xl, xr) != 1)
    {
		if(flagShowDebug)
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
	if(flagShowStep)
		printf("Find root for %d steps\n", stepcount);
	return xr;
}

void findAllRoot(float (*f)(float), float (*fM)(float (*f)(float), float, float, float), float xl, float xr, float eps, float *minx, float *maxx)
{
	float step = eps * 100;
	float xxr = xl + step;
	do
	{
		float result = fM(f, xl, xxr, eps);
		if(!isnan(result)) // not equal NAN
		{
			printf("Find root = %f\n", result);
			if(result < *minx) *minx = result;
			if(result > *maxx) *maxx = result;
		}
		xl = xxr;
		xxr += step;
		if(xl < 0 && (-xl) < eps)
			xl = 0;
		if(xxr > 0 && xxr < eps)
			xxr = 0;
	} while (xxr < xr);	
}

float nearestAbove(float y, float y1, float y2, float y3)
{
	if(y1 > y && (y1 < y2 || y2 < y) && (y1 < y3 || y3 < y)) return y1;
	if(y2 > y && (y2 < y1 || y1 < y) && (y2 < y3 || y3 < y)) return y2;
	if(y3 > y && (y3 < y1 || y1 < y) && (y3 < y2 || y2 < y)) return y3;
	return y;	
}

float nearestBelow(float y, float y1, float y2, float y3)
{
	if(y1 < y && (y1 > y2 || y2 > y) && (y1 > y3 || y3 > y)) return y1;
	if(y2 < y && (y2 > y1 || y1 > y) && (y2 > y3 || y3 > y)) return y2;
	if(y3 < y && (y3 > y1 || y1 > y) && (y3 > y2 || y2 > y)) return y3;
	return y;	
}

float calcIntegralSquare(float (*f_1)(float), float (*f_2)(float), float (*f_3)(float), float xl, float xr, float eps, float sX, float sY)
{
	float sum = 0, x, y;
	x = sX;
	y = sY;
	while(x > xl)
	{
		float res_1 = f_1(x);
		float res_2 = f_2(x);
		float res_3 = f_3(x);
		if(isnan(res_1)) res_1 = 999;
		if(isnan(res_2)) res_2 = 999;
		if(isnan(res_3)) res_3 = 999;
		float na = nearestAbove(y, res_1, res_2, res_3);
		float nb = nearestBelow(y, res_1, res_2, res_3);
		if(na - nb <= eps * 3) break;		
		if(y == na)
		{
			if(fabs(res_1 - y) < eps) na = res_1;
			if(fabs(res_2 - y) < eps) na = res_2;
			if(fabs(res_3 - y) < eps) na = res_3;
		}
		if(y == nb)
		{
			if(fabs(y - res_1) < eps) nb = res_1;
			if(fabs(y - res_2) < eps) nb = res_2;
			if(fabs(y - res_3) < eps) nb = res_3;
		}		
		if(y == na || y == nb)
			return -1;
		sum += (fabs(na) + fabs(nb)) * eps;
		y = na - (na - nb) / 2;
		x -= eps;
	}
	x = sX + eps;
	y = sY;
	while(x < xr)
	{
		float res_1 = f_1(x);
		float res_2 = f_2(x);
		float res_3 = f_3(x);
		if(isnan(res_1)) res_1 = 999;
		if(isnan(res_2)) res_2 = 999;
		if(isnan(res_3)) res_3 = 999;
		float na = nearestAbove(y, res_1, res_2, res_3);
		float nb = nearestBelow(y, res_1, res_2, res_3);
		if(na - nb <= eps * 3) break;
		if(y == na)
		{
			if(fabs(res_1 - y) < eps) na = res_1;
			if(fabs(res_2 - y) < eps) na = res_2;
			if(fabs(res_3 - y) < eps) na = res_3;
		}
		if(y == nb)
		{
			if(fabs(y - res_1) < eps) nb = res_1;
			if(fabs(y - res_2) < eps) nb = res_2;
			if(fabs(y - res_3) < eps) nb = res_3;
		}
		if(y == na || y == nb)
			return -1;
		sum += (fabs(na) + fabs(nb)) * eps;
		y = na - (na - nb) / 2;
		x += eps;
	}
	return sum;
}