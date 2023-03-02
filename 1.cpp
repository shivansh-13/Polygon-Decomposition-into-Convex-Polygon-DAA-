// hare krishna hare krishna , krishna krishna hare hare
// hare ram hare ram, ram ram hare hare
#include <bits/stdc++.h>
#include <vector>


//ToDo Check edge cases everywehre.
// reduce box func.
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


vector<double> minmax(vector<vector<double> > L){
  double minX = INT_MAX;
  double minY = INT_MAX;
  double maxX = INT_MIN;
  double maxY = INT_MIN;
  for(auto i:L){
    if(minX>i[0])minX = i[0];
    if(minY>i[1])minY = i[1];
    if(maxX<i[0])maxX = i[0];
    if(maxY<i[1])maxY = i[1];
  }

  vector<double> minmax;
  minmax.push_back(minX);
  minmax.push_back(minY);
  minmax.push_back(maxX);
  minmax.push_back(maxY);
  return minmax;
}


void box(vector<vector<double> > &L, double notch_x,double notch_y){
 vector<double> returnvec = minmax(L);
 if((notch_x>returnvec[0] && notch_x<returnvec[2]) &&(notch_y>returnvec[1] && notch_y<returnvec[3])){
  if(!angle_check(L[0][0],L[0][1],L[L.size()-1][0],L[L.size()-1][1],notch_x,notch_y)){
    L.pop_back();
    box(L,notch_x,notch_y);
  }
 }
  return;
}



int main()
{
  vector<vector<double>> P{
    {6,2},
    {4.5,2.52},
    {3.66,4.54},
    {4.66,6.46},
    {6.62,7.4},
    {9.2,7.66},
    {10.18,6.86},
    {9.34,6.5},
    {8.98,5.74},
    {7.04,5.42},
    {8.54,4.44},
    {11.4,5.86},
    {13.64,5.46},
    {14.3,3.72},
    {13.6,2.86},
    {11.8,2.86},
    {10.48,3.86}
    };

  vector<vector<double> > L;
  vector<vector<double> > LPVS;

  double v_1[2];
  double v_2[2];
  double v_prev[2];
  double v_i[2];
  double v_next[2];
  v_1[0] = P[0][0];
  v_1[1] = P[0][1];

  v_2[0] = P[1][0];
  v_2[1] = P[1][1];

  L.push_back(P[0]);
  L.push_back(P[1]);

  for (int i = 1; i < P.size()-1; i++)
  {
    v_prev[0] = P[i - 1][0];
    v_prev[1] = P[i - 1][1];

    v_i[0] = P[i][0];
    v_i[1] = P[i][1];

    v_next[0] = P[i + 1][0];
    v_next[1] = P[i + 1][1];

    if ((angle_check(v_prev[0], v_prev[1], v_i[0], v_i[1], v_next[0], v_next[1])) && (angle_check(v_i[0], v_i[1], v_next[0], v_next[1], v_1[0], v_1[1]) && angle_check(v_next[0], v_next[1], v_1[0], v_1[1], v_2[0], v_2[1])))
    {
      L.push_back({v_next[0], v_next[1]});
    }
    else
    {
      // cout<<v_next[0]<<","<<v_next[1]<<endl;
      // break;
       LPVS.push_back({v_next[0], v_next[1]});
      // break;
    }
  }
  for (int i = 0; i < LPVS.size(); i++)
  {
    /* code */
    box(L,LPVS[i][0],LPVS[i][1]);
  }
  
  
  for (auto i : L)
  {
    std::cout << i[0] << "," << i[1] << std::endl;
  }
  return 0;
}

