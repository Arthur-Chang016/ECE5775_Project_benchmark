//=========================================================================
// testbench.cpp
//=========================================================================
// @brief: testbench for k-nearest-neighbor digit recongnition application

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#include "digitrec.h"

using namespace std;

int main() 
{ 
  int a[10];
  int b[10];
  int c[10];
  int d[19];
  
  for(int i = 0; i < 10; ++i) {
    a[i] = 1;
    b[i] = 1;
  }
  
  // test
  Conv1d(a, b, d);
  
  for(int i = 0 ; i < 19; ++i)
    cout << d[i] << ' ';
  cout << endl;

  return 0;
}
