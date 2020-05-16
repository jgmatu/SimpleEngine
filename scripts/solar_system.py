import bpy
import mathutils
import math
import syslog

syslog.syslog(syslog.LOG_ERR, "{}".format("********* START **************"))

for obj in bpy.data.objects:
    syslog.syslog(syslog.LOG_ERR, "{}".format(obj.name))
    
EarthAux = bpy.data.objects["EarthAux"]


def __earthAuxMove(earthAux, _frame):
    angle = math.radians(_frame)
    R = mathutils.Matrix.Rotation(angle, 4, 'Z')
    T = mathutils.Matrix.Translation(mathutils.Vector((0.0, 4.0, 0.0)))
    earthAux.matrix_local = R @ T
    earthAux.keyframe_insert("location", frame=_frame, index=-1)
    syslog.syslog(syslog.LOG_ERR, "Position: {}".format(EarthAux.matrix_local.to_translation()))
    syslog.syslog(syslog.LOG_ERR, "Angle: {}".format(angle))
    
for i in range(1, 360):
    __earthAuxMove(EarthAux, i)

syslog.syslog(syslog.LOG_ERR, "{}".format("********* END **************"))

#EarthAux = bpy.data.objects["EarthAux"].matrix_local.to_translation()
