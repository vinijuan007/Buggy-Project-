#include "mbed.h"
#include "QEI.h"
#include "C12832.h"

C12832 lcd(D11, D13, D12, D7, D10);

class Encoder_Count{
protected:
QEI* REncoder;
QEI* LEncoder;
int pulse_a;
int pulse_b;

public:
Encoder_Count(QEI* r, QEI* l): REncoder(r), LEncoder(l){
    REncoder->reset();
    LEncoder->reset();
  
}

void get_pulses(void){
    pulse_a = REncoder->getPulses();
    pulse_b = LEncoder->getPulses();

}

void printRM(void){
    lcd.locate(0,3);
    lcd.printf("A");
    lcd.locate(15,3);
    lcd.printf("%d ", pulse_a);
}

void printLM(){
    lcd.locate(0,14);
    lcd.printf("B");
    lcd.locate(15,14);
    lcd.printf("%d ", pulse_b);
}

};


int main(){

    QEI* Right_Encoder = new QEI(PC_8,PC_6, NC, 1024, QEI::X4_ENCODING);
    QEI* Left_Encoder = new QEI(PB_15,PB_14, NC, 1024 , QEI::X4_ENCODING);
    Encoder_Count Encoders(Right_Encoder, Left_Encoder);
     while (1) {
         Encoders.get_pulses();
         Encoders.printRM();
         Encoders.printLM();
         wait(0.5);
     };
      
} 