from tkinter import *
import subprocess
import os

raiz = Tk()
width = 1000
height = 600
micanvas = Canvas (raiz, bg ="lightblue", width = width, height = height)

micanvas.pack()
micanvas.create_text(width/2, 100, text = "Ingrese la función que desea derivar", anchor = CENTER, font =("Purisa", "30"))

def der_fun():
    raiz.config (width = 1000, height = 600)
    e = Entry(raiz,font=('Arial',30))
    e.place(relx=0.5,rely=0.5,anchor='s',relheight=0.15,relwidth=0.4)
    a = e.get()
    der = Button (raiz, width = 5, height = 2, anchor = CENTER, text = "Derivar", command = lambda: txt(e), font =("Arial", "15"))
    micanvas.create_window(500,375 , window = der, anchor = CENTER)

    # subprocess.run(["/home/lovelace/ProyectoAlgoritmos/filename.txt"])

def limpiar():
    micanvas.delete("all")

def txt(e):
    e.get()
    file = open("/home/lovelace/ProyectoAlgoritmos/filename.txt", "w")
    file.write(str(e.get()) + os.linesep)
    file.close()
    print(e.get())

der_fun()
raiz.mainloop()
