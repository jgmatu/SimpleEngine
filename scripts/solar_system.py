import bpy
import mathutils
import math
import syslog

syslog.syslog(syslog.LOG_ERR, "{}".format("********* START **************"))

def __earthAuxMove(earthAux, _frame):
    # Generar el movimiento de traslación en dos pasos de rotación y traslación.
    angle = math.radians(_frame)
    R = mathutils.Matrix.Rotation(angle, 4, 'Z')
    T = mathutils.Matrix.Translation(mathutils.Vector((0.0, 10.0, 0.0)))

    # Añadir la tralaciónd e la tierra a la matriz local del objeto.
    earthAux.matrix_local = R @ T

    # Añadir el movimiento a la animación por cada frame
    earthAux.keyframe_insert("location", frame=_frame, index=-1)

    # Trazas de depuración
    syslog.syslog(syslog.LOG_ERR, "EarthAux Position: {}".format(earthAux.matrix_local.to_translation()))
    syslog.syslog(syslog.LOG_ERR, "EarthAux Angle: {}".format(angle))

def __earthMove(earth, _frame):
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

def __moonMove(moon, _frame):
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

def __moonAuxMove(moonAux, _frame):    
    # Generar el movimiento de traslación en dos pasos de rotación y traslación.
    angle = math.radians(_frame)
    R = mathutils.Matrix.Rotation(-angle, 4, 'Z')
    T = mathutils.Matrix.Translation(mathutils.Vector((1.0, -2.0, 0.0)))

    # Añadir la tralaciónd e la tierra a la matriz local del objeto.
    moonAux.matrix_local = R @ T

    # Añadir el movimiento a la animación por cada frame
    moonAux.keyframe_insert("location", frame=_frame, index=-1)

    # Trazas de depuración
    syslog.syslog(syslog.LOG_ERR, "EarthAux Position: {}".format(moonAux.matrix_local.to_translation()))
    syslog.syslog(syslog.LOG_ERR, "EarthAux Angle: {}".format(angle))


EarthAux = bpy.data.objects["EarthAux"]
Earth = bpy.data.objects["Earth"]

MoonAux = bpy.data.objects["MoonAux"] 
Moon = bpy.data.objects["Moon"]

# Render loop
for frame in range(1, 360):
    # Movimiento de traslación de la tierra
    __earthAuxMove(EarthAux, frame)

    # Movimiento de rotación de la tierra
    __earthMove(Earth, frame)
    
    # Movimiento de rotación de la luna
    __moonMove(Moon, frame)

    # Movimiento de traslacion de la luna
    __moonAuxMove(MoonAux, frame)

syslog.syslog(syslog.LOG_ERR, "{}".format("********* END **************"))



