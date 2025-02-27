import speech_recognition as sr

recognizer = sr.Recognizer()

def recognize_speech():
    with sr.Microphone() as source:
        print("Adjusting with ambient noise... Please wait")
        recognizer.adjust_for_ambient_noise(source)

        print("Listening")
        audio = recognizer.listen(source)
        
        try:
            print("Recognizing...")
            text = recognizer.recognize_google(audio)
            print("You said ", text)
        except sr.UnknownValueError:
            print("sorry, unable to understand!")

        except sr.RequestError as e:
            print(f"Could not request results for:{e}")

recognize_speech()
