#include <stdio.h>
#include <stdlib.h>

int main() {
    int *pArr;
    int N;

    printf("크기를 입력하세요: ");
    scanf("%d", &N);

    pArr = (int*)malloc(sizeof(int) * N);

    if (pArr == NULL) {
        printf("malloc error\n");
    }

    for (int i = 0; i < N; ++i) {
        pArr[i] = i;
    }

    for (int i = 0; i < N; ++i) {
        printf("%d\n", pArr[i]);
    }

    free(pArr);

    return 0;
}