let SD = {

    _create:        ffi('void *mgos_sd_create()'),
    _init:          ffi('void mgos_sd_begin(void *, int pin_num_miso, int pin_num_mosi, int pin_num_clk, int pin_num_cs)'),
    _close:         ffi('void mgos_sd_close(void *)'),
    _read:          ffi('int mgos_sd_read(void *, const char *filename, uint_8 bufsize)'),
    _write:         ffi('int mgos_sd_write(void *, const char *filename, uint_8 bufsize)'),
    _listFiles:     ffi('void mgos_sd_listFiles(void *)'),

    _proto: {

        // ## **`myVS1053.begin()`**
        // Initialize sensor and make it ready for use.
        // Return value: 1 if sensor is ready, 0 otherwise.
        init: function (pin_num_miso, pin_num_mosi, pin_num_clk, pin_num_cs)) {
          SD._init(this.sd, pin_num_miso, pin_num_mosi, pin_num_clk, pin_num_cs);
        },

        close: function(){
          SD._close(this.sd);
        },

        read: function(filename, bufSize){
          return SD._read(this.sd, filename, bufSize);
        },

        write: function(filename, bufSize){
          return SD._write(this.sd, filename, bufSize);
        },

        listFiles: function(){
          SD._listFiles(this.sd);
        }
    },

    // ## **`SD.create(  )`**
    // Create an SD instance.
    // Return value: an object representing the SD with the methods defined in _proto: {...} (above).
    create: function (addr) {
        let obj = null;

        obj = Object.create(SD._proto);
        obj.sd = SD._create();

        return obj;
    }

};
