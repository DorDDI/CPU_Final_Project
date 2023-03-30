from tkinter import *
import serial as ser
import turtle
import time

root = Tk()
root.config(bg="#7F7F7F")
tim = turtle.Turtle()
tim.color("red")
tim.pensize(1.5)
tim.shapesize(0.5)
tim.shape("circle")
tim.speed(0)


angle = 0 #angle delta
mode = 0 #paint mode
bool_third = 0
state = 0
string = ""
firstTime = 1
first_arg = 1

s = ser.Serial('COM3', baudrate=9600, bytesize=ser.EIGHTBITS,
               parity=ser.PARITY_NONE, stopbits=ser.STOPBITS_ONE,
               timeout=1)  # timeout of 1 sec where the read and write operations are blocking,

menulabel = Label(root,bg="#7F7F7F",text="Project Menu", font=("helvetica", 30)).grid(row=1, column=1,columnspan=4,pady= 20)
counterlabel = Label(root)
anglelabel = Label(root)
anglelleftabel = Label(root)
anglelrigthabel = Label(root)
dinamicangle = Label(root)
acknowledge = Label(root, text="finished sending the scripts" , padx=40, pady=20, bg="#7F7F7F",font=("helvetica", 12))

firstbutton = Button(root,padx=20,pady=10, text="First task", command=firstTask, font=("helvetica", 20),background="#1E90FF")
firstbutton.grid(padx=30,pady=20,row=2, column=1)
secondtbutton = Button(root, padx=13,pady=10,text="Second task", command=lambda :secondTask(string,tim,mode), font=("helvetica", 20), background="#1E90FF")
secondtbutton.grid(row=2, column=2, columnspan=2, padx=70)
thirdtbutton = Button(root, padx=17,pady=10,text="Third task", command=thirdTask, font=("helvetica", 20),background="#1E90FF")
thirdtbutton.grid(padx=10,row=3, column=1,pady=30)
fourthbutton = Button(root,padx=20,pady=10,text="Fourth task", command=fourthTask, font=("helvetica", 20), background="#1E90FF")
fourthbutton.grid(row=3, column=2,padx=4,columnspan=2)

startmovebutton = Button(root, padx=20,pady=10,text="start rotate",command = startmove,font=("helvetica", 20), background="#6A5ACD")
stopmovebutton = Button(root, padx=20,pady=10,text="stop rotate",command = stoptmove,font=("helvetica", 20), background="#6A5ACD")

exitbutton = Button(root,text = "Quit", padx=20,pady=10,font=("helvetica", 20),fg="#D9D9D9",background="#030303",command=lambda:quit(tim)).grid(row=30, column=1,pady=20)
clearbutton = Button(root,text = "Clear\ndraw", padx=20,pady=10,font=("helvetica", 18),bg="#EBEBEB",command=lambda:clear(tim)).grid(row=30, column=2, columnspan=2)
clearinfo = Button(root, text = "clear info",padx=20,pady=10,font=("helvetica", 20),command=clear_info, background="#8F8F8F")

script1button = Button(root,text = "script 1", padx=20,pady=10,font=("helvetica", 20), background="#6A5ACD",command=lambda:readScript("A"))
script2button = Button(root,text = "script 2", padx=20,pady=10,font=("helvetica", 20), background="#6A5ACD",command=lambda:readScript("B"))
script3button = Button(root,text = "script 3", padx=20,pady=10,font=("helvetica", 20), background="#6A5ACD",command=lambda:readScript("C"))

root.mainloop()





