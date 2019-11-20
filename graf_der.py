from tkinter import *

raiz = Tk()
width = 1000
height = 600
micanvas = Canvas (raiz, bg ="lightblue", width = width, height = height)

micanvas.pack()
micanvas.create_text(width/2, 100, text = "Ingrese la función que desea derivar", anchor = CENTER, font =("Purisa", "30"))


def fun_ini():
    raiz.config (width = 1000, height = 800)
    e = Entry(raiz,font=('Arial',30))
    e.place(relx=0.5,rely=0.5,anchor='s',relheight=0.15,relwidth=0.4)

def der_fun():
    fun_ini()
    der = Button (raiz, width = 5, height = 2, anchor = CENTER, text = "Derivar", command = None, font =("Arial", "15"))
    micanvas.create_window(500,375 , window = der, anchor = CENTER)
    raiz.update()

def limpiar():
    micanvas.delete("all")


fun_ini()
raiz.mainloop()
