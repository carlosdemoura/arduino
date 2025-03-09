# paresito

## pt-br

Paresito é uma aplicação em C++/arduino com o objetivo de estudar comunicação por meio de bits. Duas placas são necessárias, uma placa de envio e outra de recepção. As placas devem ser colocadas numa caixa (para que não haja interferência da luz ambiente) e o processo se dá em quatro partes:

* O usuário digita uma mensagem na placa de envio e o programa a converte em código binário; 
* O LED da placa de envio transforma o código em um sinal de luz (ligado significa 1, desligado 0);
* O sensor de luminosidade da placa receptora capta a mudança de luminosidade na caixa;
* A placa receptora converte a luminosidade em valores binários e depois em letras.

Assim, podemos fazer uma comunicação entre duas placas que não estão fisicamente conectadas. Cheque fotos [aqui](https://drive.google.com/drive/folders/1UWfe9D1-1VTWlmJ9CAKZj_37Qc9fnizx?usp=sharing).

## en

Paresito is a C++/arduino application that aims to study the communication through bits. Two boards are required, a sending board and a receiving board. The boards must be placed in a box (so that there is no interference from ambient light) and the process takes place in four parts: 

* The user types a message on the sending boards and the program converts it into binary code;
* The LED on the sending board transforms the code into a light signal (on means 1, off means 0);
* The brightness sensor on the receiving board captures the brightness change in the box;
* The receiving board converts the luminosity into binary values and then into letters.

Therefore, we established communication between two boards that aren't physically connected. Check photos [here](https://drive.google.com/drive/folders/1UWfe9D1-1VTWlmJ9CAKZj_37Qc9fnizx?usp=sharing).
