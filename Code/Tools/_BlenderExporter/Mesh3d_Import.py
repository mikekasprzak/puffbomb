#!BPY

"""
Name: 'PuffBOMB (.mesh3d)...'
Blender: 232
Group: 'Import'
Tooltip: 'Import a PuffBOMB mesh3d File'
"""

__author__ = "Richard Kasprzak"
__url__ = ("blender", "blender",
"N/A")
__version__ = "0.1"

__bpydoc__ = """\
This script imports our internal PuffBOMB Hammer engine .mesh3d files

"""

# $Id: Mesh3d_Import.py,v 1.10 2007/01/27 04:58:09 campbellbarton Exp $
#

# ***** BEGIN GPL LICENSE BLOCK *****
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software Foundation,
# Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
#
# ***** END GPL LICENCE BLOCK *****

import Blender

def read(filename):
        globalUVCoords = []
        globalNormals = []

        Blender.Window.WaitCursor(1)
        name = filename.split('\\')[-1].split('/')[-1]
        mesh = Blender.NMesh.New( name ) # create a new mesh
        # parse the file
        state = 0
        
        file = open(filename, 'r')
        for line in file.readlines():
                words = line.split()
                if len(words) == 0 or words[0].startswith('#'):
                        pass
                elif words[0] == 'Vertices':
                        state = 0
                elif words[0] == 'TextureCoord':
                        state = 1
                elif words[0] == 'VertexNormal':
                        state = 2
                elif words[0] == 'TextureName':
                        state = 3
                elif words[0] == 'FUN':
                        state = 4
                elif words[0] == 'Used':
                        state = 5
                elif state == 0:
                        x, y, z = float(words[0]), float(words[1]), float(words[2])
                        mesh.verts.append(Blender.NMesh.Vert(x, y, z))
                elif state == 1:
                        globalUVCoords.append(float(words[0]))
                        globalUVCoords.append(float(words[1]))
                        globalUVCoords.append(float(words[2]))
#                        a, b, c = float(words[0]), float(words[1]), float(words[2])
#                        mesh.verts.append(Blender.NMesh.Vert(x, y, z))
                elif state == 2:
                        globalNormals.append(float(words[0]))
                        globalNormals.append(float(words[1]))
                        globalNormals.append(float(words[2]))


#                        x, y, z = float(words[0]), float(words[1]), float(words[2])
#                        mesh.verts.append(Blender.NMesh.Vert(x, y, z))
                elif state == 4:
                        faceVertList = []
                        va, vb, vc = int(words[0]), int(words[4]), int(words[8])
                        faceVert = mesh.verts[va]
                        faceVertList.append(faceVert)
                        faceVert = mesh.verts[vb]
                        faceVertList.append(faceVert)
                        faceVert = mesh.verts[vc]
                        faceVertList.append(faceVert)

                        newFace = Blender.NMesh.Face(faceVertList)
                        mesh.addFace(newFace)

                        mesh.hasVertexColours(True)
#                        print int(words[3]) & 0xff
#                        print ( int(words[3]) >> 8 ) & 0xff
#                        print ( int(words[3]) >> 16 ) & 0xff
#                        print ( int(words[3]) >> 24 ) & 0xff
                       
                        mesh.faces[int( len(mesh.faces) ) - 1].col.append(Blender.NMesh.Col( int(words[3]) & 0xff,( int(words[3]) >> 8 ) & 0xff, ( int(words[3]) >> 16 ) & 0xff, ( int(words[3]) >> 24 ) & 0xff  ))
                        mesh.faces[int( len(mesh.faces) ) - 1].col.append(Blender.NMesh.Col( int(words[7]) & 0xff,( int(words[7]) >> 8 ) & 0xff, ( int(words[7]) >> 16 ) & 0xff, ( int(words[7]) >> 24 ) & 0xff  ))
                        mesh.faces[int( len(mesh.faces) ) - 1].col.append(Blender.NMesh.Col( int(words[11]) & 0xff,( int(words[11]) >> 8 ) & 0xff, ( int(words[11]) >> 16 ) & 0xff, ( int(words[11]) >> 24 ) & 0xff  ))
                        
                        
#                        UVList = []
#                        uva, uvb, uvc = int(words[1]), int(words[5]), int(words[9])
#                        TempUV = mesh.verts[va]
#                        UVList.append(TempUV)
#                        TempUV = mesh.verts[vb]
#                        UVList.append(TempUV)
#                        TempUV = mesh.verts[vc]
#                        UVList.append(TempUV)
                                
        
        # link the mesh to a new object
        ob = Blender.Object.New('Mesh', name) # Mesh must be spelled just this--it is a specific type
        ob.link(mesh) # tell the object to use the mesh we just made
        scn = Blender.Scene.GetCurrent()
        for o in scn.getChildren(): 
                o.sel = 0
        
        scn.link(ob) # link the object to the current scene
        ob.sel= 1
        ob.Layers = scn.Layers
        Blender.Window.WaitCursor(0)
        Blender.Window.RedrawAll()

def fs_callback(filename):
	read(filename)

if __name__ == '__main__':
	Blender.Window.FileSelector(fs_callback, "Import Mesh3D", "*.mesh3d")
