#include <stdio.h>
#include <stdlib.h>

// 1. 定义结构体
struct result {
    int *arr; // 动态数组指针
    int len;  // 有效元素个数
};

// 2. 打印函数
void print_result(struct result result) {
    for (int i = 0; i < result.len; i++) {
        printf("%d ", result.arr[i]);
    }
    printf("\n");
}

// 3. 拼接函数
void your_concat(int arr1[], int len1, int arr2[], int len2, struct result *result) {
    // 分配内存：长度为 len1 + len2
    result->arr = (int *)malloc((len1 + len2) * sizeof(int));
    if (result->arr == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    
    // 拷贝 arr1
    for (int i = 0; i < len1; i++) {
        result->arr[i] = arr1[i];
    }
    // 拷贝 arr2
    for (int i = 0; i < len2; i++) {
        result->arr[len1 + i] = arr2[i];
    }
    result->len = len1 + len2;
}

// 4. 排序函数（这里使用冒泡排序，方便你理解底层交换）
void your_sort(struct result *result) {
    for (int i = 0; i < result->len - 1; i++) {
        for (int j = 0; j < result->len - 1 - i; j++) {
            if (result->arr[j] > result->arr[j + 1]) {
                // 交换
                int temp = result->arr[j];
                result->arr[j] = result->arr[j + 1];
                result->arr[j + 1] = temp;
            }
        }
    }
}

// 5. 去重函数（基于排序后的数组，双指针原地压缩）
void your_dedup(struct result *result) {
    if (result->len <= 1) return; // 长度0或1无需去重

    int j = 0; // 慢指针，指向去重后数组的最后一个有效元素
    for (int i = 1; i < result->len; i++) { // 快指针，遍历整个数组
        if (result->arr[i] != result->arr[j]) {
            j++;
            result->arr[j] = result->arr[i]; // 将不重复的元素移到前面
        }
    }
    // 更新去重后的有效长度
    result->len = j + 1;
}

// 6. 主函数（轻微修正了传参，保证正确运行）
int main() {
    int arr1[] = { 6, 1, 2, 1, 9, 1, 3, 2, 6, 2 };
    int arr2[] = { 4, 2, 2, 1, 6, 2 };
    int len1 = sizeof(arr1) / sizeof(arr1[0]);
    int len2 = sizeof(arr2) / sizeof(arr2[0]);

    struct result result;
    // 修正：传入 &result，让函数能修改到 main 里的变量
    your_concat(arr1, len1, arr2, len2, &result); 
    
    print_result(result); // 打印拼接后的数组
    your_sort(&result);
    print_result(result); // 打印排序后的数组
    your_dedup(&result);
    print_result(result); // 打印去重后的数组
    
    free(result.arr);     // 释放动态分配的内存
    return 0;
}