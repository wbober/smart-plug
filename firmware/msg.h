/*
 *
 */

#ifndef MSG_H_
#define MSG_H_

#include <stdint.h>

typedef enum {
	SP_MSG_TOGGLE_REQ,
	SP_MSG_TOGGLE_RESP,
	SP_MSG_SENSORS_REQ,
	SP_MSG_SENSORS_RESP,
} sp_msg_type_t;

typedef struct __attribute__((packed)) {
	sp_msg_type_t type;
	uint8_t data[4];
} sp_msg_t;

#endif /* MSG_H_ */
