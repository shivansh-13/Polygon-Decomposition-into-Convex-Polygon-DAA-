// hare krishna hare krishna , krishna krishna hare hare
// hare ram hare ram, ram ram hare hare
#include <bits/stdc++.h>
#include <vector>

using namespace std;
const double PI = 3.14159265358979323846;

bool angle_check(double x1, double y1, double x2, double y2, double x3, double y3)
{
  // Calculate the vectors created by two pairs of points
  double u1 = x2 - x1;
  double v1 = y2 - y1;
  double u2 = x3 - x2;
  double v2 = y3 - y2;
  double z = (u1 * v2) - (u2 * v1);

  if (z >= 0)
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

ofstream fw("output.txt", std::ofstream::out);
ofstream fw2("output2.txt", std::ofstream::out);
ofstream fw3("output3.txt", std::ofstream::out);
struct Point
{
  double x;
  double y;
};

// Function to generate a random polygon with the specified number of points and distance range
std::vector<Point> generatePolygon(int pointAmount, double minDistance, double maxDistance)
{
  std::vector<Point> polygon;

  // Use a random number generator to generate random distances and angles
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> dist(minDistance, maxDistance);
  std::uniform_real_distribution<double> angle(0, 2 * M_PI);

  // Calculate the (x, y) coordinates for each point on the polygon
  for (int i = 0; i < pointAmount; i++)
  {
    Point point;

    double degrees = (360.0 / pointAmount) * (i + 1);
    double distance = dist(gen);
    double radians = degrees * M_PI / 180.0;

    point.x = (cos(radians) * distance) + 160.0;
    point.y = (sin(radians) * distance) + 160.0;

    polygon.push_back(point);
  }

  // Calculate the centroid of the polygon
  Point centroid = {0, 0};
  for (const Point &point : polygon)
  {
    centroid.x += point.x;
    centroid.y += point.y;
  }
  centroid.x /= polygon.size();
  centroid.y /= polygon.size();

  // Sort the points in clockwise order relative to the centroid
  std::sort(polygon.begin(), polygon.end(), [&centroid](const Point &a, const Point &b)
            {
        double angleA = atan2(a.y - centroid.y, a.x - centroid.x);
        double angleB = atan2(b.y - centroid.y, b.x - centroid.x);
        return angleA < angleB; });

  return polygon;
}

int main()
{
  std::vector<Point> polygon = generatePolygon(20, -19.0, 37.0);

  vector<vector<double>> P;
  for (const Point &point : polygon)
  {
    P.push_back({point.x, point.y});
    // std::cout << "(" << point.x << ", " << point.y << ")" << std::endl;
  }
  P.push_back(P[0]);

  // vector<vector<double>> P{
  //     {6, 2},        // 1
  //     {4.5, 2.52},   // 2
  //     {3.66, 4.54},  // 3
  //     {4.66, 6.46},  // 4
  //     {6.62, 7.4},   // 5
  //     {9.2, 7.66},   // 6
  //     {10.18, 6.86}, // 7
  //     {9.34, 6.5},   // 8
  //     {8.98, 5.74},  // 9
  //     {7.04, 5.42},  // 10
  //     {9.54, 4.44},  // 11
  //     {11.4, 5.86},  // 12
  //     {13.64, 5.46}, // 13
  //     {14.3, 3.72},  // 14
  //     {13.6, 2.86},  // 15
  //     {11.8, 2.86},  // 16
  //     {9.48, 3.86},  // 17
  //     {6, 2}};
  //     reverse(P.begin(),P.end());
  for (auto i : P)
  {
    fw2 << i[0] << "," << i[1] << endl;
  }
  fw2 << "end" << endl;
  vector<vector<double>> L;
  vector<vector<double>> LPVS;
  vector<vector<double>> LLE;
  vector<vector<vector<double>>> polygons;
  vector<vector<vector<vector<double>>>> LPVi;
  double v_1[2];
  double v_2[2];
  double v_prev[2];
  double v_i[2];
  double v_next[2];
  bool flag = 1;
  bool LPVSflag = 1;

  for (int i = 0; i < P.size() - 1;)
  {
    /* code */

    v_1[0] = P[i][0];
    v_1[1] = P[i][1];

    v_2[0] = P[i + 1][0];
    v_2[1] = P[i + 1][1];

    L.push_back(P[i]);
    L.push_back(P[i + 1]);

    for (int j = i + 1; j < P.size() - 1; j++)
    {
      v_prev[0] = P[j - 1][0];
      v_prev[1] = P[j - 1][1];

      v_i[0] = P[j][0];
      v_i[1] = P[j][1];

      v_next[0] = P[j + 1][0];
      v_next[1] = P[j + 1][1];

      if ((angle_check(v_prev[0], v_prev[1], v_i[0], v_i[1], v_next[0], v_next[1])) &&
          (angle_check(v_i[0], v_i[1], v_next[0], v_next[1], v_1[0], v_1[1]) &&
           angle_check(v_next[0], v_next[1], v_1[0], v_1[1], v_2[0], v_2[1])))
      {
        if (flag && LPVSflag)
        {
          L.push_back({v_next[0], v_next[1]});
        }
      }
      else
      {
        LPVS.push_back({v_next[0], v_next[1]});
        LPVSflag = 0;
        if (L.size() == 2)
        {
          flag = 0;
        }
        // Flag checks if only two vertices are thre i.e. one edge then dont push in L
        //  LPVSflag checks if first vertex is notch then push nothing in L
      }
    }

    if (flag)
    {
      for (int k = 0; k < LPVS.size(); k++)
      {
        box(L, LPVS[k][0], LPVS[k][1]);
      }
      if (L.size() != 2)
      {
        polygons.push_back(L);
      }
      if (L.size() != 2)
      {
        LLE.push_back({L[0][0], L[0][1], L[L.size() - 1][0], L[L.size() - 1][1]});
      }
      // P.push_back({L[0],L[L.size()-1]});
      // P.push_back(L[0]);
      if (L[0] != L[L.size() - 1])
      {
        P.push_back(L[L.size() - 1]);
      }
    }
    else if (L[0] != L[L.size() - 1])
    {
      P.push_back(L[1]);
      if (L.size() != 2)
      {
        polygons.push_back(L);
      }
    }

    for (auto i : L)
    {
      fw << i[0] << "," << i[1] << endl;
    }
    fw << "end" << endl;
    // cout << "end" << endl;
    i = i + L.size() - 1;

    L.clear();
    LPVS.clear();
    flag = 1;
    LPVSflag = 1;
  }

  LLE.pop_back();
  // We have correct LLE at this point
  polygons[polygons.size() - 1].pop_back();

  int dfjdhfj = 0;

  for (int k = 0; k < LLE.size(); k++) // 1
  {                                    // This is looping for all vertex in all diagonal list.

    // for (auto i : polygons)
    // {
    //   for (auto j : i)
    //   {
    //     cout << "{" << j[0] << "," << j[1] << "}"
    //          << "  ";
    //   }
    //   cout << endl;
    // }
    int polygon1, polygon2, a_in_2, b_in_1;
    vector<vector<double>> aleft1, aright1, aleft2, aright2;
    vector<vector<double>> merged_poly;
    for (int i = 0; i < polygons.size(); i++) // 2
    {                                         // This will find a particular edge (i.e 2 vertices ) in the two polygons
      for (int j = 0; j < polygons[i].size(); j++)
      { // this will look for second vertex in a particular polygon
        if (LLE[k][0] == polygons[i][j][0] && LLE[k][1] == polygons[i][j][1])
        { // this if checks, if a vertexx in a diagonal is there in this iteration of polygon
          if (LLE[k][2] == polygons[i][(j + 1) % polygons[i].size()][0] && LLE[k][3] == polygons[i][(j + 1) % polygons[i].size()][1])
          {
            // this check for second vertex of the diagonal
            dfjdhfj++;
            aleft1.push_back({polygons[i][(j - 1 + polygons[i].size()) % polygons[i].size()][0],
                              polygons[i][(j - 1 + polygons[i].size()) % polygons[i].size()][1]});
            aright1.push_back({polygons[i][(j + 2) % polygons[i].size()][0],
                               polygons[i][(j + 2) % polygons[i].size()][1]});
            polygon1 = i;
            b_in_1 = (j + 1) % polygons[i].size();
            // break;
          }
        }
        // We cheked for first A then B now we chek for first b then A
        if (LLE[k][2] == polygons[i][j][0] && LLE[k][3] == polygons[i][j][1])
        { // this if checks, if a vertexx in a diagonal is there in this iteration of polygon
          if (LLE[k][0] == polygons[i][(j + 1) % polygons[i].size()][0] && LLE[k][1] == polygons[i][(j + 1) % polygons[i].size()][1])
          {
            // this check for second vertex of the diagonal
            dfjdhfj++;
            aleft2.push_back({polygons[i][(j - 1 + polygons[i].size()) % polygons[i].size()][0],
                              polygons[i][(j - 1 + polygons[i].size()) % polygons[i].size()][1]});
            aright2.push_back({polygons[i][(j + 2) % polygons[i].size()][0],
                               polygons[i][(j + 2) % polygons[i].size()][1]});
            polygon2 = i;
            a_in_2 = (j + 1) % polygons[i].size();
            // break;
          }
        }
      }
    }

    if (dfjdhfj == 2)
    {
      // cout<<"anglecheck";
      // cout<<angle_check(aleft1[0][0], aleft1[0][1], LLE[k][0], LLE[k][1], aright2[0][0], aright2[0][1])<<endl;
      // cout<<angle_check(aleft2[0][0], aleft2[0][1], LLE[k][2], LLE[k][3], aright1[0][0], aright1[0][1])<<endl;
      if (angle_check(aleft1[0][0], aleft1[0][1], LLE[k][0], LLE[k][1], aright2[0][0], aright2[0][1]) &&
          angle_check(aleft2[0][0], aleft2[0][1], LLE[k][2], LLE[k][3], aright1[0][0], aright1[0][1]))
      {
        // cout << aleft1[0][0];
        // cout << aleft1[0][1] << endl;
        // cout << LLE[k][0];
        // cout << LLE[k][1] << endl;
        // cout << aright2[0][0];
        // cout << aright2[0][1] << endl;
        // cout << endl;
        // cout << aleft2[0][0];
        // cout << aleft2[0][1] << endl;
        // cout << LLE[k][2];
        // cout << LLE[k][3] << endl;
        // cout << aright1[0][0];
        // cout << aright1[0][1] << endl;
        // cout << "mergeeeeeeee" << endl;
        // cout << polygon1 << "," << polygon2 << endl;

        int counter = b_in_1;
        // cout<<"a"<<a+1 % (polygons[polygon1].size())<<"b"<<b % (polygons[polygon1].size())<<endl;
        // polygons.push_back({});
        while (polygons[polygon1][counter % (polygons[polygon1].size())][0] != LLE[k][0] && polygons[polygon1][counter % (polygons[polygon1].size())][1] != LLE[k][1])
        {
          // cout<<"hi1"<<counter<<endl;
          // cout << polygons[polygon1][counter % (polygons[polygon1].size())][0] << "," << polygons[polygon1][counter % (polygons[polygon1].size())][1] << endl;
          merged_poly.push_back({polygons[polygon1][counter % (polygons[polygon1].size())][0], polygons[polygon1][counter % (polygons[polygon1].size())][1]});
          counter++;
        }

        counter = a_in_2;
        while (polygons[polygon2][counter % (polygons[polygon2].size())][0] != LLE[k][2] && polygons[polygon2][counter % (polygons[polygon2].size())][1] != LLE[k][3])
        {
          // cout<<"hi2"<<counter<<endl;
          // cout << polygons[polygon2][counter % (polygons[polygon2].size())][0] << "," << polygons[polygon2][counter % (polygons[polygon2].size())][1] << endl;

          merged_poly.push_back({polygons[polygon2][counter % (polygons[polygon2].size())][0], polygons[polygon2][counter % (polygons[polygon2].size())][1]});
          counter++;
        }
        // cout<<"superend"<<endl;
        vector<vector<double>> copypoly;
        for (auto i : merged_poly)
        {
          copypoly.push_back({i[0], i[1]});
        }
        polygons.push_back(copypoly);
        if (polygon1 > polygon2)
        {
          polygons.erase(polygons.begin() + polygon1);
          polygons.erase(polygons.begin() + polygon2);
        }
        else
        {
          polygons.erase(polygons.begin() + polygon2);
          polygons.erase(polygons.begin() + polygon1);
        }
      }
    }
    // for(auto o:merged_poly){
    //   cout<<"mergerddpoly"<<o[0]<<","<<o[1]<<endl;
    // }
    aleft1.clear();
    aleft2.clear();
    aright1.clear();
    aright2.clear();
    merged_poly.clear();
    dfjdhfj = 0;
  }
  // for (auto i : LLE)
  // {

  //   cout << "{" << i[0] << "," << i[1] << "}"
  //        << ","
  //        << "{" << i[2] << "," << i[3] << "}" << endl;
  //   // std::cout << j[0] << "," << j[1] << std::endl;

  //   // cout << "end" << endl;
  // }

  for (auto i : polygons)
  {
    for (auto j : i)
    {
      fw3 << j[0] << "," << j[1] << endl;
    }
    fw3 << "end" << endl;
  }
  return 0;
}