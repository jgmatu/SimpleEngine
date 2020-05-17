import bpy
import mathutils
import math
import syslog
import time

t0 = -1
def timer(scene):
    global t0
    t1 = time.clock()
    fps = scene.render.fps  / scene.render.fps_base
    ms = 1000 * (t1 - t0)
    fps = min(fps, (1000 / ms))
#    syslog.syslog(syslog.LOG_ERR, "Fps : {}".format(fps))
    t0 = t1

def __earthAuxMove(_frame):
    earthAux = bpy.data.objects["EarthAux"]

    # Generar el movimiento de traslación en dos pasos de rotación y traslación.
    angle = math.radians(_frame)
    R = mathutils.Matrix.Rotation(angle, 4, 'Z')
    T = mathutils.Matrix.Translation(mathutils.Vector((0.0, 25.0, 0.0)))

    # Añadir la tralaciónd e la tierra a la matriz local del objeto.
    earthAux.matrix_local = R @ T

    # Añadir el movimiento a la animación por cada frame
    earthAux.keyframe_insert("location", frame=_frame, index=-1)

    # Trazas de depuración
    syslog.syslog(syslog.LOG_ERR, "EarthAux Position: {}".format(earthAux.matrix_local.to_translation()))
    syslog.syslog(syslog.LOG_ERR, "EarthAux Angle: {}".format(angle))

def __earthMove(_frame):
    earth = bpy.data.objects["Earth"]
    
    # Generar el movimiento de rotación.
    angle = math.radians(_frame) * (-1)
    R = mathutils.Matrix.Rotation(angle, 4, 'Z')

    # Añadir la rotación e la tierra a la matriz local del objeto.
    earth.matrix_local = R

    earth.scale = (0.5, 0.5, 0.5)

    # Añadir a la animación la rotación de la tierra.
    earth.keyframe_insert("rotation_euler", frame=_frame, index=-1)

    # Trazas de depuración
    syslog.syslog(syslog.LOG_ERR, "Earth Position: {}".format(earth.matrix_local.to_translation()))
    syslog.syslog(syslog.LOG_ERR, "Earth Angle: {}".format(angle))

def __moonMove(_frame):
    moon = bpy.data.objects["Moon"]

    # Generar el movimiento de rotación.
    angle = math.radians(_frame) * (-1)
    R = mathutils.Matrix.Rotation(angle, 4, 'Z')

    # Añadir la rotación e la tierra a la matriz local del objeto.
    moon.matrix_local = R

    moon.scale = (0.25, 0.25, 0.25)

    # Añadir a la animación la rotación de la tierra.
    moon.keyframe_insert("rotation_euler", frame=_frame, index=-1)

    # Trazas de depuración
    syslog.syslog(syslog.LOG_ERR, "Moon Position: {}".format(moon.matrix_local.to_translation()))
    syslog.syslog(syslog.LOG_ERR, "Moon Angle: {}".format(angle))

def __moonAuxMove(_frame):
    moonAux = bpy.data.objects["MoonAux"] 
   
    # Generar el movimiento de traslación en dos pasos de rotación y traslación.
    angle = math.radians(_frame)
    R = mathutils.Matrix.Rotation(2.0 * angle, 4, 'Z')
    T = mathutils.Matrix.Translation(mathutils.Vector((1.0, -2.0, 0.0)))

    # Añadir la tralaciónd e la tierra a la matriz local del objeto.
    moonAux.matrix_local = R @ T

    # Añadir el movimiento a la animación por cada frame
    moonAux.keyframe_insert("location", frame=_frame, index=-1)

    # Trazas de depuración
    syslog.syslog(syslog.LOG_ERR, "MoonAux Position: {}".format(moonAux.matrix_local.to_translation()))
    syslog.syslog(syslog.LOG_ERR, "MoonAux Angle: {}".format(angle))

syslog.syslog(syslog.LOG_ERR, "{}".format("********* START **************"))

def __marsAuxMove(_frame):
    marsAux = bpy.data.objects["MarsAux"] 
   
    # Generar el movimiento de traslación en dos pasos de rotación y traslación.
    angle = math.radians(_frame)
    R = mathutils.Matrix.Rotation(angle, 4, 'Z')
    T = mathutils.Matrix.Translation(mathutils.Vector((30.0, 30.0, 0.0)))

    # Añadir la tralaciónd e la tierra a la matriz local del objeto.
    marsAux.matrix_local = R @ T

    # Añadir el movimiento a la animación por cada frame
    marsAux.keyframe_insert("location", frame=_frame, index=-1)

    # Trazas de depuración
    syslog.syslog(syslog.LOG_ERR, "MarsAux Position: {}".format(marsAux.matrix_local.to_translation()))
    syslog.syslog(syslog.LOG_ERR, "MarsAux Angle: {}".format(angle))

syslog.syslog(syslog.LOG_ERR, "{}".format("********* START **************"))

def __traslationPlanet(planet, position, angle, _frame):
    # Generar el movimiento de traslación en dos pasos de rotación y traslación.
    angle = math.radians(_frame)
    R = mathutils.Matrix.Rotation(angle, 4, 'Z')
    T = mathutils.Matrix.Translation(mathutils.Vector(position))

    # Añadir la tralaciónd e la tierra a la matriz local del objeto.
    planet.matrix_local = R @ T

    # Añadir el movimiento a la animación por cada frame
    planet.keyframe_insert("location", frame=_frame, index=-1)

    # Trazas de depuración
    syslog.syslog(syslog.LOG_ERR, "Planet: {} -> Position: {}".format(planet.name, planet.matrix_local.to_translation()))
    syslog.syslog(syslog.LOG_ERR, "Planet: {} -> Angle: {}".format(planet.name, angle))

    
def __rotationPlanet(planet, rotation, scale, _frame):
    R = mathutils.Matrix.Rotation(rotation, 4, 'Z')

    # Añadir la rotación e la tierra a la matriz local del objeto.
    planet.matrix_local = R
    planet.scale = scale

    # Añadir a la animación la rotación de la tierra.
    planet.keyframe_insert("rotation_euler", frame=_frame, index=-1)

    # Trazas de depuración
    syslog.syslog(syslog.LOG_ERR, "Planet: {} -> Position: {}".format(planet.name, planet.matrix_local.to_translation()))
    syslog.syslog(syslog.LOG_ERR, "Planet: {} -> Angle: {}".format(planet.name, rotation))

# Render loop
for frame in range(1, 360):
    # Earth Movement
    __traslationPlanet(bpy.data.objects["EarthAux"], (0.0, 25.0, 0.0), math.radians(frame), frame)
    __rotationPlanet(bpy.data.objects["Earth"], math.radians((-2.0) * frame), (1.00, 1.00, 1.00), frame)
    
    # Moon Movement
    __traslationPlanet(bpy.data.objects["MoonAux"], (0.0, -3.0, 0.0), (-2) * math.radians(frame), frame)
    __rotationPlanet(bpy.data.objects["Moon"], math.radians(frame), (0.25, 0.25, 0.25), frame)

    # Movimiento de traslacion de marte
    __traslationPlanet(bpy.data.objects["MarsAux"], (30.0, 30.0, 0.0), math.radians((5) * frame), frame)
    __rotationPlanet(bpy.data.objects["Mars"], math.radians(frame), (1.00, 1.00, 1.00), frame)

# Observer frame rate per seconds
bpy.app.handlers.frame_change_post.append(timer)

syslog.syslog(syslog.LOG_ERR, "{}".format("********* END **************"))
