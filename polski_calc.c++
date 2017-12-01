#include <stdio.h> 
#include <iostream> 
#include <cmath> 
int main() 
{ 
int stack[10];//массив чисел начинается с 0-999 
// sp = индекс ячейки, куда будет push-иться очередное число 
int sp = 0; // (sp-1) = индекс ячейки, являющейся вершиной стека 
printf("enter retern poland expression\n"); 
while ( !feof(stdin) ) //!- логическое "не" stdin (стандартный поток ввода)используется для считывания с консоли 
{ 
int c = getchar();//возвращает из стандартного потока stdin (ввода)следующий символ. При чтении символа предполагается, что символ имеет тип unsigned char, который потом преобразуется в целый. 
int x; 
switch (c)//цикл выполняющий мат. операции и записывающий их в стек 
{ 
case ' ':// ? пропустить этот символ в цикле 
case '\n':// ? пропустить этот символ в цикле 
break; 
case '=': 
printf("My Result = %d\n", stack[sp-1]); sp--; 
break; 
case '+': 
stack[sp-2] = stack[sp-2]+ stack[sp-1]; sp--; 
break; 
case '-': 
stack[sp-2] = stack[sp-2] - stack[sp-1]; sp--; 
break; 
case '*': 
stack[sp-2] = stack[sp-1] * stack[sp-2]; sp--; 
break; 
case '/': 
stack[sp-2] = stack[sp-2] / stack[sp-1]; sp--; 
break; 
case '^': 
stack[sp-1] = pow (2,4); sp--;// не работает (( 
break; 

default: 
ungetc (c, stdin); // функция ungetc возвращает только что прочитанный символ обратно в поток ввода filestream, через параметр character. Внутренний индикатор позиции файла уменьшается обратно, на предыдущее положение, так что этот символ возвращается при следующем вызове операции чтения для этого потока. 
if (scanf("%d", &x) != 1)//? по идее проверка введенного типа данных 
{ 
fprintf(stderr, "Can't read integer\n");//stderr (стандартный поток ошибок)для записи на консоль 
return -1; 
} 
else { 
stack[sp] = x; sp++; 
} 
} 
} 
printf("Result = %d\n",stack[sp-1]); 
return 0; 
return 0; 
}
