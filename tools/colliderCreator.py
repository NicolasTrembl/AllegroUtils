from tkinter import *
from tkinter.filedialog import askopenfilename
import pyperclip


""" ==========================================================================================#
|   Ce code permet de générer plus simplement les triangles utilisé pour les test de collision|
|   C'est pas beau mais ça marche plus ou moins                                               |
""""=========================================================================================="


center_x = 400
center_y = 250

def toCenter(pos) :
    out = [pos[0] + center_x, pos[1] + center_y]
    return out

def drawRound(pos, cnv, size):
    topLeft = [pos[0] - size, pos[1] - size]
    bottomRight = [pos[0] + size, pos[1] + size]
    return cnv.create_oval(topLeft, bottomRight)
    
class image :
    def __init__(self):
        self.image = None
        self.addr = None

    def draw(self, cnv):
        if (self.image != None):
            self.addr = cnv.create_image(center_x, center_y,image= self.image)

class triangle :
    def __init__(self):
        self.a = toCenter([15, -5])
        self.b = toCenter([-5, 15])
        self.c = toCenter([15, 15])
        self.size = 5
    
    def isOn(self, x, y, size = None):
        if (size == None): size = self.size
        index = 0
        for pts in [self.a, self.b, self.c]:
            if (size >= pts[0] - x >= - size and size >= pts[1] - y >= - size) : return index 
            index += 1
        return -1
    
    
    def setPos(self, index, x, y):
        [self.a, self.b, self.c][index][0] = x
        [self.a, self.b, self.c][index][1] = y
    
    def drawTri(self, cnv):
        return [
            cnv.create_line(self.a, self.b, fill='green'),
            cnv.create_line(self.a, self.c, fill='green'),
            cnv.create_line(self.b, self.c, fill='green'),
            drawRound(self.a, cnv, self.size),
            drawRound(self.b, cnv, self.size),
            drawRound(self.c, cnv, self.size),
        ]

        
selected = (-1, -1)

join = False        
triangles = []
trianglesDrawing = []
img = image() 

    
def clearAll(cnv):
        cnv.delete('all')
        cnv.create_line((0, 250), (800, 250), fill='red')
        cnv.create_line((400, 0), (400, 500), fill='blue')
        trianglesDrawing.clear()

window = Tk()
window.title("Collider creator")
window.geometry('800x600')



def clicked(event):
    global selected
    index = 0
    for tri in triangles:
        ison = tri.isOn(event.x, event.y)
        if (ison >= 0) :
            selected = (index, ison)
            break
        index += 1

def endClicked(event):
    global selected
    if (join) :
        index = 0
        for tri in triangles:
            if (index != selected[1]): 
                ison = tri.isOn(event.x, event.y, 15)
                if (ison >= 0):
                    event.x = [tri.a, tri.b, tri.c][ison][0]
                    event.y = [tri.a, tri.b, tri.c][ison][1]
                    break
            index += 1
            
    if (selected[1] >= 0):
        triangles[selected[0]].setPos(selected[1], event.x, event.y)
        for element in trianglesDrawing[selected[0]]:
            canvas.delete(element)
        trianglesDrawing.pop(selected[0])
        trianglesDrawing.insert(selected[0], triangles[selected[0]].drawTri(canvas))
    selected = (-1, -1)

def shiftPressed():
    global join
    join = not join

def generateCode():
    out = f"// All the triangles points \n point triPoints[{len(triangles)}][3] = " + "{\n"
    i = 0
    for tri in triangles:
        i += 1
        out += "    { // Triangle " +f"{i}" +"\n        "
        out += "(point) { " + f"{tri.a[0] - center_x}, {tri.a[1] - center_y} " + "}, \n        "
        out += "(point) { " + f"{tri.b[0] - center_x}, {tri.b[1] - center_y} " + "}, \n        "
        out += "(point) { " + f"{tri.c[0] - center_x}, {tri.c[1] - center_y} " + "} \n    "
        out += "},\n"
    out += "};"
    pyperclip.copy(out)
    
    print(out)


canvas = Canvas(window, width=800, height=500, bg="white")
canvas.bind("<Button-1>", clicked)
canvas.bind("<ButtonRelease-1>", endClicked)
canvas.grid(row=0, column=0, columnspan=3)


canvas.create_line((0, 250), (800, 250), fill='red')
canvas.create_line((400, 0), (400, 500), fill='blue')



def setImage():
    filename = askopenfilename() 
    img.image = PhotoImage(file=filename)
    if (img.addr != None) : canvas.delete(img.addr)
    img.draw(canvas)

def addNewTri():
    tri = triangle()
    triangles.append(tri)
    triDrawing = tri.drawTri(canvas)
    trianglesDrawing.append(triDrawing)
    
def clearBtnFunc():
    clearAll(canvas)

btnClear = Button(window, text="Clear all", command=clearBtnFunc)
btnAddTri = Button(window, text="Add triangle", command=addNewTri)
btnJoin = Button(window, text="Join", command=shiftPressed)
btnExport = Button(window, text="Export", command=generateCode)
btnImg = Button(window, text="img", command=setImage)
    


btnClear.grid(row=1, column=0)
btnAddTri.grid(row=1, column=1)
btnJoin.grid(row=1, column=2)
btnExport.grid(row=2, column=0)
btnImg.grid(row=2, column=1)

window.mainloop()