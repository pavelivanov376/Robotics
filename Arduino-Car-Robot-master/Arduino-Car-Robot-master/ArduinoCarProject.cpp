int in1=2;
int enable=3;
int in2=5;
int in4=4;
int in3=6;
int inPin1 = 7;
int inPin2 = 8;
int val1 = 0;
int val2 = 0;
void turnLeft()
{
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
}
void turnRight()
{
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
}
void goStraight()
{
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
}
void setup() {
      pinMode(in1, OUTPUT);
      pinMode(in2, OUTPUT);
      pinMode(in3, OUTPUT);
      pinMode(in4, OUTPUT);
      pinMode(enable, OUTPUT);
      pinMode(inPin1, INPUT);
      pinMode(inPin2, INPUT);
      digitalWrite(enable,HIGH);
}

void loop() {
      val1 = digitalRead(inPin1);
      val2 = digitalRead(inPin2);
      if(val1>val2){turnLeft();}
      else if (val1<val2){turnRight();}
      else if (val1==val2){goStraight();}
      delay(4000);
}
