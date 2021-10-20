// --- INCLUDE --- //
#include "controle.hpp"



/////////////////////////Joystick lib//////////////////////
int read_event(int fd, struct js_event *event)
{
    ssize_t bytes;

    bytes = read(fd, event, sizeof(*event));

    if (bytes == sizeof(*event))
        return 0;

    return -1;
}

size_t get_axis_count(int fd)
{
    __u8 axes;

    if (ioctl(fd, JSIOCGAXES, &axes) == -1)
        return 0;

    return axes;
}

size_t get_button_count(int fd)
{
    __u8 buttons;
    if (ioctl(fd, JSIOCGBUTTONS, &buttons) == -1)
        return 0;

    return buttons;
}



size_t get_axis_state(struct js_event *event, struct axis_state axes[3])
{
    size_t axis = event->number / 2;

    if (axis < 3)
    {
        if (event->number % 2 == 0)
            axes[axis].x = event->value;
        else
            axes[axis].y = event->value;
    }

    return axis;
}


void manette(){
  Torque_enable_all();
  
  int dt_base = 0;
  int dt_bras1 = 0;
  int dt_bras2 = 0;
  int dt_bras3 = 0;
  int dt_pince = 0;

  //Variables Joystick
  const char *device;
  int js;
  struct js_event event;
  struct axis_state axes[3] = {0};
  size_t axis;

  device = "/dev/input/js0";

  js = open(device, O_NONBLOCK);

  if (js == -1)
      perror("Could not open joystick");

  /* This loop will exit if the controller is unplugged. */
  int quit = 1;
  while (quit)
  {
    if(read_event(js, &event) == 0){
      switch (event.type)
      {
          case JS_EVENT_BUTTON:
              printf("Button %u %s\n", event.number, event.value ? "pressed" : "released");
              if ((event.number == 0)&&(event.value)){
                position();
              }
              else if((event.number == 1)&&(event.value)){

              }
              else if((event.number == 2)&&(event.value)){
                
              }
              else if((event.number == 3)&&(event.value)){
                
              }
              else if((event.number == 6)&&(event.value)){
                quit = 0;
              }
              break;
          case JS_EVENT_AXIS:
              axis = get_axis_state(&event, axes);
              if (axis < 7){
                  printf("Axis %zu at (%6d, %6d)\n", axis, axes[axis].x, axes[axis].y);
                  if(axis == 0){
                    if((int(axes[axis].y/3000)>5)||(int(axes[axis].y/3000)<-5))
                      dt_bras2 = int(axes[axis].y/3000)*3;
                    else
                      dt_bras2 = 0;

                    if((int(axes[axis].x/3000)>5)||(int(axes[axis].x/3000)<-5))
                      dt_bras1 = int(axes[axis].x/3000)*4;
                    else
                      dt_bras1 = 0;
                  }
                  else if(axis == 1){
                    if((int(axes[axis].y/3000)>5)||(int(axes[axis].y/3000)<-5))
                      dt_base = int(axes[axis].y/3000)*3;
                    else
                      dt_base = 0;
                    if((int(axes[axis].x)) > 0)
                      dt_pince = -10;
                    else
                      dt_pince = 0;
                    }
                  else if(axis == 2){
                    if((int(axes[axis].x/3000)>5)||(int(axes[axis].x/3000)<-5))
                      dt_bras3 = int(axes[axis].x/3000)*3;
                    else
                      dt_bras3 = 0;
                    
                    if((int(axes[axis].y))  > 0)
                      dt_pince = 10;
                    else
                      dt_pince = 0;
                    }
              }

              break;
          default:
              /* Ignore init events. */
              break;
      }
    }
    fflush(stdout);

    moteur_dt(dt_base, dt_bras1, dt_bras2, dt_bras3, dt_pince);
    
  }
  //Fermeture du joystick
  close(js);
  position();
}