const int LMotFwd = 9;   // conectar ao pin 09 motor esq para frente
const int RMotFwd = 10;  // conectar ao pin 10 motor dir para frente
const int LMotRev = 11;  // conectar ao pin 11 motor esq reverte
const int RMotRev = 12;  // conectar ao pin 12 motor dir reverte
const int onblack = 300; // se ler valor menor que este está na linha preta
const int onWhite = 700; // se ler valor maior que este está no fundo branco

void setup()
{
    Serial.begin(9600);
    // pinMode(A0, INPUT);
    pinMode(A1, INPUT); // sensor da extrema esquerda
    pinMode(A2, INPUT); // sensor esquerdo
    pinMode(A3, INPUT); // sensor do meio
    pinMode(A4, INPUT); // sensor da direita
    pinMode(A5, INPUT); // sensor da extrema direita

    pinMode(LMotFwd, OUTPUT);
    pinMode(RMotFwd, OUTPUT);
    pinMode(LMotRev, OUTPUT);
    pinMode(RMotRev, OUTPUT);
}

bool isOnBlack(int sensor)
{
    if (sensor <= onblack)
        return true;
    else
        return false;
}

bool isOnWhite(int sensor)
{
    if (sensor >= onWhite)
        return true;
    else
        return false;
}

void moveForward()
{
    digitalWrite(LMotFwd, HIGH);
    digitalWrite(RMotFwd, HIGH);

    digitalWrite(RMotRev, LOW);
    digitalWrite(LMotRev, LOW);
}

void turnLeft()
{
    digitalWrite(LMotFwd, LOW);
    digitalWrite(RMotFwd, HIGH);

    digitalWrite(RMotRev, LOW);
    digitalWrite(LMotRev, LOW);
}

void turnRight()
{
    digitalWrite(LMotFwd, HIGH);
    digitalWrite(RMotFwd, LOW);

    digitalWrite(RMotRev, LOW);
    digitalWrite(LMotRev, LOW);
}

void turnCircle()
{
    digitalWrite(LMotFwd, LOW);
    digitalWrite(RMotFwd, HIGH);

    digitalWrite(RMotRev, LOW);
    digitalWrite(LMotRev, HIGH);
}

void Stop()
{
    digitalWrite(LMotFwd, LOW);
    digitalWrite(RMotFwd, LOW);

    digitalWrite(LMotRev, LOW);
    digitalWrite(RMotRev, LOW);
}

void loop()
{
    int sensor1 = analogRead(A1); // sensor1 Extrema esquerda
    int sensor2 = analogRead(A2); // sensor2
    int sensor3 = analogRead(A3); // sensor3 Meio
    int sensor4 = analogRead(A4); // sensor4
    int sensor5 = analogRead(A5); // sensor5 Extrema direita

    Serial.print("extrema Esquerda: ");
    Serial.print(sensor1);
    Serial.print("\t Esquerda: ");
    Serial.print(sensor2);
    Serial.print("\t Meio: ");
    Serial.print(sensor3);
    Serial.print("\t Direita: ");
    Serial.print(sensor4);
    Serial.print("\t Extrema Direita: ");
    Serial.println(sensor5);

    if (isOnWhite(sensor3))
    {
        moveForward();
    }
    else
    {
        if (isOnBlack(sensor1) && isOnWhite(sensor3))
        {
            moveForward();
        }
        else if (isOnBlack(sensor1) && isOnBlack(sensor3) && isOnWhite(sensor5))
        {
            turnLeft();
            delay(220);
            turnRight();
            delay(120);
        }
        else if (isOnWhite(sensor2) || isOnWhite(sensor1))
        {
            turnRight();
            delay(220);
            turnLeft();
            delay(120);
        }
        else if (isOnWhite(sensor4) || isOnWhite(sensor5))
        {
            turnLeft();
            delay(230);
            turnRight();
            delay(120);
            // } else if(isOnBlack(sensor1) && isOnBlack(sensor2) && isOnBlack(sensor3) && isOnBlack(sensor4) && isOnBlack(sensor5) ){
            //   turnCircle();
            //   delay(300);   // substitua por esquerda se tiver gap na pista
            // } else if (isOnWhite(sensor4) && isOnWhite(sensor5)){
            //   turnRight();
            //   delay(200);
            //   turnLeft();
            //   delay(100);
            // } else if (isOnWhite(sensor1) && isOnWhite(sensor2)){
            //   turnLeft();
            //   delay(200);
            //   turnRight();
            //   delay(100);
        }
    }
}
