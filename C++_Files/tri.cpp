#include "LEDA/core/list.h"
#include "LEDA/geo/rat_point.h"
#include "LEDA/geo/point.h"
#include "LEDA/geo/random_rat_point.h"
#include <LEDA/graph/graph.h>
#include <LEDA/graph/node_array.h>
#include "LEDA/geo/geo_alg.h"
#include "LEDA/geo/d3_rat_point.h"
#include "LEDA/geo/d3_delaunay.h"
#include "LEDA/graphics/window.h"
#include "LEDA/geo/d3_triangle.h"
#include "LEDA/geo/geo_alg.h"

//#include "LEDA/graphics/graphwin.h"
#include "Kernel/graph/graph_draw.h"
#include <iostream>





using namespace leda;
using std::cout;
using std::endl;
list<point> L;
  GRAPH<point,int> G;

int main()
{ 
  
   point p(0.0,0.0);
   L.append(p);
    point q(4.0,0.0);
   L.append(q);
    point r(0.0,4.0);
   L.append(r);
   point s(4.0,4.0);
    L.append(s);
  TRIANGULATE_POINTS(L,G);
  
  
            cout << "Adjacent edges (out_edges):" << endl;
  node v;
  forall_nodes(v,G) {
    cout << "Node " << G.inf(v) << ": ";
    point z=G.inf(v);
    cout<<z.xcoord();
    cout << "Outdegree=" << G.outdeg(v) << ". ";
    edge e;
    forall_out_edges(e,v) { // same as forall_adj_edges(e,v)
      node s = G.source(e);
      node t = G.target(e);
      cout << G[e] << "=(" << G[s] << "," << G[t] << ") ";
    }
    cout << endl;
  }
  
  return 0;
}	  
