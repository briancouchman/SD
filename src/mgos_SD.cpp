#include "mgos_SD.h"

SD *mgos_sd_create() {
  return new SD();
}

void mgos_sd_close(SD *sd) {
  if (sd != nullptr) {
    sd->close();
    delete sd;
    sd = nullptr;
  }
}

// void mgos_SD_init(SD *sd) {
//   if (sd == nullptr) return;
//   sd->init();
// }

int mgos_sd_begin(SD *sd, int pin_num_miso, int pin_num_mosi, int pin_num_clk, int pin_num_cs) {
  if (sd == nullptr) return 0;
  return sd->init(pin_num_miso, pin_num_mosi, pin_num_clk, pin_num_cs);
}

FILE* mgos_sd_openFile(SD *sd, const char *filename, const char *mode){
  if (sd == nullptr) return NULL;
  return sd->openFile(filename, mode);
}

void mgos_sd_closeFile(SD *sd, FILE *f){
  if (sd == nullptr) return;
  sd->closeFile(f);
}

int mgos_sd_readFile(SD *sd, const char *filename, uint8_t** buffer) {
  if (sd == nullptr) return 0;
  return sd->readFile(filename, buffer);
}

int mgos_sd_read(SD *sd, FILE *f, uint8_t* buffer, size_t toRead) {
  if (sd == nullptr) return 0;
  return sd->read(f, buffer, toRead);
}

//int mgos_sd_read_from_position(SD *sd, FILE *f, int position, uint8_t* buffer, size_t toRead) {
//    if (sd == nullptr) return 0;
//    return sd->readFromPosition(f, position, buffer, toRead);
//}

int mgos_sd_get_position(SD *sd, FILE *f) {
  if (sd == nullptr) return -1;
  return sd->getPosition(f);
}

int mgos_sd_go_to_position(SD *sd, FILE *f, int pos) {
  if (sd == nullptr) return -1;
  return sd->goToPosition(f, pos);
}
//
// int mgos_sd_write(SD *sd, FILE *f, uint8_t* buffer) {
//   if (sd == nullptr) return 0;
//   return sd->write(f, buffer);
// }

void mgos_sd_listFiles(SD *sd) {
  if (sd == nullptr) return;
  sd->listFiles();
}
