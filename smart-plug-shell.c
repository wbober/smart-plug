#include "shell.h"
#include "serial-shell.h"

/*---------------------------------------------------------------------------*/
PROCESS(smart_plug_shell_process, "Smart plug shell");
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(smart_plug_shell_process, ev, data)
{
  PROCESS_BEGIN();

  serial_shell_init();
  shell_blink_init();
  shell_ps_init();
  shell_reboot_init();

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
