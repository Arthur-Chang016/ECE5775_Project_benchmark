//==========================================================================
//digitrec.cpp
//==========================================================================
// @brief: A k-nearest-neighbors implementation for digit recognition

#include "digitrec.h"

//----------------------------------------------------------
// Top function
//----------------------------------------------------------
// @param[in] : input - the testing instance
// @return : the recognized digit (0~9)

bit4 digitrec(int a[N], int b[N], int c[N], int &res, int conv1d[19], int A[N][N], int d[N]) 
{
  VVadd(a, b, c);
  res = DotProd(a, b);
  Conv1d(a, b, conv1d);
  MatVecMul(A, a, d);
  MatMul();
}
// hand-made swap funciton
// inline void swap(bit6 &a, bit6 &b) {
//   bit6 tmp = a;
//   a = b;
//   b = tmp;
// }

//-----------------------------------------------------------------------
// update_knn function
//-----------------------------------------------------------------------
// Given the test instance and a (new) training instance, this
// function maintains/updates an array of K minimum
// distances per training set.

// @param[in] : test_inst - the testing instance
// @param[in] : train_inst - the training instance
// @param[in/out] : min_distances[K_CONST] - the array that stores the current
//                  K_CONST minimum distance values per training set

// void update_knn( digit test_inst, digit train_inst, bit6 min_distances[K_CONST] )
// {
//   // -----------------------------
//   // YOUR CODE GOES HERE
//   // -----------------------------
//   digit xor_result = test_inst ^ train_inst;
//   bit6 dist = 0, tmp;
  
//   // count the number of 1 bit, which is the distance
//   POPCOUNT:
//   for(int i = 0; i <= 44; i += 4)
//     dist += popcount_map[xor_result(i + 3, i)];
  
//   dist += popcount_map[xor_result(48, 47)];  // the extra 2 bits
  
//   // as the K distances are sorted
//   // by the flavor of min heap
//   if(dist < min_distances[K_CONST - 1]) min_distances[K_CONST - 1] = dist;
//   // sift up
//   INSERT_NUM:
//   for(int i = K_CONST - 2; i >= 0; --i) {
//     if(min_distances[i + 1] < min_distances[i]) {
//       tmp = min_distances[i + 1];
//       min_distances[i + 1] = min_distances[i];
//       min_distances[i] = tmp;
//     }
//       // swap(min_distances[i + 1], min_distances[i]);
//   }
// }


// //-----------------------------------------------------------------------
// // knn_vote function
// //-----------------------------------------------------------------------
// // Given 10xK minimum distance values, this function 
// // finds the actual K nearest neighbors and determines the
// // final output based on the most common digit represented by 
// // these nearest neighbors (i.e., a vote among KNNs). 
// //
// // @param[in] : knn_set - 10xK_CONST min distance values
// // @return : the recognized digit (0-9)
// // 

// bit4 knn_vote( bit6 knn_set[10][K_CONST] )
// {
//   // -----------------------------
//   // YOUR CODE GOES HERE
//   // -----------------------------
  
//   bit4 ret = 0;  // the result
//   ap_uint<16> min_sum = 65535;  // sum of each row
  
//   VOTE:
//   for(int i = 0; i < 10; ++i) {
//     bit6 *knn_set_row = (bit6*)knn_set[i];
//     ap_uint<16> cur = 0;
    
//     SUM_ROW:
//     for(int j = 0; j < K_CONST; ++j)
//       cur += knn_set_row[j];
      
//     if(cur < min_sum) {
//       min_sum = cur;
//       ret = i;
//     }
//   }
//   return ret;
// }

// #define N 10

void VVadd(int a[N], int b[N], int res[N]) {
  VVadd_pipe:
  for(int i = 0; i < N; ++i)
    res[i] = a[i] + b[i];
}

int DotProd(int a[N], int b[N]) {
  int res = 0;
  DotProd_pipe:
  for(int i = 0; i < N; ++i)
    res = a[i] * b[i];
  return res;
}

void MatVecMul(int A[N][N], int x[N], int res[N]) {
  // init to 0
  MatVecMul_pipe1:
  for(int i = 0; i < N; ++i)
    res[i] = 0;
  
  MatVecMul_pipe2:
  for(int r = 0; r < N; ++r) { // each row of A
    // int res_r = 0;
    for(int i = 0; i < N; ++i)
      res[r] += A[r][i] * x[i];
      // res_r += A[r][i] * x[i];
      
    // res[r] = res_r;
  }
}

void Conv1d(int a[N], int b[N], int res[19]) {
  // init to 0
  Conv1d_pipe1:
  for(int i = 0; i < 19; ++i)
    res[i] = 0;
    
  Conv1d_pipe2:
  for(int i = 0; i < 19; ++i) {
    int sum = 0;
    
    for(int j = 0; j < N; ++j) for(int k = 0; k < N; ++k)
      if(j + k == i) sum += a[j] * b[k];
    
    // l + r == i
    // for(int l = i, r = 0; l >= 0; --l, ++r) {
    //   if(l < N && r < N) sum += a[l] * b[r];
    // }
    res[i] = sum;
  }
  
  // Conv1d_pipe2:
  // for(int i = 0; i < N; ++i) {
  // // #pragma HLS unroll
  //   int magni = b[i];
    
  //   // #pragma HLS UNROLL factor=10
  //   for(int j = 0; j < N; ++j) {
  //     #pragma HLS UNROLL factor=10
  //     res[i + j] += magni * a[j];
  //   }
  // }
}

void MatMul() {
  
}
