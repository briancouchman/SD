let SD = {

    _create: ffi('void *mgos_sd_create()'),
    _begin: ffi('int mgos_sd_begin(void*, int, int, int, int)'),
    _close: ffi('void mgos_sd_close(void*)'),
    // _read: ffi('int mgos_sd_read(void*, char*, int )'),
    // _write: ffi('int mgos_sd_write(void*, char*, int)'),
    _listFiles: ffi('void mgos_sd_listFiles(void*)'),

    _proto: {

        // ## **`myVS1053.begin()`**
        // Initialize sensor and make it ready for use.
        // Return value: 1 if sensor is ready, 0 otherwise.
        begin: function (pin_num_miso, pin_num_mosi, pin_num_clk, pin_num_cs) {
            SD._begin(this.sd, pin_num_miso, pin_num_mosi, pin_num_clk, pin_num_cs);
        },

        close: function () {
            SD._close(this.sd);
        },

        // read: function (filename, bufSize) {
        //     return SD._read(this.sd, filename, bufSize);
        // },
        //
        // write: function (filename, bufSize) {
        //     return SD._write(this.sd, filename, bufSize);
        // },

        listFiles: function () {
            SD._listFiles(this.sd);
        }
    },

    // ## **`SD.create(  )`**
    // Create an SD instance.
    // Return value: an object representing the SD with the methods defined in _proto: {...} (above).
    create: function () {
        let obj = null;

        obj = Object.create(SD._proto);
        obj.sd = SD._create();

        return obj;
    }

};
