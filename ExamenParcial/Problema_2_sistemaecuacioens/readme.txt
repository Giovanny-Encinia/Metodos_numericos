Para compilar y generar el ejecutable corre:

    make

Para correr el ejecutable correr:

    make run

Si se quiere eliminar el ejecutable hacer:

    make clean

Si make no funciona usar:
    gcc -o problema2 main.c print_read/print_read_dinamyc.c LU/factorization_lu.c gauss_pivoteo_total/solve_gauss_pt.c matrix_math/matrix_math.c
