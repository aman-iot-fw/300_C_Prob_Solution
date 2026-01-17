#include <stdio.h>
#include <math.h>


struct point3D
{
    double x;
    double y;
    double z;
};

double distanceBetweenPoints(const struct point3D *p1, const struct point3D *p2){
    //To calculate distance use formula -  sqrt(((x2-x1)*(x2-x1)) + ((y2-y1)*(y2-y1)) + ((z2-z1)*(z2-z1)))
    double dx = (p2->x - p1->x);
    double dy = (p2->y - p1->y);
    double dz = (p2->z - p1->z);
    
    double distance = sqrt((dx*dx) + (dy*dy) + (dz*dz));
    return distance;
}


int main(void){
    struct point3D p1 = {2, 4, 6}; 
    struct point3D p2 = {1, 3, 5}; 

    double distance  = distanceBetweenPoints(&p1, &p2);
    printf("Distance between point : %.3f\n", distance);


    return 0;
}
