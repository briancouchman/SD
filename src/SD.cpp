#include "mgos.h"

#include <stdio.h>
#include <string.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include <sys/dirent.h>
//#include "sdkconfig.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_vfs.h"
#include "esp_vfs_fat.h"
//#include "freertos/task.h"
//#include "driver/sdmmc_host.h"
#include "driver/sdspi_host.h"
#include "sdmmc_cmd.h"
// #include "dirent.h"

#include "SD.h"

static const char *TAG = "sd";

SD::SD() {

}


int SD::init(int pin_num_miso, int pin_num_mosi, int pin_num_clk, int pin_num_cs){
  sdmmc_host_t host = SDSPI_HOST_DEFAULT();
  sdspi_slot_config_t slot_config = SDSPI_SLOT_CONFIG_DEFAULT();
  slot_config.gpio_miso = (gpio_num_t)pin_num_miso;
  slot_config.gpio_mosi = (gpio_num_t)pin_num_mosi;
  slot_config.gpio_sck  = (gpio_num_t)pin_num_clk;
  slot_config.gpio_cs   = (gpio_num_t)pin_num_cs;
  // This initializes the slot without card detect (CD) and write protect (WP) signals.
  // Modify slot_config.gpio_cd and slot_config.gpio_wp if your board has these signals.

  // Options for mounting the filesystem.
  // If format_if_mount_failed is set to true, SD card will be partitioned and
  // formatted in case when mounting fails.
  // max_files Max number of open files
  esp_vfs_fat_sdmmc_mount_config_t mount_config = {
      .format_if_mount_failed = false,
      .max_files = 5
  };

  // Use settings defined above to initialize SD card and mount FAT filesystem.
  // Note: esp_vfs_fat_sdmmc_mount is an all-in-one convenience function.
  // Please check its source code and implement error recovery when developing
  // production applications.
  sdmmc_card_t* card;
  esp_err_t ret = esp_vfs_fat_sdmmc_mount("/sdcard", &host, &slot_config, &mount_config, &card);

  if (ret != ESP_OK) {
      if (ret == ESP_FAIL) {
          ESP_LOGE(TAG, "Failed to mount filesystem. "
              "If you want the card to be formatted, set format_if_mount_failed = true.");
      } else {
          ESP_LOGE(TAG, "Failed to initialize the card (%d). "
              "Make sure SD card lines have pull-up resistors in place.", ret);
      }
      return 0;
  }

  // Card has been initialized, print its properties
  sdmmc_card_print_info(stdout, card);
  return 1;
}

// int SD::init(){
//   return init(PIN_NUM_MISO, PIN_NUM_MOSI, PIN_NUM_CLK, PIN_NUM_CS);
// }

FILE* SD::openFile(const char *filename, const char *mode="r"){
  return fopen((char*)filename, mode);
}

void SD::closeFile(FILE* f){
  fclose(f);
}


int SD::readFile(const char *filename, uint8_t** buf){
  FILE* f;
  uint32_t bufsize = 32;
  // static uint8_t buf[MAX_BUFSIZE];
  struct stat _stat;
  f = fopen(filename, "r");
  if(f){
      stat(filename, &_stat);

      size_t length = _stat.st_size;
      size_t remaining = _stat.st_size;

      *buf = (uint8_t*)malloc(length+1);
      int buf_idx = 0;
      while(remaining){

          size_t toRead = remaining;
          if(toRead > bufsize){
              toRead = bufsize;
          }
          fread(*buf + buf_idx, toRead, 1, f);
          buf_idx += toRead;
          remaining -= toRead;
      }
      (*buf)[length] = '\0';

      fclose(f);
      return length;
  } else {
    ESP_LOGE(TAG, "Failed to open file for reading");
    return -1;
  }
}

int SD::read(FILE *f, uint8_t* buf, size_t toRead){
  return fread(buf, 1, toRead, f);
}


// int SD::write(FILE *f, uint8_t* buf){
//   uint32_t bufsize = 32;
//   //static uint8_t buf[MAX_BUFSIZE];
//   uint32_t loops;
//
//   f = fopen(filename, "w");
//   if(!f){
//     ESP_LOGE(TAG, "Failed to open file for writing");
//       return 0;
//   }
//
//   size_t i;
//   loops = 1048576 / bufsize;
//   // ESP_LOGI(TAG,"loops %u bufsize (%d)", loops, bufsize);
//
//   for(i=0; i<loops; i++){
//     fwrite(buf, bufsize, 1, f);
//   }
//   fclose(f);
//   return 1;
// }

void SD::listFiles(){
  struct dirent *pDirent;
  DIR *pDir;
  struct stat _stat;
  char cPath[1024];

  pDir = opendir("/sdcard");
  if (pDir == NULL) {
      printf ("Cannot open directory '/sdcard'\n");
      return;
  }

  while ((pDirent = readdir(pDir)) != NULL) {
    sprintf(cPath,"/sdcard/%s",pDirent->d_name);
    stat(cPath,&_stat);
    if(S_ISDIR(_stat.st_mode)) {
      printf ("[%s] DIR %ld\n", pDirent->d_name,_stat.st_size);
    } else {
      printf ("[%s] FILE %ld\n", pDirent->d_name,_stat.st_size);
    }
  }
  closedir (pDir);
}
