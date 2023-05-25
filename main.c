#include <stdio.h>
#include <unistd.h>
#include "my_func.h"

unsigned char flagShowStep = 0; // флаг отображения кол-ва шагов при нахождении корней
unsigned char flagShowRootPoint = 0; // флаг отображения точек пересечения функций
unsigned char flagShowDebug = 0; // флаг вывода сообщений отладки

int main(int argc, char **argv)
{
    int option = 0;
    float xl = -6, xr = 10, eps = 1e-3;
    float minx = 0, // минимальный найденный корень
          maxx = 0; // максимальный найденный корень
    float r_eps; // читаемый с командной строки eps
    float px = 0, // координата по оси X для указания области рассчета площади
          py = 0; // координата по оси Y для указания области рассчета площади

    if(argc == 1)
    {
        printf("-h for help.\n");
    }
    do
    {
        option = getopt(argc,argv,"hose:x:y:");
        if(option == -1)
            break;
        
        switch (option)
        {            
            case 'h':
                printf("Equation root finder application and calc area square.\n");
                printf("-o show of intersection points of functions.\n");
                printf("-s show of interation numbers.\n");
                printf("-e x.xxx set eps value (0.001 default).\n");
                printf("-x x.xx set X coord to calc area square.\n");
                printf("-y y.yy set Y coord to calc area square.\n");
                return 0;
                break;
            case 'o':
                flagShowRootPoint = 1;
                break;
            case 's':
                flagShowStep = 1;
                break;
            case 'e':
                r_eps = atof(optarg);
                if(!isnan(r_eps) && r_eps <= 0.1 && r_eps >= 1e-12) eps = r_eps;
                break;
            case 'x':
                if(!isnan(atof(optarg))) px = atof(optarg);
                break;
            case 'y':
                if(!isnan(atof(optarg))) py = atof(optarg);
                break;
            case '?':
                printf("Unknown option.\n");
                printf("-h for help.\n");
                break;
        }
    } while(option != -1);

    printf("Eps value is %f\n", eps);
    printf("X value is %f\n", px);
    printf("Y value is %f\n", py);
    
    if(flagShowRootPoint) printf("Search intersection points of functions 1 and 2:\n");
    findAllRoot(f1_2, rootFindLineSearch, xl, xr, eps, &minx, &maxx);
    findAllRoot(f1_2, rootFindDiv2, xl, xr, eps, &minx, &maxx);
    findAllRoot(f1_2, rootFindChord, xl, xr, eps, &minx, &maxx);

    if(flagShowRootPoint) printf("Search intersection points of functions 1 and 3:\n");
    findAllRoot(f1_3, rootFindLineSearch, xl, xr, eps, &minx, &maxx);
    findAllRoot(f1_3, rootFindDiv2, xl, xr, eps, &minx, &maxx);
    findAllRoot(f1_3, rootFindChord, xl, xr, eps, &minx, &maxx);

    if(flagShowRootPoint) printf("Search intersection points of functions 2 and 3:\n");
    findAllRoot(f2_3, rootFindLineSearch, xl, xr, eps, &minx, &maxx);
    findAllRoot(f2_3, rootFindDiv2, xl, xr, eps, &minx, &maxx);
    findAllRoot(f2_3, rootFindChord, xl, xr, eps, &minx, &maxx);

    printf("Figure area calculation:\n");
    printf("rectangle method: ");
    float resSq = calcIntegralSquare(minx, maxx, eps, px, py);
    if(resSq < 0) printf("calc error\n"); 
    else printf("%f\n", resSq);

    printf("trapezoidal method: ");
    resSq = calcIntegralSquare(minx, maxx, eps, px, py);
    if(resSq < 0) printf("calc error\n"); 
    else printf("%f\n", resSq);

    printf("Simpson method: ");
    resSq = calcIntegralSimpson(minx, maxx, eps, px, py);
    if(resSq < 0) printf("calc error\n"); 
    else printf("%f\n", resSq);

    return 0;
}