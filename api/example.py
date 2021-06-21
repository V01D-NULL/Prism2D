from prism2d.Prism2d import Console, Renderer

# Called before the first frame is executed
def Enter():
        Console.log("Hello engine")

# Called once per frame, use Update to modify the position of game objects
def Update():
        pass

# Called once per frame, used to update a position after update (if required)
def LateUpdate():
        pass

# Called once per frame, use only for rendering (Renderer.clear *must* be called first otherwise it will draw over your textures)
def RenderCycle():
        Renderer.clear(102, 153, 255) #Cornflower blue
        Renderer.render_texture("../res/epic.png", 100, 100)
