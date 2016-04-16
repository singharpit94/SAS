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
#include "LEDA/graphics/window.h"
#include "LEDA/geo/polygon.h"


//#include "LEDA/graphics/graphwin.h"
#include "Kernel/graph/graph_draw.h"
#include <iostream>





using namespace leda;
using std::cout;
using std::endl;
list<point> L;
list<polygon> K;
  GRAPH<point,int> G;

int main()
{ 
  
  /* point p(0.0,0.0);
   L.append(p);
    point q(4.0,0.0);
   L.append(q);
    point r(0.0,4.0);
   L.append(r);
   point s(4.0,4.0);
    L.append(s);*/
    double x,y;
	int m,i=1,j;
	leda::window W;
                  W.init(-110,110,-110); 
                 W.open();
                 W.display();
                 W.set_line_width(3);
                  W.set_node_width(1);
                 j=W.button("Run",4);
                  m= W.read_mouse(x,y);
                  leda::point q(x,y);
                  leda::point s(x,y);
                 

                  if(m==MOUSE_BUTTON(1))
                  {W.draw_filled_node(q,2);
                  	  L.append(q);
                  }

                 while(1)
                 {
                    m= W.read_mouse(x,y);
                  
                  
                  leda::point r(x,y);
                  if(m==MOUSE_BUTTON(1))
                 { 
                 W.draw_filled_node(r,2);
                  W.draw_edge(q,r,2);
                  q=r;
                  
                L.append(q);
                  //cout<<"Arpit";



                 }
                  else  if(m==MOUSE_BUTTON(3))
                  {
                          W.draw_edge(s,r,2);
                  	     // W.clear();
                          
                          break;
                  }
                 
                 


              }
               W.read_mouse();
               W.clear();
               polygon p(L);
               K=CONVEX_COMPONENTS(p);
  TRIANGULATE_POINTS(L,G);
  
  
            cout << "Adjacent edges (out_edges):" << endl;
  node v;
  forall_nodes(v,G) {
    cout << "Node " << G.inf(v) << ": ";
    point z=G.inf(v);
    W.draw_filled_node(z,1);
   // cout<<z.xcoord();
    cout << "Outdegree=" << G.outdeg(v) << ". ";
    edge e;
    forall_out_edges(e,v) { // same as forall_adj_edges(e,v)
      node s = G.source(e);
      node t = G.target(e);
      point y=G.inf(t);
      cout << G[e] << "=(" << G[s] << "," << G[t] << ") ";
     W.draw_filled_node(y,1);   
     W.draw_edge(z,y,1);    


    }
    cout << endl;
     
  }
  W.read_mouse();
             W.screenshot("poly");
  
  return 0;
}	  
