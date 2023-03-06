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

////////////////////////////////////////////////////////////////////////////////
struct HalfEdge;

struct Vertex {
    double x, y;
    HalfEdge *incident_edge;
};
struct Face;
struct HalfEdge {
    Vertex *origin;
    HalfEdge *twin;
    HalfEdge *next;
    Face *incident_face;
};

struct Face {
    HalfEdge *outer_component;
};

struct DCEL
{
    vector<Vertex> vertices;
    vector<HalfEdge> half_edges;
    vector<Face> faces;
};
DCEL convertPolygonsToDCEL(const vector<vector<vector<double>>> &polygons)
{
    DCEL dcel;
    vector<HalfEdge *> half_edges;
    int vertex_count = 0;

    // Create vertices
    for (const auto &polygon : polygons)
    {
        for (const auto &vertex : polygon)
        {
            Vertex v = {vertex[0], vertex[1], nullptr};
            dcel.vertices.push_back(v);
        }
        vertex_count += polygon.size();
    }

    // Create half-edges
    for (int i = 0; i < vertex_count; i++)
    {
        HalfEdge *e1 = new HalfEdge;
        HalfEdge *e2 = new HalfEdge;
        e1->origin = &dcel.vertices[i];
        e2->origin = &dcel.vertices[(i + 1) % vertex_count];
        e1->twin = e2;
        e2->twin = e1;
        e1->next = e2;
        dcel.half_edges.push_back(*e1);
        dcel.half_edges.push_back(*e2);
        half_edges.push_back(e1);
    }

    // Link half-edges to vertices and faces
    int offset = 0;
    for (const auto &polygon : polygons)
    {
        for (int i = 0; i < polygon.size(); i++)
        {
            Vertex *v = &dcel.vertices[offset + i];
            HalfEdge *e = half_edges[offset + i];
            v->incident_edge = e;
            e->incident_face = new Face;
            e->incident_face->outer_component = e;
        }
        for (int i = 0; i < polygon.size(); i++)
        {
            HalfEdge *e = half_edges[offset + i];
            e->next = half_edges[offset + (i + 1) % polygon.size()];
            e->twin->incident_face = e->incident_face;
        }
        offset += polygon.size();
    }
    return dcel;
}



void printDCEL(const DCEL& dcel) {
    // Print vertices
    std::cout << "Vertices:\n";
    for (const auto& v : dcel.vertices) {
        std::cout << "(" << v.x << ", " << v.y << ")\n";
    }

    // Print half-edges
    std::cout << "Half-edges:\n";
    for (const auto& e : dcel.half_edges) {
        std::cout << "Origin: (" << e.origin->x << ", " << e.origin->y << "), ";
        std::cout << "Twin: (" << e.twin->origin->x << ", " << e.twin->origin->y << "), ";
        std::cout << "Next: (" << e.next->origin->x << ", " << e.next->origin->y << "), ";
        std::cout << "Face: " << e.incident_face << "\n";
    }

    // Print faces
    std::cout << "Faces:\n";
    for (const auto& f : dcel.faces) {
        std::cout << "Outer component: (" << f.outer_component->origin->x << ", " << f.outer_component->origin->y << ")\n";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    std::vector<Point> polygon = generatePolygon(19, 15.0, 20.0);

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
    //     {8.54, 4.44},  // 11
    //     {11.4, 5.86},  // 12
    //     {13.64, 5.46}, // 13
    //     {14.3, 3.72},  // 14
    //     {13.6, 2.86},  // 15
    //     {11.8, 2.86},  // 16
    //     {9.48, 3.86},  // 17
    //     {6, 2}};
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
            polygons.push_back(L);
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
            polygons.push_back(L);
        }

        for (auto i : L)
        {
            fw << i[0] << "," << i[1] << endl;
        }
        fw << "end" << endl;
        cout << "end" << endl;
        i = i + L.size() - 1;

        L.clear();
        LPVS.clear();
        flag = 1;
        LPVSflag = 1;
    }

    LLE.pop_back();
    //  DCEL dcel;
    printDCEL(convertPolygonsToDCEL(polygons));
    // We have correct LLE at this point
    for (auto i : LLE)
    {

        cout << "{" << i[0] << "," << i[1] << "}"
             << ","
             << "{" << i[2] << "," << i[3] << "}" << endl;
        // std::cout << j[0] << "," << j[1] << std::endl;

        // cout << "end" << endl;
    }
    return 0;
}