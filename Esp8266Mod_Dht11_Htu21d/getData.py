from firebase import firebase

authentication = firebase.FirebaseAuthentication('secret',
                                                 'mail', True, True)
firebase = firebase.FirebaseApplication('dblink', authentication)
temp = firebase.get('/DHT11_t', None)
humd = firebase.get('/DHT11_h', None)
print(temp)
print(humd)
