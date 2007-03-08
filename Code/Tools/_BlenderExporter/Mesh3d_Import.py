#!BPY

"""
Name: 'PuffBOMB (.mesh3d)'
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

import Blender, meshtools

# ================================
# === Read SLP Triangle Format ===
# ================================
def read(filename):
	#start = time.clock()
	file = open(filename, "rb")

	raw = []
	for line in file.xreadlines():
		data = line.split()
		if data[0] == "vertex":
			vert = map(float, data[1:])
			raw.append(vert)
	
	tri = []
	for i in xrange(0, len(raw), 3):
		tri.append(raw[i] + raw[i+1] + raw[i+2])

	#$import pprint; pprint.pprint(tri)

	# Collect data from RAW format
	faces = []
	for line in tri:
		f1, f2, f3, f4, f5, f6, f7, f8, f9 = line
		faces.append([(f1, f2, f3), (f4, f5, f6), (f7, f8, f9)])

	# Generate verts and faces lists, without duplicates
	verts = []
	coords = {}
	index = 0
	for i in xrange(len(faces)):
		for j in xrange(len(faces[i])):
			vertex = faces[i][j]
			if not coords.has_key(vertex):
				coords[vertex] = index
				index += 1
				verts.append(vertex)
			faces[i][j] = coords[vertex]

	objname = Blender.sys.splitext(Blender.sys.basename(filename))[0]

	meshtools.create_mesh(verts, faces, objname)
	Blender.Window.DrawProgressBar(1.0, '')  # clear progressbar
	file.close()
	#end = time.clock()
	#seconds = " in %.2f %s" % (end-start, "seconds")
	message = "Successfully imported " + Blender.sys.basename(filename)# + seconds
	meshtools.print_boxed(message)

def fs_callback(filename):
	read(filename)

if __name__ == '__main__':
	Blender.Window.FileSelector(fs_callback, "Import Mesh3D", "*.mesh3d")
