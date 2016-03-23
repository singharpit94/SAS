

#include "LEDA/geo/point.h"
#include "LEDA/graphics/window.h"
#include "LEDA/core/list.h"
#include <cstdint>
#include <list>
#include <vector>
#include <algorithm>
#include<iostream>

using namespace std;
// This code uses C++11 features like "auto" and initializer lists.

// Compare two floating point numbers accurately.
bool compf(float a, float b, float threshold=0.00001f)
{
    return (a + threshold > b && a - threshold < b);
}

// A point in space. 
struct vector_t 
{
    float x, y;
    inline bool operator==(const vector_t& B)
    { return compf(B.x, x) && compf(B.y, y); }
};

// Determine orientation of a triangle.
// TRUE if ccw, FALSE if cw or not a triangle.
bool orientation(const std::vector<vector_t>& p)
{
    return (p[1].x - p[0].x) * (p[2].y - p[0].y) - 
           (p[2].x - p[0].x) * (p[1].y - p[0].y) > 0;
}

// Barycentric coordinate calculation.
bool in_triangle(const vector_t& V, const vector_t& A,
                 const vector_t& B, const vector_t& C)
{
    float denom = ((B.y - C.y) * (A.x - C.x) + (C.x - B.x) * (A.y - C.y));
    if(compf(denom, 0.0)) return true;
    denom = 1 / denom;
    
    float alpha = denom * ((B.y - C.y) * (V.x - C.x) + (C.x - B.x) * (V.y - C.y));
    if(alpha < 0) return false;
 
    float beta  = denom * ((C.y - A.y) * (V.x - C.x) + (A.x - C.x) * (V.y - C.y));
    if(beta < 0) return false;
    
    return alpha + beta >= 1;
}

std::vector<vector_t> triangulate(std::vector<vector_t> Polygon)
{
    std::vector<uint16_t> reflex;
    std::vector<vector_t> triangles;    
    
    if(Polygon.size() < 3) return Polygon;
    
    // Polygon orientation
    vector_t left = Polygon[0];
    size_t index = 0;
    
    for(size_t i = 0; i < Polygon.size(); ++i)
    {
        if(Polygon[i].x < left.x ||
          (compf(Polygon[i].x, left.x) && Polygon[i].y < left.y))
        {
            index = i;
            left = Polygon[i];
        }
    }
    
    // C++11 initializer list (not on <= MSVC11)
    std::vector<vector_t> tri {
        Polygon[(index > 0) ? index - 1 : Polygon.size() - 1],
        Polygon[index],
        Polygon[(index < Polygon.size()) ? index + 1 : 0]
    };
    bool ccw = orientation(tri);
    
    // We know there will be vertex_count - 2 triangles made.
    triangles.reserve(Polygon.size() - 2);

    if(Polygon.size() == 3) return Polygon;
    while(Polygon.size() >= 3)
    {
        reflex.clear();
        int16_t eartip = -1, index = -1;
        for(auto& i : Polygon)
        {
            ++index;
            if(eartip >= 0) break;
            
            uint16_t p = (index > 0) ? index - 1 : Polygon.size() - 1;
            uint16_t n = (index < Polygon.size()) ? index + 1 : 0;
            
            std::vector<vector_t> tri { Polygon[p], i, Polygon[n] };
            if(orientation(tri) != ccw)
            {
                reflex.emplace_back(index);
                continue;
            }
            
            bool ear = true;
            for(auto& j : reflex)
            {
                if(j == p || j == n) continue;
                if(in_triangle(Polygon[j], Polygon[p], i, Polygon[n]))
                {
                    ear = false;
                    break;
                }
            }
            
            if(ear)
            {
                auto j = Polygon.begin() + index + 1,
                     k = Polygon.end();
                 
                for( ; j != k; ++j)
                {
                    auto& v = *j;

                    if(&v == &Polygon[p] ||
                       &v == &Polygon[n] ||
                       &v == &Polygon[index]) continue;

                    if(in_triangle(v, Polygon[p], i, Polygon[n]))
                    {
                        ear = false;
                        break;
                    }
                }
            }
            
            if(ear) eartip = index;
        }
        
        if(eartip < 0) break;
        
        uint16_t p = (eartip > 0) ? eartip - 1 : Polygon.size() - 1;
        uint16_t n = (eartip < Polygon.size()) ? eartip + 1 : 0;
        vector_t* parts[3] = { 
            &Polygon[p], &Polygon[eartip], &Polygon[n]
        };
        
        // Create the triangulated piece.
        for(const auto& i : parts) triangles.push_back(*i);
        
        // Clip the ear from the polygon.
        Polygon.erase(std::find(Polygon.begin(), Polygon.end(), *parts[1]));
    }
    
    return triangles;
}
int main()
{
	 vector<vector_t> Polygon,tri;
	 vector_t a;
               

               
                  
	/* a.x=0.0;
	 a.y=0.0;
	 Polygon.push_back(a);
	 a.x=60.0;
	 a.y=0.0;
	 Polygon.push_back(a); 
	 a.x=60.0;
	 a.y=60.0;
	 Polygon.push_back(a); 
	  a.x=0.0;
	 a.y=60.0;
	 Polygon.push_back(a); 
	 tri=triangulate(Polygon);
                 
                W.read_mouse();
	 leda::point p(tri[0].x,tri[0].y);
                leda::point q(tri[1].x,tri[1].y);
                leda::point r(tri[2].x,tri[2].y);
                leda::point s(tri[3].x,tri[3].y);
                leda::point t(tri[4].x,tri[4].y);
                leda::point u(tri[5].x,tri[5].y);
                W.draw_filled_node(p,2);
                W.draw_filled_node(q,2);
                W.draw_filled_node(r,2);
                W.draw_filled_node(s,2);
                W.draw_filled_node(t,2);
                W.draw_filled_node(u,2);
                W.draw_edge(p,q,2);
                W.read_mouse();
                 W.draw_edge(q,r,2);

                W.read_mouse();
                 W.draw_edge(r,p,2);


                W.read_mouse();
                 W.draw_edge(p,s,2);
                W.read_mouse();
                  W.draw_edge(s,r,2);
                  W.read_mouse();
                   W.draw_edge(p,r,2);
                 W.read_mouse();
                W.screenshot("poly");*/

                  double x,y;
	int m,i=1,j;
	leda::window W;
                  W.init(-110,110,-110); 
                 W.open();
                 W.display();
                 W.set_line_width(3);
                 j=W.button("Run",4);
                  m= W.read_mouse(x,y);
                  leda::point q(x,y);
                  leda::point s(x,y);
                  a.x=x;
	              a.y=y;

                  if(m==MOUSE_BUTTON(1))
                  {W.draw_filled_node(q,2);
                  	Polygon.push_back(a);
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
                  a.x=x;
                  a.y=y;
                  Polygon.push_back(a);
                  cout<<"Arpit";



                 }
                  else  if(m==MOUSE_BUTTON(3))
                  {
                          W.draw_edge(s,r,2);
                  	     // W.clear();
                          
                          break;
                  }
                 
                 


              }
                /*for(i=0;i<1000000000;i++)
                {

                }*/
               //
              m=W.read_mouse();
              {

              W.clear();
              tri=triangulate(Polygon);
              int size=tri.size();
              for(i=0;i<size;i=i+3)
              {
              	leda::point p(tri[i].x,tri[i].y);
                leda::point q(tri[i+1].x,tri[i+1].y);
                leda::point r(tri[i+2].x,tri[i+2].y);
                // W.read_mouse();
                  W.draw_filled_node(p,2);
                 // W.read_mouse();

                   W.draw_filled_node(q,2);
                  // W.read_mouse();
                   W.draw_filled_node(r,2);
                   // W.read_mouse();
                    W.draw_edge(p,q,2);
                   // W.read_mouse();
                     W.draw_edge(p,r,2);
                    //  W.read_mouse();
                     W.draw_edge(q,r,2);
                  
                  

                  




              }
              }
             W.read_mouse();
             W.screenshot("poly");

	return  0;

}
