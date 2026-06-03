#ifndef PROTOCOL_H_
#define PROTOCOL_H_

// --- 데이터 구조체 ---

typedef struct {
	uint8_t slave_id;
	char command;    // 'W' or 'R'
	uint8_t address;
	uint8_t data;    // 데이터가 없는 경우0
} ProtocolData;

//for master
void master_write(uint8_t slave_id, uint8_t address, uint8_t data);
void master_read(uint8_t slave_id, uint8_t address);
uint8_t master_receive(const char* frame_in, ProtocolData* out_data);

//for slave
void slave_receive_and_respond(const char* frame_in);

#endif /* PROTOCOL_H_ */ 