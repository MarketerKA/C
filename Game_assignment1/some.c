#include <stdio.h>
#include <stdlib.h>
#define si 20
int f(int p) {

    int* ptr = (int*)malloc(sizeof(int)); *ptr = p; return p*2;
}
int max(int a, int b){
    if (a > b) return a;
    return b;
}
void swap(int* a1, int* a2){
    int tamp = *a1;
    *a1 = *a2;
    *a2 = tamp;
}
int strt(char * s){
    int  i = 0;
    while (*(s+i) != '\0'){
        i++;
    }
    return i;
}
void print_array(int* array, int size){
    for (int i = 0; i < size; i++){
        printf("%d\n", *(array + i));
    }
}

int main(){
//    int (*f)(int, int);
//    f = max;
//    printf("%d\n", max(4, 7));
//    int a = 1, b = 2;
//    printf("a = %d b = %d\n", a, b);
//    swap(&a, &b);
//    printf("a = %d b = %d\n", a, b);

//    char str[] = "ITP";
//    printf("%d\n", strt(str));
    int array[] = {1,2,3,4};
    int* parray = array;

//    print_array(array, 4);

//    printf("%d\n", *(parray+1));
//    printf("%d\n", (array+1));

//    int p = 10;
//    int* pointer_p = &p;
//    printf("%p\n", pointer_p);
//    printf("%d\n", *pointer_p);

//    int d = 10;
//    char c = 'G';
//    float df = 10.23;
//
//    void *pointer;
//    pointer = &d;
//    printf("%d\n", *(int *)pointer);


    int x1 = 123, x3 = 21;
    int * arrray[] = {&x1, &x3};
//    printf("x1 = %d\nx2 = %d\n", **arrray, **(arrray+1));

   char *strin[] = {"c"
                    "c++"
                    "python"
                    "assembler"};


    return 0;
}