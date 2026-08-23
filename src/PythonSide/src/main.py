import serial
import cv2

ser = serial.Serial("COM6", 9600)  # Make sure to set the port and the baudrate that your Arduino uses
cap = cv2.VideoCapture(0)
face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + "haarcascade_frontalface_default.xml")
smile_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + "haarcascade_smile.xml")
last_state = None

while True:
    ret, frame = cap.read()
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray, 1.1, 15)
    for (x, y, w, h) in faces:
        cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0))
        roi_gray = gray[y:y+h, x:x+w]
        smiles = smile_cascade.detectMultiScale(roi_gray, 1.2, 25)
        current_state =  "smile" if len(smiles) > 0 else "normal"
        if current_state != last_state:
            ser.write(current_state.encode())
            last_state = current_state
        for (sx, sy, sw, sh) in smiles:
            cv2.rectangle(frame, (x + sx, y + sy), (x + sx + sw, y + sy + sh), (255, 0, 0))
    cv2.imshow('Smile Detector', frame)
    cv2.waitKey(1)
    if cv2.getWindowProperty("Smile Detector", cv2.WND_PROP_VISIBLE) < 1:
        break
ser.close()
cap.release()
cv2.destroyAllWindows()
