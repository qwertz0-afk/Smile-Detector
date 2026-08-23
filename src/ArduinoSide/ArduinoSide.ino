const int rows[3] = {2, 3, 4};
const int columns[4] = {5, 6, 7, 8};

const int normal[3][4] = {
  {1, 0, 0, 1},
  {0, 0, 0, 0},
  {1, 1, 1, 1}
};
const int smile[3][4] = {
  {1, 0, 0, 1},
  {1, 0, 0, 1},
  {0, 1, 1, 0}
};
String command;
void draw_normal() {
  for (int r = 0; r < 3; r++) {
    for (int c = 0; c < 4; c++) {
      digitalWrite(columns[c], normal[r][c] == 1 ? HIGH : LOW);
    }
    digitalWrite(rows[r], LOW);
    delay(2);
    digitalWrite(rows[r], HIGH);
  }
}
void draw_smile() {
  for (int r = 0; r < 3; r++) {
    for (int c = 0; c < 4; c++) {
      digitalWrite(columns[c], smile[r][c] == 1 ? HIGH : LOW);
    }
    digitalWrite(rows[r], LOW);
    delay(2);
    digitalWrite(rows[r], HIGH);
  }
}
void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < 3; i++) {
    pinMode(rows[i], OUTPUT);
    digitalWrite(rows[i], HIGH);
  }
  for (int i = 0; i < 4; i++) {
    pinMode(columns[i], OUTPUT);
    digitalWrite(columns[i], LOW);
  }
  Serial.begin(9600);
  Serial.setTimeout(2);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    command = Serial.readStringUntil('\n');
    command.trim();
  }
  if (command == "smile") {
    draw_smile();
  } else if (command == "normal") {
    draw_normal();
  }
}
