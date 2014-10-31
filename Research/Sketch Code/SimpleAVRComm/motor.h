/*    ATmega8 mikrovezerlo labkiosztas
 
                                +--------------+
                        RESET  -|1       PC5 28|-
                               -|2 PD0   PC4 27|-
                               -|3 PD1   PC3 26|-
                 Nyomogomb     -|4 PD2   PC2 25|-
              Mikrokapcs. jobb -|5 PD3   PC1 24|-
            Mikrokapcs. bal    -|6 PD4   PC0 23|-
                         VCC   -|7 22          |- GND
                        GND    -|8 21          |- AREF
                       (xtal)  -|9 PB6       20|- AVCC
                       (xtal)  -|10 PB7  PB5 19|- ISP(SCK)
                      Motor2 A -|11 PD5  PB4 18|- ISP(MISO)
                      Motor2 B -|12 PD6  PB3 17|- ISP(MOSI), servo PWM
                      Motor1 A -|13 PD7  PB2 16|- Motor2 PWM
                      Motor1 B -|14 PB0  PB1 15|- Motor1 PWM
                                +--------------+
 
L293D motorvezerlo IC labkiosztas
 
                                  +---------------+
                      Motor1 PWM -| 1 1-2EN  5V 16|- VCC
                        Motor1 A -| 2 BE1   BE4 15|- Motor2 B
                       Motor1(+) -| 3 KI1   KI4 14|- Motor2(-)
                             GND -| 4 GND   GND 13|- GND
                             GND -| 5 GND   GND 12|- GND 
                       Motor1(-) -| 6 KI2   KI3 11|- Motor2(+)
                        Motor1 B -| 7 BE2   BE3 10|- Motor2 A
                 Motor Fesz.(6V) -| 8 VMo  3-4EN 9|- Motor2 PWM
                                  +---------------+
*/
//---------------------------------------------------------------------
 
#include <avr/io.h>
#include <stdlib.h>
 
#define mind 3         // mindket motor
#define Motor1A PD7     // Motor1A = PD7
#define Motor1B PB0     // Motor1B = PB0
#define Motor2A PD5     // Motor2A = PD5
#define Motor2B PD6     // Motor2B = PD6
 
unsigned char _duty1=0,_duty2=0;         /* motor 1 es 2 sebesseget (PWM kitolsesi tenyezot) allito valtozo */
char pwm_ini=0;
 
char be_b(char _bit)     // be_b(x) fuggveny definialasa PORTB-re
{
          DDRB &= ~(1<<_bit);     // PORTB x. lab bemenet
          return ((PINB & _BV(_bit))>>_bit);     /* PORTB x. lab ertekenek beolvasasa (0 vagy 1)*/
}
 
char be_c(char _bit)     // ugyan az mint az elozo fuggveny, de PORTC-re
{
          DDRC &= ~(1<<_bit);
          return ((PINC & _BV(_bit))>>_bit);
}
 
char be_d(char _bit)     // be_d(x) fuggveny definialasa PORTD-re
{
            DDRD &= ~(1<<_bit);     // PORTB x. lab bemenet
            return ((PIND & _BV(_bit))>>_bit);
}
 
void ki_b(char _bit,char _dat)     /* ki_b(x,y) fuggveny definialasa PORTB-re. PORTB x. labara 0V-ot vagy 5V-ot adunk, attol fuggoen hogy y erteke 0 vagy 1 */
{
          DDRB |= _BV(_bit);     // PORTB x. lab kimenet
            if(_dat)
                 PORTB |= _BV(_bit);     // ha y=1, az x. labra 5V-ot ad
            else
                PORTB &= ~_BV(_bit);     // ha y=0, az x. labra 5V-ot ad
}
 
void ki_c(char _bit,char _dat)     /* ki_c(x,y) fuggveny definialasa PORTC-re */
{
          DDRC |= _BV(_bit);
          if(_dat)
               PORTC |= _BV(_bit);
          else
              PORTC &= ~_BV(_bit);
}
 
void ki_d(char _bit,char _dat)     /* ki_d(x,y) fuggveny definialasa PORTD-re */
{
          DDRD |= _BV(_bit);
            if(_dat)
                PORTD |= _BV(_bit);
            else
                PORTD &= ~_BV(_bit);
}
 
void pwm_init()         //Timer1 PWM beallitasa
{
             TCCR1A |= (1<<WGM10);     //8 bites fazishelyes PWM
             TCCR1B |= (1<<CS10);         //elooszto = FCPU/1
}
 
void pwm(char _channel,unsigned int _duty)     /* pwm(a,b) fuggveny definialasa. a = 1 vagy 2 attol fuggoen hogy melyik motor, b = 0 &ndash; 100% (PWM kitoltesi tenyezo) */
{
          _duty = (_duty*255)/100;         /*motor sebesseg konvertalasa 0-100%-rol 0-255-re */
          if(pwm_ini==0)
             {
                pwm_init();
                pwm_ini=1;
             }
          if(_channel==1)
            {
                TCCR1A |= _BV(COM1A1);     //nem-invertalt PWM, A csatorna
                DDRB |= _BV(PB1);     // PORTB PB1 lab kimenet
                OCR1A = _duty;         // motor1 pwm kitoltesi tenyezo
                _duty1 = _duty;
            }
          else if(_channel==2)
             {
                TCCR1A |= _BV(COM1B1);     //nem-invertalt PWM, B csatorna
                DDRB |= _BV(PB2);         // PORTB PB2 lab kimenet
                OCR1B = _duty;         // motor2 pwm kitoltesi tenyezo
               _duty2 = _duty;
             }
          else if(_channel==3)
            {
               TCCR1A |= _BV(COM1A1);     //nem-invertalt PWM, A csatorna
               DDRB |= _BV(PB1);
               OCR1A = _duty;
               _duty1 = _duty;
               TCCR1A |= _BV(COM1B1);     //nem-invertalt PWM, B csatorna
               DDRB |= _BV(PB2);
               OCR1B = _duty;
               _duty2 = _duty;
           }
}
 
void motor(char _channel,int _power)     /* motor(a,b) fuggveny definialasa. a = 1 vagy 2 attol fuggoen hogy melyik motor, b = -100% &ndash; 100% (motor sebesseg) */
{
            if(_power>0)     // ha b (motor sebesseg) > 0, motor elore
            {
               pwm(_channel,_power);     // motor PWM bekapcsol
               if(_channel==1)         // ha a=1 (motor1 elore)
                     {
                         ki_d(Motor1A,1);
                         ki_b(Motor1B,0);
                     }
              else if(_channel==2)     // ha a=2 (motor2 elore)
                   {
                        ki_d(Motor2A,0);
                        ki_d(Motor2B,1);
                   }
           }
          else     // ha b (motor sebesseg) < 0, motor hatra
          {
              pwm(_channel,abs(_power));     // motor PWM bekapcsol
              if(_channel==1)         // ha a=1 (motor1 hatra)
              {
                 ki_d(Motor1A,0);
                 ki_b(Motor1B,1);
              }
            else if(_channel==2)     // ha a=2 (motor2 hatra)
            {
                ki_d(Motor2A,1);
                ki_d(Motor2B,0);
            }
         }
}
 
void motor_stop(char _channel)         /* motor_stop(a) fuggveny definialasa. a = 1, 2 vagy mind (3) attol fuggoen hogy melyik motort akarjuk megallitani */
{
           pwm(_channel,0);     // motor PWM kikapcsol
           if(_channel==1 ||_channel==3)     //motor1 stop
           {
                  ki_d(Motor1A,0);
                  ki_b(Motor1B,0);
           }
          if(_channel==2 ||_channel==3)     //motor2 stop
          {
                 ki_d(Motor2A,0);
                ki_d(Motor2B,0);
          }
}
 
void motor_ki()
{
           pwm(3,0);     // motor PWM kikapcsol, motor1 es 2 stop
           ki_d(Motor1A,0);
           ki_b(Motor1B,0);
           ki_d(Motor2A,0);
           ki_d(Motor2B,0);
}
 
void fordul_bal(int speed)     /* elore(z) fuggveny definialasa, mindket motor elore, z = 0-100% */
{
           motor(1,speed);
           motor(2,speed);
}
 
void fordul_jobb(int speed)     /* hatra(y) fuggveny definialasa, mindket motor hatra, y = 0-100% */
{
           motor(1,speed*-1);
           motor(2,speed*-1);
}
 
void elore(int speed)         /* fordul_bal(n) fuggveny definialasa, balra fordulas: motor1 elore, motor2 hatra, n = 0-100% */
{
           motor(1,speed);
           motor(2,speed*-1);
}
 
void hatra(int speed)     /* fordul_jobb(m) fuggveny definialasa, jobbra fordulas: motor1 hatra, motor2 elore, m = 0-100% */
{
           motor(1,speed*-1);
           motor(2,speed);
}
