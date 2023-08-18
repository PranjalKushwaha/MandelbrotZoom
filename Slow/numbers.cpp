#include <vector>
#include <math.h>
#define height 600
#define width 600

#define num_iterations 500

double max_x = 2;
double max_y = 2;
double x_centre = -0.761574;
double y_centre = -0.0847596;

using namespace std;
void gen_num(vector<double> *xcor, vector<double> *ycor, vector<int> *iter)
{
    double step_factor_x = (max_x / width) * 2;
    double step_factor_y = (max_y / height) *2;
    int count_x = 0;
    int count_y = 0;
    for (double x = -1 * max_x + x_centre; x <= max_x + x_centre; x += step_factor_x)
    {
        if(count_x==width)
        break;
        count_x++;
        for (double y = -1 * max_y + y_centre; y <= max_y + y_centre; y += step_factor_y)
        {

        if(count_y==width)
        break;
        count_y++;
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
            iter->push_back(count);
        }
        count_y=0;
    }
}