import cv2
import face_recognition as fr
import numpy as np

#Load the image file from response
def load_image():
    known_encodings = []
    image = fr.load_image_file("image.jpg")
    encodings = fr.face_encodings(image)
    
    if len(encodings) > 0:
        known_encodings.append(encodings[0])

    return known_encodings

known_encodings = load_image()

video_capture = cv2.VideoCapture(0)

while True:
    ret, frame = video_capture.read()

    if not ret:
        break

    rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

    face_locations = fr.face_locations(rgb_frame)
    face_encodings = fr.face_encodings(rgb_frame, face_locations)

    for face_encding, (top, right, bottom, left) in zip(face_encodings, face_locations):
        matches = fr.compare_faces(known_encodings, face_encodings[0])

        face_distances = fr.face_distance(known_encodings, face_encodings[0])

        cv2.rectangle(frame, (top, left), (right, bottom), (0, 255, 0), 2)
        cv2.putText(frame, "Customer", (left, top-10), cv2.FONT_HERSHEY_PLAIN, 0.6, (0,255,0))

    cv2.imshow("Face recognition", frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break


video_capture.release()
cv2.destroyAllWindows()
