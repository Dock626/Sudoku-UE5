#include "SudokuGenerator.h"
#include "Math/UnrealMathUtility.h"

USudokuGenerator::USudokuGenerator()
{
}

TArray<int32> USudokuGenerator::GenerateSolvedSudoku()
{
    TArray<int32> Grid;
    Grid.Init(0, 81); // Initialize 9x9 grid with zeros

    // Fill the diagonal boxes (top-left, middle, bottom-right)
    for (int i = 0; i < 9; i += 3)
    {
        TArray<int32> Numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        ShuffleArray(Numbers);

        int index = 0;
        for (int r = 0; r < 3; r++)
        {
            for (int c = 0; c < 3; c++)
            {
                Grid[(i + r) * 9 + (i + c)] = Numbers[index++];
            }
        }
    }

    // Solve the rest of the grid
    SolveSudoku(Grid);

    return Grid;
}

bool USudokuGenerator::SolveSudoku(TArray<int32>& Grid)
{
    int32 Row, Col;

    // If there's no empty cell, we're done
    if (!FindEmptyCell(Grid, Row, Col))
    {
        return true;
    }

    // Try numbers 1 through 9
    for (int32 Num = 1; Num <= 9; Num++)
    {
        if (IsSafe(Grid, Row, Col, Num))
        {
            // Try this number
            Grid[Row * 9 + Col] = Num;

            // Recursively continue
            if (SolveSudoku(Grid))
            {
                return true;
            }

            // If recursion fails, backtrack
            Grid[Row * 9 + Col] = 0;
        }
    }

    // Trigger backtracking
    return false;
}

bool USudokuGenerator::FindEmptyCell(const TArray<int32>& Grid, int32& Row, int32& Col)
{
    for (Row = 0; Row < 9; Row++)
    {
        for (Col = 0; Col < 9; Col++)
        {
            if (Grid[Row * 9 + Col] == 0)
            {
                return true;
            }
        }
    }
    return false;
}

bool USudokuGenerator::IsSafe(const TArray<int32>& Grid, int32 Row, int32 Col, int32 Num)
{
    // Check row
    for (int c = 0; c < 9; c++)
    {
        if (Grid[Row * 9 + c] == Num)
        {
            return false;
        }
    }

    // Check column
    for (int r = 0; r < 9; r++)
    {
        if (Grid[r * 9 + Col] == Num)
        {
            return false;
        }
    }

    // Check 3x3 box
    int32 BoxStartRow = Row - Row % 3;
    int32 BoxStartCol = Col - Col % 3;
    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            if (Grid[(BoxStartRow + r) * 9 + (BoxStartCol + c)] == Num)
            {
                return false;
            }
        }
    }

    return true;
}

void USudokuGenerator::ShuffleArray(TArray<int32>& Array)
{
    for (int i = Array.Num() - 1; i > 0; i--)
    {
        int32 j = FMath::RandRange(0, i);
        Array.Swap(i, j);
    }
}