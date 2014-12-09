#include "shell.h"
#include "shell-settings.h"
#include "serial-shell.h"

/*---------------------------------------------------------------------------*/
PROCESS(sp_shell_process, "Smart plug shell");
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(sp_shell_process, ev, data)
{
  PROCESS_BEGIN();

  serial_shell_init();
  shell_blink_init();
  shell_ps_init();
  shell_reboot_init();
  shell_settings_init();

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
