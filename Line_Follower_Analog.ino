//Menggunakan 2 sensor//
int EN_A  = 9;      
int EN_B  = 10;     
int IN_A1 = 5;      
int IN_A2 = 6;      
int IN_B1 = 7;      
int IN_B2 = 8;      
int speed =320;
boolean direction = 1;  // 1 (true) menunjukkan Maju dan 0 (false) menunjukkan arah sebaliknya //
int left = 0;
int right = 0;
int limit = 900;   //IR nilai Sensor cahaya, batas menunjukkan refleksi IR dari permukaan putih//

void setup()
{
init_motors();
Serial.begin(9600);
}

void loop()
{
read_sensors();
move_robot();
}
void read_sensors()
{

//Nilai sensor IR membaca harus di atas jalur hitam ketika sensor berada di atas permukaan putih//
left  = analogRead(A0);
right = analogRead(A1);
Serial.print("              Kiri : ");
Serial.println(left);
Serial.print("              Kanan: ");
Serial.println(right);
}

//Kedua sensor mendeteksi permukaan hitam//
//         Maka Bergerak Maju            //
void move_robot(){
if ( left >= limit && right >= limit )
{
set_left_motor(400, 1);
set_right_motor(400, 1);
Serial.println("Maju =>");
}

else if ( left < limit && right >= limit )
{
//Sensor kanan membaca garis Hitam//
//     Maka Bergerak kekanan    //
set_left_motor(330, 0);       // dinamo kiri bergerak ke depan
set_right_motor(speed, 1);      // dinamo kanan bergerak kebelakang
Serial.println("Belok Kanan");
}

else if ( left >= limit && right < limit)
{
//Sensor kiri membaca garis hitam//
//      Maka Bergerak Kekiri      //
set_left_motor(speed, 1);     // Dinamo kiri bergerak kebelakang
set_right_motor(330, 0);    // Dinamo kanan bergerak kedepan
Serial.println("Belok Kiri");
}

else
{
//Kedua sensor mendeteksi permukaan putih//
//        Maka bergerak kedepan          //
set_left_motor(320, 1);
set_right_motor(320, 1);
Serial.println("Lurus =>");
}
}

void init_motors()
{
// Mengatur Mode Keluaran//
pinMode(IN_A1, OUTPUT);
pinMode(IN_A2, OUTPUT);
pinMode(IN_B1, OUTPUT);
pinMode(IN_B2, OUTPUT);
pinMode(EN_A, OUTPUT);
pinMode(EN_B, OUTPUT);

// Menginisialisasi port untuk mematikan dinamo //
analogWrite(EN_A, 0);
analogWrite(EN_B, 0);
digitalWrite(IN_A1, 1);
digitalWrite(IN_A2, 0);
digitalWrite(IN_B1, 1);
digitalWrite(IN_B2, 0);
}

void set_left_motor(int speed, boolean dir)
{
analogWrite(EN_A, speed);     // PWM pada pengaktifan jaluur
digitalWrite(IN_A1, dir);
digitalWrite(IN_A2, ! dir);
}

void set_right_motor(int speed, boolean dir)
{
analogWrite(EN_B, speed);
digitalWrite(IN_B1, dir);
digitalWrite(IN_B2, ! dir);
}
