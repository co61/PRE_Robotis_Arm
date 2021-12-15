/******************************************************************************\
* Réutilisation de l'exemple du Leap Motion SDK et adaptation au projet        *
* https://developer.leapmotion.com/                                            *
* Lancer "sudo leapd" dans un terminal pour utiliser le Leap Motion            *
* PROJET PRE - ENIB 2021                                                       *
\******************************************************************************/

#include <iostream>
#include <cstring>
#include "Leap.h"

#include "widget.h"
#include "moteur/moteur.hpp"


extern QApplication a;

extern Moteur base;
extern Moteur bras1;
extern Moteur bras2;
extern Moteur bras3;
extern Moteur pince;


int getch() {
#if defined(__linux__) || defined(__APPLE__)
  struct termios oldt, newt;
  int ch;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  return ch;
#elif defined(_WIN32) || defined(_WIN64)
  return _getch();
#endif
}

int kbhit(void) {
#if defined(__linux__) || defined(__APPLE__)
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if (ch != EOF) {
    ungetc(ch, stdin);
    return 1;
  }


  return 0;
#elif defined(_WIN32) || defined(_WIN64)
  return _kbhit();
#endif
}



using namespace Leap;

class SampleListener : public Listener {
  public:
    virtual void onInit(const Controller&);
    virtual void onConnect(const Controller&);
    virtual void onDisconnect(const Controller&);
    virtual void onExit(const Controller&);
    virtual void onFrame(const Controller&);
    virtual void onFocusGained(const Controller&);
    virtual void onFocusLost(const Controller&);
    virtual void onDeviceChange(const Controller&);
    virtual void onServiceConnect(const Controller&);
    virtual void onServiceDisconnect(const Controller&);

  private:
};

const std::string fingerNames[] = {"Thumb", "Index", "Middle", "Ring", "Pinky"};
const std::string boneNames[] = {"Metacarpal", "Proximal", "Middle", "Distal"};
const std::string stateNames[] = {"STATE_INVALID", "STATE_START", "STATE_UPDATE", "STATE_END"};

void SampleListener::onInit(const Controller& controller) {
  std::cout << "Initialized" << std::endl;
}

void SampleListener::onConnect(const Controller& controller) {
  std::cout << "Connected" << std::endl;
  
  /*
  controller.enableGesture(Gesture::TYPE_CIRCLE);
  controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
  */
  controller.enableGesture(Gesture::TYPE_KEY_TAP);
  controller.enableGesture(Gesture::TYPE_SWIPE);
  
}

void SampleListener::onDisconnect(const Controller& controller) {
  // Note: not dispatched when running in a debugger.
  std::cout << "Disconnected" << std::endl;
}

void SampleListener::onExit(const Controller& controller) {
  std::cout << "Exited" << std::endl;
}

void SampleListener::onFrame(const Controller& controller) {
  // Get the most recent frame and report some basic information
  const Frame frame = controller.frame();
  /*
  std::cout << "Frame id: " << frame.id()
            << ", timestamp: " << frame.timestamp()
            << ", hands: " << frame.hands().count()
            << ", extended fingers: " << frame.fingers().extended().count()
            << ", tools: " << frame.tools().count()
            << ", gestures: " << frame.gestures().count() << std::endl;
            */

  HandList hands = frame.hands();
  for (HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl) {
    // Get the first hand
    const Hand hand = *hl;
    std::string handType = hand.isLeft() ? "Left hand" : "Right hand";
    
   /* std::cout << std::string(2, ' ') << handType << ", id: " << hand.id()
              << ", palm position: " << hand.palmPosition() << (hand.direction().pitch() * RAD_TO_DEG) << std::endl;
     */         
    // Get the hand's normal vector and direction
    const Vector normal = hand.palmNormal();
    const Vector direction = hand.direction();

    //oovePince(int(hand.palmPosition()[0]));
    if(hand.isRight()){
      float x = float(hand.palmPosition()[0])/400.0f;
      float y = float(hand.palmPosition()[1])/800.0f;
      float z = float(hand.palmPosition()[2])/400.0f;

      //Borne de X
      if(x > 0.24)
        x = 0.24;
      if(x < -0.24)
        x = -0.24;
      if((x > 0.08) && (x < 0.08))
        x = 0.08;

      //Borne de Y
      if(y < 0.1)
        y = 0.1;

      //Borne de Z
      if(z > 0.24)
        z = 0.24;
      if(z < -0.24)
        z = -0.24;
      if((z > -0.08) && (z < 0.08))
        z = 0.08;

      printf("x: %f  y: %f  z: %f \n",x,y,z);
      Angles anglesR=calculate_angles(x,y,z);
      Angles anglesD = anglesToDegree(anglesR);
      Angles anglesP = anglesToPosition(anglesR);
      //Suit la position de la main
      bras1.position(2350 - int(hand.palmPosition()[1]));
      bras2.position(2200 - int(hand.palmPosition()[1]));

      //Suit l'angle de la main
      bras3.position(2000 - int(10*(hand.direction().pitch() * RAD_TO_DEG)));

      base.position(2000 - int(800*hand.direction()[0]));

      //pince.position(600-500*hand.pinchStrength());

      printf("Pinch: %f", hand.pinchStrength());

      //goToPosition(anglesP);
      
      }

      a.processEvents();

  }


  if (!frame.hands().isEmpty()) {
    std::cout << std::endl;
  }

}

void SampleListener::onFocusGained(const Controller& controller) {
  std::cout << "Focus Gained" << std::endl;
}

void SampleListener::onFocusLost(const Controller& controller) {
  std::cout << "Focus Lost" << std::endl;
}

void SampleListener::onDeviceChange(const Controller& controller) {
  std::cout << "Device Changed" << std::endl;
  const DeviceList devices = controller.devices();

  for (int i = 0; i < devices.count(); ++i) {
    std::cout << "id: " << devices[i].toString() << std::endl;
    std::cout << "  isStreaming: " << (devices[i].isStreaming() ? "true" : "false") << std::endl;
  }
}

void SampleListener::onServiceConnect(const Controller& controller) {
  std::cout << "Service Connected" << std::endl;
}

void SampleListener::onServiceDisconnect(const Controller& controller) {
  std::cout << "Service Disconnected" << std::endl;
}


void leap(){
  // Create a sample listener and controller
  SampleListener listener;
  Controller controller;

  //Torque_enable_all();
  // Have the sample listener receive events from the controller
  controller.addListener(listener);

  //if (argc > 1 && strcmp(argv[1], "--bg") == 0)
  //  vef
  controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);

  // Keep this process running until Enter is pressed
  std::cout << "Press Enter to quit..." << std::endl;

  int quit = 1;
  while(quit){
    int chr = getch();
    switch(chr){
      case 'a':
        pince.moove(40);
        break;
      case 'q':
        pince.moove(-40);
        break;
      default:
        quit = 0;
        break;

    }
  }

  // Remove the sample listener when done
  controller.removeListener(listener);

  //Torque_disable_all();
  //return 0;

}