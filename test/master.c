#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mqtt.h>
#include <mqtt.c>

#include <unistd.h> // for sleep function

const char *client_name = "smartron_master"; 	
const char *ip_addr     = "37.187.106.16";   
uint32_t    port        = 1883;			
const char *topic1      = "smartron_result";
const char *topic2 	= "smartron_notify";
const char *topic3	= "smartron_send";	
//uint32_t    count       = 10;			

int main ()
{   

    //mqtt_broker_handle_t *broker = mqtt_connect("default_pub","127.0.0.1", 1883);
    mqtt_broker_handle_t *broker = mqtt_connect(client_name, ip_addr, port);

    
    if(broker == 0) {
        puts("Failed to connect");
        exit(1);
    }
 	else{
 	char msg[128];
	
 
        if(mqtt_publish(broker, topic1, msg, QoS1) == -1) 
	{
            printf("publish failed\n");
        }
        else {
            printf("Sent messages\n");
        }
        sleep(1);
    }
int result = mqtt_subscribe(broker, topic3, QoS0);
    
    if(result != 1) {
        puts("failed to Subscribe");
        exit(1);
    }

    while(1)
    {
        mqtt_display_message(broker, &putchar);
    }
    return 0;
    mqtt_disconnect(broker);
}
