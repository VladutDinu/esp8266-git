from firebase import firebase
import matplotlib as mpl
import csv
authentication = firebase.FirebaseAuthentication('secret',
                                                 'dinuionutvladut99@gmail.com', True, True)
firebase = firebase.FirebaseApplication('https://link.firebaseio.com/', authentication)
temp = firebase.get('temperaturaDHT11', None)
humd = firebase.get('umiditateDHT11', None)
o = open('data.txt', 'a+')
o.write(str(temp)+","+str(humd)+"\n")
print(temp)
print(humd)
