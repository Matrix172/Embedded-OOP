# Embedded-OOP

Utilisation d'une carte STM32 L152RETx, logiciel STM32CUBE IDE dans le cadre d'un projet de POO embarquée sur MCU.

## Contraintes et exigeances : 
- **Coder en C++**
- **Utiliser des périphériques**
- **Utiliser une interface**

  ### Réalisé :
  Reproduction du jeu de séquence SIMON.  

  ### Périphériques : 
  Utilisation des périphériques de la carte en remplacement des couleurs du SIMON.  
  Bleu Vert Jaune Rouge -> Moteur (PWM), Buzzer (PWM), Leds(GPIO), 7Seg(SPI).

  ### Jouer :  
  Sélectionner via les boutons de la carte fournie 1 ou 2 pour indiquer le nombre de joueurs.
  Lorsque "Pret" s'affiche sur l'afficheur 7 segments attendre le défilement de la séquence de 4 actions. 
  Ensuite, reproduire la séquence à l'aide des boutons de la carte.  

  Si la séquence est valide, le jeu continue, sinon le score de chaque joueur est affiché.  
  A chaque nouveau tour, une nouvelle séquence est générée aléatoirement.

  ### Intéractions :

  *Bouton 1 : Moteur*  
  *Bouton 2 : Buzzer*  
  *Bouton 3 : Leds*  
  *Bouton 4 : 7Seg*
