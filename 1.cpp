// hare krishna hare krishna , krishna krishna hare hare
// hare ram hare ram, ram ram hare hare
#include <bits/stdc++.h>
#include <vector>

// ToDo Check edge cases everywehre.
//  reduce box func.
using namespace std;

bool angle_check(double x1, double y1, double x2, double y2, double x3, double y3)
{
  // Calculate the vectors created by two pairs of points
  double u1 = x2 - x1;
  double v1 = y2 - y1;
  double u2 = x3 - x2;
  double v2 = y3 - y2;
  double z = (u1 * v2) - (u2 * v1);

  if (z <= 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

vector<double> minmax(vector<vector<double>> L)
{
  double minX = INT_MAX;
  double minY = INT_MAX;
  double maxX = INT_MIN;
  double maxY = INT_MIN;
  for (auto i : L)
  {
    if (minX > i[0])
      minX = i[0];
    if (minY > i[1])
      minY = i[1];
    if (maxX < i[0])
      maxX = i[0];
    if (maxY < i[1])
      maxY = i[1];
  }

  vector<double> minmax;
  minmax.push_back(minX);
  minmax.push_back(minY);
  minmax.push_back(maxX);
  minmax.push_back(maxY);
  return minmax;
}

void box(vector<vector<double>> &L, double notch_x, double notch_y)
{
  vector<double> returnvec = minmax(L);
  if ((notch_x > returnvec[0] && notch_x < returnvec[2]) && (notch_y > returnvec[1] && notch_y < returnvec[3]))
  {
    if (!angle_check(L[0][0], L[0][1], L[L.size() - 1][0], L[L.size() - 1][1], notch_x, notch_y))
    {
      L.pop_back();
      box(L, notch_x, notch_y);
    }
  }
  return;
}

int main()
{
  vector<vector<double>> P{
      {6, 2}, //1
      {4.5, 2.52}, //2
      {3.66, 4.54}, //3
      {4.66, 6.46}, //4
      {6.62, 7.4},  //5
      {9.2, 7.66},  //6
      {10.18, 6.86}, //7
      {9.34, 6.5},  //8
      {8.98, 5.74},  //9
      {7.04, 5.42},  //10
      {8.54, 4.44},  //11
      {11.4, 5.86},  //12
      {13.64, 5.46},  //13
      {14.3, 3.72},  //14
      {13.6, 2.86},  //15
      {11.8, 2.86},  //16
      {9.48, 3.86},//17
      {6,2}
      };

  vector<vector<double>> L;
  vector<vector<double>> LPVS;
  vector<vector<vector<double>>> polygons;
  double v_1[2];
  double v_2[2];
  double v_prev[2];
  double v_i[2];
  double v_next[2];
  bool flag = 1;
  bool LPVSflag = 1;
  for (int i = 0; i < P.size() - 1;){
    /* code */

    v_1[0] = P[i][0];
    v_1[1] = P[i][1];

    v_2[0] = P[i + 1][0];
    v_2[1] = P[i + 1][1];

    L.push_back(P[i]);
    L.push_back(P[i + 1]);

    for (int j = i + 1; j < P.size() - 1; j++){
      v_prev[0] = P[j - 1][0];
      v_prev[1] = P[j - 1][1];

      v_i[0] = P[j][0];
      v_i[1] = P[j][1];

      v_next[0] = P[j + 1][0];
      v_next[1] = P[j + 1][1];

      if ((angle_check(v_prev[0], v_prev[1], v_i[0], v_i[1], v_next[0], v_next[1])) &&
          (angle_check(v_i[0], v_i[1], v_next[0], v_next[1], v_1[0], v_1[1]) &&
           angle_check(v_next[0], v_next[1], v_1[0], v_1[1], v_2[0], v_2[1]))){
        if (flag && LPVSflag){
          L.push_back({v_next[0], v_next[1]});
        }
      }
      else{
        LPVS.push_back({v_next[0], v_next[1]});
        LPVSflag=0;
        if (L.size() == 2){
          flag = 0;
        }
      }
    }

    if (flag){
      for (int k = 0; k < LPVS.size(); k++){
        box(L, LPVS[k][0], LPVS[k][1]);
      }
      polygons.push_back(L);
    }

    i = i + L.size();
    L.clear();


    // for(auto i:LPVS){
    //   cout<<i[0]<<","<<i[1]<<endl;
    // }
    // cout << "end" << endl;



    LPVS.clear();
    flag = 1;
    LPVSflag = 1;
  }

  for (auto i : polygons){
    for (auto j : i){
      std::cout << j[0] << "," << j[1] << std::endl;
    }
    cout << "end" << endl;
  }
  return 0;
}