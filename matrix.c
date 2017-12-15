#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

int i, j, k, I, J;

int min_el = INT_MAX;
int min_x = 0, min_y = 0;

int** memory(int a,int b)
{
    int** matrix = (int**)malloc(a*sizeof(int*));
    for( i = 0; i<a ; i++ )
    {
        matrix[i] =  malloc(b*sizeof(int));
    }
    return matrix;
}

void fill(int a, int b, int** matrix)
{
    for( i = 0; i < a; i++ )
    {
        for ( j = 0; j < b; j++)
        {
            matrix[i][j] = rand()%10;
        }
    }
}

void output(int a, int b, int** matrix)
{
    printf("\n");
    for( i = 0; i < a ; i++ )
    {
        for ( j = 0; j < b; j++)
        {
            printf("%d\t",matrix[i][j]);
        } 
        printf("\n");
    }
    printf("\n");
}

int** buffer( int b)
{
    int** buff= (int**)malloc(2*sizeof(int*));
    for(int j = 0; j<b ; j++ )
    {
        buff[j] =  malloc(b*sizeof(int));
    }
    return buff;
}

void minimum(int a, int b ,int** matrix)
{
    for( i = 0; i<a ; i++ )
    {
        for ( j = 0; j<b; j++)
        {
            if  (matrix[i][j] < min_el )
            {
                min_el = matrix[i][j];
                min_x = i;
                min_y = j;
            }
        }
    }
}

void exchange(int a, int b, int**buff, int** matrix){
    
    for ( i = 0, j = b; i<b; j--,i++)
    {
        buff[0][i] = matrix[0][j-1];
    }
    
    for ( i = 0, j = b; i < b; j--,i++)
    {
        buff[1][i] = matrix[a-1][j-1];
    }
    
    for( j = 0; j < b ;j++)
    {
        matrix[0][j] = buff[1][j];
        matrix[a-1][j] = buff[0][j];
    }
}

void fill_2(int a, int b, int **matrix,int **matrix_2)
{
    for( I = 0, i = 0; I<a-1; I++, i++)
    {
        if (i == min_x)
        {
            I--;
            continue;
        }
        for ( J = 0, j = 0; J<b-1;J++, j++)
        {
            if (j == min_y)
            {
                J--;
                continue;
            }
            matrix_2[I][J] = matrix[i][j];
        }
    }
}

void convert(int **matrix, int a, int b, const char *line) 
{
    for(int char_num = 0, i = 0, j = 0; char_num < strlen(line); char_num++) 
    {
        switch (line[char_num]) 
        {
            case '.':
                return;
            case ',':
                i++;
                j = 0;
            default:
                if(isdigit(line[char_num])) 
                {
                    char *tmp;
                    matrix[i][j] = (int) strtol(line+char_num, &tmp, 10);
                    int offset = (int) (tmp-(line+char_num));
                    char_num += offset;
                    j++;
                }
        }
    }
}

int** multiply(int x, int y, int a, int b, int** matrix1, int** matrix2)
{
    int** resultmatrix = memory(x-1, b);
    for( i = 0; i <x-1 ; i++)
    {
        for( j = 0; j < y-1  ; j++)
        {
            for ( k = 0; k < a ; k++)
            {
                resultmatrix[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return resultmatrix;
}


int main(int argc, const char * argv[]) 
{
    int x , y ;
    extern int min_el;
    min_el = INT_MAX;
    extern int min_x,  min_y;
    min_x = min_y = 0;
    
    int a = 0 ,b = 0;
    printf("Good day for a swell matrix multiplication!\nInput the amount of lines and columns in the first matrix!\n");
    printf("The amount of lines is\t");
    scanf("%d",&x);
    printf("The amount of columns is\t");
    scanf("%d",&y);
    getchar();
    srand ((unsigned int) time(NULL));
    int** matrix_1 = memory(x,y);

    fill(x,y,matrix_1);
    printf("\nYour matrix is\n");
    output(x, y, matrix_1);

    int** buff = buffer(y);
    exchange(x, y, buff, matrix_1);
    printf("\nThe modified version of your matrix  is\n");
    output(x, y, matrix_1);
    minimum(x, y, matrix_1);

    int **matrix_2 = memory(x-1, y-1);
    fill_2(x, y, matrix_1, matrix_2);
    printf("\nThe smaller version of your matrix without the line and the column containing the minimal element is\n");
    output(x-1, y-1, matrix_2);
    char *line = NULL;
    size_t linecap = 0;
    ssize_t matrix_s;
    
    printf("\nNow, input your own matrix!\n");
    printf("Be Careful with the syntax!\n");
    printf("Here's a quick example:\n");
    printf("You are to input a 2 by 2 matrix \n\t3 4\n\t2 4\n");
    printf("To do so, you should input your matrix this way:\n");
    printf("3 4 ,2 4 .\n");
    printf("Got it? Try for yourself!\n");
   
    matrix_s = getline(&line, &linecap, stdin);
    for(int i = 0; i < strlen(line);i++) 
    {
        if (isdigit(line[i])) 
        {
            char *tmp;
            strtol(line+i, &tmp, 10);
            int offset = (int) (tmp-(line+i));
            i += offset;
            b++; 
        }
        else if (line[i] == ',')
        { 
            a++;
        }
        else  if(line[i] == '.')
        { 
            break;
        }
        else continue;
    }
    a = a + 1;
    b = b/a + b%a;
    printf("\n%d\t%d\n",a,b);
    printf("\n");
    int **matrix_frln = memory(a,b);
    convert(matrix_frln, a, b, line);
    printf("\nYour second matrix is");
    output(a, b, matrix_frln);
    printf("Warning! The rules of working with matrices clearly state that");
    printf(" you can only multiply matrices when the amount of columns in the first matrix");
    printf(" equals the amount of lines in the second matrix.\n");
    if (y-1 == a)
    {
        printf("The operation of multiplication is possible,good job!\n");
        int** new_matrix = memory(x-1, b);
        new_matrix = multiply(x, y, a, b , matrix_2 , matrix_frln);
        output(x-1, b, new_matrix);
    }
    else 
    {
        printf("You managed to screw this up!\n");
        printf("Restart the program and try again!\n");
    }
    free(matrix_1);
    free(matrix_2);
    free(matrix_frln);
    return 0;
}
