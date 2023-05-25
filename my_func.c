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

unsigned char rootPresent(float (*f)(float), float xl, float xr)
{
    if(f(xl) * f(xr) >= 0) // если знак одинаковый, то корней нет
	    return 0;
    return 1;
}

float rootFindLineSearch(float (*f)(float), float xl, float xr, float eps, unsigned int *step)
{   
	if(!rootPresent(f, xl, xr))
	    return NAN; 
	while(xl < xr)
	{
		if(rootPresent(f, xl, xl + eps))
			return xl + eps/ 2;
		*step += 1;
		xl += eps;
	}
	return NAN;	
}

float rootFindDiv2(float (*f)(float), float xl, float xr, float eps, unsigned int *step)
{
    if(!rootPresent(f, xl, xr))
	    return NAN;
	float xm;
	while(fabs(xr-xl) > eps)
	{ 
		*step += 1;
		xm = (xl + xr) / 2; // середина отрезка
		if(rootPresent(f, xl, xm))
			xr = xm;
		else
			xl = xm;
	}
	return (xl + xr) / 2;
}

float rootFindChord(float (*f)(float), float xl, float xr, float eps, unsigned int *step)
{
    if(!rootPresent(f, xl, xr))
	    return NAN;
	while(fabs(xr - xl) > eps)
	{
		xl = xr - (xr - xl) * f(xr) / (f(xr) - f(xl));
		xr = xl - (xl - xr) * f(xl) / (f(xl) - f(xr));
		*step += 1;
	}
	return xr;
}

void findAllRoot(float (*f)(float), float (*fM)(float (*f)(float), float, float, float, unsigned int *), float xl, float xr, float eps, float *minx, float *maxx)
{
	if(flagShowRootPoint)
	{
		if(fM == rootFindLineSearch) printf("Linear method search root:\n");
		if(fM == rootFindDiv2) printf("Div2 method search root:\n");
		if(fM == rootFindChord) printf("Chord method search root:\n");
	}
	unsigned int stepcount = 0;
	unsigned char findRoot = 0;
	float step = eps * 100;
	float xxr = xl + step;
	do
	{
		float result = fM(f, xl, xxr, eps, &stepcount);
		if(!isnan(result)) // not equal NAN
		{		
			findRoot = 1;	
			if(flagShowRootPoint) printf("Find root = %f\n", result);
			if(flagShowStep)
				printf("Step to find root - %u\n", stepcount);
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
	if(!findRoot && flagShowRootPoint)
		printf("Root not find.");
}

float getBetween(float y, float y1, float y2, float y3, float *na, float *nb)
{
	if(isnan(y1)) y1 = 999;
	if(isnan(y2)) y2 = 999;
	if(isnan(y3)) y3 = 999;
	if(y == y1 || y == y2 || y == y3) return 0;
	if(y > y1) { 
		if(y > y2) {
			if(y > y3) return 0;				
			else {
				if(y1 > y2) {
					*na = y3, *nb = y1;
					return y3 - y1;
				} 
				else {
					*na = y3, *nb = y2;
					return y3 - y2;
				}
			}
		} else {
			if(y < y3) {
				if(y3 < y2)	{
					*na = y3, *nb = y1;
					return y3 - y1;
				}
				else {
					*na = y2, *nb = y1;
					return y2 - y1;
				}
			} else {
				if(y1 > y3) {
					*na = y2, *nb = y1;
					return y2 - y1;
				}
				else {
					*na = y2, *nb = y3;
					return y2 - y3;
				}
			}
		}
	} else {
		if(y < y2) {
			if(y < y3) return 0;
			else {
				if(y1 > y2) {
					*na = y2, *nb = y3;
					return y2 - y3;
				}
				else {
					*na = y1, *nb = y3;
					return y1 - y3;
				}
			}
		} else {
			if(y > y3) {
				if(y2 > y3) {
					*na = y1, *nb = y2;
					return y1 - y2;
				}
				else {
					*na = y1, *nb = y3;
					return y1 - y3;
				}
			} else {
				if(y1 > y3) {
					*na = y3, *nb = y2;
					return y3 - y2;
				}
				else {
					*na = y1, *nb = y2;
					return y1 - y2;
				}
			}			
		}
	}
}
// Считает кол-во нулей перед значимой частью
unsigned char getNumZero(float value)
{
	unsigned char result = 0;
	while(value + 0.1 < 1)
	{
		result++;
		value *= 10;
	}
	return result;
}

float calcIntegralSquare(float xl, float xr, float eps, float sX, float sY)
{
	float sum = 0; // площадь
	float x, y, na, nb, py, ty, res;
	unsigned char ordEps = getNumZero(eps);
	/* Идем от указанной точки влево. Проверяем значение функций в искомой точке, если положение указанной точки
	*  по оси Y оказывается за пределами диапазона функций, то существует разрыв, выходим. Если она оказывается
	*  между найденными значениями, то ищем ближайшие к указанной точке и считаем расстояние до них.
	*/
	y = sY, py = sY, x = sX;
	if(x < xl) return -1;
	while(x > xl)
	{
		res = getBetween(y, f1(x), f2(x), f3(x), &na, &nb);
		if(res == 0)
			return -1;		
		if(na - nb <= eps * 3 * ordEps)
			break;		
		if(y == na || y == nb)
			return -1;
		sum += res * eps;
		ty = py;
		py = y;
		y = ty + ((na + nb) / 2 - ty) * 1.3;
		x -= eps;
	}
	y = sY, py = sY, x = sX;
	if(x > xr) return -1;
	while(x < xr)
	{		
		res = getBetween(y, f1(x), f2(x), f3(x), &na, &nb);
		if(res == 0)
			return -1;		
		if(na - nb <= eps * 3 * ordEps)
			break;		
		if(y == na || y == nb)
			return -1;
		sum += res * eps;
		ty = py;
		py = y;
		y = ty + ((na + nb) / 2 - ty) * 1.3;
		x += eps;
	}
	return sum;
}

float calcIntegralTrap(float xl, float xr, float eps, float sX, float sY)
{
	float sum = 0; // площадь
	float x, y, na, nb, py, ty, res;
	unsigned char ordEps = getNumZero(eps);
	/* Идем от указанной точки влево. Проверяем значение функций в искомой точке, если положение указанной точки
	*  по оси Y оказывается за пределами диапазона функций, то существует разрыв, выходим. Если она оказывается
	*  между найденными значениями, то ищем ближайшие к указанной точке и считаем расстояние до них.
	*/
	y = sY, py = sY, x = sX - eps;
	if(x < xl) return -1;
	while(x > xl)
	{
		res = getBetween(y, f1(x), f2(x), f3(x), &na, &nb);
		if(res == 0)
			return -1;		
		if(na - nb <= eps * 3 * ordEps)
			break;		
		if(y == na || y == nb)
			return -1;
		sum += eps * 0.5 * (res + getBetween(y, f1(x + eps), f2(x + eps), f3(x + eps), &na, &nb));
		ty = py;
		py = y;
		y = ty + ((na + nb) / 2 - ty) * 1.3;
		x -= eps;
	}
	y = sY, py = sY, x = sX + eps;
	if(x > xr) return -1;
	while(x < xr)
	{		
		res = getBetween(y, f1(x), f2(x), f3(x), &na, &nb);
		if(res == 0)
			return -1;		
		if(na - nb <= eps * 3 * ordEps)
			break;		
		if(y == na || y == nb)
			return -1;
		sum += eps * 0.5 * (res + getBetween(y, f1(x - eps), f2(x - eps), f3(x - eps), &na, &nb));
		ty = py;
		py = y;
		y = ty + ((na + nb) / 2 - ty) * 1.3;
		x += eps;
	}
	return sum;
}

float calcIntegralSimpson(float xl, float xr, float eps, float sX, float sY)
{
	float sum = 0; // площадь
	float x, y, na, nb, py, ty, res, pres, res_05;
	unsigned char ordEps = getNumZero(eps);
	/* Идем от указанной точки влево. Проверяем значение функций в искомой точке, если положение указанной точки
	*  по оси Y оказывается за пределами диапазона функций, то существует разрыв, выходим. Если она оказывается
	*  между найденными значениями, то ищем ближайшие к указанной точке и считаем расстояние до них.
	*/
	y = sY, py = sY, x = sX - eps;
	if(x < xl) return -1;
	while(x > xl)
	{
		res = getBetween(y, f1(x), f2(x), f3(x), &na, &nb);
		pres = getBetween(y, f1(x + eps), f2(x + eps), f3(x + eps), &na, &nb);
		res_05 = getBetween(y, f1(x + eps / 2), f2(x + eps / 2), f3(x + eps / 2), &na, &nb);
		if(res == 0)
			return -1;		
		if(na - nb <= eps * 3 * ordEps)
			break;		
		if(y == na || y == nb)
			return -1;
		sum += eps / 6.0 * (res + 4.0 * res_05 + pres);
		ty = py;
		py = y;
		y = ty + ((na + nb) / 2 - ty) * 1.3;
		x -= eps;
	}
	y = sY, py = sY, x = sX + eps;
	if(x > xr) return -1;
	while(x < xr)
	{		
		res = getBetween(y, f1(x), f2(x), f3(x), &na, &nb);
		pres = getBetween(y, f1(x + eps), f2(x + eps), f3(x + eps), &na, &nb);
		res_05 = getBetween(y, f1(x + eps / 2), f2(x + eps / 2), f3(x + eps / 2), &na, &nb);
		if(res == 0)
			return -1;		
		if(na - nb <= eps * 3 * ordEps)
			break;		
		if(y == na || y == nb)
			return -1;
		sum += eps / 6.0 * (res + 4.0 * res_05 + pres);
		ty = py;
		py = y;
		y = ty + ((na + nb) / 2 - ty) * 1.3;
		x += eps;
	}
	return sum;
}