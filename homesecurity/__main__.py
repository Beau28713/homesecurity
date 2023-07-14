import cv2
from socket import socket, AF_INET, SOCK_DGRAM
import time


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


def send_receive_data():
    address = ("169.254.104.124", 5000)
    client_socket = socket(AF_INET, SOCK_DGRAM)
    client_socket.settimeout(1)

    data = "red"
    client_socket.sendto(str.encode(data), address) # send data to arduino

    try:
        recieved_data = client_socket.recvfrom(2048)  # reading data sent from arduino
        print(recieved_data)

    except:
        pass

    time.sleep(2)


def main():
    send_receive_data()


if __name__ == "__main__":
    main()
