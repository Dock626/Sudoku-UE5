#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SudokuGenerator.generated.h"

UCLASS(Blueprintable)
class SUDOKU_API USudokuGenerator : public UObject
{
    GENERATED_BODY()

public:
    USudokuGenerator();
    // Generates a solved Sudoku grid
    UFUNCTION(BlueprintCallable, Category = "Sudoku")
    TArray<int32> GenerateSolvedSudoku();

private:
    bool SolveSudoku(TArray<int32>& Grid);
    bool FindEmptyCell(const TArray<int32>& Grid, int32& Row, int32& Col);
    bool IsSafe(const TArray<int32>& Grid, int32 Row, int32 Col, int32 Num);
    void ShuffleArray(TArray<int32>& Array);
};