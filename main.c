#include <stdio.h>
#include <math.h>


typedef struct Points {
    float x;
    float y;
} Points;
typedef struct Centers {
    float x_c;
    float y_c;
} Centers, Init_center, split_center;

typedef struct tmpCenters {
    float x_c;
    float y_c;
    int num;
} tmpCenters, tmpCenters1 ;

typedef struct Split_vect{
    float x;
    float y;
}Split_vect;

void K_mean(Points *Points, Centers *Centers, tmpCenters *tmpCenters) {
    for (int iteration = 0; iteration < 100; iteration++) {
        for (int pos = 0; pos < sizeof(tmpCenters)-1 ; pos++) {
            tmpCenters[pos].x_c = 0.0;
            tmpCenters[pos].y_c = 0.0;
            tmpCenters[pos].num = 0;
        }
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
            if (iteration == 0 || iteration == 99)
                printf("At iteration %d new center %d is locater at x:%1.2f, y:%1.2f\n", iteration+1, l + 1, Centers[l].x_c, Centers[l].y_c);
        }

    }

}

void NUS_alg(Points *Points, Split_vect *split_vect) {
    tmpCenters tmpCenters1[2];
    Init_center Init_center = {0.0, 0.0};
    for (int i = 0; i < sizeof(Points) - 1; ++i) {
        Init_center.x_c += Points[i].x;
        Init_center.y_c += Points[i].y;
    }
    Init_center.x_c /= sizeof(Points);
    Init_center.y_c /= sizeof(Points);
    split_center split_center[2] = {{0.0, 0.0},
                               {0.0, 0.0}};
    for (int iteration = 0; iteration < sizeof(split_vect) - 1; iteration++) {

        float distance_1, distance_2 = 0;

        for (int pos = 0; pos < sizeof(tmpCenters1) - 1; pos++) {
            tmpCenters1[pos].x_c = 0.0;
            tmpCenters1[pos].y_c = 0.0;
            tmpCenters1[pos].num = 0;
        }

        split_center[0].x_c = Init_center.x_c + split_vect[iteration].x;
        split_center[0].y_c = Init_center.y_c + split_vect[iteration].y;

        split_center[1].x_c = Init_center.x_c - split_vect[iteration].x;
        split_center[1].y_c = Init_center.y_c - split_vect[iteration].y;
        for (int j = 0; j < sizeof(Points) - 1; ++j) {
            float distance = 0;
            float min_d = 100;
            int ID_center = 0;
            for (int i = 0; i < sizeof(split_center) - 1; ++i) {
                distance = sqrt(((Points[j].x - split_center[i].x_c) * (Points[j].x - split_center[i].x_c) +
                                 (Points[j].y - split_center[i].y_c) * (Points[j].y - split_center[i].y_c)));
                //printf("Distnace %f\n", distance);
                if (distance < min_d) {
                    ID_center = i;
                    min_d = distance;
                }
                if (ID_center == 0) distance_1 += min_d;
                else distance_2 += min_d;

                tmpCenters1[ID_center].x_c += Points[j].x;
                tmpCenters1[ID_center].y_c += Points[j].y;
                tmpCenters1[ID_center].num++;
            }
        }
        for (int k = 0; k < 2; ++k) {
            tmpCenters1[k].x_c = tmpCenters1[k].x_c / tmpCenters1[k].num;
            tmpCenters1[k].y_c = tmpCenters1[k].y_c / tmpCenters1[k].num;
        }
        if (distance_1 < distance_2) {
            Init_center.x_c = tmpCenters1[0].x_c;
            Init_center.y_c = tmpCenters1[0].y_c;
        } else {
            Init_center.x_c = tmpCenters1[1].x_c;
            Init_center.y_c = tmpCenters1[1].y_c;
        }
    }
}


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
    tmpCenters tmpCenters[3];
    Split_vect split_vect[2] = {{0.1, 0.1},
                                {0.02, 0.1}};
    K_mean(Points, Centers, tmpCenters);
    NUS_alg(Points, split_vect);
}


