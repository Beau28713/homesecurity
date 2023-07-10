import cv2


def display_image():
    img = cv2.imread("homesecurity\crope.jpg", 0)

    if img is None:
        print("no image")

    else:
        cv2.imshow("image", img)
        cv2.waitKey(0)
        cv2.destroyAllWindows()


def vid_capture():
    cap = cv2.VideoCapture(0)

    if not cap.isOpened():
            raise IOError("cam is not opened")

    else:
        while True:
            result, image = cap.read()

            if result:
                cv2.imshow('image', image)

                if cv2.waitKey(1) & 0xFF == ord('q'):
                    break
            else:
                print("No Video")

    cap.release()
    cv2.destroyAllWindows()

def main():
    # display_image()
    vid_capture()


if __name__ == "__main__":
    main()
