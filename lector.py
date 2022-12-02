import sys
import glob
import serial
import time
#with serial.Serial('/dev/cu.usbserial-1110', 9600, timeout=1) as ser:
     #ser.writelines(b'adc_0')
     #name = input('What is your name?\n') 
     #line = ser.read   # read a '\n' terminated line
     #ser.writelines(b'adc_0\r\n')
     #print(line)
     #x = input("opcion: ")
     
# serial_arduino = serial.Serial('/dev/cu.usbserial-1110', 9600)
# print("Phase 1")
# #time.sleep(10)
# cadena  = "hola bebe"
# xd = cadena.encode('ascii')
# serial_arduino.write(bytes(cadena, 'utf-8'))
# time.sleep(0.05)
# data = serial_arduino.readline()
     
     # while(True):
     #      #time.sleep(0.5)
     #      la = ser.read()
     #      print(la)
     #      print("_"*10)
          


def serial_ports():
    """ Lists serial port names

        :raises EnvironmentError:
            On unsupported or unknown platforms
        :returns:
            A list of the serial ports available on the system
    """
    if sys.platform.startswith('win'):
        ports = ['COM%s' % (i + 1) for i in range(256)]
    elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
        # this excludes your current terminal "/dev/tty"
        ports = glob.glob('/dev/tty[A-Za-z]*')
    elif sys.platform.startswith('darwin'):
        ports = glob.glob('/dev/tty.*')
    else:
        raise EnvironmentError('Unsupported platform')

    result = []
    for port in ports:
        try:
            s = serial.Serial(port)
            s.close()
            result.append(port)
        except (OSError, serial.SerialException):
            pass
    return result

def select_port(result):
     for idx, item in enumerate(result):
          print(f"Option {idx} \t  \t Port {item}  ")
          #print(f" {idx}, {item}")
     puerto = int(input(""))
     if puerto in range(len(result)):
           print(f"Seleccionaste {result[puerto]}")
     else:
          print("Puerto no valido")
     return result[puerto]

def open_port_serial(port_string):
     serial_arduino = serial.Serial(port_string, 9600)
     print("Phase 1")
     #time.sleep(10)
     cadena  = "hola bebe"
     xd = cadena.encode('ascii')
     serial_arduino.write(bytes(cadena, 'utf-8'))
     time.sleep(0.05)
     print("Phase 2")
     data = serial_arduino.readline()
     print(data)
     print("Phase 3")
     cadena  = "hola bebe"
     xd = cadena.encode('ascii')
     serial_arduino.write(bytes(cadena, 'utf-8'))
     print("Phase 4")
     data = serial_arduino.readline()
     print(data)
     

if __name__ == '__main__':
    print("Hola")
    port = select_port(serial_ports())
    open_port_serial(port)
    
    