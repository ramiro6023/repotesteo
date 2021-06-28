#define DEBOUNCE_UPDATE 100
#define T_DELAY1_MS 50
#define T_DELAY2_US 500
#define T_DELAY3_US 50

typedef enum estado_t
{
  BOT_CERO,
  BOT_UNO,
  BOT_FALLING,
  BOT_RISING
};

const int pinboton = 2;
const int pinled = 13;

int i = 0;
int estadoBoton;
int estadoLed = LOW;
int ultimoEstadoBoton = HIGH;
unsigned long tiempoUltimoPulso = 0;
unsigned long delayLectura = 50;
unsigned long millisAnterior = 0;
unsigned long millisActual = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(pinboton, INPUT_PULLUP);
  pinMode(pinled, OUTPUT);
}

void loop()
{
  /*  int lectura = digitalRead(pinboton);

  if (lectura != ultimoEstadoBoton)
  {
    tiempoUltimoPulso = millis();
  }

  if ((millis() - tiempoUltimoPulso) > delayLectura)
  {
    if (lectura != estadoBoton)
    {
      estadoBoton = lectura;

      if (estadoBoton == LOW)
      {
        i += 1;
        if (i > 2)
        {
          i = 0;
        }
        Serial.print("El valor de i es: ");
        Serial.println(i);
      }
    }
  }

  ultimoEstadoBoton = lectura;*/

  debouncePullUp(pinboton, &i);

  if (i == 0)
  {
    millisActual = millis();

    if ((millisActual - millisAnterior) > T_DELAY1_MS)
    {
      millisAnterior = millisActual;

      if (estadoLed == LOW)
      {
        estadoLed = HIGH;
      }
      else
      {
        estadoLed = LOW;
      }
      digitalWrite(pinled, estadoLed);
      /*Serial.print("Valor de i: ");
        Serial.println(i);*/
    }
  }

  if (i == 1)
  {
    millisActual = micros();

    if ((millisActual - millisAnterior) > T_DELAY2_US)
    {
      millisAnterior = millisActual;

      if (estadoLed == LOW)
      {
        estadoLed = HIGH;
      }
      else
      {
        estadoLed = LOW;
      }
      digitalWrite(pinled, estadoLed);
      /*Serial.print("Valor de i: ");
      Serial.println(i);*/
    }
  }
  if (i == 2)
  {
    millisActual = micros();

    if ((millisActual - millisAnterior) > T_DELAY3_US)
    {
      millisAnterior = millisActual;

      if (estadoLed == LOW)
      {
        estadoLed = HIGH;
      }
      else
      {
        estadoLed = LOW;
      }
      digitalWrite(pinled, estadoLed);
      /*Serial.print("Valor de i: ");
      Serial.println(i);*/
    }
  }
}

void debouncePullUp(int pinBoton, int *contador)
{
  static estado_t estado;
  static unsigned long millisTrigger = 0;
  unsigned long millisActual;

  millisActual = millis();
  if (millisTrigger < millisActual)
  {
    millisTrigger = millisActual + DEBOUNCE_UPDATE;

    int pinEstado = digitalRead(pinBoton);

    switch (estado)
    {
    case BOT_CERO:
      if (pinEstado)
      {
        estado = BOT_RISING; //R
      }
      break;

    case BOT_UNO:
      if (pinEstado == 0)
      {
        estado = BOT_FALLING; //F
      }
      break;

    case BOT_FALLING: //F
      if (pinEstado)
      {
        estado = BOT_UNO;
      }
      else
      {
        estado = BOT_UNO;
        *contador += 1;
        if (*contador > 2)
        {
          *contador = 0;
        }
        Serial.print("El valor es: ");
        Serial.println(*contador);
      }
      break;

    case BOT_RISING: //R
      if (pinEstado)
      {
        estado = BOT_UNO;
      }
      else
      {
        estado = BOT_CERO;
      }
      break;
    }
  }
}