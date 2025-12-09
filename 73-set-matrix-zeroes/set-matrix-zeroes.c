void setZeroes(int** matrix, int matrixSize, int* matrixColSize) {
    int Y = matrixSize;
    int X = *matrixColSize;

    bool is_col = false;

    for (int y = 0; y < Y; y++) {
        if (matrix[y][0] == 0)
            is_col = true;
        for (int x = 1; x < X; x++)
            if (matrix[y][x] == 0)  {
                matrix[y][0] = 0;
                matrix[0][x] = 0;
            }
    }

    for (int y = 1; y < Y; y++) 
        for (int x = 1; x < X; x++)
            if (matrix[y][0] == 0 || matrix[0][x] == 0)
                matrix[y][x] = 0;

    if (matrix[0][0] == 0)
        for (int x = 0; x < X; x++)
            matrix[0][x] = 0;
        
    if (is_col)
        for (int y = 0; y < Y; y++)
            matrix[y][0] = 0;
}