/* File: clcs_fast.cpp
 * Date: 06/01/14
 * -------------------
 * oh CS 161
 * it rhymes with fun boba run
 * but it is not fun
 */

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

// Constants.
const int MAX_WORD_LEN = 2048;

// Global arrays.
int AB[2 * MAX_WORD_LEN][MAX_WORD_LEN];
int starts[MAX_WORD_LEN][MAX_WORD_LEN];
int ends[MAX_WORD_LEN][MAX_WORD_LEN];
int bds[MAX_WORD_LEN][2];
int curr_clcs;

string A, B;

int LCS() {
  int m = A.length(), n = B.length();
  int i, j;
  for (i = 0; i <= m; i++) AB[i][0] = 0;
  for (j = 0; j <= n; j++) AB[0][j] = 0;
  
  for (i = 1; i <= m; i++) {
    for (j = 1; j <= n; j++) {
      AB[i][j] = max(AB[i-1][j], AB[i][j-1]);
      if (A[i-1] == B[j-1]) AB[i][j] = max(AB[i][j], AB[i-1][j-1]+1);
    }
  }
  
  return AB[m][n];

}

bool IsUpValid(int path, int r, int c) {

  // Conditions on current point:
  //
  // 1. The upper point has the same value as the current point.
  // 2. It is not true that the current point is not on the path, but 
  //     the upper point is not on the path (i.e., not crossing the path).

  return AB[r - 1][c] == val && 
    !(c >= starts[path][r] && c <= ends[path][r] && 
      !(c >= starts[path][r - 1] && c <= ends[path][r - 1]));

}

bool IsLeftValid(int path, int r, int c) {

  // Conditions on current point:
  //
  // 1. The left point has the same value as the current point.
  // 2. It is not true that the current point is not on the path, but 
  //     the left point is not on the path (i.e., not crossing the path).

  return AB[r][c - 1] == val && 
    !(c >= starts[path][r] && c <= ends[path][r] && 
      !((c - 1) >= starts[path][r] && (c - 1) <= ends[path][r]));

}

void BackTrace(int path) {

  int r = path + A.length();
  int c = B.length();
  int val = AB[path + A.length()][B.length()];

  starts[path][path + A.length()] = B.length();
  ends[path][path + A.length()] = B.length();

  while (r != path && c != 0) {

    if (r == path) c--;
    else if (c == 0) r--;
    else if (IsUpValid(path, r, c)) {

      r--;
      ends[path][r] = c;

    } else if (IsLeftValid(path, r, c)) {

      c--;
      starts[path][r] = c;

    } else if (AB[r - 1][c - 1] == val - 1) {

      r--;
      c--;
      starts[path][r] = c;
      ends[path][r] = c;

    } else cerr << "BACKTRACE CHECKS OR ARRAY FILLING INCORRECT" << endl;

  }

}

void InitPathBounds() {
  // do stuff with path_bds
}

int main() {
  int num_test_case_idx;
  cin >> num_test_case_idx;
  for (int case_idx = 0; case_idx < num_test_case_idxs; case_idx++) {

    InitPathBounds();
    curr_clcs = 0;

    cin >> A >> B;
    cout << LCS() << endl;
  }
  return 0;
}

