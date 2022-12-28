#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <iostream>


void draw_painting(Display* display, Window window, GC gc){
    unsigned long black = 0x0000000;
    unsigned long yellow = 0xFFED00;
    unsigned long brown = 0xC6AB78;
    unsigned long sky = 0x98DDE5;
    unsigned long white = 0xFDFFFF;
    unsigned long sun  = 0xF1ED87;
    unsigned long grass = 0x1EC60E;

    XSetForeground(display, gc, sky); //Sky with sun
    XFillRectangle(display, window, gc, 0, 0, 800, 600);
    XSetForeground(display, gc, sun);
    XFillArc(display, window, gc, 200, 100, 100, 100, 0, 360*64);
    XSetForeground(display, gc, grass);//Grass
    XFillRectangle(display, window, gc, 0, 450, 800, 650);
    XSetForeground(display, gc, brown);//hive
    XFillArc(display, window, gc, 350, 200, 300, 300, 0, 360*64);

    XSetForeground(display, gc, black);
    XFillArc(display, window, gc, 440, 220, 100, 100, 0, 360*64);

    XSetForeground(display, gc, yellow);//Bee bzzz
    XFillArc(display, window, gc, 400, 400, 100, 100, 0, 360*64);
    XSetForeground(display, gc, black);
    XFillArc(display, window, gc, 390, 390, 100, 100, 0, 360*64);
    XSetForeground(display, gc, yellow);
    XFillArc(display, window, gc, 380, 380, 100, 100, 0, 360*64);
    XSetForeground(display, gc, white);
    XFillArc(display, window, gc, 449, 361, 78, 42, 0, 360*64);
    XFillArc(display, window, gc, 428, 340, 65, 80, 0, 360*64);
}
int main() {
    Display *main_display;
    GC gc;
    XEvent event;

    if ((main_display = XOpenDisplay(NULL)) == NULL)
        exit(1);

    int main_screen_number = DefaultScreen(main_display);

    Window main_window = XCreateSimpleWindow(main_display, RootWindow(main_display, main_screen_number), 10, 10, 800, 600, 1, 0xFFFFFF, 0);
    XSelectInput(main_display, main_window, ExposureMask | KeyPressMask| ButtonPressMask);
    XMapWindow(main_display, main_window);

    gc = XCreateGC(main_display, DefaultRootWindow(main_display), 0, 0);
    while(true)
    {
        XNextEvent(main_display, &event);
        if (event.type == Expose) draw_painting(main_display, main_window, gc);
        if ((event.type == KeyPress) && (XLookupKeysym(&event.xkey, 0) == XK_Escape)) break;
        if ((event.type == ButtonPress) && (event.xbutton.x < 10) && (event.xbutton.y < 10)) break;
    }
    XCloseDisplay(main_display);
    return 0;
}
