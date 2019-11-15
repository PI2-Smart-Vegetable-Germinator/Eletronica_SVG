#include <CustomStepper.h>

//Define os parametros iniciais de ligacao do motor de passo
CustomStepper stepper(8, 9, 10, 11, (byte[]){8, B1000, B1100, B0100,
B0110, B0010, B0011, B0001, B1001}, 4075.7728395, 12, CW);

void setup()
{
//Define a velocidade do motor
stepper.setRPM(12);
//Define o numero de passos por rotacao
stepper.setSPR(4075.7728395);
}

void loop()
{
if (stepper.isDone())
{
//Intervalo entre acionamentos
delay(2000);
//Define o sentido de rotacao (CW = Horario)
stepper.setDirection(CW);
//Define o angulo de rotacao
stepper.rotateDegrees(180);
}

stepper.run();
}
