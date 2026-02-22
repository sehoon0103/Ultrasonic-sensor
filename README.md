# Ultrasonic Sensor Practice (개인 실습)

이 레포는 완성형 프로젝트 라기보다, 임베디드 현업에서 자주 쓰는 기본기(Interrupt, UART 등)를
혼자 실습하고 정리한 기록입니다.  
초음파 센서(Ultrasonic)를 예제로 삼아, 거리 측정 흐름과 입출력 제어를 연습했습니다.

---

## 목적 (Why)

- 초음파 센서의 기본 동작(TRIG/ECHO) 이해
- 타이밍 기반 측정 로직을 직접 구현해보기
- 디버깅/검증을 위해 UART 출력(Serial logging) 습관 만들기
- Interrupt(또는 타이머 기반 처리) 같은 “실무 빈출” 포인트를 개인 실습으로 체득

---

## 무엇을 해봤나 (What I practiced)

- Ultrasonic distance measurement
  - TRIG 펄스 출력 → ECHO 펄스 폭 측정 → 거리(cm) 계산
- Interrupt / Timing
  - ECHO 펄스 폭을 안정적으로 읽기 위한 인터럽트(또는 타이머 기반) 처리 연습
- UART (Serial logging)
  - 측정값/상태를 UART로 출력해 동작 확인(테스트/검증용)

> ※ 실제 구현 방식(외부 인터럽트 사용 여부, 타이머 채널, baudrate 등)은 코드 기준으로 결정됩니다.

---

## 사용 환경 (Environment)

- MCU/보드: (예: Arduino UNO / AVR / STM32 등)  ← 네 환경에 맞게 한 줄만 수정
- Sensor: Ultrasonic (예: HC-SR04 등)
- Interface: GPIO, (optional) Timer/Interrupt, UART

---

## 실행/테스트 방법 (How to test)

1. 보드 연결 후 업로드/빌드
2. 센서 앞 거리를 바꿔가며 값 변화 확인
3. Serial Monitor(UART)로 출력 로그 확인

---

## 내가 얻은 것 (What I learned)

- 작은 기능이라도 측정 → 계산 → 출력(로그) → 검증까지 흐름을 끝까지 가져가는 연습
- 인터럽트/타이밍 이슈(노이즈, 튀는 값, 측정 안정화)를 의식하고 구조를 잡는 습관
- UART 로그를 활용해 원인 파악을 빠르게 하는 습관

---

## Notes

- 이 레포는 개인 학습/기록 목적이라 코드가 간단할 수 있습니다.
- 추후에는 필터링(예: moving average) 또는 타이머 캡처 입력 같은 방식으로 개선할 수 있습니다.

---

## Links

- tinkercad :(https://www.tinkercad.com/things/6vAZcxkCDwX-05/editel?returnTo=https%3A%2F%2Fwww.tinkercad.com%2Fdashboard%2Fdesigns%2Fall)
