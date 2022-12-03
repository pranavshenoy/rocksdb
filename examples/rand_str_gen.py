import string
import random
 
# initializing size of string
 #maximum length of a key
arr = [] 
# using random.choices()
# generating random strings
f = open("input.txt", "a")
for i in range(0,2000000):
    res = ''.join(random.choices(string.ascii_letters +
                                string.digits, k=random.randint(1,20)))
    arr.append(res)
    f.write(res+'\n')
    
# print result
print("The generated random string : " + str(len(arr)))
f.close()