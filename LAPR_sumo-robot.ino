class DCMotor
{
    int spd = 200, pin1, pin2; // aqui estava spd = 150, alterei para 200

public:
    void Pinout(int in1, int in2)
    {
        pin1 = in1;
        pin2 = in2;
        pinMode(pin1, OUTPUT);
        pinMode(pin2, OUTPUT);
    }

    void Speed(int in1)
    {
        spd = in1;
    }

    void Forward()
    { // frente
        analogWrite(pin1, spd);
        digitalWrite(pin2, LOW);
    }

    void Backward()
    { // ré
        digitalWrite(pin1, LOW);
        analogWrite(pin2, spd);
    }

    void Stop()
    { // parar
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
    }
};

// variaveis dos sensores
int gatilho = 11, echo = 10, luzEsq = 8, luzDir = 9;
float tempo, dist;

DCMotor Motor1, Motor2;

void setup()
{
    Serial.begin(9600);
    pinMode(gatilho, OUTPUT);
    digitalWrite(gatilho, LOW);
    delayMicroseconds(10);
    pinMode(echo, INPUT);
    pinMode(luzEsq, INPUT);
    pinMode(luzDir, INPUT);

    Motor1.Pinout(7, 6);
    Motor2.Pinout(4, 5);

    delay(4000); // delay de 5s antes de iniciar a batalha
}

void loop()
{
    int estadoEsq = lerLuz(luzEsq);
    int estadoDir = lerLuz(luzDir);
    float distancia = Ultrassonico();

    Motor1.Forward();
    Motor2.Forward();

    if (distancia <= 12.0)
    {
        Motor1.Forward();
        Motor2.Forward();
    }
    else
    {                                         // essa lógica é a para os sensores de luz (branco/preto)
        if (estadoEsq == 1 && estadoDir == 1) // Ambos os sensores detectam branco
        {
            Motor1.Backward();
            Motor2.Backward();
            delay(300);      // Ré por 300ms para dar uma leve ré
            girarEsquerda(); // Vira para a esquerda após dar a ré
        }
        else if (estadoEsq == 1) // Sensor esquerdo detecta branco
        {
            Motor1.Backward();
            Motor2.Backward();
            delay(300);
            girarDireita();
        }
        else if (estadoDir == 1) // Sensor direito detecta branco
        {
            Motor1.Backward();
            Motor2.Backward();
            delay(300);
            girarEsquerda();
        }
        else // Ambos os sensores detectam preto
        {
            Motor1.Forward();
            Motor2.Forward();
        }
    }
}

float Ultrassonico()
{
    digitalWrite(gatilho, HIGH);
    delayMicroseconds(10);
    digitalWrite(gatilho, LOW);
    tempo = pulseIn(echo, HIGH);
    dist = (tempo / 29.4) / 2;
    Serial.println(dist);
    return dist;
}

int lerLuz(int pino)
{
    int estadoSensor = digitalRead(pino);
    delay(10);
    if (estadoSensor)
    {
        Serial.println("PRETO");
        return 0;
    }
    else
    {
        Serial.println("BRANCO");
        return 1;
    }
}

void girarEsquerda()
{
    Motor1.Backward();
    Motor2.Forward();
    delay(1000);
}

void girarDireita()
{
    Motor1.Forward();
    Motor2.Backward();
    delay(1000);
}
