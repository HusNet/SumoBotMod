/***********************************************************************************
      ___       ___         |          ____  _     _      ____  ____  ____  _____        
     [___] /~\ [___]        |         / ___\/ \ /\/ \__/|/  _ \/  __\/  _ \/__ __\       
     |ooo|.\_/.|ooo|        |         |    \| | ||| |\/||| / \|| | //| / \|  / \         
     |888||   ||888|        |         \___ || \_/|| |  ||| \_/|| |_\\| \_/|  | |         
    /|888||   ||888|\       |    _____\____/\________ ______________________ \____  _____
  /_,|###||___||###|._\     |   /  __// ___\/ \/  __//  __// ___\/  __\/  _ \/   _\/  __/
 /~\  ~~~ /[_]\ ~~~  /~\    |  |  \  |    \| ||  \  |  \  |    \|  \/|| / \||  /  |  \  
(O_O) /~~[_____]~~\ (O_O)   |  |  /_ \___ || ||  /_ |  /_ \___ ||  __/| |-|||  \__|  /_ 
     (  |       |  )        |   \____\\____/\_/\___________\\____/\_/   \_/ \|\____/\____\
    [~` ]       [ '~]       |                    /_   \/  _ \/ \/ ___\                        
    |~~|         |~~|       |                     /   /| / \|| ||    \                        
    |  |         |  |       |                    /   /_| \_/|| |\___ |                        
   _<\/>_       _<\/>_      |                    \____/\____/\_/\____/                        
  /_====_\     /_====_\     |
.d                          |                    ¦̵̵̱̱(͇̅└͇̅┘͇̅(▤8כ−◦
************************************************************************************                                                         
SumoBotV2.ino - Code fourni avec le kit SumoBot 2015 développé par l'association
ESIEESPACE.(http://www.esieespace.fr/)
Pour toute question visiter le forum sumobot. (sumobot.esieespace.fr)
Ecrit par Bruno IATRIDES le 25/05/2014.
Corrigé par un inconnu.
Ce code est dans le domaine public.
Ce code n'est qu'un exemple de ce qu'il est possible de faire, n'hésitez pas à innover,
à le modifier et à le faire votre!

/***********************************************************************************
 ____  _  _        ____  _____ _____ _____ ____  _____  ____  _____  _  ____  _     
/  __\/ \/ \  /|  /  _ \/    //    //  __//   _\/__ __\/  _ \/__ __\/ \/  _ \/ \  /|
|  \/|| || |\ ||  | / \||  __\|  __\|  \  |  /    / \  | / \|  / \  | || / \|| |\ ||
|  __/| || | \||  | |-||| |   | |   |  /_ |  \__  | |  | |-||  | |  | || \_/|| | \||
\_/   \_/\_/  \|  \_/ \|\_/   \_/   \____\\____/  \_/  \_/ \|  \_/  \_/\____/\_/  \|

************************************************************************************
Affectation de numeros de PIN a des variables qui on un nom plus parlant, cela 
permet dans le reste du programme de faire réference au bouton GO, au lieu du 
numero de PIN.
Ainsi a chaque fois que GO sera écris, le programme comprendra 12.
************************************************************************************
***********************************************************************************/
//Entrée
const int GO = 12;				//PIN D4 est le bouton GO
const int CNY_1 = 2;				//PIN D2 est le CNY_1
const int CNY_2 = 3;				//PIN D3 est le CNY_2
const int SHARP = 0;				//PIN A0 est le SHARP

//Sortie
const int LED_1 = 13;				//PIN D4 est la LED_1
const int LED_2 = 5;				//PIN D5 est le LED_2

//Commande du pont en H, pour plus d'indication voir la bible du SUMO sur les ponts en H
const int leftWheel = 10;			//PIN D10 est le PWM de la roue GAUCHE
const int rightWheel = 11;			//PIN D11 est le PWM de la roue DROITE
const int leftWheelDirection0 = 6;		//PIN D6 est la direction 0 de la roue GAUCHE
const int leftWheelDirection1 = 7;		//PIN D7 est la direction 1 de la roue GAUCHE
const int rightWheelDirection0 = 8;		//PIN D8 est la direction 0 de la roue DROITE
const int rightWheelDirection1 = 9;		//PIN D9 est la direction 1 de la roue DROITE


/**********************************************************************************
			 ____  _____ _____  _     ____ 
			/ ___\/  __//__ __\/ \ /\/  __\
			|    \|  \    / \  | | |||  \/|
			\___ ||  /_   | |  | \_/||  __/
			\____/\____\  \_/  \____/\_/   
													   
***********************************************************************************
Dans le setup, on va initialiser tout les PIN en définissant leur mode de 
fonctionnement, c'est la première chose que va faire l'Arduino en s'allumant.
http://arduino.cc/en/Reference/pinMode
***********************************************************************************
**********************************************************************************/
void setup(void)
{
	pinMode(GO,INPUT_PULLUP);		//le PIN GO (c'est a dire le 12) est en mode entrée avec resistance de tirage au +5V
	pinMode(LED_2,OUTPUT);			//le PIN LED_2 (5) est en mode sortie
	pinMode(CNY_1,INPUT);		        //le PIN CNY_1 (2) est en mode entrée avec resistance de tirage au +5V
	pinMode(CNY_2,INPUT);		        //le PIN CNY_2 (3) est en mode entrée avec resistance de tirage au +5V
	pinMode(LED_1,OUTPUT);	        	//le PIN LED_1 (13) est en mode sortie
	pinMode(leftWheel, OUTPUT);		//le PIN leftWheel (10) est en mode sortie
	pinMode(rightWheel, OUTPUT);		//le PIN rightWheel (11) est en mode sortie
	pinMode(leftWheelDirection0, OUTPUT);	//le PIN leftWheelDirection0 (6) est en mode sortie
	pinMode(leftWheelDirection1, OUTPUT);	//le PIN leftWheelDirection1 (7) est en mode sortie
	pinMode(rightWheelDirection0, OUTPUT);	//le PIN rightWheelDirection0(8) est en mode sortie
	pinMode(rightWheelDirection1, OUTPUT);	//le PIN rightWheelDirection1 (9) est en mode sortie
}

/*********************************************************************************
			 _      ____  _  _     
			/ \__/|/  _ \/ \/ \  /|
			| |\/||| / \|| || |\ ||
			| |  ||| |-||| || | \||
			\_/  \|\_/ \|\_/\_/  \|
													   
**********************************************************************************
Dans la loop (boucle en français), on met le programme principal, il est appelé 
juste apres le setup.
C'est ici que l'on va mettre la stratégie du robot.
**********************************************************************************
*********************************************************************************/

void loop(void)
{

    start();    //appele la fonction start()
    go(255);
    while(1)                               // le programme ne sortira plus de cette boucle, il la repetera toujours 
                                           // ce code se lit : tant que vrai est vrai, on execute le code qui suit
    {
	digitalWrite(LED_1,LOW); 
	digitalWrite(LED_2,LOW);
        if(whiteLine() == 1)
        {
          escape();
        }
        else
        {
          if(sharpDistance(50))
          {
            go(255);
            digitalWrite(LED_2,HIGH);
            digitalWrite(LED_1,HIGH);
          }
          else
          {
            turnLeft(150,200);
            delay(75);
		
          }
        }
        delay(50);
    }
}


/********************************************************************************
	             ____  _____  ____  ____  _____ 
	    	    / ___\/__ __\/  _ \/  __\/__ __\
		    |    \  / \  | / \||  \/|  / \  
		    \___ |  | |  | |-|||    /  | |  
		    \____/  \_/  \_/ \|\_/\_\  \_/  
														
*********************************************************************************
Fonction de démarrage, on met en place un délais de 5s après avoir appuyé sur le 
bouton G0, tout cela avant de passer à la partie stratégie du code.
http://arduino.cc/en/Reference/digitalRead
http://arduino.cc/en/Reference/digitalWrite
http://arduino.cc/en/Reference/delay
*********************************************************************************
********************************************************************************/

void start(void)
{
	digitalWrite(LED_1, HIGH);    //On allume la LED_1

	while( digitalRead(GO) == HIGH)	      //Tant que le bouton n'est pas appuyé, on ne fait rien
	{
	}

	digitalWrite(LED_1,LOW);              //On eteint la LED_1
    delay(5000);			      //On attend 5000 ms
}


/********************************************************************************
   ____  _     ____  ____  ____  ____  _  ____  _____  ____  _      ____  _____
  / ___\/ \ /|/  _ \/  __\/  __\/  _ \/ \/ ___\/__ __\/  _ \/ \  /|/   _\/  __/
  |    \| |_||| / \||  \/||  \/|| | \|| ||    \  / \  | / \|| |\ |||  /  |  \  
  \___ || | ||| |-|||    /|  __/| |_/|| |\___ |  | |  | |-||| | \|||  \__|  /_ 
  \____/\_/ \|\_/ \|\_/\_\\_/   \____/\_/\____/  \_/  \_/ \|\_/  \|\____/\____\
                                                                             
*********************************************************************************
Cette fonction compare la valeur (entre 0V et 5V) mesuré (entre 0 et 1023) fournis 
sur l'entré analogique A0 par le SHARP, et l'entier passé en paramétre.
La fonction retourne 1 si la valeur mesurée est inférieure à celle passée en 
paramètre, sinon elle retourne 0.
Un 0 en numérique corespond à 0V en analogique, un 1023 en numérique corespond à 
5V en analogique.
Voir ADC dans le cour.
http://arduino.cc/en/Reference/analogRead
*********************************************************************************
********************************************************************************/
int sharpDistance(int distance)
{
  if(analogRead(SHARP) < distance)
  {
    return 0;
  }
    else
  {
    return 1;
  }
}


/********************************************************************************
		 _      _     _  _____  _____ _     _  _      _____
		/ \  /|/ \ /|/ \/__ __\/  __// \   / \/ \  /|/  __/
		| |  ||| |_||| |  / \  |  \  | |   | || |\ |||  \  
		| |/\||| | ||| |  | |  |  /_ | |_/\| || | \|||  /_ 
		\_/  \|\_/ \|\_/  \_/  \____\\____/\_/\_/  \|\____\
																   
*********************************************************************************
Cette fonction retourne 1 si une ligne blanche se trouve sous le CNY_1 ou le 
CNY_2, sinon elle retourne 0.
*********************************************************************************
********************************************************************************/
int whiteLine()
{
  if(digitalRead(CNY_1) == HIGH || digitalRead(CNY_2) == HIGH)	
	// le symbole || represente un OU logique.
	//http://www.commentcamarche.net/contents/115-langage-c-les-operateurs
  {
    return 1;
  }
  else
  {
    return 0;
  }
}


/********************************************************************************
	             _____ ____  ____  ____  ____  _____
	    	    /  __// ___\/   _\/  _ \/  __\/  __/
		    |  \  |    \|  /  | / \||  \/||  \  
		    |  /_ \___ ||  \__| |-|||  __/|  /_ 
		    \____\\____/\____/\_/ \|\_/   \____\
															
*********************************************************************************
Fonction d'évitement de ligne blanche.
********************************************************************************/
void escape(void)
{
  digitalWrite(LED_1,HIGH);
  back(255);
  delay(1000);
  turnLeft(255,255);
  delay(1000);
  digitalWrite(LED_1,LOW);
}


/********************************************************************************
      			           _____ ____ 
			          /  __//  _ \
				  | |  _| / \|
				  | |_//| \_/|
				  \____\\____/
												
*********************************************************************************
Avance tout droit, prend un char en parametre (donc de 0 à 255) qui définit le 
taux du PWM transmit au moteur.
voir PWM et pont en H dans la bible du sumo.
http://arduino.cc/en/Reference/analogWrite
On mets également le pont en H dans la bonne configuration pour faire tourner 
chacune des roues dans la bonne direction.
********************************************************************************/
void go(unsigned char wheelSpeed)
{
  digitalWrite(leftWheelDirection0, HIGH);
  digitalWrite(leftWheelDirection1, LOW);
  digitalWrite(rightWheelDirection0, HIGH);
  digitalWrite(rightWheelDirection1, LOW);
  analogWrite(leftWheel, wheelSpeed);
  analogWrite(rightWheel, wheelSpeed);
}


/********************************************************************************
	          	 ____  ____  ____  _  __
		        /  __\/  _ \/   _\/ |/ /
			| | //| / \||  /  |   / 
			| |_\\| |-|||  \__|   \ 
			\____/\_/ \|\____/\_|\_\
													
*********************************************************************************
Recule, prend un char en paramètre (donc de 0 à 255) qui définit le taux du PWM 
transmit au moteur.
voir PWM et pont en H dans la bible du sumo.
http://arduino.cc/en/Reference/analogWrite
On met également le pont en H dans la bonne configuration pour faire tourner 
chacune des roues dans la bonne direction.
********************************************************************************/
void back(unsigned char wheelSpeed)
{
  digitalWrite(leftWheelDirection0, LOW);
  digitalWrite(leftWheelDirection1, HIGH);
  digitalWrite(rightWheelDirection0, LOW);
  digitalWrite(rightWheelDirection1, HIGH);
  analogWrite(leftWheel, wheelSpeed);
  analogWrite(rightWheel, wheelSpeed);
}


/********************************************************************************
		 _____  _     ____  _      _     _____ _____ _____ 
		/__ __\/ \ /\/  __\/ \  /|/ \   /  __//    //__ __\
		  / \  | | |||  \/|| |\ ||| |   |  \  |  __\  / \  
		  | |  | \_/||    /| | \||| |_/\|  /_ | |     | |  
		  \_/  \____/\_/\_\\_/  \|\____/\____\\_/     \_/  
																   
*********************************************************************************
Tourne à gauche, prend un char en paramètre (donc de 0 à 255) qui définit le taux 
du PWM transmit à chaque moteur.
voir PWM et pont en H dans la bible du sumo.
http://arduino.cc/en/Reference/analogWrite
On met également le pont en H dans la bonne configuration pour faire tourner 
chacune des roues dans la bonne direction.
********************************************************************************/
void turnLeft(unsigned char leftWheelSpeed, unsigned char rightWheelSpeed)
{
  digitalWrite(leftWheelDirection0, LOW);
  digitalWrite(leftWheelDirection1, HIGH);
  digitalWrite(rightWheelDirection0, HIGH);
  digitalWrite(rightWheelDirection1, LOW);
  analogWrite(leftWheel, leftWheelSpeed);
  analogWrite(rightWheel, rightWheelSpeed);
}


/********************************************************************************
           _____  _     ____  _      ____  _  _____ _     _____ 
          /__ __\/ \ /\/  __\/ \  /|/  __\/ \/  __// \ /|/__ __\
            / \  | | |||  \/|| |\ |||  \/|| || |  _| |_||  / \  
            | |  | \_/||    /| | \|||    /| || |_//| | ||  | |  
            \_/  \____/\_/\_\\_/  \|\_/\_\\_/\____\\_/ \|  \_/  
                                                      
*********************************************************************************
Tourne à droite, prend deux char en parametre (donc de 0 à 255) qui définissent 
le taux du PWM transmit à chaque moteur.
voir PWM et pont en H dans la bilbe du sumo.
http://arduino.cc/en/Reference/analogWrite
On met également le pont en H dans la bonne configuration pour faire tourner 
chacune des roues dans la bonne direction.
********************************************************************************/
void turnRight(unsigned char leftWheelSpeed, unsigned char rightWheelSpeed)
{
  digitalWrite(leftWheelDirection0, HIGH);
  digitalWrite(leftWheelDirection1, LOW);
  digitalWrite(rightWheelDirection0, LOW);
  digitalWrite(rightWheelDirection1, HIGH);
  analogWrite(leftWheel, leftWheelSpeed);
  analogWrite(rightWheel, rightWheelSpeed);
}
