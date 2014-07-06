#define D1 13

const int numRows = 4;       // number of rows in the keypad
const int numCols = 3;       // number of columns
const int debounceTime = 20; // number of milliseconds for switch to be stable

const int numberPin[7] = {0,1,2,3,4,5,6};


// this array determines the pins used for rows and columns
const int rowPins[numRows] = { 14, 15, 16, 17 }; // Rows 0 through 3
const int colPins[numCols] = { 10, 9, 8 };    // Columns 0 through 2

// keymap defines the character returned when the corresponding key is pressed
const int keymap[numRows][numCols] = {
  { 1, 2, 3  } ,
  { 4, 5, 6  } ,
  { 7, 8, 9  } ,
  { 0, 0, 0  }
};


// Segments that make each number
const byte numbers[10] = 
{//  abcdefg
    B1000000, // 0 
    B1111001, // 1
    B0100100, // 2
    B0110000, // 3
    B0011001, // 4
    B0010010, // 5
    B0000010, // 6
    B1111000, // 7
    B0000000, // 8
    B0010000  // 9
};

  
void setup(){
  for(int i=0; i<=7; i++){
    pinMode(i, OUTPUT);
  } 
  pinMode(D1, OUTPUT);
  digitalWrite(D1, HIGH);
  digitalWrite(7, HIGH);  //OFF decimal point

  //keypad row
  for (int row = 0; row < numRows; row++){
    pinMode(rowPins[row], INPUT);
    digitalWrite(rowPins[row], HIGH);   
  }
  //keypad column
  for (int column = 0; column < numCols; column++){
    pinMode(colPins[column],OUTPUT);
    digitalWrite(colPins[column],HIGH);
  }
}

void loop(){
  int key = getKey();

  if (key != -1) {
     lightDigit(numbers[key]);
  }
}

//writing segments
void numberWrite(byte number) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(numberPin[i], bitRead(number, i));
  }
}

//light 7-segment
void lightDigit(byte number) {
  digitalWrite(D1, LOW);
  numberWrite(number);
}


//getting pressed key
char getKey(){
  int key = -1; //no key pressed
  
  for(int column = 0; column < numCols; column++) {
    digitalWrite(colPins[column],LOW);         
    for(int row = 0; row < numRows; row++) {
      if(digitalRead(rowPins[row]) == LOW) {
        delay(debounceTime);                     // Debounce
        while(digitalRead(rowPins[row]) == LOW);                    
        key = keymap[row][column];
      }
    }
    digitalWrite(colPins[column],HIGH);    
  }
  return key;
}
