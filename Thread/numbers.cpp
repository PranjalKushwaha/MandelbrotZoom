#include <vector>
#include <math.h>
#include <queue>
#include <iostream>
#include<thread>
#define height 600
#define width 600
#define num_threads 7
#define num_iterations 500
using namespace std;
bool displaying  = true;
double zoom = 1.0009;
double max_x = 2;
double max_y = 2;
double x_centre = 0.37209928062771297;
double y_centre = -0.2720334349969608;
double tot_zoom = pow(zoom,num_threads+1);
double max_xi[num_threads];
double max_yi[num_threads];
double zoom_i[num_threads];
void fill_max()
{
    for(int i = 0;i<num_threads;i++)
    {
        zoom_i[i] = pow(zoom,i);
        max_xi[i] = max_x/zoom_i[i];
        max_yi[i] = max_y/zoom_i[i];
        //cout << max_xi[i]<< endl;
    }
}


vector<queue<vector<int*>*>*> frame_queue;


void gen_num(int index)
{
    vector<int*>* iter = new vector<int*>;
    double mx = max_xi[index];
    double my = max_yi[index];
    double step_factor_x = (mx / width) * 2;
    double step_factor_y = (my / height) * 2;
    int count_x = 0;
    int count_y = 0;
    for (double x = -1 * mx + x_centre; x <= mx + x_centre; x += step_factor_x)
    {
        if (count_x == width)
            break;
        count_x++;
        for (double y = -1 *my+ y_centre; y <=my + y_centre; y += step_factor_y)
        {

            if (count_y == height)
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
            int* t = new int();
            *t = count;
            iter->push_back(t);
        }
        count_y = 0;
    }
    if(iter->size()<height*width)
    {
    //cout << "mx : "<<mx << " my : "<<my<<" zoom : "<<zoom_i[index]<< " Step : "<< step_factor_x <<" Size : "<<iter->size()<< endl;
    }
        frame_queue[index]->push(iter);
    max_xi[index] = max_xi[index]/zoom_i[index];
     max_yi[index] = max_yi[index]/zoom_i[index];
     zoom_i[index]*=tot_zoom;
    
    int sum = 0;
    
    for(int i = 0;i<num_threads;i++)
    sum +=frame_queue[i]->size();
    //std::cout<< sum<< endl;
}

void loop(int index)
{
    for(;;)
    {
        gen_num(index);
    }
}


// int main()
// {
//     fill_max();
//     queue<vector<int*>*>* q1 = new queue<vector<int*>*>;
//     frame_queue.push_back(q1);
//     thread t1(loop,0);
    
//         queue<vector<int*>*>* q2 = new queue<vector<int*>*>;
//     frame_queue.push_back(q2);
//     thread t2(loop,1);

//         queue<vector<int*>*>* q3 = new queue<vector<int*>*>;
//     frame_queue.push_back(q3);
//     thread t3(loop,2);

//         queue<vector<int*>*>* q4 = new queue<vector<int*>*>;
//     frame_queue.push_back(q4);
//     thread t4(loop,3);

//         queue<vector<int*>*>* q5 = new queue<vector<int*>*>;
//     frame_queue.push_back(q5);
//     thread t5(loop,4);

//         queue<vector<int*>*>* q6 = new queue<vector<int*>*>;
//     frame_queue.push_back(q6);
//     thread t6(loop,5);

//      queue<vector<int*>*>* q7 = new queue<vector<int*>*>;
//     frame_queue.push_back(q7);
//     thread t7(loop,6);

//      queue<vector<int*>*>* q8 = new queue<vector<int*>*>;
//     frame_queue.push_back(q8);
//     thread t8(loop,7);

//     int x;
//     cin >> x;
// }