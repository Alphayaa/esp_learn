idf_component_register(
    SRCS 
        "hello_world_main.c" 
        "../hardware/src/bsp_led.c"
        "../hardware/src/bsp_timer.c"
    INCLUDE_DIRS 
        "." 
        "../hardware/inc"
)
