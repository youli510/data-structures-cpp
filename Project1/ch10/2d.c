#include "exercise.h"



void** creat_2d_arr(int a, int b, size_t type_size) {
    void** arr = (void**)malloc(sizeof(void*) * a);
    for (int i = 0; i < a; i++) {
        arr[i] = malloc(type_size * b);
    }
    return arr;
}
void show_2d_arr(void** arr, int a, int b, size_t type_size, PrintFunc print) {
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            char* row = (char*)arr[i];
            const void* elem = &row[j * type_size];
            print(elem);
        }
        printf("\n");
    }
}
void input_2d_arr(int** str, int a, int b) {
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            scanf("%d", &str[i][j]);
        }
    }
}
void free_2d_arr(void** arr, int a) {
    for (int i = 0; i < a; i++) {
        free(arr[i]);
    }
    free(arr);
}
