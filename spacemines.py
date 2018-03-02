#!/usr/bin/python

import random
import os

def getinput(prompt):
   value = None
   while value is None: 
      try: 
         value = int(raw_input(prompt))   
      except ValueError: 
         continue
      if value < 0:
         continue
      else:
         break
   return value

mines = random.randint(1,3)+5
people = random.randint(1,60)+40
money = (random.randint(1,50)+10)*people
prod = random.randint(1,40)+80
stored = 0
satisfaction = 1
year = 0
finalyear=10

while True:

   os.system('clear')
   print "Space Mines"
   year=year+1
   mineprice = random.randint(1,2000)+2000
   oreprice = random.randint(1,12)+7

   print "Year : %d" % year
   print
   print "There are %d people in the colony" % people
   print "You have %d mines, and $ %d" % (mines,money)
   print "Satisfaction factor: %.2f" % satisfaction
   print
   
   if mines==0: prod=0
   
   print "Your mines produced %d tone each" % prod
  
   stored=stored+(prod*mines)

   print "Ore in store: %d tons" % stored
   print
   print "SELLING"
   print "Ore selling price: %d" % oreprice
   print "Mine selling price: %d" % mineprice
   print

   while True:
      oretosell = getinput("How much ore to sell? ")
      if oretosell > stored:
         continue
      else:
         break

   stored=stored-oretosell
   money=money+(oretosell * oreprice)

   while True:
      minestosell = getinput("How many mines to sell? ")
      if minestosell > mines:
         continue
      else:
         break

   mines=mines-minestosell
   money=money+(minestosell * mineprice)

   print 
   print "You have $ %d" % money
   print
   print "BUYING"
   print

   while True:
      foodtobuy = getinput("How much to spend on food (Approx $100 p.p)? ")
      if foodtobuy > money:
         continue
      else:
         break

   money=money-foodtobuy
   if (foodtobuy/people) > 120:
      satisfaction=satisfaction+.1
   if (foodtobuy/people) < 80:
      satisfaction=satisfaction-.2

   while True:
      minestobuy = getinput("How many mines to buy? ")
      if minestobuy*mineprice > money:
         continue
      else:
         break

   mines=mines+minestobuy
   money=money-(minestobuy*mineprice)

   if satisfaction < .6:
      print "The peasants are revolting!"
      break

   if satisfaction > 1.1:
      prod=prod+random.randint(1,20)
      people=people+random.randint(1,10)

   if satisfaction < .9:
      prod=prod-random.randint(1,20)
      people=people-random.randint(1,10)

   if (mines > 0) and (people/mines < 10):
      print "You've overworked everyone!"
      break

   if (people < 30):
      print "Not enough people left!"
      break
 
   if random.randint(0,100) <=1:
      print "RADIOACTIVE LEAK. MANY DIE!!"
      people=people/2

   if (prod >= 150):
      print "MARKET GLUT - PRICE DROPS"
      prod=prod/2

   if (year == finalyear):
      print "You survived your term in office!!!"
      score= ((stored*oreprice)+(mines*mineprice)+money)*(people*satisfaction)/1000
      print "You scored : %d" % score
      break 

