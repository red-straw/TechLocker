# 🔐 TechLocker

**스마트폰으로 원격 잠금/해제하는 스마트 자물쇠**입니다. 열쇠 분실·비밀번호 노출 문제를 줄이기 위해, 비밀 명령을 코드에 숨기고 앱이 설치된 본인 스마트폰으로만 열 수 있게 했습니다.

`23-2` · 팀 프로젝트 (4인, 팀장)

▶ [시연 영상 (YouTube)](https://www.youtube.com/watch?v=OBdjbJFhI0M)

<p>
  <img src="docs/breadboard.png" width="49%">
  <img src="docs/app_inventor_blocks.png" width="49%">
</p>

## 동작

1. 앱(App Inventor)에서 블루투스로 아두이노 연결
2. **LOCK** → 잠금 명령 문자열 전송 → 연속 회전 서보가 회전식 자물쇠를 잠그고, 올라가는 알림음 + LED 켜짐
3. **UNLOCK** → 반대 방향 회전으로 해제, 내려가는 알림음 + LED 꺼짐
4. 이미 잠긴 상태에서 LOCK(또는 열린 상태에서 UNLOCK)을 다시 누르면 **무시** → 서보가 같은 방향으로 계속 도는 것을 막아 내구성 확보

## 문제 해결

- **전력 부족**: 블루투스·서보·스피커·LED를 동시에 구동하자 일부 부품이 동작하지 않음 → 동작을 **순차 실행**하도록 설계 변경
- **중복 명령**: 버튼 연타 시 서보 과회전 → LED 상태로 잠금 상태를 판단해 같은 명령 차단
- **부피**: 아두이노·배터리·브레드보드를 적층해 상자 하나에 수납, 기존 회전식 자물쇠에 바로 결합

## 구성

```text
.
├── arduino/TechLocker/TechLocker.ino  # 아두이노 펌웨어
├── app/TechLocker.aab                 # App Inventor 앱
└── docs/
    ├── breadboard.png                 # 회로도 (Fritzing)
    ├── circuit.fzz                    # Fritzing 원본
    ├── app_inventor_blocks.png        # 앱 블록 코드
    └── leaflet.jpg                    # 홍보 리플릿
```

**하드웨어**: Arduino Uno, 블루투스 모듈, 연속 회전 서보모터, 피에조 스피커, LED, 배터리

## 회고

목표 기능은 모두 달성했지만, 일반 자물쇠에 비해 전력 소모와 부피가 크다는 한계를 확인했습니다. 저전력 부품과 소형화로 휴대 가능한 형태로 개선하는 것이 다음 과제입니다.

## 기술 스택

Arduino (C++) · MIT App Inventor · Bluetooth Serial · Fritzing
