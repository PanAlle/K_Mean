#include <stdio.h>
#include <math.h>


typedef struct Points{
    float x;
    float y;
}Points;
typedef struct Centers{
    float x_c;
    float y_c;
}Centers;

typedef struct tmpCenters{
    float x_c;
    float y_c;
    int num;
}tmpCenters;


int main() {
    Points Points[10] = {{2.0,  2.5},
                         {7.0,  0.5},
                         {12.0, 1.0},
                         {4.0,  -0.5},
                         {10.0, 2.0},
                         {3.0,  2.0},
                         {7.0,  0.0},
                         {9.0,  1.5},
                         {4.0,  2.5},
                         {10.0, 1.0}};
    Centers Centers[3] = {{2.0,  2.5},
                          {4.0,  -0.5},
                          {10.0, 2.0}};

    for (int iteration = 0; iteration < 100; iteration++) {
    tmpCenters tmpCenters[3] = {{0.0, 0.0, 0},
                                {0.0, 0.0, 0},
                                {0.0, 0.0, 0}};

        for (int j = 0; j < 10; ++j) {
            float distance = 0;
            float min_d = 100;
            int ID_center = 0;

            for (int i = 0; i < 3; ++i) {
                distance = sqrt(((Points[j].x - Centers[i].x_c) * (Points[j].x - Centers[i].x_c) +
                                (Points[j].y - Centers[i].y_c) * (Points[j].y - Centers[i].y_c)));
                //printf("Distnace %f\n", distance);
                if (distance < min_d) {
                    min_d = distance;
                    ID_center = i;
                }
            }
            tmpCenters[ID_center].x_c += Points[j].x;
            tmpCenters[ID_center].y_c += Points[j].y;
            tmpCenters[ID_center].num++;
            //printf("Point %d is closer to center %d\n", j + 1, ID_center + 1);
            //printf("num val %d for center %d\n", tmpCenters[ID_center].num, ID_center+1);
        }
        for (int k = 0; k < 3; ++k) {
            tmpCenters[k].x_c = tmpCenters[k].x_c / tmpCenters[k].num;
            tmpCenters[k].y_c = tmpCenters[k].y_c / tmpCenters[k].num;
        }
        for (int l = 0; l < 3; ++l) {
            Centers[l].x_c = tmpCenters[l].x_c;
            Centers[l].y_c = tmpCenters[l].y_c;
            if (iteration == 0 || iteration == 99) printf("New center %d is locater at x:%1.15f, %1.15f\n", l + 1, Centers[l].x_c, Centers[l].y_c);
        }

    }
}


