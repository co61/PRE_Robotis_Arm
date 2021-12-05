//Controle avec sliders

void Widget::pince_moove(int pos){
    pince.Torque_enable();
    //pince.profileVelocity(30);
    pince.position(pos);
}

void Widget::bras1_moove(int pos){
    bras1.Torque_enable();
    //bras1.profileVelocity(30);
    bras1.position(pos);
}


void Widget::bras2_moove(int pos){
  bras2.Torque_enable();
  //bras2.profileVelocity(30);
  bras2.position(pos);
}


void Widget::test_moove(int pos, Moteur mot){
  mot.Torque_enable();
  mot.profileVelocity(30);
  mot.position(pos);
}

void Widget::bras3_moove(int pos){
  bras3.Torque_enable();
  //bras3.profileVelocity(30);
  bras3.position(pos);
}

void Widget::base_moove(int pos){
  base.Torque_enable();
  //base.profileVelocity(30);
  base.position(pos);
}

//Utiliser la manette

void Widget::widget_manette(){
  QPixmap pix_on("manette_on.jpg");
  int w = ui->label_manette->width();
  int h = ui->label_manette->height();
  ui->label_manette->setPixmap(pix_on.scaled(w,h,Qt::KeepAspectRatio));

  QApplication::processEvents();
  
  manette();


  QPixmap pix_off("manette_off.jpg");
  ui->label_manette->setPixmap(pix_off.scaled(w,h,Qt::KeepAspectRatio));
}

void Widget::widget_manetteLineaire(){

  QPixmap pix_on("manette_on.jpg");
  int w = ui->label_manette->width();
  int h = ui->label_manette->height();
  ui->label_manette->setPixmap(pix_on.scaled(w,h,Qt::KeepAspectRatio));


  QApplication::processEvents();
  
  manetteLineaire();


  QPixmap pix_off("manette_off.jpg");
  ui->label_manette->setPixmap(pix_off.scaled(w,h,Qt::KeepAspectRatio));
}