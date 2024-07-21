***OVERVIEW***
We have here, a positioning controller System with the Arduino Uno
microcontroller board. It uses the Step Motor, coded 28byj-48, the
Driver, coded uln2003 and an Incremental Rotary Encoder, coded ky-040.
It also contains two mini printed circuit boards, for soldering of
two smd leds in each one of them. They will signalize as to the 
stages of the Control Process operation :
Direct drive and Reverse drive of the motor and if is occuring 
Recovery of the positioning by the motor, with the Control System,
after an eventual fault of the electrical Power Supply.
This project does not involves any Limit Switches, because it involves
the use of an incremental rotary encoder.
The Accuracy is equal to  +/- 1 (one) pulse of encoder.
***VIEWING & DOWNLOADING THE VIDEO***
You can view the video 'Step Motor Control' in the Brazilian and English
versions (downloads available only from the English version), at the links:
https://youtu.be/vKYuhkvZ-ec?feature=shared                  (Brazilian v.)
https://youtu.be/L1CZxgx3B20?si=s6bXeFy8mACiA8z3             (English v.)
For a better viewing experience, see this video with the Maximized Screen (
device in the Horizontal position).
***DOWNLOADING THE SKETCH(CODE) & THE LIBRARY***
You can download the Sketch(Code), what already contains the Library
RotaryEncoder-master (by Matthias Hertel - mathertel), directly from the
GitHub Repository, at the following link (my Home Page):
https://github.com/GilbertoCsar/Step_Motor_Control.git
Create, firstly, a new folder in the explorer with the path :
C:\Users\yourname*\Documents\Arduino\sketch_stepmotor10\
* yourname : is the owner's name of the computer
And then, move all the 8 files (unpacked) + 1 file(packed) to that new folder.
One from those 8 unpacked files is the : sketch_stepmotor10.ino .
The packed file is the RotaryEncoder-master.zip (it should be left so, packed).
***USAGE APPLICATION***
 ***Unexpected Operation***
 When you would be to transfer the Sketch(Code) from the computer to the
 Arduino board (so making Upload), may be that the Software begins the run and
 stop by some few seconds :
 That's the enough, for the Control System, to recognize that has occured a
 pseudo-fault in the electrical Power Supply (due the brief initial stopping).
 In these cases, the Control System will assume the reverse Recovery Mode,
 lighting the smd stable blue led (at the left side of motor), when the upload
 finishes. Thus, how should I proceed?
 It's enough to wait by the smd stable blue led to turn to off; and then to
 press and left once, the Stop Button.
 So, the Step Motor Control System will finalize with the motor's operation, at
 the final of that cycle (Direct/Reverse).
 Then, to start in fact, the motor's operation, you can press and left once, the
 reset Button (on the Arduino board).
 ***Runnig the Sketch(Code) - Three Particular Cases***
 You may Simulate, with this code, each one among 3 particular cases, as follows:
 1) One fault in the electrical Power Supply, occuring during the Direct Mode of
    the step motor, followed by another fault occurig in the Reverse Mode (
    strictly in this order);
 2) One fault in the electrical Power Supply, occuring once, during the Direct Mode,
    only;
 3) One fault in the electrical Power Supply, occuring once, during the Reverse Mode,
    only.
 In order to begin again, each one of these cases, you should press and left once,
 before, the Stop Button.
 As an example of this 1), you can see the Video, cited before, in this README.md
***ACKNOWLEDGEMENTS***
I, Gilberto César Balthazar, thanks
To  GitHub.com, Matthias Hertel, YouTube.com.br, Electrical e-Library.com,Microsoft,
    Google.com, Mercado Libre.com.br, Instituto Digital.com.br, Eugenio H.P.,
    Universidade Estadual de Campinas(UNICAMP), Universidade Federal de Itajubá(
    UNIFEI), Escola Técnica Estadual de Segundo Grau 'Bento Quirino', Petrobras,
    Samsung, Motorola, Hp/calculators, Extra.com.br, Mastercard and Visa cards,
    Bank Itaú, Bank Mercado Pago, TIM, Net.Claro, the Feitosa married couple,
    Isabel C.B.(my syster), Cláudio H.B.(my brother), Zoraide B.B.(my mother),
    Gilberto C.P.B.(my father) and particularly, to God !
    
