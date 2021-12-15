
extern float x_balle;
extern float y_balle;


extern Moteur base;
extern Moteur bras1;
extern Moteur bras2;
extern Moteur bras3;
extern Moteur pince;

void Widget::widget_camera(){
  printf("cam");

  base.Torque_enable();
  bras1.Torque_enable();
  bras2.Torque_enable();
  bras3.Torque_enable();
  pince.Torque_enable(); 

  pince.position(920);
  base.position(2000);

  usleep(3000000); 



  camera();

  printf("%f et %f\n",x_balle,y_balle);

        //Borne de X
      if(x_balle > 0.24)
        x_balle = 0.24;
      if(x_balle < -0.24)
        x_balle = -0.24;
      if((x_balle > 0.08) && (x_balle < 0.08))
        x_balle = 0.08;


      //Borne de Z
      if(y_balle > 0.24)
        y_balle = 0.24;
      if(y_balle < -0.24)
        y_balle = -0.24;
      if((y_balle > -0.08) && (y_balle < 0.08))
        y_balle = 0.08;

  
  bras1.position(1500);
  bras2.position(1500);

  usleep(3000000);

  Angles anglesR=calculate_angles(y_balle,0.2,x_balle);
  Angles anglesD = anglesToDegree(anglesR);
  Angles anglesP = anglesToPosition(anglesR);
  //Torque_enable_all();
  goToPosition(anglesP);


  usleep(5000000);


  anglesR=calculate_angles(y_balle,0.05,x_balle);
  anglesD = anglesToDegree(anglesR);
  anglesP = anglesToPosition(anglesR);
  //Torque_enable_all();
  goToPosition(anglesP);

  usleep(3000000);

  pince.position(500);



  usleep(3000000);

  anglesR=calculate_angles(y_balle,0.2,x_balle);
  anglesD = anglesToDegree(anglesR);
  anglesP = anglesToPosition(anglesR);
  //Torque_enable_all();
  goToPosition(anglesP);


  usleep(3000000);

  anglesR=calculate_angles(-0.33,0.21,0.0);
  anglesD = anglesToDegree(anglesR);
  anglesP = anglesToPosition(anglesR);
  //Torque_enable_all();
  goToPosition(anglesP);
  usleep(4000000);
  pince.position(920);

}
