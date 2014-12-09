#include "contiki.h"

#include "dev/leds.h"
#include "dev/temperature-sensor.h"
#include "dev/emeter-sensor.h"

#include "msg.h"

#include <stdio.h>
#include <string.h>

static const struct sensors_sensor *power;
static const struct sensors_sensor *temp;
static const struct sensors_sensor *energy;

extern struct process sp_shell_process;

/*---------------------------------------------------------------------------*/
PROCESS(sp_main_process, "Main process");
AUTOSTART_PROCESSES(&sp_main_process, &sp_shell_process);
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
PROCESS_THREAD(sp_main_process, ev, data) {
	PROCESS_BEGIN();

	temp = sensors_find(TEMPERATURE_SENSOR);
	power = sensors_find(POWER_SENSOR);
	energy = sensors_find(ENERGY_SENSOR);

	while (1) {
		PROCESS_WAIT_EVENT();
	}

	PROCESS_END();
}
/*---------------------------------------------------------------------------*/
