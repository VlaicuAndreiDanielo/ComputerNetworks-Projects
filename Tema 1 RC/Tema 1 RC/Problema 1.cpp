
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void printMatrix(const vector<vector<int>>& matrix, const vector<int>& parityRow, const vector<int>& parityCol, int cornerParity) {
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            cout << matrix[i][j] << " ";
            if (j == matrix[i].size() - 1) cout << "| " << parityRow[i];
        }
        cout << endl;
        if (i == matrix.size() - 1) {
            cout << "-----------------" << endl;
        }
    }
    for (size_t j = 0; j < parityCol.size(); ++j) {
        cout << parityCol[j] << " ";
    }
    cout << "| " << cornerParity << endl;
}

void initializeMatrix(const string& input, vector<vector<int>>& matrix, vector<int>& parityRow, vector<int>& parityCol, int& cornerParity) {
    int rows = input.length() / 7;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < 7; ++j) {
            matrix[i][j] = input[i * 7 + j] - '0';
            parityRow[i] ^= matrix[i][j];
            parityCol[j] ^= matrix[i][j];
        }
        cornerParity ^= parityRow[i];
    }
}

void introduceError(vector<vector<int>>& matrix, vector<int>& parityRow, vector<int>& parityCol, int& cornerParity) {
    srand(time(0));
    int rows = matrix.size();
    int errorIndex = rand() % (rows * 7);
    int errorRow = errorIndex / 7;
    int errorCol = errorIndex % 7;
    cout << "\nThe random position in original message is: " << errorIndex << endl;
    cout << "The corresponding matrix position is: (" << errorRow << ", " << errorCol << ")" << endl;
    matrix[errorRow][errorCol] ^= 1;

    parityRow[errorRow] = 0;
    for (int j = 0; j < 7; ++j) {
        parityRow[errorRow] ^= matrix[errorRow][j];
    }

    parityCol[errorCol] = 0;
    for (int i = 0; i < rows; ++i) {
        parityCol[errorCol] ^= matrix[i][errorCol];
    }

    cornerParity = 0;
    for (int i = 0; i < rows; ++i) {
        cornerParity ^= parityRow[i];
    }
}

void detectErrors(const vector<vector<int>>& matrix, const vector<vector<int>>& originalMatrix) {
    vector<pair<int, int>> errorPositions;
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            if (matrix[i][j] != originalMatrix[i][j]) {
                errorPositions.push_back({ i, j });
            }
        }
    }
    if (!errorPositions.empty()) {
        cout << "\nErrors detected at positions: ";
        for (const auto& pos : errorPositions) {
            cout << "(" << pos.first << ", " << pos.second << ") ";
        }
        cout << endl;
    }
    else {
        cout << "\nNo single-bit error detected." << endl;
    }
}

void printMessageFromMatrix(const vector<vector<int>>& matrix, const vector<int>& parityRow) {
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (int bit : matrix[i]) {
            cout << bit;
        }
        cout << parityRow[i];
    }
    cout << endl;
}


int main() {
    string input;
    cout << "Please input the binary message: ";
    cin >> input;

    if (input.size() % 7 != 0) {
        cout << "Error: The length must be a multiple of 7!" << endl;
        return 1;
    }

    int rows = input.length() / 7;
    vector<vector<int>> matrix(rows, vector<int>(7, 0));
    vector<vector<int>> originalMatrix;
    vector<int> parityRow(rows, 0);
    vector<int> originalParityRow;
    vector<int> parityCol(7, 0);
    vector<int> originalParityCol;
    int cornerParity = 0;
    int originalCornerParity;

    initializeMatrix(input, matrix, parityRow, parityCol, cornerParity);
    originalMatrix = matrix;
    originalParityRow = parityRow;
    originalParityCol = parityCol;
    originalCornerParity = cornerParity;

    cout << "\nThe Matrix for the message is:" << endl;
    printMatrix(matrix, parityRow, parityCol, cornerParity);

    cout << "\nThe message from the matrix before corruption is: ";
    printMessageFromMatrix(matrix, parityRow);

    introduceError(matrix, parityRow, parityCol, cornerParity);

    cout << "\nThe message from the matrix after corruption is: ";
    printMessageFromMatrix(matrix, parityRow);

    cout << "\nThe Matrix after the corruption:" << endl;
    printMatrix(matrix, parityRow, parityCol, cornerParity);

    cout << "\nOriginal Matrix before corruption:" << endl;
    printMatrix(originalMatrix, originalParityRow, originalParityCol, originalCornerParity);

    detectErrors(matrix, originalMatrix);
    return 0;
}

