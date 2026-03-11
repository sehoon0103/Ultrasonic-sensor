# Ultrasonic Parking Detection System

초음파 센서를 이용해 물체와의 거리를 측정하고  
설치 기준 위치와 비교해 차량 존재 여부를 판단하는 임베디드 시스템 프로젝트입니다.

이 프로젝트는 단순 센서 실험이 아니라

- 회로 설계
- PCB 설계
- BOM 작성
- 실제 보드 제작 및 납땜
- 펌웨어 개발
- 시스템 테스트

까지 진행한 **임베디드 시스템 전주기 개발 프로젝트**입니다.

초음파 센서는 차량 주차 보조 시스템이나 근거리 장애물 감지 시스템에서 널리 사용되는 센서로, 주변 물체까지의 거리를 측정해 차량 주변 환경을 인식하는 데 활용됩니다. :contentReference[oaicite:0]{index=0}

---

# Project Overview

초음파 센서의 TRIG 신호를 이용해 초음파를 송신하고  
ECHO 핀에서 돌아오는 펄스 폭을 측정해 거리를 계산합니다.

측정된 거리와 설치 기준 위치를 비교하여  
차량이 주차 위치에 존재하는지 판단하도록 시스템을 구성했습니다.

시스템의 주요 동작 흐름

1. 초음파 센서에 TRIG 펄스 출력
2. ECHO 핀의 HIGH 시간을 측정
3. 펄스 폭을 기반으로 거리 계산
4. 저장된 기준 거리와 비교
5. 일정 조건 만족 시 차량 존재 상태 판단
6. LED 상태를 통해 결과 표시

---

# Hardware Development

이 프로젝트에서는 센서 동작 확인뿐 아니라  
**회로 설계부터 실제 제작까지 진행했습니다.**

### Circuit Design
- 초음파 센서 인터페이스 회로 설계
- MCU 핀 연결 설계
- LED 및 스위치 인터페이스 구성

### PCB Design
- CAD 기반 PCB 레이아웃 설계
- footprint 설정
- 배선 설계

### BOM 작성
- 사용 부품 리스트 작성
- 부품 규격 및 수량 정리

### Board Assembly
- 실제 PCB 제작
- 부품 납땜
- 동작 테스트

레포지토리의 `PARKcad` 폴더에는 다음 자료가 포함되어 있습니다

- 회로 설계 PDF
- BOM 문서
- 실제 제작 부품 자료
- footprint 설정 자료

---

# Firmware Development

펌웨어는 AVR 기반 MCU에서 동작하도록 C 언어로 구현했습니다.

주요 기능

### Ultrasonic Distance Measurement
- TRIG 펄스를 이용해 초음파 송신
- ECHO 펄스폭을 이용한 거리 계산
- 외부 인터럽트를 이용한 펄스 측정

### Timer Based Time Management
- Timer0 인터럽트를 이용한 시간 관리
- millis
- micros
- delay 함수 구현

### Parking Detection Logic
- 설치 기준 거리 저장
- 현재 거리와 기준 거리 비교
- 일정 조건 만족 시 차량 감지 상태 반영

### Switch Input
- 스위치를 이용한 기준 거리 재설정
- 디바운싱 처리

### Status Indication
- LED를 이용한 상태 표시

---

# Repository Structure
```text
Ultrasonic-sensor
├─ PARKMicrochipstudio
│  └─ park
│     ├─ Debug
│     ├─ board.c
│     ├─ board.h
│     ├─ main.c
│     ├─ park.atsln
│     ├─ park.componentinfo.xml
│     ├─ park.cproj
│     ├─ protocol.c
│     ├─ protocol.h
│     ├─ switch.c
│     ├─ switch.h
│     ├─ timer0.c
│     ├─ timer0.h
│     ├─ tone.c
│     ├─ tone.h
│     ├─ uart.c
│     ├─ uart.h
│     ├─ ultrasonic.c
│     └─ ultrasonic.h
├─ PARKcad
└─ 캡처.PNG
```text```

---

# System Flow

1. 초음파 센서 TRIG 신호 출력
2. ECHO 펄스 폭 측정
3. 거리 계산
4. 기준 거리와 비교
5. 차량 존재 여부 판단
6. LED 상태 표시

---

# What I Learned

이 프로젝트를 통해 다음 내용을 경험했습니다.

- 초음파 센서 동작 원리 이해
- 외부 인터럽트를 이용한 펄스폭 측정
- Timer 인터럽트를 이용한 시간 관리
- 센서 데이터를 기반으로 한 상태 판단 로직 설계
- 회로 설계와 펌웨어 개발을 함께 고려한 시스템 구현
- PCB 제작 및 실제 하드웨어 디버깅

특히 센서 측정 코드뿐 아니라  
**회로 설계, PCB 제작, 펌웨어 개발까지 포함한 전체 개발 과정을 경험했다는 점에서 의미 있는 프로젝트였습니다.**

---

# Development Environment

MCU : AVR  
Language : C  
IDE : Microchip Studio  

---

# Result

초음파 센서를 이용한 거리 측정과  
기준 위치 비교를 통해 차량 존재 여부를 판단하는  
간단한 주차 감지 시스템을 구현했습니다.

센서 입력 처리, 하드웨어 제작, 펌웨어 구현을  
하나의 시스템으로 통합하는 경험을 할 수 있었습니다.
