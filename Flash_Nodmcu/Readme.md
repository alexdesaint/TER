
# Comment flasher sa carte ?
1. Télécharger et décompresser le fichier « nodemcu-flasher-master »
2. Lancer l'application qui convient à votre ordinateur :
	- /nodemcu-flasher-master/Win64/Release/ESP8266Flasher.exe Pour la version 64 bits
	- /nodemcu-flasher-master/Win32/Release/ESP8266Flasher.exe Pour la version 32 bits
3. Dans « Config », cliquer sur 1er petit engrenage et sélectionner le fichier :
	- /nodemcu-flasher-master/ai-thinker-0.9.5.2-115200.bin
4. Dans « Advanced », rentrer les données suivantes :
	- Baudrate = 115200
	- Falsh size = 4MByte
	- Flash speed = 80MHz
	- SPI Mode = DIO
5. Pour finir, aller sans « Operation », sélectionner votre port et cliquer sur le bouton Flash(F)
- Voilà, votre carte est flashée et vous pouvez utiliser le wifi !!!