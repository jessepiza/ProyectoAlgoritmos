from tkinter import *
import subprocess
import os

raiz = Tk()
raiz.title ("Derivadas")

width = 1000
height = 600
fondo = PhotoImage(file ="fondo.gif")
micanvas = Canvas (raiz, bg ="lightblue", width = width, height = height)
micanvas.create_image(1000,1000, anchor=NW, image=fondo)
micanvas.pack()
# l = Label(image = fondo)
# l.pack()


def der_fun():
    micanvas.create_text(width/2, 100, text = "CÁLCULADORA DE DERIVADAS", anchor = CENTER, font = ("Times New Roman", "35"))
    micanvas.create_text(width/2, 200, text = "Ingrese la función que desea derivar", anchor = CENTER, font =('Times New Roman', "30"))
    raiz.config (width = 1200, height = 800, bg = "black")
    e = Entry(raiz,font=('Arial',30))
    e.place(relx=0.5,rely=0.63,anchor='s',relheight=0.15,relwidth=0.55)
    e.config(justify = CENTER)
    a = e.get()
    der = Button (raiz, width = 5, height = 2, anchor = CENTER, text = "Derivar", command = lambda: txt(e), font =("Arial", "15"))
    micanvas.create_window(500,450 , window = der, anchor = CENTER)

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
