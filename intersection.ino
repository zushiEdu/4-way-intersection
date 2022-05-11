
int counter = 0;
int state = 0;
int cycleLength = 20;
int tickLength = 1000;

int startingOutputPin = 2;
int endingOutputPin = 8;

int yellowLeadTime = 10;

int overrideState = LOW;

int buttonState;

void setup()
{
    for (int i = startingOutputPin; i <= endingOutputPin; i++)
    {
        pinMode(i, OUTPUT);
    }

    pinMode(9, INPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(12, OUTPUT);
    
    Serial.begin(9600);
}

void loop()
{
    // Green and Red Light Control
    if (state == 0){
      // Vertical Going Light
      digitalWrite(8, HIGH);
      digitalWrite(7, LOW);
      digitalWrite(4, LOW);

      // Horizontal Going Light
      digitalWrite(2, LOW);

      analogWrite(3, 255); //RED
      analogWrite(5, 0); //GREEN
      analogWrite(6, 0); // BLUE
      
      if (counter < (cycleLength - yellowLeadTime)){
        // Green light horizontal on
        digitalWrite(11, HIGH);
        digitalWrite(12, LOW);
      } else {
        // yellow light
        digitalWrite(11, LOW);
        digitalWrite(12, HIGH);
      }
    } else if (state == 1){
      // Horizontal Going Light
      digitalWrite(2, HIGH);
      digitalWrite(12, LOW);
      digitalWrite(11, LOW);

      // Vertical Going Light
      digitalWrite(8, LOW);

      analogWrite(3, 255);
      analogWrite(5, 255);
      analogWrite(6, 255);
      if (counter < (cycleLength - yellowLeadTime)){
        // Green light vertial on
        digitalWrite(4, HIGH);
        digitalWrite(7, LOW);
      } else {
        digitalWrite(4, LOW);
        digitalWrite(7, HIGH);

        analogWrite(3, 255);
        analogWrite(5, 255);
        analogWrite(6, 0);
      }
    }
  
    // Counter Logic
    if (counter < cycleLength)
    {
        counter++;
    }
    else
    {
      if (overrideState == HIGH){
        state = 1;
        overrideState = LOW;
      } else {
        if (state == 0)
        {
            state = 1;
        }
        else if (state == 1)
        {
            state = 0;
        }
      }
      counter = 0;
    }

    buttonState = digitalRead(9);
    if (buttonState == HIGH){
      overrideState = HIGH;
    }

    digitalWrite(10, overrideState);

    // Per Cycle Logic
    delay(tickLength);
}
