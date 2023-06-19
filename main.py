import cv2
import serial
import time
# Config the arduino
# ArduinoSerial = serial.Serial('COM8', 9600, timeout=1)
ArduinoSerial=serial.Serial('COM4', 9600, timeout=1) #Start communications with the bluetooth unit
face_cascade = cv2.CascadeClassifier('open/cascadeFace.xml')
eye_cascade = cv2.CascadeClassifier('open/eyeGlass.xml')
cap = cv2.VideoCapture(0)
while cap.isOpened():
    time.sleep(0.5)
    key = 0
    ret, frame = cap.read()
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(
        frame,
        scaleFactor = 1.1,
        minNeighbors = 6,
        minSize = (350, 350)
    )
    for x, y, w, h in faces:
        cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 0, 255), 3)
        face = frame[y:y + h, x:x + w]
          eyes = eye_cascade.detectMultiScale(
            face, 
            scaleFactor = 1.1,
            minNeighbors = 6
        )
        for x2, y2, w2, h2 in eyes:
            cv2.rectangle(face, (x2, y2), (x2 + w2, y2 + h2), (0, 255, 0), 3)
            key = 1
    cv2.imshow('img', frame)
    if cv2.waitKey(10) & 0xFF == ord('q'):
        break
    print(key)
    cnvKey = str(key)
    ArduinoSerial.write(cnvKey.encode('utf-8'))
cap.release()
cv2.destroyAllWindows()
