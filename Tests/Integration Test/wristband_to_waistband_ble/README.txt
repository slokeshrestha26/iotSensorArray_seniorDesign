the data goes through parsed and all, i think
but need to fix timing issues.
idk if there's queuing packet loss on teensy side, if ble has packet loss protection (i dont think it does. idk if this would make it easier/harder to deal with). If we doubt that there is queuing packet loss, we can make the sending side slower so that there is no bottlenecking.
also, need more info about how to receive data in the wristband from waistband