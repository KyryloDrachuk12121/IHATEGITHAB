#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int age;
    double salary;
} Employee;

void exch(void* a, void* b, size_t size) {
    unsigned char* pa = (unsigned char*)a;
    unsigned char* pb = (unsigned char*)b;
    unsigned char tmp;
    for (size_t i = 0; i < size; i++) {
        tmp = pa[i];
        pa[i] = pb[i];
        pb[i] = tmp;
    }
}

void shell_sort(void* arr, int N, size_t size, int (*cmp)(const void*, const void*)) {
    int h = 1;
    while (h < N / 3) {
        h = 3 * h + 1;
    }
    while (h >= 1) {
        for (int i = h; i < N; i++) {
            for (int j = i; j >= h; j -= h) {
                void* current = (char*)arr + j * size;
                void* prev = (char*)arr + (j - h) * size;
                if (cmp(current, prev) < 0) {
                    exch(current, prev, size);
                }
                else {
                    break;
                }
            }
        }
        h /= 3;
    }
}

int compare_by_age(const void* a, const void* b) {
    const Employee* ea = a;
    const Employee* eb = b;
    return ea->age - eb->age;
}

int compare_by_salary(const void* a, const void* b) {
    const Employee* ea = a;
    const Employee* eb = b;
    if (ea->salary < eb->salary)
        return -1;
    else if (ea->salary > eb->salary)
        return 1;
    else
        return 0;
}

int compare_by_name(const void* a, const void* b) {
    const Employee* ea = a;
    const Employee* eb = b;
    return strcmp(ea->name, eb->name);
}

void print_employees(Employee* employees, int N) {
    for (int i = 0; i < N; i++) {
        printf("%s, Age: %d, Salary: %.2f\n",
            employees[i].name, employees[i].age, employees[i].salary);
    }
    printf("\n");
}

int main() {

    Employee employees[] = {
        {"Alice", 25, 50000},
        {"Bob", 30, 70000},
        {"Charlie", 22, 45000},
        {"Dave", 35, 80000}
    };
    int N = sizeof(employees) / sizeof(employees[0]);

    Employee* temp = malloc(N * sizeof(Employee));
    if (temp == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return 1;
    }

    memcpy(temp, employees, N * sizeof(Employee));
    shell_sort(temp, N, sizeof(Employee), compare_by_age);
    printf("Sorted by Age:\n");
    print_employees(temp, N);

    memcpy(temp, employees, N * sizeof(Employee));
    shell_sort(temp, N, sizeof(Employee), compare_by_salary);
    printf("Sorted by Salary:\n");
    print_employees(temp, N);

    memcpy(temp, employees, N * sizeof(Employee));
    shell_sort(temp, N, sizeof(Employee), compare_by_name);
    printf("Sorted by Name:\n");
    print_employees(temp, N);

    free(temp);
    return 0;
}

