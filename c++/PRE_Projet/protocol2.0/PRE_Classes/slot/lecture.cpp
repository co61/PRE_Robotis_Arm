
void Widget::widget_lecture(){

    usleep(1000000);

    while(ui->checkBox_lecture->isChecked()){
    char test[512];

    //Ecriture dans l'editbox
    sprintf(test, "POSITIONS:\nBase: %d\nBras 1: %d\nBras 2: %d\nBras 3: %d\nPince: %d\n", base.read(), bras1.read(), bras2.read(), bras3.read(),pince.read());
    Position a = getPositionPince3D();
    sprintf(test, "%sPositions Pince X Y Z\nX: %2.2fcm\nY: %2.2fcm\nZ: %2.2fcm\n",test,(a.x*100),(a.y*100),(a.z*100));
    ui->textEdit->setText(test);
    ui->textEdit->update();

    //Ecriture dans les LCD
    ui->lcdNumber_base->display(base.read());
    ui->lcdNumber_bras1->display(bras1.read());
    ui->lcdNumber_bras2->display(bras2.read());
    ui->lcdNumber_bras3->display(bras3.read());
    ui->lcdNumber_pince->display(pince.read());

    //Pour mettre à jour l'IHM selon les events 
    QApplication::processEvents();

    usleep(250000);

    }


    ui->textEdit->setText("POSITIONS:\nBase: xxx\nBras 1: xxx\nBras 2: xxx\nBras 3: xxx\nPince: xxx\n");
    ui->textEdit->update();

}


void Widget::enregistrer_chore(){
    FILE* fichier = NULL;
    char saves[50] = "";
    sprintf(saves, "enregistrement/saves/%s.txt", ui->plainTextEdit->toPlainText().toUtf8().constData());
    ui->comboBox->addItem(saves);
    fichier = fopen(saves, "w");

    Widget::disable();

  int taille = 2500;

  int i = 0;
  
    while(i < taille){
      if((i%50)==0){
        ui->progressBar_enregistrer->setValue((int)(i/25));
        QApplication::processEvents();
      }


      char chaine[512] = "";
      sprintf(chaine, "%d\n", base.read());
      sprintf(chaine, "%s%d\n", chaine,bras1.read());
      sprintf(chaine, "%s%d\n", chaine,bras2.read());
      sprintf(chaine, "%s%d\n", chaine,bras3.read());
      sprintf(chaine, "%s%d\n", chaine,pince.read());

      fputs(chaine, fichier);

      sleep(0.1);

      i++;
    }
    
    fclose(fichier);
}



void Widget::lire_chore(){
    FILE* fichier = NULL;
    
    fichier = fopen(ui->comboBox->currentText().toUtf8().constData(), "r");
    printf(ui->comboBox->currentText().toUtf8().constData());
    //Widget::disable();

    int taille = 2500;

    int i = 0;
  
    while(i < taille){
      if((i%50)==0){
        ui->progressBar_lire->setValue((int)(i/25));
        QApplication::processEvents();
      }
      
      char chaine1[512] = "";
      fgets(chaine1, 512, fichier);
      printf("base %d\n", std::atoi(chaine1));
      base.position(std::atoi(chaine1));
      
      char chaine2[512] = "";
      fgets(chaine2, 512, fichier);
      printf("Bras1 %d\n", std::atoi(chaine2));
      bras1.position(std::atoi(chaine2));
      

      char chaine3[512] = "";
      fgets(chaine3, 512, fichier);
      printf("Bras2 %d\n", std::atoi(chaine3));
      bras2.position(std::atoi(chaine3));


      char chaine4[512] = "";
      fgets(chaine4, 512, fichier);
      printf("Bras3 %d\n", std::atoi(chaine4));
      bras3.position(std::atoi(chaine4));
      

      char chaine5[512] = "";
      fgets(chaine5, 512, fichier);

      printf("Pince %d\n", std::atoi(chaine5));
      pince.position(std::atoi(chaine5));

      printf("Test recup %d\n", std::stoi("10",nullptr,10));

      sleep(0.1);

      i++;
    }
    
    printf(ui->comboBox->currentText().toUtf8().constData());
    fclose(fichier);
}