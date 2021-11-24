#include <Arduino.h>


typedef struct Display
{
    int num[7];
    int dot;
    int index[4];

    int num_mask[10][7] = {
        {1, 1, 1, 1, 1, 1, 0}, //0
        {0, 1, 1, 0, 0, 0, 0}, //1
        {1, 1, 0, 1, 1, 0, 1}, //2
        {1, 1, 1, 1, 0, 0, 1}, //3
        {0, 1, 1, 0, 0, 1, 1}, //4
        {1, 0, 1, 1, 0, 1, 1}, //5
        {1, 0, 1, 1, 1, 1, 1}, //6
        {1, 1, 1, 0, 0, 0, 0}, //7
        {1, 1, 1, 1, 1, 1, 1}, //8
        {1, 1, 1, 1, 0, 1, 1}, //9
    };

    void set(int num[7], int dot, int index[4]){
        for (int i = 0; i < 7; i++)
        {
            this->num[i] = num[i];
            pinMode(num[i], OUTPUT);
        }
        this->dot = dot;
        pinMode(dot, OUTPUT);
        for (int i = 0; i < 4; i++)
        {
            this->index[i] = index[i];
            pinMode(index[i], OUTPUT);
        }
    }

    void display_8_seg(int number, int indx){

        for (int i = 0; i < 7; i++) {
            digitalWrite(this->num[i], this->num_mask[number][i]);
        }

        for(int i = 0; i < 4; i++) {
            digitalWrite(this->index[i], 1);
            if(i == indx) {
                digitalWrite(this->index[i], 0);
            }
        }

    }

    void display_4_digit_nuber(int number) {
        this->display_8_seg(number/1000, 0);
        delay(5);
        this->display_8_seg((number%1000)/100, 1);
        delay(5);
        this->display_8_seg((number%100)/10, 2);
        delay(5);
        this->display_8_seg(number%10, 3);
        delay(5);
    }

    void roll(int speed){


        int roll_mask[6][7] = {
            {1, 0, 0, 0, 0, 0, 0}, //top
            {0, 1, 0, 0, 0, 0, 0}, //tr
            {0, 0, 1, 0, 0, 0, 0}, //br
            {0, 0, 0, 1, 0, 0, 0}, //bottom
            {0, 0, 0, 0, 1, 0, 0}, //bl
            {0, 0, 0, 0, 0, 1, 0}, //tl
        };

        for(int i = 0; i <= 6; i++) {
            digitalWrite(this->num[i], LOW);
        }
        for(int i = 0; i <= 3; i++) {
            digitalWrite(this->index[i], HIGH);
        }

        //FIRST DIGIT
        digitalWrite(this->index[0], LOW);

        digitalWrite(this->num[3], HIGH); //D
        delay(speed);
        digitalWrite(this->num[3], LOW);
        digitalWrite(this->num[4], HIGH); //E
        delay(speed);
        digitalWrite(this->num[4], LOW);
        digitalWrite(this->num[5], HIGH); //F
        delay(speed);
        digitalWrite(this->num[5], LOW);
        digitalWrite(this->num[0], HIGH); //A
        delay(speed);

        //SECOND DIGIT
        digitalWrite(this->index[0], HIGH);
        digitalWrite(this->index[1], LOW);

        delay(speed);                 //A

        //THIRD DIGIT
        digitalWrite(this->index[1], HIGH);
        digitalWrite(this->index[2], LOW);

        delay(speed);                 //A

        //FOURTH DIGIT
        digitalWrite(this->index[2], HIGH);
        digitalWrite(this->index[3], LOW);

        delay(speed);
        digitalWrite(this->num[0], LOW);
        digitalWrite(this->num[1], HIGH); //B
        delay(speed);
        digitalWrite(this->num[1], LOW);
        digitalWrite(this->num[2], HIGH); //C
        delay(speed);
        digitalWrite(this->num[2], LOW);
        digitalWrite(this->num[3], HIGH); //D
        delay(speed);

        //FIFTH DIGIT
        digitalWrite(this->index[3], HIGH);
        digitalWrite(this->index[2], LOW);

        delay(speed);                 //D

        //SIXTH DIGIT
        digitalWrite(this->index[2], HIGH);
        digitalWrite(this->index[1], LOW);

        delay(speed);                 //D
    }


} display;



// void draw_custom_char(int* custom_char, int pos){
//     for(int i = 0; i < 7; i++) {
//         digitalWrite(num[i], custom_char[i]);
//     }
//     for(int i = 0; i < 4; i++) {
//         digitalWrite(index[i], HIGH);
//         if(i == pos) {
//             digitalWrite(index[i], LOW);
//         }
//     }
//     delay(5);
//     for(int i = 0; i < 4; i++) {
//         digitalWrite(index[i], HIGH);
//     }
// }