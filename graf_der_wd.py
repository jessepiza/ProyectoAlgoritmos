from tkinter import *
import subprocess
import os

raiz = Tk()
raiz.title ("Derivadas")

width = 1000
height = 600
micanvas = Canvas (raiz, bg ="lightblue", width = width, height = height)
micanvas.pack()
fondo = PhotoImage(file = 'fondo.png')
micanvas.create_image(500,150, anchor=CENTER, image=fondo)
micanvas.pack()


def der_fun():
    micanvas.create_text(width/2, 100, text = "CÁLCULADORA DE DERIVADAS", anchor = CENTER, font = ("Arial Black", "38"), fill = "navy")
    micanvas.create_text(width/2, 200, text = "Ingrese la función que desea derivar", anchor = CENTER, font =('Aharoni', "30"))
    raiz.config (width = 1200, height = 800, bg = "black")
    e = Entry(raiz,font=('Arial',30))
    e.place(relx=0.5,rely=0.55,anchor='s',relheight=0.15,relwidth=0.55)
    e.config(justify = CENTER)
    a = e.get()
    der = Button (raiz, width = 6, height = 2, anchor = CENTER, text = "Derivar", command = lambda: txt(e), font =("Arial", "15"), bg = "slateblue")
    micanvas.create_window(830,280 , window = der, anchor = CENTER)
    sal= Button(raiz, width = 6, height= 2, anchor = CENTER, text = "Salir", command = lambda: salir(), font = ("Arial", "15"), bg = "indian red")
    micanvas.create_window(700, 540, window = sal, anchor = CENTER)


def limpiar():
    micanvas.delete("all")

def salir():
    raiz.quit()

def deleteContent(fName):
    with open(fName, "w"):
        pass

def txt(e):
    deleteContent("Derivada.txt")
    file = open("Funcion.txt", "w")
    file.write(str(e.get()) + os.linesep)
    file.close()
    micanvas.create_text(width/2, 365, text = "Respuesta", anchor = CENTER, font =('Arial Black', "30"))
    subprocess.call("./a.exe")
    file = open("Derivada.txt", "r")
    deri = file.read()
    a = Entry(raiz,font=('Arial',30), fg = "navy")
    a.config(state = NORMAL)
    a.insert(0, deri)
    a.config(state = "readonly")
    a.place(relx=0.5,rely=0.8,anchor='s',relheight=0.15,relwidth=0.9)
    a.config(justify = CENTER)
    otra = Button (raiz, width = 20, height = 2, anchor = CENTER, text = "Ingresar nueva derivada", command = lambda: otra_der(e, a), font = ("Arial", "15"), bg = "slateblue")
    micanvas.create_window(340, 540, window = otra, anchor = CENTER)
    file.close()


def otra_der(e, a):
    e.delete(0, END)
    a.config(state = NORMAL)
    a.delete(0,END)
    a.config (state = DISABLED)


der_fun()
raiz.mainloop()
