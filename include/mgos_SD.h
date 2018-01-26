#ifdef __cplusplus
#include "SD.h"
#else
typedef struct SDtag SD;
#endif

#ifdef __cplusplus
extern "C"
{
#endif


SD *mgos_sd_create();

void mgos_sd_close(SD *sd);
//
// void mgos_SD_init(SD *sd);

int mgos_sd_begin(SD *sd, int pin_num_miso, int pin_num_mosi, int pin_num_clk, int pin_num_cs);

FILE* mgos_sd_openFile(SD *sd, const char *filename, const char *mode);

void mgos_sd_closeFile(SD *sd, FILE *f);

int mgos_sd_readFile(SD *sd, const char *filename, uint8_t** buffer);

int mgos_sd_read(SD *sd, FILE *f, uint8_t* buffer, size_t toRead);

// int mgos_sd_write(SD *sd, FILE *f, int* buffer);
//
void mgos_sd_listFiles(SD *sd);

#ifdef __cplusplus
}
#endif  /* __cplusplus */
