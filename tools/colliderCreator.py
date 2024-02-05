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
    """
    Translates the given position to the center of the canvas.
    
    Args:
        pos (list): The position to be translated.
        
    Returns:
        list: The translated position.
    """
    out = [pos[0] + center_x, pos[1] + center_y]
    return out

def drawRound(pos, cnv, size):
    """
    Draws a round shape on the canvas.
    
    Args:
        pos (list): The position of the center of the round shape.
        cnv (Canvas): The canvas on which to draw the round shape.
        size (int): The size of the round shape.
        
    Returns:
        int: The id of the drawn round shape on the canvas.
    """
    topLeft = [pos[0] - size, pos[1] - size]
    bottomRight = [pos[0] + size, pos[1] + size]
    return cnv.create_oval(topLeft, bottomRight)
    
class image :
    def __init__(self):
        self.image = None
        self.addr = None

    def draw(self, cnv):
        """
        Draws the image on the canvas.
        
        Args:
            cnv (Canvas): The canvas on which to draw the image.
        """
        if (self.image != None):
            self.addr = cnv.create_image(center_x, center_y,image= self.image)

class triangle :
    def __init__(self):
        self.a = toCenter([15, -5])
        self.b = toCenter([-5, 15])
        self.c = toCenter([15, 15])
        self.size = 5
    
    def isOn(self, x, y, size = None):
        """
        Checks if the given point is inside the triangle.
        
        Args:
            x (int): The x-coordinate of the point.
            y (int): The y-coordinate of the point.
            size (int, optional): The size of the triangle. Defaults to None.
        
        Returns:
            int: The index of the point inside the triangle, or -1 if the point is not inside the triangle.
        """
        if (size == None): size = self.size
        index = 0
        for pts in [self.a, self.b, self.c]:
            if (size >= pts[0] - x >= - size and size >= pts[1] - y >= - size) : return index 
            index += 1
        return -1
    
    
    def setPos(self, index, x, y):
        """
        Sets the position of a point in the triangle.
        
        Args:
            index (int): The index of the point to be set.
            x (int): The new x-coordinate of the point.
            y (int): The new y-coordinate of the point.
        """
        [self.a, self.b, self.c][index][0] = x
        [self.a, self.b, self.c][index][1] = y
    
    def drawTri(self, cnv):
        """
        Draws the triangle on the canvas.
        
        Args:
            cnv (Canvas): The canvas on which to draw the triangle.
        
        Returns:
            list: The ids of the drawn lines and round shapes on the canvas.
        """
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
    """
    Clears the canvas and redraws the axes.
    
    Args:
        cnv (Canvas): The canvas to be cleared.
    """
    cnv.delete('all')
    cnv.create_line((0, 250), (800, 250), fill='red')
    cnv.create_line((400, 0), (400, 500), fill='blue')
    trianglesDrawing.clear()

window = Tk()
window.title("Collider creator")
window.geometry('800x600')



def clicked(event):
    """
    Handles the click event on the canvas.
    
    Args:
        event (Event): The click event.
    """
    global selected
    index = 0
    for tri in triangles:
        ison = tri.isOn(event.x, event.y)
        if (ison >= 0) :
            selected = (index, ison)
            break
        index += 1

def endClicked(event):
    """
    Handles the release of the mouse button on the canvas.
    
    Args:
        event (Event): The release event.
    """
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
    """
    Toggles the join mode.
    """
    global join
    join = not join

def generateCode():
    """
    Generates the code for the triangles and copies it to the clipboard.
    """
    out = f"// All the triangle's points \n point triPoints[{len(triangles)}][3] = " + "{\n"
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
    """
    Sets the image to be displayed on the canvas.
    """
    filename = askopenfilename() 
    img.image = PhotoImage(file=filename)
    if (img.addr != None) : canvas.delete(img.addr)
    img.draw(canvas)

def addNewTri():
    """
    Adds a new triangle to the canvas.
    """
    tri = triangle()
    triangles.append(tri)
    triDrawing = tri.drawTri(canvas)
    trianglesDrawing.append(triDrawing)
    
def clearBtnFunc():
    """
    Clears all the triangles from the canvas.
    """
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