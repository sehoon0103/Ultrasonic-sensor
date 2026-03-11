# Ultrasonic Parking Detection System

AVR 기반 마이크로컨트롤러에서 초음파 센서를 이용해 거리를 측정하고  
설치 기준 위치와 비교하여 주차 여부를 판단하는 임베디드 실습 프로젝트입니다.

이 레포는 단순 센서 테스트 수준을 넘어서  
초음파 센서 제어, 인터럽트 기반 시간 측정, UART 통신, RS 485 프로토콜 처리,  
EEPROM 저장, 스위치 입력 처리까지 함께 다룬 기록입니다.

---

## Overview

프로젝트의 핵심 흐름은 다음과 같습니다.

1. 초음파 센서에 TRIG 펄스를 출력
2. ECHO 핀의 HIGH 유지 시간을 인터럽트로 측정
3. 측정된 시간으로 거리 계산
4. 저장된 설치 기준 위치와 비교
5. 차량 감지 여부를 LED와 내부 레지스터 값으로 반영
6. UART 및 RS 485 통신으로 상태 확인 가능

---

## Main Features

- Ultrasonic distance measurement
  - TRIG 출력
  - ECHO 펄스폭 측정
  - 거리 계산

- Interrupt based timing
  - INT0 인터럽트를 사용해 ECHO rising falling edge 처리

- Timer0 utility
  - millis
  - micros
  - delay

- Parking detection logic
  - 설치 기준 위치와 현재 거리 차이를 비교해 주차 여부 판단
  - 일정 시간 이상 유지된 상태만 반영하도록 안정화 로직 적용

- EEPROM storage
  - 설치 기준 위치를 EEPROM에 저장
  - 전원 재시작 후에도 기준값 유지

- Switch input
  - 스위치 입력으로 현재 거리를 설치 기준 위치로 저장

- UART and RS 485 communication
  - UART 링버퍼 기반 송수신
  - RS 485 송수신 방향 제어
  - ASCII 프레임 기반 프로토콜 지원

---

## Repository Structure

```text
Ultrasonic-sensor
├─ PARKMicrochipstudio
│  └─ park
│     ├─ main.c
│     ├─ board.c / board.h
│     ├─ ultrasonic.c / ultrasonic.h
│     ├─ timer0.c / timer0.h
│     ├─ uart.c / uart.h
│     ├─ protocol.c / protocol.h
│     ├─ switch.c / switch.h
│     ├─ tone.c / tone.h
│     ├─ park.cproj
│     └─ park.atsln
├─ PARKcad
│  ├─ park.pdf
│  ├─ PARK_BOM.pdf
│  ├─ PARK 발주품.PNG
│  └─ footprint설정.png
└─ 캡처.PNG
