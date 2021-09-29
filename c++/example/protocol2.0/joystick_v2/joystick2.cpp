#include <fcntl.h> //fuction open
#include <stdio.h>
#include <unistd.h>
#include <linux/joystick.h>


int main(int argc, char *argv[])
{
    const char *device;
    int js;

    int joystick1_x = 0;
    int joystick1_y = 0; 
    int joystick2_x = 0;
    int joystick2_y = 0;

    device = "/dev/input/js0";
    js = open("/dev/input/js0", O_RDONLY);
    printf("JS:%d", int(js));
    if (js == -1)
        printf("Could not find the controller");

    struct js_event *event;


    while (true)
    {
        ssize_t bytes;
        printf("JS:%d", int(js));
        bytes = read(js, event, sizeof(*event));
        switch (event->type)
        {
            case JS_EVENT_BUTTON:

                printf("Button %u %s\n", event->number, event->value ? "pressed" : "released");
                break;  

            case JS_EVENT_AXIS:

                if (  event -> number == 0)//event-> number < 5 && event-> number > 1)
                {
                    //printf("Joystick%u %i \n", event-> number, event->value);
                    joystick1_x = int(event->value / 100);
                }

                if (  event -> number == 1)//event-> number < 5 && event-> number > 1)
                {
                    //printf("Joystick%u %i \n", event-> number, event->value);
                    joystick1_y = int((event->value *-1)/100);
                }

                if (  event -> number == 3)//event-> number < 5 && event-> number > 1)
                {
                    //printf("Joystick%u %i \n", event-> number, event->value);
                    joystick2_x = int((event->value )/100);
                }

                if (  event -> number == 4)//event-> number < 5 && event-> number > 1)
                {
                    //printf("Joystick%u %i \n", event-> number, event->value);
                    joystick2_y = int((event->value *-1)/100);
                }

                printf("Joystick 1 (%d,%d)     ", joystick1_x/30, joystick1_y/30);
                printf("Joystick 2 (%d,%d) \n"  , joystick2_x, joystick2_y);
                


            default:
                /* Ignore init events. */
                break;
        }
        fflush(stdout);
        

    }
    close(js);
}