# PRE_Robotis_Arm
Control of a robotic arm with different tools.²

# Project by

Thibaut ROLLAND
Arnaud MORE
Corentin REGNE 
Sarah BUCQUET
Tanguy BOITTIN
Axel NOUGIER

# Orginisation des fichiers

Pour lancer l'IHM il faut lancer "./PRE_main" se trouvant dans le dossier "PRE_Robotis_Arm/c++/PRE_Projet/protocol2.0/PRE_Classes"

PRE_main
|
|-- Slot: Contient les Slot pour les Widget QT \n
| \n
|-- Moteur: Contient la representation orientée objets des moteurs
|
|-- Manette: Contient les utilisations d'une manette pour controler le robot
|
|-- Camera: Contient l'utilisation de la camera pour detecter la balle
|
|-- PRE_main.cpp: main du projet qui lance l'ihm Qt
|
|-- widget.cpp et widget.ui: IHM Qt avec connexions des signaux/slots
