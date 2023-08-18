#include <X11/Xlib.h>
#include <vector>
#define window_height 700
#define window_length 700
unsigned long long int spread= 150;
double step_factor =0.01;
#define num_iterations 1000
#define zoom 2
double max_x=2;
double max_y=2;
double x_centre=0;
double y_centre=0;
double x1,y1;
using namespace std;
int gen_num(vector<XPoint>* point,vector<int>* iter)
{
    vector<double> a;
    vector<double> b;
    XPoint p;
    int i = 0;
    for (double x = -1*max_x+x_centre; x <= max_x+x_centre; x += step_factor)
    {
        for (double y = -1*max_y+y_centre; y <= max_y+y_centre; y += step_factor)
        {
            int count = 0;
            double result_x = 0;
            double result_y = 0;
            for (int i = 0; i < num_iterations; i += 1)
            {
                double tmp = result_x;
                result_x = result_x * result_x - result_y * result_y + x;
                result_y = tmp * result_y * 2 + y;
                if ((result_x * result_x + result_y * result_y) > 4)
                {
                    break;
                }
                count++;
            }
           
                p.x = (x-x_centre)*spread+window_length/2;
                p.y = (y-y_centre)*spread+window_height/2;
                point->push_back(p);
                iter->push_back(count);
        }
    }
    //cout<<p.x<<"   "<<p.y<< endl;
    return i;
}