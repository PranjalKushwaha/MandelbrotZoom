#include <iostream>
#include <vector>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include "./numbers.cpp"
#include <chrono>
using namespace std;

Display *dis;
int screen;
Window win;
GC gc;
unsigned long red,yellow,green,purple,blue;
unsigned long RGB(int r, int g, int b) {
    return b + (g<<8) + (r<<16);
}
void init_x()
{
    /* get the colors black and white  */
    unsigned long black, white;

    /* use the information from the environment variable DISPLAY
       to create the X connection:
    */
    dis = XOpenDisplay((char *)0);
    screen = DefaultScreen(dis);
    black = BlackPixel(dis, screen),     /* get color black */
        white = WhitePixel(dis, screen); /* get color white */
        cout<<white<<"  111111"<<black<< endl;
        red = RGB(255,0,0);
        yellow = RGB(255,255,0);
        green = RGB(0,255,0);
        blue= RGB(0,0,255);
        purple = RGB(25,0,51);
        
    /* once the display is initialized, create the window.
       This window will be have be 200 pixels across and 300 down.
       It will have the foreground white and background black
    */
    win = XCreateSimpleWindow(dis, DefaultRootWindow(dis), 0, 0,

                              window_length, window_height, 5, black, white);

    /* here is where some properties of the window can be set.
       The third and fourth items indicate the name which appears
       at the top of the window and the name of the minimized window
       respectively.
    */
    XSetStandardProperties(dis, win, "Mandelbrot", "", None, NULL, 0, NULL);

    /* this routine determines which types of input are allowed in
       the input.  see the appropriate section for details...
    */
    XSelectInput(dis, win, ExposureMask | ButtonPressMask | KeyPressMask | NoEventMask);

    /* create the Graphics Context */
    gc = XCreateGC(dis, win, 0, 0);

    /* here is another routine to set the foreground and background
       colors _currently_ in use in the window.
    */
    XSetBackground(dis, gc, white);
    XSetForeground(dis, gc, black);
    /* clear the window and bring it on top of the other windows */
    XClearWindow(dis, win);
    XMapRaised(dis, win);
};
void close()
{
}

int main()
{
    using std::chrono::duration;
    using std::chrono::high_resolution_clock;
    using std::chrono::seconds;
    init_x();
    vector<XPoint> p;
    vector<int> count;
    auto t1 = high_resolution_clock::now();
    // gen_num(&redcol,&yellowcol,&purplecol,&bluecol,&greencol);
    auto t2 = high_resolution_clock::now();
    duration<double> ms_double = t2 - t1;
    // cout << ms_double.count() << endl;
    // XPoint *point ;
    XEvent event;
    XWindowAttributes window_attributes_return;
    
    XGetWindowAttributes(dis, win, &window_attributes_return);
    int depth = window_attributes_return.depth;
    //Pixmap pix = XCreatePixmap(dis,win,window_length,window_height,depth);

    while (1)
    {
        // XDrawRectangle(dis,win,gc,window_length/2,window_height/2,10,10);
        XNextEvent(dis, &event);
        XClearWindow(dis, win);
        //XDrawPoints(dis, win, gc, point, purplecol.size(), CoordModeOrigin);
        
        
        if (event.type == ButtonPress)
        {
            XSetForeground(dis, gc, yellow);
            
            step_factor /= zoom;
            spread *= zoom;
            max_x /= zoom;
            max_y /= zoom;
            //cout << max_x << "  " << max_y << "  " << spread << "  " << step_factor << endl;
            p.clear();
            count.clear();

            x1 = event.xbutton.x,
            y1 = event.xbutton.y;
            x_centre += (x1 - window_length / 2) / spread;
            y_centre += (y1 - window_height / 2) / spread;
            t1 = high_resolution_clock::now();
            gen_num(&p,&count);
            t2 = high_resolution_clock::now();
             ms_double = t2 - t1;
            
            XClearWindow(dis, win);
            t1 = high_resolution_clock::now();
            XSetForeground(dis, gc, purple);
            
            for(int i = 0;i<p.size();i++)
            {
                XSetForeground(dis, gc, RGB(count[i]%255,(count[i]-400)%255,(count[i]-800)%255));
                XFillRectangle(dis,win,gc,p[i].x,p[i].y,3,3);                
            }
            t2 = high_resolution_clock::now();
             ms_double = t2 - t1;
        }
    };
}