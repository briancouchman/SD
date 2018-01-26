deps_config := \
	/opt/Espressif/esp-idf/components/app_trace/Kconfig \
	/opt/Espressif/esp-idf/components/esp32/Kconfig \
	/opt/Espressif/esp-idf/components/ethernet/Kconfig \
	/opt/Espressif/esp-idf/components/freertos/Kconfig \
	/opt/Espressif/esp-idf/components/heap/Kconfig \
	/opt/Espressif/esp-idf/components/log/Kconfig \
	/opt/Espressif/esp-idf/components/lwip/Kconfig \
	/opt/Espressif/esp-idf/components/pthread/Kconfig \
	/opt/Espressif/esp-idf/components/spi_flash/Kconfig \
	/opt/Espressif/esp-idf/components/tcpip_adapter/Kconfig \
	/opt/Espressif/esp-idf/components/fatfs/Kconfig \
	/opt/Espressif/esp-idf/components/wear_levelling/Kconfig \
	/opt/Espressif/esp-idf/components/bootloader/Kconfig.projbuild \
	/opt/Espressif/esp-idf/components/esptool_py/Kconfig.projbuild \
	/opt/Espressif/esp-idf/components/partition_table/Kconfig.projbuild \
	/opt/Espressif/esp-idf/Kconfig

include/config/auto.conf: \
	$(deps_config)


$(deps_config): ;
