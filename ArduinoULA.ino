int X;
int Y;
int S;
const int PINOS_SAIDA[] = {10, 11, 12, 13};

void (*operacoes[16])() = {
    [](){ S = ~X & 0xF; },   // A'B
    [](){ S = ~(X | Y); },   // (A+B)'
    [](){ S = X & Y; },      // AB
    [](){ S = 0x0; },        // 0 Lógico
    [](){ S = ~(X & Y); },   // (AB)'
    [](){ S = ~Y & 0xF; },   // B'
    [](){ S = X ^ Y; },      // A⊕B
    [](){ S = X & ~Y; },     // AB'
    [](){ S = ~X | Y; },     // A'+ B
    [](){ S = ~(X ^ Y); },   // (A⊕B)'
    [](){ S = Y; },          // B
    [](){ S = X & Y; },      // AB
    [](){ S = 0xF; },        // 1 Lógico
    [](){ S = X | ~Y; },     // A+B'
    [](){ S = X | Y; },      // A+B
    [](){ S = X; }           // A
};

int hexCharToInt(char c)
{
    if (c >= 'A' && c <= 'F') {
        return c - '7';  // A a F
    }
    else {
        return c - '0';  // 0 a 9
    }
}

void setup()
{
    Serial.begin(9600);
    for (int i = 0; i < 4; i++) {
        pinMode(PINOS_SAIDA[i], OUTPUT);
    }
}

void loop()
{
    String memoria[100];
    int i = 0;
    while (true) {
        if (Serial.available() > 0) {
            String op = Serial.readStringUntil(' ');
            if (op == "FIM") {
                break;
            }
            memoria[i++] = op;
        }
    }

    for (int j = 0; j < i; j++) {
        String op = memoria[j];
        X = hexCharToInt(op[0]);
        Y = hexCharToInt(op[1]);
        operacoes[hexCharToInt(op[2])]();
        S &= 0xF;
        for (int k = 0; k < 4; k++) {
            digitalWrite(PINOS_SAIDA[k], bitRead(S, k));
        }
        memoria[j] = String(j) + ' ' + String(S, HEX) + ' ' + op.substring(0, 2);
    }

    for (int j = 0; j < i; j++) {
        Serial.println(memoria[j]);
    }
    Serial.println("FIM");
}
