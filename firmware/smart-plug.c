#include "contiki.h"
#include "net/rime/rime.h"
#include "net/rime/mesh.h"

#include "dev/leds.h"
#include "dev/temperature-sensor.h"
#include "dev/emeter-sensor.h"

#include "msg.h"

#include <stdio.h>
#include <string.h>

#define MESH_CHANNEL 132

static struct mesh_conn mesh;
static const struct sensors_sensor *power;
static const struct sensors_sensor *temp;
static const struct sensors_sensor *energy;

extern struct process smart_plug_shell_process;

/*---------------------------------------------------------------------------*/
PROCESS(mesh_process, "Mesh process");
AUTOSTART_PROCESSES(&mesh_process, &smart_plug_shell_process);
/*---------------------------------------------------------------------------*/

static void sent(struct mesh_conn *c) {
	printf("packet sent\n");
}

static void timedout(struct mesh_conn *c) {
	printf("packet timedout\n");
}

static void recv(struct mesh_conn *c, const linkaddr_t *from, uint8_t hops) {
	printf("Data received from %d.%d: %.*s (%d)\n", from->u8[0], from->u8[1],
			packetbuf_datalen(), (char *) packetbuf_dataptr(),
			packetbuf_datalen());

	sp_msg_t *msg = (sp_msg_t *)packetbuf_dataptr();

	switch (msg->type) {
		case SP_MSG_SENSORS_REQ:
			msg->type = SP_MSG_SENSORS_RESP;
			break;

		case SP_MSG_TOGGLE_REQ:
			msg->type = SP_MSG_TOGGLE_RESP;
			break;

		default:
			return;
	}

	mesh_send(&mesh, from);
}

const static struct mesh_callbacks callbacks = { recv, sent, timedout };

/*---------------------------------------------------------------------------*/
PROCESS_THREAD(mesh_process, ev, data) {
	PROCESS_EXITHANDLER(mesh_close(&mesh);)
	PROCESS_BEGIN();

	mesh_open(&mesh, MESH_CHANNEL, &callbacks);

	temp = sensors_find(TEMPERATURE_SENSOR);
	power = sensors_find(POWER_SENSOR);
	energy = sensors_find(ENERGY_SENSOR);

	while (1) {
		PROCESS_WAIT_EVENT();
	}

	PROCESS_END();
}
/*---------------------------------------------------------------------------*/
