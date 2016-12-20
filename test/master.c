#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <mqtt.h>
#include <mqtt.c>

#include <unistd.h> // for sleep function

const char *client_name = "smartron_master"; 	
const char *ip_addr     = "37.187.106.16";   
uint32_t    port        = 1883;			
const char *topic1      = "smartron_result";
const char *topic2 	= "smartron_notify";
const char *topic3	= "smartron_send";					
int TIMEOUT 		= 10;

int timeout ( int seconds )
{
    clock_t endwait;
    endwait = clock () + seconds * CLOCKS_PER_SEC ;
    while (clock() < endwait) {}

    return  1;
}

mqtt_broker_handle_t* mqtt_connection()
	{
	mqtt_broker_handle_t *broker = mqtt_connect(client_name, ip_addr, port);

	if(broker == 0) 
	{  
		printf("Connection failed, Please check the IP and port of broker\n");	
 		 return NULL;      	
    	}
	else 
	{
		printf("Connection established successfully\n");
	}
		return broker;
		
}


int publish_mqtt(mqtt_broker_handle_t* broker)
{
//char msg[1024];

char *msg = NULL;
size_t size = 0;

/* Open your_file in read-only mode */
FILE *fp = fopen("test.txt", "r");

/* Get the buffer size */
fseek(fp, 0, SEEK_END); /* Go to end of file */
size = ftell(fp); /* How many bytes did we pass ? */

/* Set position of stream to the beginning */
rewind(fp);

/* Allocate the buffer (no need to initialize it with calloc) */
msg = malloc((size + 1) * sizeof(*msg)); /* size + 1 byte for the \0 */

// Print the array size
printf("Size of the array is %lu\n", size);

/* Read the file into the buffer */
fread(msg, size, 1, fp); /* Read 1 chunk of size bytes from fp into buffer */

/* NULL-terminate the buffer */
msg[size] = '\0';

/* Print it ! */
//printf("%s\n", buffer);
//msg[1024]= buffer[size];
printf("%s", msg);


	// "Hello message from thome API";

	if(mqtt_publish(broker, topic3, msg, QoS0) == -1) 
	{
            printf("publish failed\n");
        }
        else {
            printf("Sent messages\n");
        }
        return(0);
    }


int subscribe_mqtt(mqtt_broker_handle_t* broker)
	{
 		int result = mqtt_subscribe(broker, topic1, QoS1);
		int a,b;
    
   		 if(result != 1) {
       		 printf("failed to Subscribe");
        	 exit(1);
    	}

    		while(1)
    	{
        	mqtt_display_message(broker, &putchar, &a);
		printf("%d",a);
    	}
    		return 0;
	}

int main ()
{   

 	printf("Please wait while server establishes connection.....\n");
	mqtt_broker_handle_t* broker = mqtt_connection();
	
	/*if( timeout(10) == 1 )
	{
        	printf("Time Out\n");
       		return 0;
	}
	//else
	//{
	//printf("Check Broker connection");

	}
	else
	{
	printf("Check Broker connection");
	}*/
	sleep(1);
	//publish_mqtt(broker);
	subscribe_mqtt(broker);


//************************implement timeout for connection******************
//if( timeout(10) == 1)
//{
//printf("Failed to connect, Retrying to connect.....");
//mqtt_connection();
//}
//**************************************************************************

	
 
        
/*int result = mqtt_subscribe(broker, topic3, QoS1);
    
    if(result != 1) {
        puts("failed to Subscribe");
        exit(1);
    }

    while(1)
    {
        mqtt_display_message(broker, &putchar);
    }
    return 0;
    mqtt_disconnect(broker);*/
}
