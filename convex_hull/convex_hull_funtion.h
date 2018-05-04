#ifndef CONVEX_HULL_FUNTION_H
#define CONVEX_HULL_FUNTION_H
#include <math.h>
#include <QGraphicsView>
#include <iostream>
#include <stack>
#include <stdlib.h>
#include <QPainter>
#include <QPoint>

using namespace std;
QPoint p0;

QPoint second_top(stack<QPoint> &S)
{
    QPoint p = S.top();
    S.pop();
    QPoint res = S.top();
    S.push(p);
    return res;
}
int dist(QPoint p1, QPoint p2)
{
    return pow(p1.x() - p2.x(),2) + pow(p1.y() - p2.y(),2) ;
}
float orientation(QPoint p, QPoint q, QPoint r)
{
      return (q.y() - p.y()) * (r.x() - q.x()) - (q.x() - p.x()) * (r.y() - q.y());
}
int compare(const void *vp1, const void *vp2)
{
    QPoint *p1 = (QPoint *) vp1;
    QPoint *p2 = (QPoint *) vp2;
    int orie = orientation(p0, *p1, *p2);
    if (orie == 0)
        return (dist(p0, *p2) >= dist(p0, *p1)) ? -1 : 1;
    return (orie < 0) ? -1 : 1;
}
void convexHull(QPoint points[], int n, QGraphicsScene* scene)
{
    for(int w=0; w<n; w++)
       scene->addEllipse( points[w].x(),points[w].y(),10,10 );
    scene->update();

    int y_menor = points[0].y();
    int min_position = 0;
    int y;
    for (int i = 1; i < n; i++)
    {

        while(points[i].y() > y_menor)
            i++;
        y = points[i].y();
        if ((y < y_menor) || (y_menor == y && points[i].x() < points[min_position].x() ))
            y_menor = points[i].y(), min_position = i;
    }
    swap(points[0], points[min_position]);
    p0 = points[0];
    qsort(&points[1], n - 1, sizeof(QPoint), compare);
    stack<QPoint> S;
    S.push(points[0]);
    S.push(points[1]);
    S.push(points[2]);
    if (n<3) return;
    for (int i = 3; i < n; i++)
    {
        while (orientation(second_top (S), S.top(), points[i]) > 0)
            S.pop();
        S.push(points[i]);
    }
    int size=S.size()-1;
    int w=0;
    QPoint p_inicial = S.top();
    QPoint p = S.top();
    while (w<size)
    {
        p = S.top();
        cout << "(" << p.x() << ", " << p.y() << ")" << endl;
        S.pop();
        scene->addLine(p.x(),p.y(),S.top().x(),S.top().y());
        w++;
    }
    scene->addLine(p.x(),p.y(),S.top().x(),S.top().y());
    scene->addLine(S.top().x(),S.top().y(),p_inicial.x(),p_inicial.y());
}

#endif // CONVEX_HULL_FUNTION_H
