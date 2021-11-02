/*
* Sudoku Solver using backtracking method
*/

#include <iostream>
#include <array>

constexpr void printBoard(const std::array<std::array<int, 9>, 9> &board);

class SudokuSolver
{
private:
    std::array<std::array<int, 9>, 9> board;

public:
    SudokuSolver(std::array<std::array<int, 9>, 9> &matrix);
    constexpr bool solve();
    constexpr bool check(const int &value, const int &rowIndex, const int &colIndex);
    [[nodiscard]] std::array<std::array<int, 9>, 9> &result();
};

SudokuSolver::SudokuSolver(std::array<std::array<int, 9>, 9> &matrix) : board{matrix}
{
}

constexpr bool SudokuSolver::solve()
{
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            if (board[i][j] == 0)
            {
                for (int k = 1; k <= 9; ++k)
                {
                    // Check if its a valid location
                    if (check(k, i, j))
                    {
                        // Yes, change it and look further
                        board[i][j] = k;
                        if (solve())
                            return true;
                        // If we take any wrong decision just revert back
                        board[i][j] = 0;
                    }
                }
                return false;
            }
        }
    }

    return true;
}

constexpr bool SudokuSolver::check(const int &value, const int &rowIndex, const int &colIndex)
{
    for (int x = 0; x < 9; ++x)
        if (board[rowIndex][x] == value)
            return false;

    for (int x = 0; x < 9; ++x)
        if (board[x][colIndex] == value)
            return false;

    const int u = (rowIndex / 3) * 3;
    const int v = (colIndex / 3) * 3;

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (board[u + i][v + j] == value)
                return false;
        }
    }
    return true;
}

constexpr void printBoard(const std::array<std::array<int, 9>, 9> &board)
{
    for (const auto &row : board)
    {
        for (const auto &elem : row)
            std::cout << elem << '\t';
        std::cout << '\n';
    }
}

[[nodiscard]] std::array<std::array<int, 9>, 9> &SudokuSolver::result()
{
    return board;
}

int main()
{
    std::array<std::array<int, 9>, 9> matrix{{
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
    }};
    SudokuSolver s(matrix);

    std::cout << "Before Solve" << '\n';
    printBoard(matrix);

    const bool found = s.solve();

    if (found)
    {
        const auto solvedBoard = s.result();
        std::cout << "After Solve" << '\n';
        printBoard(solvedBoard);
    }
    else
        std::cout << "No Solution" << '\n';

    return 0;
}