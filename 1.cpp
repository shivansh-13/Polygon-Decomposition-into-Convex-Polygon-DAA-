// hare krishna hare krishna , krishna krishna hare hare
// hare ram hare ram, ram ram hare hare



//Shivansh Shrivastava 2020A7PS2095H 
// Bhavya Jain 2020A7PS0240H
// Dhruv Agrawal 2020A7PS2193H

#include <bits/stdc++.h>
#include <vector>

using namespace std;
/// @brief Value of pi to 20th decimal place for calculation
const double PI = 3.14159265358979323846;

/// @brief This function is used to evaluate the angle between 3 points and return true if the angle is convex and false if angle is convex
/// @param x1 X Coordinate of point 1
/// @param y1 Y Coordinate of point 1
/// @param x2 X Coordinate of point 2
/// @param y2 Y Coordinate of point 2
/// @param x3 X Coordinate of point 3
/// @param y3 Y Coordinate of point 3
/// @return True if the angle is convex else false
bool angle_check(double x1, double y1, double x2, double y2, double x3, double y3)
{// Calculate the vectors created by two pairs of points
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

/// @brief This function takes a vector of (x, y) pairs and returns a vector containing the minimum and maximum x and y values.
/// @param L vector of (x,y) coordinates
/// @return A vector with 4 elements min x,y and max x,y
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

/// @brief The box() function takes the polygon and a point (notch_x, notch_y) as input and checks whether the point lies inside the polygon. If it does not, the function removes the last point from the polygon and calls itself recursively until the point lies inside the polygon.
/// @param L vector of coordinates
/// @param notch_x coordinate X
/// @param notch_y coordinate Y
void box(vector<vector<double>> &L, double notch_x, double notch_y)
{
  vector<double> returnvec = minmax(L);
  if(L.size() == 2) return;
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
/// @brief Stores the coordinates for randomly generated polygon
ofstream fw("output.txt", ofstream::out);
/// @brief Stores the coordinates for decomposed polygon
ofstream fw2("output2.txt", ofstream::out);
/// @brief Stores the coordinates for final merged polygon
ofstream fw3("output3.txt", ofstream::out);

/// @brief Struct for Coordinates x and y
struct Point
{
  double x;
  double y;
};

/// @brief Function to generate a random polygon with the specified number of points and distance range
/// @param pointAmount Number of points
/// @param minDistance Minimum distance from the center of the polygon
/// @param maxDistance Maximum distance from the center of the polygon
/// @return A vector of Points containing the coordinates of the polygon

// Function to generate a random polygon with the specified number of points and distance range

vector<Point> generatePolygon(int pointAmount, double minDistance, double maxDistance)
{
  vector<Point> polygon;

  /// The generatePolygon function uses a random number generator to generate the distances and angles for each point and then calculates the (x, y) coordinates for each point based on these values.
  /// After the polygon is generated, it is stored in the P vector as a vector of (x, y) pairs.
  // Use a random number generator to generate random distances and angles
  random_device rd; /// random_device generates random numbers
  mt19937 gen(rd()); /// mt19937 sort the points
  uniform_real_distribution<double> dist(minDistance, maxDistance); /// uniform_real_distribution Produces random doubleing-point values uniformly distributed between interval a and b
  uniform_real_distribution<double> angle(0, 2 * M_PI);

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

  sort(polygon.begin(), polygon.end(), [&centroid](const Point &a, const Point &b)
            {
        double angleA = atan2(a.y - centroid.y, a.x - centroid.x);
        double angleB = atan2(b.y - centroid.y, b.x - centroid.x);
        return angleA < angleB; });

  return polygon;
}

//  vector<vector<double>> P{
//       {6, 2},        // 1
//       {4.5, 2.52},   // 2
//       {3.66, 4.54},  // 3
//       {4.66, 6.46},  // 4
//       {6.62, 7.4},   // 5
//       {9.2, 7.66},   // 6
//       {10.18, 6.86}, // 7
//       {9.34, 6.5},   // 8
//       {8.98, 5.74},  // 9
//       {7.04, 4.42},  // 10
//       {9.54, 4.44},  // 11
//       {11.4, 5.86},  // 12
//       {13.64, 5.46}, // 13
//       {14.3, 3.72},  // 14
//       {13.6, 2.86},  // 15
//       {11.8, 2.86},  // 16
//       {9.48, 3.86},  // 17
//       {6, 2}};
//       reverse(P.begin(),P.end());

/// @brief Represents a vertex in 2D space. It has an identifier called key and two coordinates x and y.
class vertex1
{
public:
  int key;     /// An identifier for the vertex
  double x, y; /// The coordinates of the vertex
};

/// @brief Represents a half-edge. It stores the keys and pointers to the origin and end vertices of the half-edge, as well as a pointer to its twin half-edge.
class half_edge
{
public:
  int origin_v, end_v;         /// Keys of the vertices that the half-edge connects
  class vertex1 *origin, *end; /// Pointers to the vertices that the half-edge connects
  class half_edge *twin;       /// Pointer to the twin half-edge
};

/// @brief This class represents a face. It has an identifier called key.
class face
{
public:
  int key = -1; /// An identifier for the face
};

/// @brief This class represents a vertex table. It stores pointers to a vertex and a half-edge that starts at the vertex.
class vertex_table
{
public:
  class vertex1 *v;   /// Pointer to a vertex
  class half_edge *e; /// Pointer to a half-edge that starts at the vertex
};

/// @brief This class represents a face table. It stores pointers to a face, pointers to the inner half-edges of the face, a pointer to the outer half-edge of the face, and the area of the face.
class face_table
{
public:
  class face *face = NULL;                 /// Pointer to a face
  vector<half_edge *> inner_components;    /// Pointers to the inner half-edges of the face
  class half_edge *outer_component = NULL; /// Pointer to the outer half-edge of the face
  double area = -1;                        /// The area of the face
};

/// @brief This class represents a half-edge table. It stores pointers to a half-edge, its next and previous half-edges, and a pointer to the face that is incident to the half-edge.
class half_edge_table
{
public:
  class half_edge *half_edge, *next, *prev; /// Pointers to the half-edge, its next and previous half-edges
  class face *incident_face = NULL;         /// Pointer to the face incident to the half-edge
};

#define INF 10000

/// @brief Given three points checks whether they are collinear or not
/// @param p
/// @param q
/// @param r
/// @return True if collinear and false if not collinear
bool onSegment(Point p, Point q, Point r)
{
  if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && q.y <= max(p.y, r.y) &&
      q.y >= min(p.y, r.y))
    return true;
  return false;
}

/// @brief Finds orientation of 3 points whether collinear, clockwise or counterclockwise
/// @param p 
/// @param q 
/// @param r 
/// @return 0 for collinear, 1 for clockwise and 2 for counterclockwise
int orientation(Point p, Point q, Point r)
{
  double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

  if (val == 0)
    return 0;               // colinear
  return (val > 0) ? 1 : 2; // clock or counterclock wise
}

/// @brief Checks if 2 line segments intersect
/// @param p1
/// @param q1
/// @param p2
/// @param q2
/// @return The function that returns true if line segment 'p1q1' and 'p2q2' intersect.
bool doIntersect(Point p1, Point q1, Point p2, Point q2)
{
  // Find the four orientations needed for general and
  // special cases
  double o1 = orientation(p1, q1, p2);
  double o2 = orientation(p1, q1, q2);
  double o3 = orientation(p2, q2, p1);
  double o4 = orientation(p2, q2, q1);

  // General case
  if (o1 != o2 && o3 != o4)
    return true;

  // Special Cases
  // p1, q1 and p2 are colinear and p2 lies on segment p1q1
  if (o1 == 0 && onSegment(p1, p2, q1))
    return true;

  // p1, q1 and p2 are colinear and q2 lies on segment p1q1
  if (o2 == 0 && onSegment(p1, q2, q1))
    return true;

  // p2, q2 and p1 are colinear and p1 lies on segment p2q2
  if (o3 == 0 && onSegment(p2, p1, q2))
    return true;

  // p2, q2 and q1 are colinear and q1 lies on segment p2q2
  if (o4 == 0 && onSegment(p2, q1, q2))
    return true;

  return false; // Doesn't fall in any of the above cases
}

/// @brief checks if a point lies inside the polygon or not
/// @param polygon
/// @param n
/// @param p
/// @return Returns true if the point p lies inside and false otherwise
bool isInside(Point polygon[], int n, Point p)
{
  // There must be at least 3 vertices in polygon[]
  if (n < 3)
    return false;

  // Create a point for line segment from p to infinite
  Point extreme = {INF, p.y};

  // Count intersections of the above line with sides of polygon
  int count = 0, i = 0;
  do
  {
    int next = (i + 1) % n;

    // Check if the line segment from 'p' to 'extreme' intersects
    // with the line segment from 'polygon[i]' to 'polygon[next]'
    if (doIntersect(polygon[i], polygon[next], p, extreme))
    {
      // If the point 'p' is colinear with line segment 'i-next',
      // then check if it lies on segment. If it lies, return true,
      // otherwise false
      if (orientation(polygon[i], p, polygon[next]) == 0)
        return onSegment(polygon[i], p, polygon[next]);

      count++;
    }
    i = next;
  } while (i != 0);

  // Return true if count is odd, false otherwise
  return count & 1; // Same as (count%2 == 1)
}

/// @brief Print half edge
/// @param a 
/// @param v 
/// @param l 
void print_half_edge(vector<half_edge> &a, vector<vertex1> &v, int l)
{
  for (int i = 0; i < l; i++)
  {
    int s, e;
    half_edge *temp;
    s = a[i].origin_v;
    e = a[i].end_v;
    temp = a[i].twin;
    cout << "edge :" << s << "-" << e << " ";
    cout << "coordinates : (" << v[s].x << " , " << v[s].y << ") , (" << v[e].x
         << " , " << v[e].y << ") ";
    cout << "Twin edge :" << temp->origin_v << "-" << temp->end_v << "\n";
  }
}

/// @brief Search for half edge
/// @param s 
/// @param e 
/// @param h 
/// @return half-edge
int search_half_edge(int s, int e, vector<half_edge> &h)
{
  int l = h.size();
  for (int i = 0; i < l; i++)
  {
    if (h[i].origin_v == s && h[i].end_v == e)
    {
      return i;
    }
  }
  cout << "Error in serching half edge"
       << "\n";
  return -1;
}

/// @brief Searches half-edge table
/// @param half_edge 
/// @param half_edge_table 
/// @return index if found otherwise 0
int search_half_edge_table(half_edge *half_edge,
                           vector<half_edge_table> half_edge_table)
{
  int l = half_edge_table.size();
  for (int i = 0; i < l; i++)
  {
    if (half_edge_table[i].half_edge == half_edge)
      return i;
  }
  return 0;
}

/// @brief Fills vertex table
/// @param ver_tab 
/// @param l 
/// @param adj 
/// @param h 
/// @param v 
void fill_vertex_table(vector<vertex_table> &ver_tab, int l,
                       vector<vector<double>> adj, vector<half_edge> &h,
                       vector<vertex1> &v)
{
  for (int i = 0; i < l; i++)
  {
    int s = v[i].key;
    int e = adj[s][0]; // Assuming no stand alone vertex
    ver_tab[i].v = &v[i];
    ver_tab[i].e = &h[search_half_edge(s, e, h)];
  }
}

double angle(double x1, double y1, double x2, double y2, double x3, double y3)
{
  x1 = x1 - x2;
  y1 = y1 - y2;
  x3 = x3 - x2;
  y3 = y3 - y2;
  double dot = x1 * x3 + y1 * y3;
  double det = x1 * y3 - y1 * x3;
  double result = atan2(det, dot);
  return ((result < 0) ? (result * 180 / 3.141592) + 360
                       : (result * 180 / 3.141592));
}

/// @brief Finds next half edge
/// @param current 
/// @param adj 
/// @param vertex 
/// @param half_edge 
/// @return next half-edge
int next_half_edge(int current, vector<vector<double>> adj,
                   vector<vertex1> vertex, vector<half_edge> &half_edge)
{
  int s, e;
  double max_angle = 0, temp_angle;
  int next_vertex;
  s = half_edge[current].origin_v;
  e = half_edge[current].end_v;
  double x1, x2, y1, y2;
  next_vertex = s;
  x1 = vertex[s].x;
  y1 = vertex[s].y;
  x2 = vertex[e].x;
  y2 = vertex[e].y;
  for (auto k : adj[e])
  {
    if (k == e)
      continue;
    else
    {
      temp_angle = angle(x1, y1, x2, y2, vertex[k].x, vertex[k].y);
      if (max_angle < temp_angle)
      {
        max_angle = temp_angle;
        next_vertex = k;
      }
    }
  }
  return search_half_edge(e, next_vertex, half_edge);
}

double area_poly(vector<int> key, vector<vertex1> vertex)
{
  double x2, y2;
  double signedArea = 0;
  int l = key.size();
  for (int i = 0; i < l; i++)
  {
    double x1 = vertex[key[i]].x;
    double y1 = vertex[key[i]].y;
    if (i == l - 1)
    {
      x2 = vertex[key[0]].x;
      y2 = vertex[key[0]].y;
      signedArea += (x1 * y2 - x2 * y1);
    }
    else
    {
      x2 = vertex[key[i + 1]].x;
      y2 = vertex[key[i + 1]].y;
      signedArea += (x1 * y2 - x2 * y1);
    }
  }
  return abs(signedArea / 2);
}

/// @brief Fills half-edge face
/// @param half_edge_table 
/// @param face 
/// @param vertex 
/// @param face_table 
void fill_half_edge_face(vector<half_edge_table> &half_edge_table,
                         vector<face> &face, vector<vertex1> vertex,
                         vector<face_table> &face_table)
{
  int l = half_edge_table.size();
  int face_key = 0;
  int head = 0;
  double x2, y2;
  double signedArea = 0;
  for (int i = 0; i < l; i++)
  {
    double x1 = vertex[half_edge_table[i].half_edge->origin_v].x;
    double y1 = vertex[half_edge_table[i].half_edge->origin_v].y;
    if (half_edge_table[i].next == half_edge_table[head].half_edge)
    {
      x2 = vertex[half_edge_table[head].half_edge->origin_v].x;
      y2 = vertex[half_edge_table[head].half_edge->origin_v].y;
      signedArea += (x1 * y2 - x2 * y1);
      if (signedArea > 0) // Assuming no standalone edge
      {
        face_table[face_key].area = abs(signedArea / 2);
        face[face_key].key = face_key;
        face_table[face_key].face = &face[face_key];
        face_table[face_key].outer_component = half_edge_table[head].half_edge;
        for (int j = head; j <= i; j++)
          half_edge_table[j].incident_face = &face[face_key];
        face_key++;
      }
      signedArea = 0;
      head = i + 1;
    }
    else
    {
      x2 = vertex[half_edge_table[i].half_edge->end_v].x;
      y2 = vertex[half_edge_table[i].half_edge->end_v].y;
      signedArea += (x1 * y2 - x2 * y1);
    }
  }
  face[face_key].key = -1;
  face_table[face_key].face = &face[face_key];
}

/// @brief Fills half-edge table
/// @param half_edge_table 
/// @param half_edge 
/// @param unvisited_half_edge 
/// @param vertex 
/// @param adj 
/// @param face 
/// @param face_table 
void fill_half_edge_table(vector<half_edge_table> &half_edge_table,
                          vector<half_edge> &half_edge,
                          vector<bool> &unvisited_half_edge,
                          vector<vertex1> vertex, vector<vector<double>> adj,
                          vector<face> &face, vector<face_table> &face_table)
{
  int l = unvisited_half_edge.size();
  int current, next, previous;
  int head, j = 0, head_index;
  for (int i = 0; i < l; i++)
  {
    if (unvisited_half_edge[i] == 0)
    {
      unvisited_half_edge[i] = 1;
      head = i;
      head_index = j;
      half_edge_table[j].half_edge = &half_edge[i];
      next = next_half_edge(i, adj, vertex, half_edge);
      half_edge_table[j].next = &half_edge[next];
      j++;
      previous = i;
      current = next;
      while (1)
      {
        unvisited_half_edge[current] = 1;
        half_edge_table[j].half_edge = &half_edge[current];
        next = next_half_edge(current, adj, vertex, half_edge);
        half_edge_table[j].next = &half_edge[next];
        half_edge_table[j].prev = &half_edge[previous];
        j++;
        previous = current;
        current = next;
        if (next == head)
        {
          break;
        }
      }
      half_edge_table[head_index].prev = &half_edge[previous];
    }
  }
  fill_half_edge_face(half_edge_table, face, vertex, face_table);
}

/// @brief Checks if a point is inside or outside
/// @param ver
/// @param key
/// @param vertex
/// @return Returns true if the point p lies inside and false otherwise
bool check_if_point_is_inside(int ver, vector<int> key,
                              vector<vertex1> &vertex)
{
  double x, y;
  int n = key.size();
  Point polygon1[n];
  for (int i = 0; i < n; i++)
  {
    polygon1[i] = {vertex[key[i]].x, vertex[key[i]].y};
  }
  Point p = {vertex[ver].x, vertex[ver].y};
  return isInside(polygon1, n, p);
}

int check_if_inside(vector<face_table> &face_table, vector<vertex1> &vertex,
                    vector<int> key, vector<face> face,
                    vector<half_edge_table> half_edge_table)
{
  int face_index = -1;
  double self_area;
  int l = face_table.size();
  class face_table temp;
  class half_edge *half_edge, *temp2, *head;
  double min_area = 100021.1;
  self_area = area_poly(key, vertex);
  for (int i = 0; i < l; i++)
  {
    if (face_table[i].face == NULL)
      break;
    temp = face_table[i];
    half_edge = temp.outer_component;
    int index = search_half_edge_table(half_edge, half_edge_table);
    temp2 = half_edge_table[index].half_edge;
    head = temp2;
    vector<int> key2;
    while (1)
    {
      key2.push_back(temp2->origin_v);
      temp2 = half_edge_table[index].next;
      if (head == temp2)
        break;
      index++;
    }
    bool flag = 1;
    for (int k = 0; k < key.size(); k++)
    {
      flag = flag & check_if_point_is_inside(key[k], key2, vertex);
      if (flag == 0)
        break;
    }
    if (flag)
    {
      double a = area_poly(key2, vertex);
      if (min_area > a && self_area != a && self_area < a)
      {
        min_area = a;
        face_index = i;
      }
    }
  }
  return face_index;
}

int search_outer_face(vector<face> face)
{
  for (int i = 0; i < face.size(); i++)
  {
    if (face[i].key == -1)
      return i;
  }
  return 0;
}

void fill_face_table_inner_components(vector<face_table> &face_table,
                                      vector<half_edge> &half_edge,
                                      vector<half_edge_table> &half_edge_table,
                                      vector<face> &face,
                                      vector<vertex1> vertex)
{
  int face_index;
  int l = half_edge_table.size();
  class half_edge *temp, *head;
  for (int i = 0; i < l; i++)
  {
    if (half_edge_table[i].incident_face != NULL)
      continue;
    temp = half_edge_table[i].half_edge;
    head = temp;
    vector<int> key;
    while (1)
    {
      key.push_back(temp->origin_v);
      temp = half_edge_table[i].next;
      if (head == temp)
      {
        face_index =
            check_if_inside(face_table, vertex, key, face, half_edge_table);
        if (face_index != -1)
        {
          int index = search_half_edge_table(temp, half_edge_table);
          face_table[face_index].inner_components.push_back(
              half_edge_table[index].half_edge);
          while (1)
          {
            half_edge_table[index].incident_face = &face[face_index];
            temp = half_edge_table[index].next;
            if (temp == head)
              break;
            index++;
          }
        }
        else
        {
          face_index = search_outer_face(face);
          int index = search_half_edge_table(temp, half_edge_table);
          face_table[face_index].inner_components.push_back(
              half_edge_table[index].half_edge);
          while (1)
          {
            half_edge_table[index].incident_face = &face[face_index];
            temp = half_edge_table[index].next;
            if (temp == head)
              break;
            index++;
          }
        }

        break;
      }
      i++;
    }
    key.clear();
  }
}

/// @brief Prints vertex table
/// @param ver_tab 
/// @param l 
void print_vertex_table(vector<vertex_table> &ver_tab, int l)
{
  vertex1 *temp_v;
  half_edge *temp_e;
  cout << "\n"
       << "********** Vertex Table ***********"
       << "\n";
  cout << "vertex "
       << " Coordinates "
       << "Incident Edge "
       << "\n";
  for (int i = 0; i < l; i++)
  {
    temp_v = ver_tab[i].v;
    temp_e = ver_tab[i].e;
    cout << temp_v->key << "\t(" << temp_v->x << " , " << temp_v->y << ") ";
    cout << "\t" << temp_e->origin_v << "-" << temp_e->end_v << "\n";
  }
}

/// @brief Prints half-edge table
/// @param half_edge_table 
/// @param half_edge 
void print_half_edge_table(vector<half_edge_table> &half_edge_table,
                           vector<half_edge> &half_edge)
{
  int l = half_edge_table.size();
  class half_edge_table temp;
  cout << "\n"
       << "********** Half Edge Table **********"
       << "\n";
  cout << "Half-edge "
       << "Origin "
       << "Twin Incident_Face Next Previous"
       << "\n";
  for (int i = 0; i < l; i++)
  {
    temp = half_edge_table[i];
    cout << temp.half_edge->origin_v << "-" << temp.half_edge->end_v << "\t   ";
    cout << temp.half_edge->origin_v << "\t";
    cout << temp.half_edge->twin->origin_v << "-" << temp.half_edge->twin->end_v
         << "\t";
    if (temp.incident_face != NULL)
      cout << "   F" << temp.incident_face->key << "\t    ";
    else
      cout << "   NULL"
           << "     ";
    cout << temp.next->origin_v << "-" << temp.next->end_v << "   ";
    cout << temp.prev->origin_v << "-" << temp.prev->end_v << "\n";
  }
}

/// @brief Prints face table
/// @param face_table 
void print_face_table(vector<face_table> face_table)
{
  int l = face_table.size();
  class face_table temp;
  cout << "*************** Face_Table **************"
       << "\n";
  cout << "Face   Outer_component"
       << "  Inner_Components"
       << "\n";
  for (int i = 0; i < l; i++)
  {
    temp = face_table[i];
    if (temp.face == NULL)
      break;
    if (temp.outer_component == NULL)
    {
      cout << "Finf" << setw(3) << "|" << setw(8) << "NULL" << setw(9) << "|"
           << setw(5);
      int n = temp.inner_components.size();
      for (int j = 0; j < n; j++)
        cout << temp.inner_components[j]->origin_v << "-"
             << temp.inner_components[j]->end_v << "  ";
      if (n == 0)
        cout << setw(5) << "NULL\t";
      cout << "\n";
    }
    else
    {
      cout << "F" << temp.face->key << setw(5) << "|" << setw(5)
           << temp.outer_component->origin_v << "-"
           << temp.outer_component->end_v;
      cout << setw(10) << "|" << setw(5);
      int n = temp.inner_components.size();
      for (int j = 0; j < n; j++)
        cout << temp.inner_components[j]->origin_v << "-"
             << temp.inner_components[j]->end_v << "\t";
      if (n == 0)
        cout << "    NULL";
      cout << "\n";
    }
  }
}

/// @brief Searched face table
/// @param key 
/// @param face_table 
/// @return returns index if found otherwise -1
int search_face_table(int key, vector<face_table> &face_table)
{
  for (int i = 0; i < face_table.size(); i++)
  {
    if (face_table[i].face->key == key)
      return i;
  }

  cout << "Error in search_face_table" << endl;
  return -1;
}

void print_faces_with_area_lessthan_threshhold(
    double threshhold_area, vector<face_table> &face_table,
    vector<class half_edge_table> half_edge_table,
    vector<class vertex1> vertex)
{
  class face_table temp = face_table[0];
  int i = 0;
  // cout<<"*****Area of faces******"<<endl;
  while (1)
  {
    if (temp.face == NULL)
      break;

    vector<class half_edge *> inner_edges = temp.inner_components;
    double area = temp.area;
    for (int i = 0; i < inner_edges.size(); i++)
    {
      int index = search_half_edge_table(inner_edges[i], half_edge_table);
      class half_edge *temp2 = half_edge_table[index].half_edge, *head;
      head = temp2;
      vector<int> key;

      while (1)
      {
        key.push_back(temp2->origin_v);
        temp2 = half_edge_table[index].next;

        if (head == temp2)
          break;
        index++;
      }
      area -= area_poly(key, vertex);
    }

    // cout<<"F "<<temp.face->key<<" "<<area<<endl;

    if (area < threshhold_area && area > 0)
      cout << "F" << temp.face->key << ", less than threshhold.\n";
    i++;
    temp = face_table[i];
  }
}

/// @brief Prints neighbouring faces
/// @param x 
/// @param y 
/// @param half_edge_vector 
/// @param half_edge_table 
/// @param face_table 
void print_neighbouring_faces(double x, double y,
                              vector<half_edge> &half_edge_vector,
                              vector<half_edge_table> &half_edge_table,
                              vector<face_table> &face_table)
{
  class half_edge *half_edge, *head, *temp;
  map<int, bool> m;
  int index = search_half_edge(x, y, half_edge_vector);
  half_edge = &half_edge_vector[index];
  index = search_half_edge_table(half_edge, half_edge_table);
  int stored_index = index;
  int original_face = half_edge_table[stored_index].incident_face->key;
  if (original_face == -1) // For handling Outer boundary
  {
    int face_table_index = search_face_table(original_face, face_table);
    vector<class half_edge *> outer_component =
        face_table[face_table_index].inner_components;
    int index_inner;
    for (int k = 0; k < outer_component.size(); k++)
    {
      int outer_component_index =
          search_half_edge_table(outer_component[k], half_edge_table);
      index = outer_component_index;
      head = half_edge_table[outer_component_index].half_edge;
      temp = head;
      while (1)
      {
        temp = half_edge_table[outer_component_index].next;
        index_inner = search_half_edge_table(temp->twin, half_edge_table);
        m[half_edge_table[index_inner].incident_face->key] = 1;
        outer_component_index++;
        if (temp == head)
          break;
      }
    }
    for (auto j : m)
    {
      cout << "F" << j.first << endl;
    }
    return;
  }
  int face_table_index = search_face_table(original_face, face_table);
  class half_edge *outer_component =
      face_table[face_table_index].outer_component;
  int outer_component_index =
      search_half_edge_table(outer_component, half_edge_table);
  index = outer_component_index;
  head = half_edge_table[outer_component_index].half_edge;
  temp = head;
  bool flag = 0;
  while (1)
  {
    temp = half_edge_table[outer_component_index].half_edge;
    if (temp == half_edge_table[stored_index].half_edge)
    {
      flag = 1;
      break;
    }
    outer_component_index++;
    if (temp == head)
      break;
  }
  // cout << flag <<"\n";
  int indext;
  if (flag)
  { // For handaling outer edge
    head = half_edge_table[index].half_edge;
    temp = head;
    while (1)
    {
      indext = search_half_edge_table(temp->twin, half_edge_table);
      m[half_edge_table[indext].incident_face->key] = 1;
      temp = half_edge_table[index].next;
      if (temp == head)
        break;
      index++;
    }
    vector<class half_edge *> inner_components =
        face_table[face_table_index].inner_components;

    for (int i = 0; i < inner_components.size(); i++)
    {
      index =
          search_half_edge_table(inner_components[i]->twin, half_edge_table);
      m[half_edge_table[index].incident_face->key] = 1;
    }
    for (auto j : m)
    {
      cout << "F" << j.first << endl;
    }
  }
  else
  {
    print_neighbouring_faces(outer_component->origin_v, outer_component->end_v,
                             half_edge_vector, half_edge_table, face_table);
  }
}

int main(int argc, char* argv[])
{
  int n=stoi(argv[1]);
  //cout<<"n"<<n<<endl;
  vector<Point> polygon = generatePolygon(n, 70.0, 100.0);
  auto start = std::chrono::high_resolution_clock::now();
  vector<vector<double>> P;
  int nodes=0;
  for (const Point &point : polygon)
  {
    P.push_back({point.x, point.y});
    nodes++;
  }
  P.push_back(P[0]);
  vector<vertex1> vertex(nodes);
  int i=0;
  for (const Point &point : polygon)
  {
    vertex[i].key = i;
    vertex[i].x = point.x;
    vertex[i].y = point.y;
    i++;
  }
  int edges =nodes;
  vector<half_edge> h(2 * edges);
  vector<vector<double>> adj(nodes);
  i=0;
  for (i = 0; i < edges-1; i++)
  {
    int ver1=i, ver2=i+1;
    adj[ver1].push_back(ver2);
    adj[ver2].push_back(ver1);
    h[2 * i].origin_v = ver1;
    h[2 * i].end_v = ver2;
    h[2 * i].origin = &vertex[ver1];
    h[2 * i].end = &vertex[ver2];
    h[2 * i + 1].origin_v = ver2;
    h[2 * i + 1].end_v = ver1;
    h[2 * i + 1].origin = &vertex[ver2];
    h[2 * i + 1].end = &vertex[ver1];
    h[2 * i].twin = &h[2 * i + 1];
    h[2 * i + 1].twin = &h[2 * i];
  }
  int ver1 = edges-1, ver2 = 0;
  adj[ver1].push_back(ver2);
  adj[ver2].push_back(ver1);
  h[2 * i].origin_v = ver1;
  h[2 * i].end_v = ver2;
  h[2 * i].origin = &vertex[ver1];
  h[2 * i].end = &vertex[ver2];
  h[2 * i + 1].origin_v = ver2;
  h[2 * i + 1].end_v = ver1;
  h[2 * i + 1].origin = &vertex[ver2];
  h[2 * i + 1].end = &vertex[ver1];
  h[2 * i].twin = &h[2 * i + 1];
  h[2 * i + 1].twin = &h[2 * i];

  vector<vertex_table> ver_tab(nodes);
  vector<half_edge_table> half_edge_table(2 * edges);
  vector<bool> unvisited_half_edge(2 * edges);
  vector<face> face(nodes);
  vector<face_table> face_table(nodes);

  fill_vertex_table(ver_tab, nodes, adj, h, vertex);
  fill_half_edge_table(half_edge_table, h, unvisited_half_edge, vertex, adj, face, face_table);
  fill_face_table_inner_components(face_table, h, half_edge_table, face,vertex);
  // print_half_edge(h , vertex , 2*edges);
  // print_vertex_table(ver_tab, nodes);
  // print_half_edge_table(half_edge_table, h);
  // print_face_table(face_table);
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
      { // This is looping for all vertex in all diagonal list.
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
    i = i + L.size() - 1;

    L.clear();
    LPVS.clear();
    flag = 1;
    LPVSflag = 1;
  }
  
  

  LLE.pop_back();
  polygons[polygons.size() - 1].pop_back();

  int dfjdhfj = 0;

  for (int k = 0; k < LLE.size(); k++)
  {                                   
    int polygon1, polygon2, a_in_2, b_in_1;
    vector<vector<double>> aleft1, aright1, aleft2, aright2;
    vector<vector<double>> merged_poly;
    for (int i = 0; i < polygons.size(); i++)
    {          // This will find a particular edge (i.e 2 vertices ) in the two polygons
      for (int j = 0; j < polygons[i].size(); j++)
      { // this will look for second vertex in a particular polygon
        if (LLE[k][0] == polygons[i][j][0] && LLE[k][1] == polygons[i][j][1])
        { // this if checks, if a vertexx in a diagonal is there in this iteration of polygon
          if (LLE[k][2] == polygons[i][(j + 1) % polygons[i].size()][0] && LLE[k][3] == polygons[i][(j + 1) % polygons[i].size()][1])
          {// this check for second vertex of the diagonal
            dfjdhfj++;
            aleft1.push_back({polygons[i][(j - 1 + polygons[i].size()) % polygons[i].size()][0],
                              polygons[i][(j - 1 + polygons[i].size()) % polygons[i].size()][1]});
            aright1.push_back({polygons[i][(j + 2) % polygons[i].size()][0],
                               polygons[i][(j + 2) % polygons[i].size()][1]});
            polygon1 = i;
            b_in_1 = (j + 1) % polygons[i].size();
          }
        }

        // We cheked for first A then B now we chek for first b then A
        if (LLE[k][2] == polygons[i][j][0] && LLE[k][3] == polygons[i][j][1])
        { // this if checks, if a vertexx in a diagonal is there in this iteration of polygon
          if (LLE[k][0] == polygons[i][(j + 1) % polygons[i].size()][0] && LLE[k][1] == polygons[i][(j + 1) % polygons[i].size()][1])
          { // this check for second vertex of the diagonal
            dfjdhfj++;
            aleft2.push_back({polygons[i][(j - 1 + polygons[i].size()) % polygons[i].size()][0],
                              polygons[i][(j - 1 + polygons[i].size()) % polygons[i].size()][1]});
            aright2.push_back({polygons[i][(j + 2) % polygons[i].size()][0],
                               polygons[i][(j + 2) % polygons[i].size()][1]});
            polygon2 = i;
            a_in_2 = (j + 1) % polygons[i].size();
          }
        }
      }
    }

    if (dfjdhfj == 2)
    {
      if (angle_check(aleft1[0][0], aleft1[0][1], LLE[k][0], LLE[k][1], aright2[0][0], aright2[0][1]) &&
          angle_check(aleft2[0][0], aleft2[0][1], LLE[k][2], LLE[k][3], aright1[0][0], aright1[0][1]))
      {

        int counter = b_in_1;
        while (polygons[polygon1][counter % (polygons[polygon1].size())][0] != LLE[k][0] && polygons[polygon1][counter % (polygons[polygon1].size())][1] != LLE[k][1])
        {
          merged_poly.push_back({polygons[polygon1][counter % (polygons[polygon1].size())][0], polygons[polygon1][counter % (polygons[polygon1].size())][1]});
          counter++;
        }

        counter = a_in_2;
        while (polygons[polygon2][counter % (polygons[polygon2].size())][0] != LLE[k][2] && polygons[polygon2][counter % (polygons[polygon2].size())][1] != LLE[k][3])
        {
          merged_poly.push_back({polygons[polygon2][counter % (polygons[polygon2].size())][0], polygons[polygon2][counter % (polygons[polygon2].size())][1]});
          counter++;
        }
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
    aleft1.clear();
    aleft2.clear();
    aright1.clear();
    aright2.clear();
    merged_poly.clear();
    dfjdhfj = 0;
  }
  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();

  // Write the time to a CSV file
  ofstream outfile("times.csv", ios_base::app);
  outfile << duration;
  outfile<<","<<endl;
  outfile.close();
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