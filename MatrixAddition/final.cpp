#include <iostream>
#include <fstream>
#include <vector>
#include "thread"

using namespace std;

vector<vector<int>> resultMatrix;

vector<vector<int>> generateMatrix(int matrixSize, int maxElement) {
    vector <vector<int>> Matrix;
    vector<int> row_i;
    for (int i = 0; i < matrixSize; i++) {
        row_i.clear();
        for (int i = 0; i < matrixSize; i++) {
            int new_number = rand() % maxElement;
            row_i.push_back(new_number);
        }
        Matrix.push_back(row_i);
    }
    return Matrix;
}

vector<int> addVectors(vector<int> firstVector, vector<int> secondVector) {
    int N = firstVector.size();
    vector<int> resultVector;

    int first_element_i, second_element_i, result_element_i;

    for (int i = 0; i < N; i++) {
        first_element_i = firstVector.at(i);
        second_element_i = secondVector.at(i);
        result_element_i = first_element_i + second_element_i;

        resultVector.push_back(result_element_i);
    }
    return resultVector;
}

void addPartOfMatrix(int rowFrom, int rowTo, vector<vector<int>> firstMarix, vector<vector<int>> secondMatrix){
    vector<int> first_row_i, second_row_i, result_row_i;
    int N = firstMarix.size();

    for (int i = rowFrom; i < rowTo; i++) {
        first_row_i = firstMarix.at(i);
        second_row_i = secondMatrix.at(i);
        result_row_i = addVectors(first_row_i, second_row_i);

        resultMatrix[i] = result_row_i;
    }
}

void addMatrices(vector<vector<int>> firstMarix, vector<vector<int>> secondMatrix, int threads){
    thread t[threads];
    int N = firstMarix.size();

    int step_by_thread = int(N / threads) + 1;

    for (int i = 0; i < threads - 1; i++) {
        t[i] = thread(addPartOfMatrix, i * step_by_thread, (i + 1) * step_by_thread, firstMarix, secondMatrix);
    }
    // The last thread
    t[threads-1] = thread(addPartOfMatrix, (N-1)*step_by_thread, N, firstMarix, secondMatrix);

    for (int i = 0; i < threads; ++i) {
        t[i].join();
    }
}

void printMatrix(vector<vector<int>> Matrix) {
    int N = Matrix.size();
    vector<int> row_i;

    for (int i = 0; i < N; i++) {
        row_i = Matrix.at(i);
        for (int j = 0; j < 10; j++) {
            cout.width(3);
            cout << row_i[j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void printMatrixInFile(vector<vector<int>> Matrix, string fileName) {
    ofstream myfile (fileName);
    if (myfile.is_open()) {
        int N = Matrix.size();
        vector<int> row_i;

        for (int i = 0; i < N; i++) {
            row_i = Matrix.at(i);
            for (int j = 0; j < N; j++) {
                myfile.width(4);
                myfile << row_i[j] << " ";
            }
            myfile << endl;
        }
        myfile << endl;
        myfile.close();
    }
    else cout << "Unable to open file";
}

int main() {

    vector<vector<int>> firstMatrix = generateMatrix(10, 10);
    vector<vector<int>> secondMatrix = generateMatrix(10, 10);

    addMatrices(firstMatrix, secondMatrix, 5);

    printMatrix(firstMatrix);
    printMatrix(secondMatrix);
    printMatrix(resultMatrix);

    // Please make sure your file is empty
    printMatrixInFile(firstMatrix, "Result.txt");
    printMatrixInFile(secondMatrix, "Result.txt");
    printMatrixInFile(resultMatrix, "Result.txt");
    return 0;
}