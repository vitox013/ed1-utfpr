#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    char str1[] = "ola ";
    char str2[] = "dino";


    printf("\n%d\n", strstr(str1, str2) - str1);
    return 0;
}