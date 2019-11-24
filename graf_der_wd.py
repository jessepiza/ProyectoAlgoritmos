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
micanvas.create_text(width/2, 100, text = "CÁLCULADORA DE DERIVADAS", anchor = CENTER, font = ("Arial Black", "38"), fill = "navy")
micanvas.create_text(width/2, 200, text = "Ingrese la función que desea derivar", anchor = CENTER, font =('Aharoni', "30"))
fun_ini = Entry(raiz,font=('Arial',30))
fun_ini.place(relx=0.5,rely=0.55,anchor='s',relheight=0.15,relwidth=0.55)
fun_ini.config(justify = CENTER)
der = Button (raiz, width = 6, height = 2, anchor = CENTER, text = "Derivar", command = lambda: txt(fun_ini), font =("Arial", "15"), bg = "slateblue")
micanvas.create_window(830,280 , window = der, anchor = CENTER)
sal= Button(raiz, width = 6, height= 2, anchor = CENTER, text = "Salir", command = lambda: salir(), font = ("Arial", "15"), bg = "indian red")
micanvas.create_window(700, 540, window = sal, anchor = CENTER)


def salir():
    """ Cierra la pestaña.
        """
    raiz.quit()


def txt(fun_ini):
    """ Crea un archivo txt, el cual es leido en 'C++' donde luego se crea otro con la respuesta para ser interpretado
        en 'python' y al final escribirla en la interfaz gráfica.
        Parametro:
        Un elemento tipo Entry el cual, tendra la información que va a ser enviada a 'C++'.
        """
    file = open("Funcion.txt", "w")
    file.write(str(fun_ini.get()) + os.linesep)
    file.close()
    print(fun_ini.get())
    micanvas.create_text(width/2, 365, text = "Respuesta", anchor = CENTER, font =('Arial Black', "30"))
    subprocess.call("./a.exe")
    file = open("Derivada.txt", "r")
    deri = file.read()
    respuesta = Entry(raiz,font=('Arial',30), fg = "navy")
    respuesta.config(state = NORMAL)
    respuesta.insert(0, deri)
    respuesta.config(state = "readonly")
    respuesta.place(relx=0.5,rely=0.8,anchor='s',relheight=0.15,relwidth=0.55)
    respuesta.config(justify = CENTER)
    fun_ini.config (state = "readonly")
    otra = Button (raiz, width = 20, height = 2, anchor = CENTER, text = "Ingresar nueva derivada", command = lambda: otra_der(fun_ini, respuesta), font = ("Arial", "15"), bg = "slateblue")
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
    """ El usuario podrá ingresar una nueva función para que el programa la derive.
        Se elimina lo que cada Entry tiene escrito para que pueda ser modificado.
        Parámetros:
        Dos elementos tipo Entry .
        """
    e.config (state = NORMAL)
    e.delete(0, END)
    a.config(state = NORMAL)
    a.delete(0,END)
    a.config (state = "readonly")

raiz.mainloop()
