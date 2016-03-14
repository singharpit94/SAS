#include "LEDA/geo/point.h"
#include "LEDA/graphics/window.h"
#include "LEDA/core/list.h"
#include <cstdint>
#include <list>
#include <vector>
#include <algorithm>
#include<iostream>

using namespace std;
int main()
{   double x,y;
	int m,i=1;;
	leda::window W;
                  W.init(-110,110,-110); 
                 W.open();
                 W.display();
                 W.set_line_width(3);
                  m= W.read_mouse(x,y);
                  leda::point q(x,y);
                  leda::point s(x,y);
                  if(m==MOUSE_BUTTON(1))
                  W.draw_filled_node(q,2);

                 while(1)
                 {
                 m= W.read_mouse(x,y);
                  
                  
                  leda::point r(x,y);
                  if(m==MOUSE_BUTTON(1))
                 { W.draw_filled_node(r,2);
                  W.draw_edge(q,r,2);
                  q=r;}
                  else  if(m==MOUSE_BUTTON(3))
                  {
                          W.draw_edge(s,r,2);
                  }
                 
                 


              }
                  return  0;

}