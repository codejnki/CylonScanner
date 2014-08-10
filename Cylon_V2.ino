const int buttonPin = 30;  //Using the Mega 2560
const int ledPin = 13;
const int ledDelay = 75;

int leds[] = { 2, 3, 4, 5, 6, 7, 8, 9 };
int len = sizeof(leds) / sizeof(int);

int ledState = HIGH;
int buttonState;
int lastButtonState = LOW;
int currentLed = 0;    // Which led in the array are we currently showing
int ledMotion = 0;     // 0 == Off , 1 == Motion
int ledDirection = 1;  // 1 == Increasing Counter, 0 == Decreasing counter
int led13State = 0;

long lastDebounceTime = 0;
long debounceDelay = 50;
long previousMillis = 0;

void setup()
{
	pinMode(buttonPin, INPUT);
	pinMode(ledPin, OUTPUT);
	
	for (int thisPin = 0; thisPin < len; thisPin++)
	{
		pinMode(leds[thisPin], OUTPUT);
	}
	
	// Serial.begin(9600);
	// Serial.println(len);
}

void loop()
{
	// read the state of the switch
	int reading = digitalRead(buttonPin);
	unsigned long currentMillis = millis();
	
	// check to see if button was just pressed
	// and if we've waited long enough to ignore noise
	if(reading != lastButtonState)
	{
		// reset the debounce time
		lastDebounceTime = millis();
	}
	
	if((millis() - lastDebounceTime) > debounceDelay)
	{
		// what ever the reading is at it has been
		// there longer than the delay
		
		if(reading != buttonState)
		{
			buttonState = reading;
			
			if(buttonState == HIGH)
			{
				ledMotion = !ledMotion;
			}
		}
	}
	
	if(ledMotion)
	{
			if(currentMillis - previousMillis > ledDelay)
			{
				// enough delay has passed time to cycle a LED
				// save our current time
				previousMillis = currentMillis;

				// turn off the current led
				digitalWrite(leds[currentLed], LOW);
				
				if (ledDirection)
				{
					currentLed++;
					if (currentLed == len - 1)
					{
						// we've reached the end, time to switch directions
						// subtract off led to make it look smoother
						currentLed--;
						ledDirection = !ledDirection;
					}
				}
				else
				{
					currentLed--;
					if(currentLed == 0)
					{
						// we've reached the end, time to switch directions
						ledDirection = !ledDirection;
					}          
				}
				
				// turn on our new led
				digitalWrite(leds[currentLed], HIGH);
			}      
		}
		else
		{
			// we've turned off the motion so shut down all the LED's
			// we could probably just turn off the current one, but this cleans it up nicely
			
			for (int thisPin = 0; thisPin < len; thisPin++)
			{
				digitalWrite(leds[thisPin], LOW );
			}
		}
	
	lastButtonState = reading;
}
	
		
