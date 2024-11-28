int m[8] = {3830, 3400, 3864, 2550, 3038, 2272, 2028, 1912};

int c[8] = {25, 50, 50 , 25, 25, 100, 25, 25};

int i;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

    for (i = 0; i < 8; i++)

    {

          tone(2, m[i], 10000);

          delay(10 * c[i]);

    }

}
