int MRF = 11; //pin 1 motor1 
int MRB = 10; //pin 2 motor1
int MLF = 9; //pin 1 motor2
int MLB = 6; //pin 2 motor2

//5 WAY IR SENSOR PINS
#define ir1 A0
#define ir2 A1
#define ir3 A2
#define ir4 A3
#define ir5 A4
//ULTRASONIC  
int trigPin = 5;
int echoPin = 4;


//DIODES
int d1 = 3; //RED DIODE 
int d2 = 2; //GREEN DIODE

//SPEEDS
int VF = 199; //FORWARD SPEED
int VB = 199; //BACKWARD SPEED 

//TURN RIGHT
void right()
{
  analogWrite(MRF, 0);
  analogWrite(MRB, VB);
  analogWrite(MLF, VF);
  analogWrite(MLB, 0); 
}
//TURN LEFT
void left()
{
  analogWrite(MRF, VF);
  analogWrite(MRB, 0);
  analogWrite(MLF, 0);
  analogWrite(MLB, VB); 
}
//GO FORWARD
void forward()
{
  analogWrite(MRF, VF);
  analogWrite(MRB, 0);
  analogWrite(MLF, VF);
  analogWrite(MLB, 0); 
}
//GO BACKWARD
void backward()
{
  analogWrite(MRF, 0);
  analogWrite(MRB, VB);
  analogWrite(MLF, 0);
  analogWrite(MLB, VB); 
}
//STOP
void stop()
{
  analogWrite(MRB, 0);
  analogWrite(MLB, 0);
  analogWrite(MRF, 0);
  analogWrite(MLF, 0); 
}

void setup() {
  pinMode(MRF, OUTPUT);
  pinMode(MRB, OUTPUT);
  pinMode(MLF, OUTPUT);
  pinMode(MLB, OUTPUT);
  pinMode(d1, OUTPUT);
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);
  pinMode(ir5, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}
int l0=0;
int l1=0;
int l2=0;
int l3=0;
int l4=0;
int flag = 0;
int step = 2;
int follow_bk;
int done = 0;
void loop() {
  //Reading Sensor Values
  int s1 = digitalRead(ir1);  //Left Most Sensor
  int s2 = digitalRead(ir2);  //Left Sensor
  int s3 = digitalRead(ir3);  //Middle Sensor
  int s4 = digitalRead(ir4);  //Right Sensor
  int s5 = digitalRead(ir5);  //Right Most Sensor
  //NORMALLY WHITE=0 BLACK=1 
  if (step == 0) {
    if (s1 == 1 && s5 ==1 && flag ==1) { //COLOR SWITCH //FLAG ADDED TO NOT CONFUSE START LINE
      step = 1;
    }else {
      follow_bk = !s1*10000+!s2*1000+!s3*100+!s4*10+!s5*1;  //BLACK=0 WHITE=1
      switch(follow_bk) {        
        //FORWARD CASE
        case 11011:
          forward();
          break;
        //LEFT CASES
        case 11:
          left();
          break;
        case 111:
          left();
          break;
        case 1111:
          left();
          break;
        //RIGHT CASES
        case 11000:
          right();
          break;
        case 11100:
          right();
          break;
        case 11110:
          right();
          break;
        //SLIGHT CORRECTIONS
        case 10011:
          left();
          break;
        case 10111:
          left();
          break;
        case 11001:
          right();
          break;
        case 11101:
          right();
          break;
        //SPECIALS CASES PER STEP
        case 10001://PROBABLY WONT HAPPEN BUT WHO KNOWS
          forward();
          break;
        case 11111://ALL WHITE = FORWARD 
          forward();
          break;
        case 0://ALL BLACK = FORWARD (START LINE)  
          forward();
          delay(500);
          flag = 1;
          break;     
      }
    }
  }else if (step == 1) {
    follow_bk = s1*10000+s2*1000+s3*100+s4*10+s5*1;  //BLACK=1 WHITE=0
    if ((follow_bk == 100) || ((l0+l1+l2+l3+l4 < 2) && (follow_bk == 1100 || follow_bk==110||follow_bk==1000))) { //BACK TO WHITE
      step = 2;
    }else {
      switch(follow_bk) {        
        //FORWARD CASE
        case 11011:
          l0=l1;
          l1=l2;
          l2=l3;
          l3=l4;
          l4=0;
          forward();
          break;
        //LEFT CASES
          case 11:
          l0=l1;
          l1=l2;
          l2=l3;
          l3=l4;
          l4=3;
          left();
          break;
        case 111:
          l0=l1;
          l1=l2;
          l2=l3;
          l3=l4;
          l4=3;
          left();
          break;
        case 1111:
          l0=l1;
          l1=l2;
          l2=l3;
          l3=l4;
          l4=3;
          left();
          break;
        //RIGHT CASES
        case 11000:
          l0=l1;
          l1=l2;
          l2=l3;
          l3=l4;
          l4=3;
          right();
          break;
        case 11100:
          l0=l1;
          l1=l2;
          l2=l3;
          l3=l4;
          l4=3;
          right();
          break;
        case 11110:
          l0=l1;
          l1=l2;
          l2=l3;
          l3=l4;
          l4=3;
          right();
          break;
        //SLIGHT CORRECTIONS
        case 10011:
          l0=l1;
          l1=l2;
          l2=l3;
          l3=l4;
          l4=0;
          forward();
          break;
        case 10111:
          l0=l1;
          l1=l2;
          l2=l3;
          l3=l4;
          l4=1;
          left();
          break;
        case 11001:
          l0=l1;
          l1=l2;
          l2=l3;
          l3=l4;
          l4=0;
          forward();
          break;
        case 11101:
          l0=l1;
          l1=l2;
          l2=l3;
          l3=l4;
          l4=1;
          right();
          break;
        //SPECIALS CASES PER STEP
        case 10001://ROUND ABOUT:
          l0=l1;
          l1=l2;
          l2=l3;
          l3=l4;
          l4=3;
          right();
         delay(320);
         break;
        case 0:
          do {
            s1 = digitalRead(ir1);  //Left Most Sensor
            s2 = digitalRead(ir2);  //Left Sensor
            s3 = digitalRead(ir3);  //Middle Sensor
            s4 = digitalRead(ir4);  //Right Sensor
            s5 = digitalRead(ir5);  //Right Most Sensor 
            int z = s1*10000+s2*1000+s3*100+s4*10+s5*1;
            if (z == 10001) {
              l0=l1;
              l1=l2;
              l2=l3;
              l3=l4;
              l4=0;
              forward();
            }else {
              l0=l1;
              l1=l2;
              l2=l3;
              l3=l4;
              l4=3;
              right();
            } 
          }while((s1 == 0 || s2 == 1 || s3 ==1 || s4 ==0 || s5 ==0) && (s1 == 0 || s2 == 0|| s3 ==1 || s4 ==1 || s5 ==0) &&(s1 == 1 || s2 == 1|| s3 ==1 || s4 ==1 || s5 ==1));
          break;
        case  11111:
          do {
            s1 = digitalRead(ir1);  //Left Most Sensor
            s2 = digitalRead(ir2);  //Left Sensor
            s3 = digitalRead(ir3);  //Middle Sensor
            s4 = digitalRead(ir4);  //Right Sensor
            s5 = digitalRead(ir5);  //Right Most Sensor 
            l0=l1;
            l1=l2;
            l2=l3;
            l3=l4;
            l4=3;
            right(); 
          }while((s1 == 0 || s2 == 0 || s3 ==1 || s4 ==1 || s5 ==0) && (s1 == 0 || s2 == 1|| s3 ==1 || s4 ==0 || s5 ==0));
          break;
      }
    } 
  }else if (step == 2) {
    if (done == 1) {
      forward();
      delay(420);
      s1 = digitalRead(ir1);  //Left Most Sensor
      s2 = digitalRead(ir2);  //Left Sensor
      s3 = digitalRead(ir3);  //Middle Sensor
      s4 = digitalRead(ir4);  //Right Sensor
      s5 = digitalRead(ir5);  //Right Most Sensor 
      follow_bk = !s1*10000+!s2*1000+!s3*100+!s4*10+!s5*1;  //BLACK=0 WHITE=1
      switch(follow_bk) {        
        //FORWARD CASE
        case 11011:
          forward();
          break;
        //LEFT CASES
        case 11:
          left();
          break;
        case 111:
          left();
          break;
        case 1111:
          left();
          break;
        //RIGHT CASES
        case 11000:
          right();
          break;
        case 11100:
          right();
          break;
        case 11110:
          right();
          break;
        //SLIGHT CORRECTIONS
        case 10011:
          left();
          break;
        case 10111:
          left();
          break;
        case 11001:
          right();
          break;
        case 11101:
          right();
          break;
        //SPECIALS CASES PER STEP
        case 0://ALL BLACK = FORWARD (START LINE)  
          stop();
          delay(300000);  
      }
    }else {
      VF = 130;
      VB = 130;
      int pk = 0;
      int counter = 0;
      int correct = 0;
      //1st do while to get the 1st horizontal
      do{
        Serial.println("trying to get to horizontal 1st");
        s1 = digitalRead(ir1);  //Left Most Sensor    
        s2 = digitalRead(ir2);  //Left Sensor
        s3 = digitalRead(ir3);  //Middle Sensor
        s4 = digitalRead(ir4);  //Right Sensor
        s5 = digitalRead(ir5);  //Right Most Sensor
        follow_bk = !s1*10000+!s2*1000+!s3*100+!s4*10+!s5*1; //BLACK=0 WHITE=1
        switch (follow_bk) {
          //FORWARD CASE
          case 11011:        
            forward();
            break;
          //SLIGHT CORRECTIONS
          case 10011:
            left();
            break;
          case 10111:
            left();
            break;
          case 11001:
            right();
            break;
          case 11101:
            right();
            break;
        }
      }while(!(follow_bk == 0));
      //2secs stop after horizontal
      stop();
      delay(2000);
      //MAIN DO WHILE (TRIPLE CHECK)
      do{
        Serial.println("GOT IN TRIPLE");
        forward();  
        float duration, distance; 
        float somme = 0;
        int correct = 0;
        counter +=1;
        //SECONDARY DO WHILE TO GET TO TURN
        do {
          s1 = digitalRead(ir1);  //Left Most Sensor
          s2 = digitalRead(ir2);  //Left Sensor
          s3 = digitalRead(ir3);  //Middle Sensor
          s4 = digitalRead(ir4);  //Right Sensor
          s5 = digitalRead(ir5);  //Right Most Sensor
          Serial.println("loop get to turn");
          follow_bk = !s1*10000+!s2*1000+!s3*100+!s4*10+!s5*1; //BLACK=0 WHITE=1 
          switch (follow_bk) {
            //FORWARD CASE
            case 11011:
              forward();
              break;
            //SLIGHT CORRECTIONS
            case 10011:
              left();
              break;
            case 10111:
              left();
              break;
            case 11001:
              right();
              break;
            case 11101:
              right();
              break;
            case 0:
              forward();
              delay(30);
              break;
          }
        }while(!(follow_bk == 111 || follow_bk == 11));
        
        //secondary do while over   
        //mini delay to get sensor aligned
        forward();
        delay(150);
        stop();
        Serial.println("stopped o test");
        //ULTRASONIC READING
        for (int i = 0; i < 21; i++) {
            digitalWrite(trigPin, LOW);
            delayMicroseconds(2);
            digitalWrite(trigPin, HIGH);
            delayMicroseconds(10);
            digitalWrite(trigPin, LOW);
            duration = pulseIn(echoPin, HIGH);
            distance = (duration * 0.343) / 2;
            Serial.println("distance:  ");
            Serial.print(distance);
            if (distance > 180 && distance < 1900) { 
              somme = somme + distance;
              correct = correct + 1;
            }      
        }
        Serial.println("somme: ");
        Serial.print(somme);
        Serial.println("corect times: ");
        Serial.print(correct);
        float averageRead = somme / correct;
        Serial.println("average read: ");
        Serial.print(averageRead);
        if (averageRead > 380) {
          Serial.println("EMPTY CASE PLS");
          //turn left with lane
          do{
            Serial.println("left to center");
            s1 = digitalRead(ir1);  //Left Most Sensor
            s2 = digitalRead(ir2);  //Left Sensor
            s3 = digitalRead(ir3);  //Middle Sensor
            s4 = digitalRead(ir4);  //Right Sensor
            s5 = digitalRead(ir5);  //Right Most Sensor
            follow_bk = !s1*10000+!s2*1000+!s3*100+!s4*10+!s5*1; //bk 0 wh 1
            left();
            delay(320);
          }while(!(follow_bk == 10011 || follow_bk == 11001));
          //forward till full black
          do {
            s1 = digitalRead(ir1);  //Left Most Sensor
            s2 = digitalRead(ir2);  //Left Sensor
            s3 = digitalRead(ir3);  //Middle Sensor
            s4 = digitalRead(ir4);  //Right Sensor
            s5 = digitalRead(ir5);  //Right Most Sensor
            follow_bk = !s1*10000+!s2*1000+!s3*100+!s4*10+!s5*1; //bk 0 wh 1
            switch (follow_bk) {
              //FORWARD CASE
              case 11011:
                forward();
                break;
              //SLIGHT CORRECTIONS
              case 10011:
                left();
                break;
              case 10111:
                left();
                break;
              case 11001:
                right();
                break;
              case 11101:
                right();
                break;
            }
          }while(!(follow_bk == 0));
          stop();
          digitalWrite(d1, HIGH);
          delay(5000);
          digitalWrite(d2, HIGH);
          digitalWrite(d1, LOW);
          delay(2000);
          digitalWrite(d2, LOW);
          do{
            s1 = digitalRead(ir1);  //Left Most Sensor
            s2 = digitalRead(ir2);  //Left Sensor
            s3 = digitalRead(ir3);  //Middle Sensor
            s4 = digitalRead(ir4);  //Right Sensor
            s5 = digitalRead(ir5);  //Right Most Sensor
            follow_bk = !s1*10000+!s2*1000+!s3*100+!s4*10+!s5*1; //bk 0 wh 1
            left();
          }while(!(follow_bk == 11011));
          do {
            s1 = digitalRead(ir1);  //Left Most Sensor
            s2 = digitalRead(ir2);  //Left Sensor
            s3 = digitalRead(ir3);  //Middle Sensor
            s4 = digitalRead(ir4);  //Right Sensor
            s5 = digitalRead(ir5);  //Right Most Sensor
            follow_bk = !s1*10000+!s2*1000+!s3*100+!s4*10+!s5*1; //bk 0 wh 1
            switch (follow_bk) {
              //FORWARD CASE
              case 11011:
                forward();
                break;
              //SLIGHT CORRECTIONS
              case 10011:
                left();
                break;
              case 10111:
                left();
                break;
              case 11001:
                right();
                break;
              case 11101:
                right();
                break;
            }
          }while(!(follow_bk == 0));
          do{
            s1 = digitalRead(ir1);  //Left Most Sensor
            s2 = digitalRead(ir2);  //Left Sensor
            s3 = digitalRead(ir3);  //Middle Sensor
            s4 = digitalRead(ir4);  //Right Sensor
            s5 = digitalRead(ir5);  //Right Most Sensor
            follow_bk = !s1*10000+!s2*1000+!s3*100+!s4*10+!s5*1; //bk 0 wh 1
            left();
          }while(!(follow_bk == 10011 || follow_bk == 11001 || follow_bk == 111));*/
          done =1;
          pk =1;
        }
      }while(!(pk || counter == 3));
      if (counter == 3) {
        done =1;  
      }
    }     
  }
}
