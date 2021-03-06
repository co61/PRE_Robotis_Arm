/**
 *
 *  Controle du robot avec une Manette de console
 * 
 *
 *
 */




// --- INCLUDE --- //
#include "controle.hpp"
#include "../position/calculateAngle.cpp"


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
  profileVelocity(100,100,100,100,100);
  
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
                    if((int(axes[axis].y/3000)>3))
                      dt_bras2 = int(axes[axis].y/3000)*4; //32k
                    else if((int(axes[axis].y/3000)<-3))
                      dt_bras2 = int(axes[axis].y/3000)*5;
                    else
                      dt_bras2 = 0;

                    if((int(axes[axis].x/3000)>3)||(int(axes[axis].x/3000)<-3))
                      dt_bras1 = int(axes[axis].x/3000)*4;
                    else
                      dt_bras1 = 0;
                  }
                  else if(axis == 1){
                    if((int(axes[axis].y/3000)>3)||(int(axes[axis].y/3000)<-3))
                      dt_base = int(axes[axis].y/3000)*4;
                    else
                      dt_base = 0;
                    if((int(axes[axis].x)) > 0)
                      dt_pince = -int(axes[axis].x/3000)*9;
                    else
                      dt_pince = 0;
                    }
                  else if(axis == 2){ 
                    if((int(axes[axis].x/3000)>3)||(int(axes[axis].x/3000)<-3))
                      dt_bras3 = int(axes[axis].x/3000)*4;
                    else
                      dt_bras3 = 0;
                    
                    if((int(axes[axis].y))  > 0)
                      dt_pince = int(axes[axis].y/3000)*9;
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

    if(dt_bras1 != 0)
      mooveBras1(dt_bras1);
    else if(dt_bras2 != 0)
      mooveBras2(dt_bras2);

    if(dt_bras3 != 0)
      mooveBras3(dt_bras3);
    else if(dt_base != 0)
      mooveBase(dt_base);

    if(dt_pince != 0)
      moovePince(dt_pince);
    //moteur_dt(dt_base, dt_bras1, dt_bras2, dt_bras3, dt_pince);
    
  }
  //Fermeture du joystick
  close(js);
  profileVelocity(30,30,30,30,30);
  position();

  
}

void manetteLineaire(){
  Torque_enable_all();
  profileVelocity(30,30,30,30,30);
  
  double dt_up = 0;
  double dt_forward = 0;
  double dt_rotation = 0;
  int dt_pince = 0;

  Position posPince;
  Angles anglesR;
  Angles anglesP;

  //Variables Joystick
  const char *device;
  int js;
  struct js_event event;
  struct axis_state axes[3] = {0};
  size_t axis;


  positionBras1(2000);
  positionBras2(2000);
  positionBras3(2000);
  sleep(3);
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
                printf("quit");
              }
              break;
          case JS_EVENT_AXIS:
              axis = get_axis_state(&event, axes);
              if (axis < 7){
                  printf("Axis %zu at (%6d, %6d)\n", axis, axes[axis].x, axes[axis].y);
                  if(axis == 0){
                    if((int(axes[axis].y/3276.7)>4))
                      dt_up = -(axes[axis].y/3276.7)/1000.0;
                    else if((int(axes[axis].y/3276.7)<-4))
                      dt_up = -(axes[axis].y/3276.7)/2000.0;
                    else
                      dt_up = 0;

                    if((int(axes[axis].x/3276.7)>4))
                      dt_pince = int(axes[axis].x/3276.7)*4;
                    else if (int(axes[axis].x/3276.7)<-4)
                      dt_pince = int(axes[axis].x/3276.7)*4;
                    else
                      dt_pince = 0;
                  }
                  else if(axis == 1){
                    if((int(axes[axis].y/3276.7)>4))
                      dt_rotation = int(axes[axis].y/3276.7)*1.5;
                    else if (int(axes[axis].y/3276.7)<-4)
                      dt_rotation = int(axes[axis].y/3276.7)*1.5;
                    else
                      dt_rotation = 0;
                    }
                  else if(axis == 2){ 
                    if((int(axes[axis].x/3276.7)>4))
                      dt_forward = -int(axes[axis].x/3276.7)/1000.0;
                    else if (int(axes[axis].x/3276.7)<-4)
                      dt_forward = -int(axes[axis].x/3276.7)/1000.0;
                    else
                      dt_forward = 0;
                    }
              }

              break;
          default:
              /* Ignore init events. */
              break;
      }
    }
    fflush(stdout);

    if (dt_up!=0 || dt_forward!=0 || dt_rotation!=0 || dt_pince!=0){
      posPince = getPositionPince3D();
      // printf("Position  x : %g, y : %g, z : %g\n", posPince.x, posPince.y, posPince.z);
      printf("  dt_up : %g, dt_forward : %g, dt_rotation : %g\n", dt_up, dt_forward, dt_rotation);
      if(dt_up<0){
        anglesR=calculate_angles(posPince.x, posPince.y + dt_up, posPince.z, dt_forward);
        anglesP = anglesToPosition(anglesR, dt_rotation);
        goToPosition(anglesP, -8);
      }else if (dt_up>0){
        anglesR=calculate_angles(posPince.x, posPince.y + dt_up, posPince.z, dt_forward);
        anglesP = anglesToPosition(anglesR, dt_rotation);
        goToPosition(anglesP, -12);
      }else{
        anglesR=calculate_angles(posPince.x, posPince.y + dt_up, posPince.z, dt_forward);
        anglesP = anglesToPosition(anglesR, dt_rotation);
        goToPosition(anglesP);
      }
      moovePince(dt_pince);
    }
  }
  //Fermeture du joystick
  close(js);
  profileVelocity(30,30,30,30,30);
  position();

  
}
/*
void manetteeLineaire(){
  printf("\n================================\n(Echap pour revenir en arri??re)\n");
  int chr;
  
  int dt;
  int dtbase = 40;

  int dxl_lecture = 0;  // Read 4 byte Position data

  Torque_enable_all();
  while(1){
    chr = getch();
    dt = 0;
    
    if (chr == ESC_ASCII_VALUE)
      break;
    posPince = getPositionPince3D();
    printf("Position  x : %g, y : %g, z : %g\n", posPince.x, posPince.y, posPince.z);
    switch(chr)
    {      
      //forward
      case 'z':
        anglesR=calculate_angles(posPince.x, posPince.y, posPince.z,0.01);
        anglesP = anglesToPosition(anglesR);
        goToPosition(anglesP);
        break;
      //back
      case 's':
        anglesR=calculate_angles(posPince.x, posPince.y, posPince.z,-0.01);
        anglesP = anglesToPosition(anglesR);
        goToPosition(anglesP);
        break;
      //right
      case 'd':
        anglesR=calculate_angles(posPince.x, posPince.y, posPince.z);
        anglesP = anglesToPosition(anglesR, 15);
        goToPosition(anglesP);
        break;
      //left
      case 'q':
        anglesR=calculate_angles(posPince.x, posPince.y, posPince.z );
        anglesP = anglesToPosition(anglesR, -15);
        goToPosition(anglesP);
        break;
      //up
      case 't':
        anglesR=calculate_angles(posPince.x, posPince.y+0.01, posPince.z);
        anglesP = anglesToPosition(anglesR);
        goToPosition(anglesP,-15);
        break;
        //down
      case 'g':
        anglesR=calculate_angles(posPince.x, posPince.y-0.005, posPince.z);
        anglesP = anglesToPosition(anglesR);
        goToPosition(anglesP,-5);
        break;
      case 'f':
        moovePince(dtbase);
        break;
      case 'h':
        moovePince(-dtbase);
        break;
      
    }


  }
  

}
*/