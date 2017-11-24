int red = 11;
int blue = 10;
int green = 9;
int brightness = 100;
int r;
int g;
int b;
int color;
bool hack;
String readString, s1, s2, s3, rs1, rs2, rs3, code;
void setup() {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
  digitalWrite(blue, LOW);
  Serial.begin(9600);
  Serial.println("ready");
}

void loop() {
  rainbow();
}
void f_HSV_to_RGB(int hue, int sat, int val)
{
  int base;
  if (sat == 0) {
    r = val;
    g = val;
    b = val;
  } else {
    base = ((255 - sat) * val) >> 8;
    switch (hue / 60) {
      case 0: {
        r = val;
        g = (((val - base) * hue) / 60) + base;
        b = base;
        break;
      }
      case 1: {
        r = (((val - base) * (60 - (hue % 60))) / 60) + base;
        g = val;
        b = base;
        break;
      }
      case 2: {
        r = base;
        g = val;
        b = (((val - base) * (hue % 60)) / 60) + base;
        break;
      }
      case 3: {
        r = base;
        g = (((val - base) * (60 - (hue % 60))) / 60) + base;
        b = val;
        break;
      }
      case 4: {
        r = (((val - base) * (hue % 60)) / 60) + base;
        g = base;
        b = val;
        break;
      }
      case 5: {
        r = val;
        g = base;
        b = (((val - base) * (60 - (hue % 60))) / 60) + base;
        break;
      }
      case 6: {
        r = val;
        g = 0;
        b = base;
        break;
      }
    }
  }
}
void rainbow() {
  if (hack) {
    for (int i = 0; i<360; i++) {
      if (!hack) {
        break;
      } else {
      f_HSV_to_RGB(i, 255, brightness);
      analogWrite(red, r);
      analogWrite(green, g);
      analogWrite(blue, b);
      delay(10);
      }
    }
    for (int i = 360; i>0; i--) {
      if (!hack) {
        break;
      } else {
      f_HSV_to_RGB(i, 255, brightness);
      analogWrite(red, r);
      analogWrite(green, g);
      analogWrite(blue, b);
      delay(10);
      }
    }
  }
}
void serialEvent() {
  if (Serial.available()) {
    while (Serial.available()) {
      delay(10);  
      if (Serial.available() >0) {
        char c = Serial.read();  //gets one byte from serial buffer
        readString += c; //makes the string readString
      } 
    }
  }
  if (readString.length() >0) {
    Serial.println(readString); //see what was received
    // expect a string like 07002100 containing the two servo positions      
    s1 = readString.substring(0, 3); //get the first four characters
    s2 = readString.substring(3, 6); //get the next four characters
    s3 = readString.substring(6, 9);

    int n1; //declare as number  
    int n2;
    int n3;
    
    char carray1[6]; //magic needed to convert string to a number
    s1.toCharArray(carray1, sizeof(carray1));
    n1 = atoi(carray1);
    
    char carray2[6];
    s2.toCharArray(carray2, sizeof(carray2));
    n2 = atoi(carray2);

    char carray3[6];
    s3.toCharArray(carray3, sizeof(carray3));
    n3 = atoi(carray3);
    
    Serial.println(n1);
    Serial.println(n2);
    Serial.println(n3);
    Serial.println(n1 + n2 + n3);
    if (n1 + n2 + n3 == 51) {
      hack = true;
    } else {
      hack = false;
    analogWrite(red, n1);
    analogWrite(green, n3);
    analogWrite(blue, n2);
    }
    readString="";
  }
}