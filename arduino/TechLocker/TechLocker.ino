// TechLocker: 스마트폰(블루투스)으로 원격 잠금/해제하는 스마트 자물쇠
//
// 앱(App Inventor)이 블루투스 시리얼로 명령 문자열을 보내면
// 서보모터로 회전식 자물쇠를 돌리고, 피에조 알림음을 낸다.
// 잠금 상태는 LED로 표시하며, 같은 명령이 반복되면 무시해 서보 과회전을 막는다.
#include <Servo.h>

const int SERVO_PIN = 8;
const int SPEAKER_PIN = 2;
const int LED_PIN = 13;  // 켜짐 = 잠김

const String CMD_LOCK = "TechLocker";
const String CMD_UNLOCK = "TechUnLocker";

// 서보 펄스 폭(us): 1500 정지, 1300/1700 반대 방향 회전
const int SERVO_STOP = 1500;
const int SERVO_LOCK = 1300;
const int SERVO_UNLOCK = 1700;
const int ROTATE_MS = 350;  // 자물쇠를 한 번 돌리는 시간

const int TONE_DO = 523, TONE_RE = 587, TONE_MI = 659;

Servo lockServo;

bool isLocked() { return digitalRead(LED_PIN) == HIGH; }

void rotate(int pulse) {
  lockServo.writeMicroseconds(pulse);
  delay(ROTATE_MS);
  lockServo.writeMicroseconds(SERVO_STOP);
}

void playTones(int a, int b, int c) {
  tone(SPEAKER_PIN, a, 500); delay(100);
  tone(SPEAKER_PIN, b, 500); delay(100);
  tone(SPEAKER_PIN, c, 500); delay(100);
}

void lock() {
  rotate(SERVO_LOCK);
  playTones(TONE_DO, TONE_RE, TONE_MI);  // 잠김: 도레미
  digitalWrite(LED_PIN, HIGH);
}

void unlock() {
  rotate(SERVO_UNLOCK);
  playTones(TONE_MI, TONE_RE, TONE_DO);  // 열림: 미레도
  digitalWrite(LED_PIN, LOW);
}

void setup() {
  Serial.begin(9600);  // 블루투스 모듈
  pinMode(LED_PIN, OUTPUT);
  pinMode(SPEAKER_PIN, OUTPUT);
  lockServo.attach(SERVO_PIN);
  lockServo.writeMicroseconds(SERVO_STOP);
}

void loop() {
  if (Serial.available() > 0) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    if (cmd == CMD_LOCK && !isLocked()) {
      lock();
    } else if (cmd == CMD_UNLOCK && isLocked()) {
      unlock();
    }
  }
}
