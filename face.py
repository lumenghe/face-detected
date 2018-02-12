import cv2

# GLOBAL PARAMS
CAP_WIDTH_PARAM = 3
CAP_HEIGHT_PARAM = 4
CAP_WIDTH = 640
CAP_HEIGHT = 480

if __name__ == "__main__":
    cap = cv2.VideoCapture(0)
    cap.set(CAP_WIDTH_PARAM, CAP_WIDTH)
    cap.set(CAP_HEIGHT_PARAM, CAP_HEIGHT)

    faceCascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')

    while(True):
        # Capture frame-by-frame
        ret, frame = cap.read()
        frame = cv2.flip(frame, 1)
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        blurred = cv2.GaussianBlur(gray, (21, 21), 0)
        faces = faceCascade.detectMultiScale(gray, 1.3, 5, minSize=(50, 50))
        for (x,y,w,h) in faces:
            cv2.rectangle(frame,(x,y),(x+w,y+h),(0,255,0),2)
        cv2.imshow('frame', frame)
        if cv2.waitKey(1) & 0xFF == ord('q'): break

    cap.release()
    cv2.destroyAllWindows()
