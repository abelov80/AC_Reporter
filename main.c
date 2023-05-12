#include <stdio.h>
#include <unistd.h>
#include "my_func.h"

unsigned char flagShowStep = 1; // флаг отображения кол-ва шагов при нахождении корней
unsigned char flagShowRootPoint = 1; // флаг отображения точек пересечения функций
unsigned char flagShowDebug = 0; // флаг вывода сообщений отладки

int main(int argc, char **argv)
{
    int option = 0;

    if(argc == 1)
    {
        printf("-h for help.\n");
    }
    do
    {
        option = getopt(argc,argv,"hopt");
        if(option == -1)
            break;
        
        switch (option)
        {            
            case 'h':
                printf("Equation root finder application.\n");
                printf("-o show of intersection points of functions.\n");
                printf("-p show of interation numbers.\n");
                printf("-t test function xxXX (xx - function, XX - test).\n");
                return 0;
                break;
            case 'o':
                flagShowRootPoint = 1;
                break;
            case 'p':
                flagShowStep = 1;
                break;
            case 't':
                
                break;
            case '?':
                printf("Unknown option.\n");
                printf("-h for help.\n");
                break;
        }
    } while(option != -1);

    float xl = -6.5, xr = 10, eps = 1e-3;
    
    printf("Search intersection points of functions 1 and 2:\n");
    printf("Linear method search root:\n");
    findAllRoot(f1_2, rootFindLineSearch, xl, xr, eps);
    printf("Div2 method search root:\n");
    findAllRoot(f1_2, rootFindDiv2, xl, xr, eps);
    printf("Chord method search root:\n");
    findAllRoot(f1_2, rootFindChord, xl, xr, eps);

    printf("Search intersection points of functions 1 and 3:\n");
    printf("Linear method search root:\n");
    findAllRoot(f1_3, rootFindLineSearch, xl, xr, eps);
    printf("Div2 method search root:\n");
    findAllRoot(f1_3, rootFindDiv2, xl, xr, eps);
    printf("Chord method search root:\n");
    findAllRoot(f1_3, rootFindChord, xl, xr, eps);

    printf("Search intersection points of functions 2 and 3:\n");
    printf("Linear method search root:\n");
    findAllRoot(f2_3, rootFindLineSearch, xl, xr, eps);
    printf("Div2 method search root:\n");
    findAllRoot(f2_3, rootFindDiv2, xl, xr, eps);
    printf("Chord method search root:\n");
    findAllRoot(f2_3, rootFindChord, xl, xr, eps);

    //printf("Linear search root: %f\n", rootFindLineSearch(f1_2, xl, xr, eps));
	//printf("Div2 root: %f\n", rootFindDiv2(f1_2, xl, xr, eps));
    //printf("Chord root: %f\n", rootFindChord(f1_2, xl, xr, eps));
    return 0;
}