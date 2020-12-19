//telhado retratil

#include "pic18f4520.h"
#include "config.h"
#include "atraso.h"
#include "lcd.h"
#include "adc.h"
#include "i2c.h"
#include "pwm.h"
#include "bits.h"

void itoa(unsigned int val, char* str);

void main() {

    unsigned char tmp, temp;
    char str[6],grau = 223;
    
    
    ADCON1 = 0x06;
    TRISA = 0xC3;
    TRISB = 0x00;
    TRISC = 0x00;
    TRISD = 0x00;
    TRISE = 0x00;

    lcd_init();
    adc_init();
    pwmInit();

    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("Init Sistema");

    

    for (;;) {

        tmp = (adc_amostra(0)*10) / 204;
        lcd_cmd(L_L2 + 1);

        itoa(tmp, str);
        temp = str[3];


        if (temp == 48 && temp <= 50) {
            pwmSet1(92);
            lcd_str("Abrindo");
            BitSet(PORTB, 1);
            BitClr(PORTB, 2);
            BitClr(PORTB, 3);
        }
        if (temp <= 52 && temp > 50) {
            pwmSet1(92);
            lcd_str("Fechando");
            BitSet(PORTB, 1);
            BitSet(PORTB, 2);
            BitClr(PORTB, 3);
        }
        if (temp <= 53 && temp > 52) {
            pwmSet1(0);
            lcd_str("Fechando ");
            BitSet(PORTB, 1);
            BitSet(PORTB, 2);
            BitSet(PORTB, 3);
        }

        lcd_dat(str[3]);
        lcd_dat('V');
        lcd_dat(' ');
        lcd_dat(str[3]);
        lcd_dat(str[4]);
        lcd_dat(grau);
        lcd_dat('C');

        atraso_ms(10);
    }
}

void itoa(unsigned int val, char* str) {
    str[0] = (val / 10000) + 0x30;
    str[1] = ((val % 10000) / 1000) + 0x30;
    str[2] = ((val % 1000) / 100) + 0x30;
    str[3] = ((val % 100) / 10) + 0x30;
    str[4] = (val % 10) + 0x30;
    str[5] = 0;
}
