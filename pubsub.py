
# Example of subscribing to an Adafruit IO group
# and publishing to the feeds within it

# Author: Brent Rubell for Adafruit Industries, 2018
# Modified by: Luis Furlán, 2024

# Import standard python modules.
import sys
import time
import serial

# Import Adafruit IO MQTT client.
from Adafruit_IO import MQTTClient

ADAFRUIT_IO_USERNAME = ""
ADAFRUIT_IO_KEY      = ""

#Declarar los canales
feedbtn1 = "btn1"
feedbtn4 = "secuencia1"
feedbtn5 = "secuencia2"
feedservo1 = "servo1"
feedservo2 = "servo2"
feedservo3 = "servo3"
feedservo4 = "servo4"
feedtexto = "texto"
feedpose = "texto2"

# Define callback functions which will be called when certain events happen.
def connected(client):
    # Connected function will be called when the client is connected to Adafruit IO.
    # This is a good place to subscribe to topic changes.  The client parameter
    # passed to this function is the Adafruit IO MQTT client so you can make
    # calls against it easily.
    print('Esperando datos...')
    # Suscribirse a los canales
    client.subscribe(feedbtn1)
    client.subscribe(feedbtn4)
    client.subscribe(feedbtn5)
    client.subscribe(feedservo1)
    client.subscribe(feedservo2)
    client.subscribe(feedservo3)
    client.subscribe(feedservo4)

def disconnected(client):
    # Disconnected function will be called when the client disconnects.
    print('Disconnected from Adafruit IO!')
    sys.exit(1)

def message(client, feed_id, payload):
    # Message function will be called when a subscribed topic has a new value.
    # The topic_id parameter identifies the topic, and the payload parameter has
    # the new value.
    print('Feed {0} received new value: {1}'.format(feed_id, payload))

    #Enviar valor dependiendo del botón presionado
    if (feed_id == feedbtn1):
        if (payload == '1'): #Botón 1
            print("Cambiado a siguiente estado.")
            arduino.write(bytes('1\n', 'utf-8'))
        if (payload == '2'): #Botón 2
            print("Cambiado a siguiente pose.")
            arduino.write(bytes('2\n', 'utf-8'))
        if (payload == '3'): #Botón 3
            print("Guardar/Cargar")
            arduino.write(bytes('3\n', 'utf-8'))
    if (feed_id == feedbtn4):
        if (payload == '1'): #Botón 4
            print("Secuencia 1")
            arduino.write(bytes('4\n', 'utf-8'))
    if (feed_id == feedbtn5): #Botón 5
        if (payload == '1'):
            print("Secuencia 2")
            arduino.write(bytes('5\n', 'utf-8'))
    #Enviar valor del slider al microcontrolador
    if (feed_id == feedservo1):
        print("Servo 1")
        print('6')
        print(payload + '\n')
        arduino.write(bytes('6' + payload + 'F', 'utf-8')) #Slider + valor de slider + F (Indica final de cadena)
    if (feed_id == feedservo2):
        print("Servo 2")
        print('7')
        print(payload + '\n')
        arduino.write(bytes('7' + payload + 'F', 'utf-8'))
    if (feed_id == feedservo3):
        print("Servo 3")
        print('8')
        print(payload + '\n')
        arduino.write(bytes('8' + payload + 'F', 'utf-8'))
    if (feed_id == feedservo4):
        print("Servo 4")
        print('9')
        print(payload + '\n')
        arduino.write(bytes('9' + payload + 'F', 'utf-8'))

try:
    # Create an MQTT client instance.
    client = MQTTClient(ADAFRUIT_IO_USERNAME, ADAFRUIT_IO_KEY)

    # Setup the callback functions defined above.
    client.on_connect    = connected
    client.on_disconnect = disconnected
    client.on_message    = message

    # Connect to the Adafruit IO server.
    client.connect()

    # Now the program needs to use a client loop function to ensure messages are
    # sent and received.  There are a few options for driving the message loop,
    # depending on what your program needs to do.

    # The first option is to run a thread in the background so you can continue
    # doing things in your program.
    client.loop_background()

    arduino = serial.Serial(port='COM3', baudrate = 9600, timeout = 0.1)

    # Now send new values every 5 seconds.
    #print('Publishing a new message every 5 seconds (press Ctrl-C to quit)...')
    while True:
        mensaje = arduino.readline().decode('utf-8')
        #Recibir en que estado se encuentra e indicarlo en adafruit
        if (mensaje == 'estado0\n'):
            print("estado 0")
            client.publish(feedtexto, "Modo Manual")
        if (mensaje == 'estado1\n'):
            print("estado 1")
            client.publish(feedtexto, "Modo EEPROM (Guardar)")
        if (mensaje == 'estado2\n'):
            print("estado 2")
            client.publish(feedtexto, "Modo EEPROM (Cargar)")
        if (mensaje == 'estado3\n'):
            print("estado 3")
            client.publish(feedtexto, "Modo UART")
        #Recibir en que pose se encuentra e indicarlo en adafruit
        if (mensaje == 'Pose 1\n'):
            print("Pose 1")
            client.publish(feedpose, "Pose 1")
        if (mensaje == 'Pose 2\n'):
            print("Pose 2")
            client.publish(feedpose, "Pose 2")
        if (mensaje == 'Pose 3\n'):
            print("Pose 3")
            client.publish(feedpose, "Pose 3")
        if (mensaje == 'Pose 4\n'):
            print("Pose 4")
            client.publish(feedpose, "Pose 4")
        time.sleep(3)
except KeyboardInterrupt:
    print("Programa terminado.")
    if arduino.is_open:
        arduino.close()
    sys.exit(1)