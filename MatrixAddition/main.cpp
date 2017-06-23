#include <iostream>
#include <fstream>
#include <vector>
#include "thread"

using namespace std;

// Global variances are evil :)
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

        resultVector[i] = result_element_i;
    }
    return resultVector;
}

void addMatrices(vector<vector<int>> firstMarix, vector<vector<int>> secondMatrix, int threads){
    thread t[threads];

    int N = firstMarix.size();

    vector<int> first_row_i, second_row_i, result_row_i;

    for (int i = 0; i < N; i++) {
        first_row_i = firstMarix.at(i);
        second_row_i = secondMatrix.at(i);
        result_row_i = addVectors(first_row_i, second_row_i);

        resultMatrix[i] = result_row_i;
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
    ofstream myfile(fileName,  ios::out);
    if (myfile.is_open()) {
        int N = Matrix.size();
        vector<int> row_i;

        for (int i = 0; i < N; i++) {
            row_i = Matrix.at(i);
            for (int j = 0; j < 10; j++) {
                myfile.width(4);
                myfile << row_i[j] << " ";
            }
            myfile << endl;
        }
        myfile << endl;
    }
    else cout << "Unable to open file";
    myfile.close();
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