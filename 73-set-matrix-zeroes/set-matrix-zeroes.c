void setZeroes(int** matrix, int matrixSize, int* matrixColSize) {
    int Y = matrixSize;
    int X = *matrixColSize;

    int* ycheck = calloc(Y, sizeof(int));
    int* xcheck = calloc(X, sizeof(int));
    for (int y = 0; y < Y; y++)
        for (int x = 0; x < X; x++)
            if (matrix[y][x] == 0)
                ycheck[y] = true, xcheck[x] = true;

    for (int y = 0; y < Y; y++)
        if (ycheck[y])
            for (int x = 0; x < X; x++)
                matrix[y][x] = 0;

    for (int x = 0; x < X; x++)
        if (xcheck[x])
            for (int y = 0; y < Y; y++)
                matrix[y][x] = 0;
}