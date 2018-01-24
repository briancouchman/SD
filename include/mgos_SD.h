#include "SD.h"

#ifdef __cplusplus
extern "C"
{
#endif


SD *mgos_sd_create();

void mgos_sd_close(SD *sd);
//
// void mgos_SD_init(SD *sd);

int mgos_sd_begin(SD *sd, int pin_num_miso, int pin_num_mosi, int pin_num_clk, int pin_num_cs);

int mgos_sd_read(SD *sd, const char *filename);

int mgos_sd_write(SD *sd, const char *filename);

void mgos_sd_listFiles(SD *sd);

#ifdef __cplusplus
}
#endif  /* __cplusplus */
