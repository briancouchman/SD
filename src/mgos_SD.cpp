#include "mgos_SD.h"

SD *mgos_SD_create() {
  return new SD();
}

void mgos_SD_close(SD *sd) {
  if (sd != nullptr) {
    delete sd;
    sd = nullptr;
  }
}

// void mgos_SD_init(SD *sd) {
//   if (sd == nullptr) return;
//   sd->init();
// }

int mgos_SD_init(SD *sd, int pin_num_miso, int pin_num_mosi, int pin_num_clk, int pin_num_cs) {
  if (sd == nullptr) return 0;
  return sd->init(pin_num_miso, pin_num_mosi, pin_num_clk, pin_num_cs);
}

int mgos_SD_read(SD *sd, const char *filename, int bufsize) {
  if (sd == nullptr) return 0;
  return sd->read(filename, bufsize);
}

int mgos_SD_write(SD *sd, const char *filename, int bufsize) {
  if (sd == nullptr) return 0;
  return sd->write(filename, bufsize);
}

void mgos_SD_listFiles(SD *sd) {
  if (sd == nullptr) return;
  sd->listFiles();
}
