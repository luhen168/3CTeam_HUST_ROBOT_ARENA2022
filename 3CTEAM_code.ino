#include <SoftwareSerial.h> //Thư viện sử dụng bất kỳ 2 chân digital nào để làm chân TX RX
#include <AFMotor.h>

SoftwareSerial mybluetooth(9,10); // Khai báo tên Bluetooth và chân TX RX (2-TX, 3-RX)
int M2;   // đầu ra m2
char docgiatri; //Biến docgiatri kiểu char
AF_DCMotor motor1(4); // banh phai vao M4
AF_DCMotor motor2(3); // banh trai vao M3
AF_DCMotor motor3(1);


int tai = 40;  // biến cho tốc độ xe di chuyển
int relay = 13; // noi chan digital 2

void setup() 
{
  Serial.begin(9600);
  mybluetooth.begin(9600); //Kết nối Bluetooth với tốc độ baud là 9600
  motor3.setSpeed(255);
  pinMode (M2,OUTPUT);
  pinMode (relay,OUTPUT);
  digitalWrite (relay, LOW);  
}
void Stop(){
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}
void loop() 
{
  while(mybluetooth.available() > 0) //Nếu tín hiệu của bluetooth lớn hơn 0, tức là đã kết nối OK
  {
    docgiatri = mybluetooth.read(); //Đọc các giá trị trên app được kết nối qua bluetooth và gán vào docgiatri
    Stop(); 
    Serial.println(docgiatri); //in giá trị lên cổng Serial
    Serial.println("");   
  // các trường hợp di chuyển của xe
      if(docgiatri =='F'){          // tiến
        motor1.setSpeed(255);
        motor2.setSpeed(255);
        motor1.run(FORWARD);
        motor2.run(FORWARD);
  
    }
    else if(docgiatri=='B'){      // lùi
        motor1.setSpeed(255);
        motor2.setSpeed(255);
        motor1.run(BACKWARD); 
        motor2.run(BACKWARD);
    }
    else if(docgiatri=='R'){      // trái
        motor1.setSpeed(255);
        motor2.setSpeed(255);
        motor1.run(RELEASE); 
        motor2.run(FORWARD);
    }
    else if(docgiatri=='L'){      // phải
        motor1.setSpeed(255);
        motor2.setSpeed(255);
        motor1.run(FORWARD); 
        motor2.run(RELEASE);
    }

    
    else if(docgiatri=='G'){      // tiến + trái
        motor1.setSpeed(255);
        motor2.setSpeed(tai);
        motor1.run(FORWARD); 
        motor2.run(FORWARD);
    }
    else if(docgiatri=='I'){      // tiến + phải
        motor1.setSpeed(tai);
        motor2.setSpeed(255);
        motor1.run(FORWARD); 
        motor2.run(FORWARD);
    }
    else if(docgiatri=='J'){      // lùi + phải
        motor1.setSpeed(tai);
        motor2.setSpeed(255);
        motor1.run(BACKWARD); 
        motor2.run(BACKWARD);
    }        
    else if(docgiatri=='H'){      // lùi + trái
        motor1.setSpeed(255);
        motor2.setSpeed(tai);
        motor1.run(BACKWARD); 
        motor2.run(BACKWARD);
    }    


    // vũ khí và relay được bật tắt đồng thời
    else if(docgiatri=='W'){        //bật vũ khí 
        motor3.run(FORWARD); 
    }
    else if(docgiatri=='w'){        // tắt vũ khí
        motor3.run(RELEASE);
    }
    else if(relay=='W'){
        digitalWrite(relay,1);      // bạt relay
    }
    else if(relay=='w'){
        digitalWrite(relay,0);      // tắt relay
    
  }
  }
}