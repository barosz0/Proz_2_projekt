// Proz2.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//
const int blocks = 2;
const int matrix_size = 1024 * blocks;
#include <iostream>
#include <iomanip>
#include <omp.h>

void rand_matrix(int A[matrix_size][matrix_size])
{
    int Min = 0;
    int Max = 10;

    for (int i = 0; i < matrix_size; i++)
        for (int j = 0; j < matrix_size; j++)
            A[i][j] = rand() % (Max-Min+1) + Min;
}

void rand_matrix(int* A)
{
    int Min = 0;
    int Max = 10;

    for (int i = 0; i < matrix_size; i++)
        for (int j = 0; j < matrix_size; j++)
            A[i*matrix_size + j] = rand() % (Max - Min + 1) + Min;
}

void print_matrix(int M[matrix_size][matrix_size])
{
    int width = 4;
   
    for (int i = 0; i < matrix_size; i++)
    {
        for (int j = 0; j < matrix_size; j++)
            std::cout << std::setw(width)<< M[i][j] << " ";
        std::cout << std::endl;
    }

}

void print_matrix(int* M)
{
    int width = 4;

    for (int i = 0; i < matrix_size; i++)
    {
        for (int j = 0; j < matrix_size; j++)
            std::cout << std::setw(width) << M[i* matrix_size + j] << " ";
        std::cout << std::endl;
    }

}

void zero_matrix(int* M)
{
    for (int i = 0; i < matrix_size; i++)
    {
        for (int j = 0; j < matrix_size; j++)
            M[i * matrix_size + j] = 0;
    }
}

void CalculateMatrix(int A[matrix_size][matrix_size], int B[matrix_size][matrix_size], 
    int C[matrix_size][matrix_size])
{
    #pragma omp parallel for
    for (int i = 0; i < matrix_size; i++)
        for(int k=0;k< matrix_size;k++)
            for (int j = 0; j < matrix_size; j++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
}

void CalculateMatrix(int* A, int* B,
    int* C)
{
    #pragma omp parallel for
    for (int i = 0; i < matrix_size; i++)
        for (int k = 0; k < matrix_size; k++)
            for (int j = 0; j < matrix_size; j++)
            {
                C[i*matrix_size + j] += A[i* matrix_size + k] * B[k* matrix_size + j];
                //std::cout << "|";
            }
}

//void CalculateMatrixDynamic(int** A, int** B, int** C, int size)
//{
//    #pragma omp parallel for
//    for (int i = 0; i < size; i++)
//        for (int k = 0; k < size; k++)
//            for (int j = 0; j < size; j++)
//            {
//                C[i][j] += A[i][k] * B[k][j];
//            }
//}

int main()
{
    srand(100);
    //int A[matrix_size][matrix_size];
    int* A = (int*) new int[matrix_size* matrix_size];
    //int B[matrix_size][matrix_size];
    int* B = (int*) new int[matrix_size * matrix_size];
    //int C[matrix_size][matrix_size] = { 0 };
    int* C = (int*) new int[matrix_size * matrix_size];
    zero_matrix(C);
    rand_matrix(A);
    rand_matrix(B);

    clock_t spstart, spstop;
    double sswtime, sewtime;

    sswtime = omp_get_wtime();
    spstart = clock();


    CalculateMatrix(A, B, C);

    spstop = clock();
    sewtime = omp_get_wtime();

    printf("Czas procesorow przetwarzania rownoleglego  %f sekund \n", ((double)(spstop - spstart) / CLOCKS_PER_SEC));
    printf("Czas trwania obliczen rownoleglego - wallclock %f sekund \n", sewtime - sswtime);

    //std::cout << "A\n";
    //print_matrix(A);
    //std::cout << "B\n";
    //print_matrix(B);
    //std::cout << "C\n";
    //print_matrix(C);

}

