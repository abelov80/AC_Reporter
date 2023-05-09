#include <stdio.h>
#include <my_func.h>

int main() {
    float xl = 1, xr = 4, eps = 1e-3;
    
    printf("Linear search root: %f\n", rootFindLineSearch(f1_2, xl, xr, eps));
	printf("Div2 root: %f\n", rootFindDiv2(f1_2, xl, xr, eps));
    printf("Div2 root: %f\n", rootFindChord(f1_2, xl, xr, eps));
    return 0;
}