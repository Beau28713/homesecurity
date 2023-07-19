import cv2
from socket import socket, AF_INET, SOCK_DGRAM
import time
import keyboard


def display_image():
    img = cv2.imread("homesecurity\crope.jpg", 0)

    if img is None:
        print("no image")

    else:
        cv2.imshow("image", img)
        cv2.waitKey(0)
        cv2.destroyAllWindows()


def vid_capture(camera_option: int):
    cap = cv2.VideoCapture(camera_option)

    if not cap.isOpened():
        raise IOError("cam is not opened")

    else:
        while True:
            result, image = cap.read()

            if result:
                cv2.imshow("image", image)

                if cv2.waitKey(1) & 0xFF == ord("q"):
                    break
            else:
                print("No Video")

    cap.release()
    cv2.destroyAllWindows()


def set_up_communication():
    client_socket = socket(AF_INET, SOCK_DGRAM)
    client_socket.settimeout(1)

    return client_socket


def send_data(client_socket):
    arduino_ip = ("169.254.104.124", 5000)
    data = "red"
    client_socket.sendto(str.encode(data), arduino_ip)  # send data to arduino

    try:
        arduino_data = client_socket.recvfrom(2048)  # reading data sent from arduino
        print(arduino_data[0].decode())

    except:
        pass

    time.sleep(2)


def recieved_data(client_socket):
    computer_ip = ("169.254.104.125", 5000)

    # used to recieve data from the Arduino
    client_socket.bind(computer_ip)
    arduino_data = client_socket.recvfrom(2048)
    client_socket.close()

    return eval(arduino_data[0].decode())


def main():
    # using the while loop for testing, will be removed when UX is created
    while True:
        try:
            client_socket = set_up_communication()
            switch_state = recieved_data(client_socket)
            if switch_state:
                vid_capture(1)
            time.sleep(1)  # used for debugging, will be removed in final
        except BaseException as error:
            print(f"The current error is {error}")
            time.sleep(1)  # used for debugging, will be removed in final


if __name__ == "__main__":
    main()
