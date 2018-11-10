// https://www.hackerrank.com/challenges/matrix-rotation-algo/problem

#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
CLARIFICATION:
The solution is not the most simple possible, because
I tried to avoid creating another  same-sized matrix.
The solution's logic follows this pattern:
We divide our matrix into different layers , starting
from the outside and moving to the center.  Later  we
encode each element starting from the upper left  and
ending with the one beneath. The latter is encoded as
0, and the first is encoded as [number of elements in
the layer]-1.
Then we create the function translate to get the coo-
rdinates from the respective encoding.
*/

int* translate(int step,int m,int n, int depth)//conversion from identification integer to coordinates
{
    int *coordinates = (int*)malloc(2 * (sizeof(int)));
    int total = 2*(m+n)-5;
    /* */if(step>2*m+n-5){coordinates[0]= depth;                coordinates[1] = total-step+depth;}
    else if(step>  m+n-3){coordinates[0]= total-n+1-step+depth; coordinates[1] = n-1+depth;}
    else if(step>  m-2  ){coordinates[0]= m-1+depth;            coordinates[1] = step -m+2+depth;}
    /*           */ else {coordinates[0]=step+1 +depth;         coordinates[1] = depth;}
    return  coordinates;
}

// Complete the matrixRotation function below.
void matrixRotation(int matrix_rows, int matrix_columns, int** matrix, int r)
{
    int max_depth = fmin(matrix_rows,matrix_columns)/2;
    int temp, temp_0, current; // temp ~> for each metathesis, temp_0 ~> for swapping temp and matrix[current]
    bool *unused_elements; // elements which have not been placed in the right position
    int *current_coordinates;

    for(int depth=0; depth<max_depth; depth++) // each time we move one layer deeper
    {
        int metathesis = 2*(matrix_rows+matrix_columns-2); // how many elements in one layer
        unused_elements = (bool*) malloc(metathesis*sizeof(bool)); // each time we recreate the matrix for the least space usage possible
        for (int i=0; i<metathesis; i++) unused_elements[i]=1; // initialize the matrix

        for(int i=metathesis-1; i>=0; i--) // to be sure that we use all the elements
        {
            if(unused_elements[i]) // check if the element is not used
            {
                current = i;
                current_coordinates = translate(current,matrix_rows,matrix_columns,depth);
                temp = *(*(matrix+current_coordinates[0])+current_coordinates[1]); // set a new current element

                while(unused_elements[(current+r) % metathesis]) // we don't want to iterate a rightly placed element
                {
                    current = (current+r) % metathesis;
                    unused_elements[current]=0;
                    current_coordinates = translate(current,matrix_rows,matrix_columns,depth);
                    temp_0 = temp;
                    temp = *(*(matrix+current_coordinates[0])+current_coordinates[1]);
                    *(*(matrix+current_coordinates[0])+current_coordinates[1]) = temp_0;
                }
            }
        }
        free(unused_elements);
        matrix_rows-=2;
        matrix_columns-=2; // each layer has 2 rows and 2 columns less opposed to the previous one
    }
}
