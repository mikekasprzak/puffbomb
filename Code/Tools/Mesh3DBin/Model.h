// - ------------------------------------------------------------------------------------------ - //
// StaticObject //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Rendo_Model_H__
#define __Rendo_Model_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <vector>
#include <string>
//#include <GL/glu.h>
//#include <SDL/SDL.h>
// - ------------------------------------------------------------------------------------------ - //
//#include <Util/Debug.h>

#include "../../Library/ClassDesigner/Set.h"
//#include "../../Library/Geometry/Rect.h"
//#include <Math/Vector.h>
//#include <Geometry/Rect.h>

//#include <Graphics/TexturePool.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// How to improve the Model, a discussion had on July 17th, 2006 //
//
// Remove the concept of group, and unify it with Object.  Object probably needs a better name, as
// at this point, object would be whatever contains all faces and each associated texture.  In fact
// the group/object should become face, and the elements in face now are something else.
//
// This unification would bring vertices directly in to the Model object.  Thus, there being a
// pool of vertices.  Pretty cool.
//
// An optimization for the future, adding quad support.  The idea for the quads is the current
// concept of Face, becomes triangle face, and a new "face" is created called Quad face, with ABCD
// parts.  This has obvious storage advantages, as the same data stored as 6 faces, can be stored
// as 4.   
//
// Another optimization for the future, triangle strips.  This would require processing to build
// the triangle strips, but should be able to even better utilize video memory.
//
// Quads and alternate textures have a potential sorting problem, at least to achive always correct
// occlusion of visible regions.  A quad, would likely exist in a list much like the current
// triangle faces.  As you draw the model, you need to make the decision which one (triangles or
// quads) to draw first.  So no matter what, there from this is always the potential to have a
// sorting problem, because a quad or triangele could occlude another one.
//
// Alternate textures sorting problem is similar.  Each set of faces having an associated texture
// needs to be drawn eventually.  So drawing one before the other, could cause them to occlude
// eachother.
//
// The only solution to this sort of occlusion is to decompose an object into convex regions in 3d
// space.  Say, a head, an upper body, arms at each joint, etc...  Technically, tools that analize
// a mesh and bone structure could determine through some means where these occludable shapes are,
// and some engine internally would have to sort them respectfully to the camera.  Sounds
// complicated, but I wonder if Crysis does this?
//
// Again, this is to achieve the possibility of complex semitransparent objects, like ghost people.
// This either achives correct occlusion, so you don't see through someones head, or so you do see
// through someones head, like they were made of glass.  Cool!
//
// Duplicate vertices, UV's, and normals could be eliminated to save space.  Normal's and vertices
// could be merged together, but who cares.
//
// Once we get to bone system's, the model, or a derivative of it, will require a system of bone
// weights.  These weights will remain constant, as will UV co-ordinates.  However, a model
// will need to have a varying list of vertices and vertex normals to reflect the trasformations
// achived through the bone structure.
// - ------------------------------------------------------------------------------------------ - //

class cLevelData;

// - ------------------------------------------------------------------------------------------ - //
class cModel {
public:
	// - -------------------------------------------------------------------------------------- - //
//	typedef Rect3D RectType;
//	RectType BoundingRect;
	// - -------------------------------------------------------------------------------------- - //
	class cObject {
	public:
		// - ---------------------------------------------------------------------------------- - //
		class cGroup {
		public:
			// - ------------------------------------------------------------------------------ - //
			bool NoCollision;
			// - ------------------------------------------------------------------------------ - //
			class cFace {
			public:
				ABCSet<int> Vertex;
				ABCSet<int> UV;
				ABCSet<int> Normal;
				ABCSet<unsigned int> VertColor;
			};
			// - ------------------------------------------------------------------------------ - //
			// Parts of all the faces //
			std::vector< cFace > Face;
			// The texture used //
			unsigned int TextureID;
			std::string TextureName;
			// - ------------------------------------------------------------------------------ - //			
		public:
			cGroup() :
				NoCollision( false ),
				TextureID( 0 )
			{
			}
			
			void clear() {
				Face.clear();
				NoCollision = false;
//				TextureID = 0;
			}
			
			size_t size() {
				return Face.size();	
			}
		};
		// - ---------------------------------------------------------------------------------- - //
	public:
		//std::vector< Vector3D > Vertex;
		std::vector< ABCSet< float >  > Vertex;
			
		std::vector< cGroup > Group;

	public:
		void clear() {
			Vertex.clear();
			Group.clear();
		}
		
		~cObject();
	};
	// - -------------------------------------------------------------------------------------- - //
//	std::vector< Vector3D > TextureCoord;
//	std::vector< Vector3D > VertexNormal;
	std::vector< ABCSet< float > > TextureCoord;
	std::vector< ABCSet< float > > VertexNormal;
	std::vector< cObject > Object;
	// - -------------------------------------------------------------------------------------- - //
	
	std::string PathName;

	cModel()
	{
		
	}
	cModel( const std::string& FileName )
	{
		Load( FileName );
//		CalcBoundingRect();
	}
	~cModel();

	void clear();
	
	//void Draw( const cLevelData* MyModel );

public:	
	// - -------------------------------------------------------------------------------------- - //	

	void Load( const std::string& FileName );
	
	/*inline void CalcBoundingRect() {
		Vector3D P1 = Object[0].Vertex[0];
		Vector3D P2 = Object[0].Vertex[0];
		
		for ( size_t idx = 0; idx < Object.size(); idx++ ) {
			for ( size_t idx2 = 0; idx2 < Object[idx].Vertex.size(); idx2++ ) {
				P1 = Object[idx].Vertex[idx2].Min( P1 );
				P2 = Object[idx].Vertex[idx2].Max( P2 );
			}
		}
		
		BoundingRect = RectType::Pair( P1, P2 );
	}
*/
	class cToMesh3d
	{
	public:
		std::vector<  ABCSet< float > > Vertex;
		std::vector<  ABCSet< float > > VertexNormal;
		std::vector<  unsigned int > VertexColor;
		std::vector<  unsigned int > Indicies;
		std::vector<  ABSet< float > > TextureCoord;
	
		//TexturePool::Texture TextureID;
	
	public:
		void clear()
		{
			Vertex.clear();
			VertexNormal.clear();
			VertexColor.clear();
			Indicies.clear();
			TextureCoord.clear();
		}
	};
	void SaveBin( char* NewName );

	// - -------------------------------------------------------------------------------------- - //	
};

// - ------------------------------------------------------------------------------------------ - //
#endif // __Rendo_Model_H__ //
// - ------------------------------------------------------------------------------------------ - //
