#ifndef DCEL_EdgeIterator_h
#define DCEL_EdgeIterator_h

#include "Vertex.h"
#include "Face.h"
#include "half_edge.h"
/**
A class that helps the iteration of the edges of a vertex or face.

In the case of a vertex, it runs over each edge that has the given
edge as origin.

In the case of a face, it runs over each edge that forms the boundary
of that face.
*/

/*
边的迭代器：
沿着面上的边遍历，碰到vertex时翻墙
*/

class EdgeIterator
{
public:

	/**
	Creates an EdgeIterator that runs over each edge that starts on the
	given vertex.
	*/
	inline EdgeIterator(Vertex* vertex)
	{
		reset(vertex);
	};

	/**
	Creates an EdgeIterator that runs over each edge that forms the
	boundary of the given face.
	*/
	inline EdgeIterator(Face* face)
	{
		reset(face);
	};

	/**
	Returns the next edge in the sequence.

	Returns NULL if all the sequence of edges has ended.
	*/
	inline HalfEdge* getNext() //关键
	{
		HalfEdge* next = nextEdge;

		if (nextEdge)
		{
			if (vertexIterator) // edges starting at a vertex iterator
			{
				HalfEdge* twin = nextEdge->twin();//翻墙
				nextEdge = twin->next();
			}
			else // edges from face iterator
			{
				nextEdge = nextEdge->next();
			}
		}

		if (nextEdge == startEdge)
		{
			nextEdge = NULL;
		}

		return next;
	};

	/**
	Check if there is any edge in the sequence of edges.
	*/
	inline bool hasNext() const
	{
		return nextEdge != NULL;
	};

	/**
	Makes the iterator start again, from the first edge
	of the sequence.
	*/
	inline void reset()
	{
		nextEdge = startEdge;
	};

	inline void reset(Vertex* vertex)
	{
		vertexIterator = true;
		startEdge = vertex->half_edge();
		reset();
	};

	inline void reset(Face* face)
	{
		vertexIterator = false;
		startEdge = face->half_edge();
		reset();
	};

protected:
private:
	HalfEdge* startEdge;
	HalfEdge* nextEdge;
	bool vertexIterator;
};

#endif//DCEL_EdgeIterator_h