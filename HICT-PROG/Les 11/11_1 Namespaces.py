import datetime

def verdubbelB(b):
   b = b + b
   print(b)

verdubbelB(7)
time = datetime.datetime.today()
print(time.strftime(("%H:%M:%S")))

def f(y):
   return 2*y + 1

def g(x):
   return 5 + x + 10

print(f(3)+g(3))

