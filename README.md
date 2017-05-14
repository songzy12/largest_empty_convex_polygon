## Largest Empty Convex Polygon

This is a course project for Computational geometry of Tsinghua University, where we try to implement the method of reporting empty convex polygons from paper [1].

## C++ Style Guide

[Google Style Guide](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/contents/)

## Polar Sort

* Reference/12-duality.pdf P31
    * 对于点 p, 在其右侧的点的极角排序 等价于 对偶图中 对于直线 p, 在其下方（斜率大于 p）的直线与 p 的交点左右顺序排序
    * 于是变换到对偶图中，只需要在 O(n) 的时间内从左向右求出 p 下方直线与直线 p 的各交点
* Reference/ln11.pdf Subsection 11.2
    * 对于直线 p, 首先使用 O(n) 求出其所在的最左侧 face（根据指向无穷远点的 halfedge 的斜率）
    * 此时 p 与该 face 的 左侧交点即为无穷远点 u
    * 然后遍历这个 face 的所有 halfedge, 找到与 p 相交的 halfedge e 及右侧交点 v
    * 使用 u 和 v 分割该 face （维护点列表，边列表，面列表）
    * 使用 e->twin->face 找到下一个要处理的面，此时 v 为 p 与 右侧面 的左交点

## DCEL

Reference/DCEL.pdf Subsection 5.2

维护边列表，点列表，面列表

### v

* halfedge(v)
* point(v)

### f

* halfedge(f)

### h

* target(h)
* face(h)
* twin(h)
* next(h)
* prev(h)

## API

* AddVertex
* ConnectVertices 

## References

[1] Dobkin, D. P., Edelsbrunner, H., & Overmars, M. H. (1990). Searching for empty convex polygons. Algorithmica, 5(1-4), 561-571.