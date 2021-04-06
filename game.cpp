#include<iostream>
#include<string>

using namespace std;

void printGrid(int Row, int Col, int grid[5][5]){
  int count1 = 0;
  int count2 = 0;
  for (int i = 0; i < Row; i++){
    if (count2 != 0) {
      cout << "---";
      for (int c = 0; c < Col-1; c++){
        cout << "+----";
      }/* code */
      cout << endl;
    }
    count2 = 1;

    for (int j = 0; j < Col; j++){
      int a  = grid[i][j];
      if (count1 % Col != 0){
        cout << "| ";
      }
      if (a < 10){
        cout << " " << a << " ";
      }
      else if (a >= 10 && a < 100){
        cout << a << " ";
      }
      count1++;
    }
    cout << endl;
  }

}

int main(){
  const int Row = 5;
  const int Col = 5;
  int grid[Row][Col];
  int a = 1;
  for (int i = 0; i < Row ; i ++){
    for (int j = 0; j < Col; j++){
      if (a != Row*Col){
      grid[i][j] = a;
    }
    else{
      grid[i][j] = 0;
    }

      a++;
    }
  }

  printGrid(Row, Col, grid);

}
