#include "SD.h"

#ifdef __cplusplus
extern "C"
{
#endif


SD *mgos_SD_create();

void mgos_SD_close(SD *sd);
//
// void mgos_SD_init(SD *sd);

int mgos_SD_init(SD *sd, int pin_num_miso, int pin_num_mosi, int pin_num_clk, int pin_num_cs);

int mgos_SD_read(SD *sd, const char *filename, int bufsize);

int mgos_SD_write(SD *sd, const char *filename, int bufsize);

void mgos_SD_listFiles(SD *sd);

#ifdef __cplusplus
}
#endif  /* __cplusplus */
