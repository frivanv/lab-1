#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

typedef struct { //лин. форма с вещественными коэф-ми
    double* f_coef;
    int len;
} flinear;

typedef struct { //лин. форма с комплексными коэф-ми
    double complex* c_coef;
    int len;
} clinear;

/*ВСЕ ДЛЯ ВЕЩЕСТВЕННЫХ КОЭФФИЦИЕНТОВ*/

void scan_flin(flinear *a) { //ввод лин. формы
    int l = 0;
    double c = 0;

    printf("%s\n", "please type length of linear form");
    scanf("%d", &l);
    a->len = l;
    a->f_coef = malloc(l * sizeof(double));

    printf("%s\n", "please type linear form's coefs");
    for (int i = 0; i < l; i++) {
        scanf("%lf", &c);
        a->f_coef[i] = c;
    }

    printf("\n");
}

void print_flin (flinear a) { //вывод лин. формы
    for (int i = 0; i < a.len - 1; i++) {
        if (a.f_coef[i] != 0) {
            printf("%fx%d + ", a.f_coef[i], i);
        }
    }
    printf("%fx%d", a.f_coef[a.len - 1], a.len - 1);
    printf("\n");
}

void f_add (flinear a, flinear b) { //сложение лин. форм

    flinear c; //получаемая лин. форма
    int temp; //граница сложения

    //определяем длину получаемой лин. формы и границу сложения
    if (a.len >= b.len) {
        c.len = a.len;
        temp = b.len;
    }
    else {
        c.len = b.len;
        temp = a.len;
    }

    c.f_coef = malloc(c.len * sizeof(double));

    //складываем лин. формы
    for (int i = 0; i < temp; i++) {
        c.f_coef[i] = a.f_coef[i] + b.f_coef[i];
    }

    if (c.len != temp) {
        if (a.len > b.len) {
            for (int j = temp; j < c.len; j++) {
                c.f_coef[j] = a.f_coef[j];
            }
        }
        else {
            for (int j = temp; j < c.len; j++) {
                c.f_coef[j] = b.f_coef[j];
            }
        }
    }

    printf("The resulting linear form: ");
    print_flin(c); //выводим полученную лин. форму
}

void f_sub (flinear a, flinear b) { //вычитание лин. форм (первый аргумент - уменьшаемое)

    flinear c; //получаемая лин. форма
    int temp; //граница вычитания

    //определяем длину получаемой лин. формы и границу вычитания
    if (a.len >= b.len) {
        c.len = a.len;
        temp = b.len;
    }
    else {
        c.len = b.len;
        temp = a.len;
    }

    c.f_coef = malloc(c.len * sizeof(double));

    //вычитаем лин. формы
    for (int i = 0; i < temp; i++) {
        c.f_coef[i] = a.f_coef[i] - b.f_coef[i];
    }

    if (c.len != temp) {
        if (a.len > b.len) {
            for (int j = temp; j < c.len; j++) {
                c.f_coef[j] = a.f_coef[j];
            }
        }
        else {
            for (int j = temp; j < c.len; j++) {
                c.f_coef[j] = (-1)*b.f_coef[j];
            }
        }
    }

    printf("The resulting linear form: ");
    print_flin(c); //выводим полученную лин. форму
}

void f_scalar_mult (flinear a, double x) { //умножение на скаляр

    flinear c; //получаемая лин. форма
    c.len = a.len; //длина получаемой лин. формы

    c.f_coef = malloc(c.len * sizeof(double));

    //умножаем лин. форму на скаляр
    for (int i = 0; i < c.len; i++) {
        c.f_coef[i] = a.f_coef[i] * x;
    }

    printf("The resulting linear form: ");
    print_flin(c); //выводим полученную лин. форму
}

void f_value (flinear a) {

    double val = 0;
    double cur;

    for (int i = 0; i < a.len; i++) {
        printf("x%d:", i);
        scanf("%lf", &cur);
        val += a.f_coef[i]*cur;
    }

    printf("The value of linear form: ");
    printf("%lf", val);
}


/*ВСЕ ДЛЯ КОМПЛЕКСНЫХ КОЭФФИЦИЕНТОВ*/

void scan_clin(clinear* a) { //ввод лин. формы
    int l = 0;
    double re = 0;
    double im = 0;
    double complex z;

    printf("%s\n", "please type length of linear form");
    scanf("%d", &l);
    a->len = l;
    a->c_coef = malloc(l * sizeof(double complex));

    printf("%s\n", "please type linear form's coefs");
    for (int i = 0; i < l; i++) {
        scanf("%lf %lf", &re, &im);
        z = re + im*I;
        a->c_coef[i] = z;
    }

    printf("\n");
}

void print_clin (clinear a) { //вывод лин. формы
    for (int i = 0; i < a.len - 1; i++) {
        if (a.c_coef[i] != 0) {
            printf("(%lf+%lfi)x%d + ", creal(a.c_coef[i]), cimag(a.c_coef[i]), i);
        }
    }
    printf("(%lf+%lfi)x%d", creal(a.c_coef[a.len - 1]), cimag(a.c_coef[a.len - 1]), a.len - 1);
    printf("\n");
}

void c_add (clinear a, clinear b) { //сложение лин. форм

    clinear c; //получаемая лин. форма
    int temp; //граница сложения

    //определяем длину получаемой лин. формы и границу сложения
    if (a.len >= b.len) {
        c.len = a.len;
        temp = b.len;
    }
    else {
        c.len = b.len;
        temp = a.len;
    }

    c.c_coef = malloc(c.len * sizeof(double complex));

    //складываем лин. формы
    for (int i = 0; i < temp; i++) {
        c.c_coef[i] = a.c_coef[i] + b.c_coef[i];
    }

    if (c.len != temp) {
        if (a.len > b.len) {
            for (int j = temp; j < c.len; j++) {
                c.c_coef[j] = a.c_coef[j];
            }
        }
        else {
            for (int j = temp; j < c.len; j++) {
                c.c_coef[j] = b.c_coef[j];
            }
        }
    }

    printf("The resulting linear form: ");
    print_clin(c); //выводим полученную лин. форму
}

void c_sub (clinear a, clinear b) { //вычитание лин. форм (первый аргумент - уменьшаемое)

    clinear c; //получаемая лин. форма
    int temp; //граница вычитания

    //определяем длину получаемой лин. формы и границу вычитания
    if (a.len >= b.len) {
        c.len = a.len;
        temp = b.len;
    }
    else {
        c.len = b.len;
        temp = a.len;
    }

    c.c_coef = malloc(c.len * sizeof(double complex));

    //вычитаем лин. формы
    for (int i = 0; i < temp; i++) {
        c.c_coef[i] = a.c_coef[i] - b.c_coef[i];
    }

    if (c.len != temp) {
        if (a.len > b.len) {
            for (int j = temp; j < c.len; j++) {
                c.c_coef[j] = a.c_coef[j];
            }
        }
        else {
            for (int j = temp; j < c.len; j++) {
                c.c_coef[j] = (-1)*b.c_coef[j];
            }
        }
    }

    printf("The resulting linear form: ");
    print_clin(c); //выводим полученную лин. форму
}

void c_scalar_mult (clinear a,  double complex x) { //умножение на скаляр

    clinear c; //получаемая лин. форма

    c.len = a.len; //длина получаемой лин. формы2

    c.c_coef = malloc(c.len * sizeof(double complex));

    //умножаем лин. форму на скаляр
    for (int i = 0; i < c.len; i++) {
        c.c_coef[i] = a.c_coef[i] * x;
    }

    printf("The resulting linear form: ");
    print_clin(c); //выводим полученную лин. форму
}

void c_value (clinear a) {

    double complex val;
    double complex z;
    double re, im;
    double re_val = 0;
    double im_val = 0;

    val = re_val + im_val * I;

    printf("Input values of x:\n");

    for (int i = 0; i < a.len; i++) {
        printf("x%d:", i);
        scanf("%lf %lf", &re, &im);
        z = re + im*I;
        val += a.c_coef[i]*z;
    }

    printf("The value of linear form: ");
    printf("%lf+%lfi", creal(val), cimag(val));
}



int main() {

    double re, im, x;
    double complex y;
    flinear fa;
    flinear fb;
    clinear ca;
    clinear cb;

    int type_of_coefs;
    int type_of_operation;

    printf("What type of coefs do you want to work with?\n(please type '1' for float or '2' for complex)\n");
    scanf("%d", &type_of_coefs);

    printf("What do you want to do with linear forms?\n(please type '1' for addition; '2' for subtraction; '3' for multiplication by a scalar; '4' for calculating the value\n");
    scanf("%d", &type_of_operation);

    if (type_of_coefs == 1 && type_of_operation == 1) { //сложение с вещ. коэф-ми
        printf("Please create first linear form: \n");
        scan_flin(&fa);
        printf("\n");

        printf("Please create second linear form: \n");
        scan_flin(&fb);
        printf("\n");

        f_add(fa, fb);
    }

    if (type_of_coefs == 1 && type_of_operation == 2) { //вычитание с вещ. коэф-ми
        printf("Please create first linear form: \n");
        scan_flin(&fa);
        printf("\n");

        printf("Please create second linear form: \n");
        scan_flin(&fb);
        printf("\n");

        f_sub(fa, fb);
    }

    if (type_of_coefs == 1 && type_of_operation == 3) { //умножение с вещ. коэф-ми
        printf("Please create linear form: \n");
        scan_flin(&fa);
        printf("\n");

        printf("Please type the scalar (float): \n");
        scanf("%lf", &x);

        f_scalar_mult(fa, x);
    }

    if (type_of_coefs == 1 && type_of_operation == 4) { //вычисление значения с вещ. коэф-ми
        printf("Please create linear form: \n");
        scan_flin(&fa);
        printf("\n");

        f_value(fa);
    }

    if (type_of_coefs == 2 && type_of_operation == 1) { //сложение с компл. коэф-ми
        printf("Please create first linear form: \n");
        scan_clin(&ca);
        printf("\n");

        printf("Please create second linear form: \n");
        scan_clin(&cb);
        printf("\n");

        c_add(ca, cb);
    }

    if (type_of_coefs == 2 && type_of_operation == 2) { //вычитание с компл. коэф-ми
        printf("Please create first linear form: \n");
        scan_clin(&ca);
        printf("\n");

        printf("Please create second linear form: \n");
        scan_clin(&cb);
        printf("\n");

        c_sub(ca, cb);
    }

    if (type_of_coefs == 2 && type_of_operation == 3) { //умножение с компл. коэф-ми
        printf("Please create linear form: \n");
        scan_clin(&ca);
        printf("\n");

        printf("Please type the scalar (complex): \n");
        scanf("%lf %lf", &re, &im);
        y = re + im*I;

        c_scalar_mult(ca, y);
    }

    if (type_of_coefs == 2 && type_of_operation == 4) { //вычисление значения с компл. коэф-ми
        printf("Please create linear form: \n");
        scan_clin(&ca);
        printf("\n");

        c_value(ca);
    }

    return 0;
}
