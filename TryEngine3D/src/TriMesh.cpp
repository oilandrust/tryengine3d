#include "TriMesh.h"
#include "Geometry/obj_load.h"
#include "CGLA\Vec2f.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

struct Vertex{
	Vec3f position;
	Vec3f normal;
	Vec2f texCoord0;
};

bool equals(const Vertex& v1, const Vertex& v2){
	return v1.normal == v2.normal && v1.position == v2.position && v1.texCoord0 == v2.texCoord0;
}

using namespace TR3D;

const RTTI TriMesh::TYPE("TriMesh", &Component::TYPE);

TriMesh::TriMesh(){
}
void buildSphere(Geometry::TriMesh& mesh){
	assert( mesh.geometry.no_vertices() == 0 );

	int slice = 5;
	int div = 10;

	mesh.geometry.add_vertex(Vec3f(0,0,1));
	mesh.normals.add_vertex(Vec3f(0,0,1));

	float phi = M_PI/slice;
	float z = cos(phi);
	for(int j = 0; j < div; j++){
		float theta = 2*j*M_PI/div;
		float x = cos(theta)*sin(phi);
		float y = sin(theta)*sin(phi);

		mesh.geometry.add_vertex(Vec3f(x,y,z));
		mesh.normals.add_vertex(Vec3f(x,y,z));
		if(j > 0){
			mesh.geometry.add_face(Vec3i(0,j,j+1));
			mesh.normals.add_face(Vec3i(0,j,j+1));
		}
	}
	mesh.geometry.add_face(Vec3i(0,div,1));
	mesh.normals.add_face(Vec3i(0,div,1));
	
	for(int i = 1; i < slice-1; i++){
		float phi = (i+1)*M_PI/slice;
		float z = cos(phi);

		for(int j = 0; j < div; j++){
			float theta = 2*j*M_PI/div;
			float x = cos(theta)*sin(phi);
			float y = sin(theta)*sin(phi);

			mesh.geometry.add_vertex(Vec3f(x,y,z));
			mesh.normals.add_vertex(Vec3f(x,y,z));

			if(j > 0){
				mesh.geometry.add_face(Vec3i((i-1)*div+j,     i*div+j,         i*div+1+j));
				mesh.geometry.add_face(Vec3i((i-1)*div+j+1  , (i-1)*div+j, i*div+1+j));
				mesh.normals.add_face(Vec3i((i-1)*div+j,     i*div+j,         i*div+1+j));
				mesh.normals.add_face(Vec3i((i-1)*div+j+1  , (i-1)*div+j, i*div+1+j));
			}
		}
		int lastIndex = mesh.geometry.no_vertices()-1;
		mesh.geometry.add_face( Vec3i(lastIndex-div,lastIndex,lastIndex-div+1) );
		mesh.geometry.add_face( Vec3i(lastIndex-2*div+1,lastIndex-div,lastIndex-div+1) );
		mesh.normals.add_face( Vec3i(lastIndex-div,lastIndex,lastIndex-div+1) );
		mesh.normals.add_face( Vec3i(lastIndex-2*div+1,lastIndex-div,lastIndex-div+1) );
	}

	mesh.geometry.add_vertex(Vec3f(0,0,-1));
	mesh.normals.add_vertex(Vec3f(0,0,-1));
	int pole = mesh.geometry.no_vertices()-1;

	phi = (slice-1)*M_PI/slice;
	z = cos(phi);
	for(int j = 0; j < div; j++){
		float theta = 2*j*M_PI/div;
		float x = cos(theta)*sin(phi);
		float y = sin(theta)*sin(phi);

		mesh.geometry.add_vertex(Vec3f(x,y,z));
		mesh.normals.add_vertex(Vec3f(x,y,z));
		if(j > 0){
			mesh.geometry.add_face(Vec3i(pole,mesh.geometry.no_vertices()-1,mesh.geometry.no_vertices()-2));
			mesh.normals.add_face(Vec3i(pole,mesh.geometry.no_vertices()-1,mesh.geometry.no_vertices()-2));
		}
	}
	mesh.geometry.add_face(Vec3i(pole,pole+1,mesh.geometry.no_vertices()-1));
	mesh.normals.add_face(Vec3i(pole,pole+1,mesh.geometry.no_vertices()-1));
	//Geometry::obj_load (string("assets/models/sphere.obj"), mesh);
}
void buildPlane(Geometry::TriMesh& mesh){
	mesh.geometry.add_vertex(Vec3f(-1,-1,0));//0
	mesh.geometry.add_vertex(Vec3f(1,-1,0)); //1
	mesh.geometry.add_vertex(Vec3f(1,1,0));  //2
	mesh.geometry.add_vertex(Vec3f(-1,1,0)); //3

	mesh.normals.add_vertex(Vec3f(0,0,1));
	
	mesh.texcoords.add_vertex(Vec3f(0,0,0));
	mesh.texcoords.add_vertex(Vec3f(0,1,0));
	mesh.texcoords.add_vertex(Vec3f(1,1,0));
	mesh.texcoords.add_vertex(Vec3f(1,0,0));

	mesh.geometry.add_face(Vec3i(0,1,2));
	mesh.geometry.add_face(Vec3i(0,2,3));
	mesh.texcoords.add_face(Vec3i(0,1,2));
	mesh.texcoords.add_face(Vec3i(0,2,3));
	mesh.normals.add_face(Vec3i(0));
	mesh.normals.add_face(Vec3i(0));
}
void buildCube(Geometry::TriMesh& mesh){
	mesh.geometry.add_vertex(Vec3f(-1,-1,-1));//0
	mesh.geometry.add_vertex(Vec3f(-1,1,-1)); //1
	mesh.geometry.add_vertex(Vec3f(1,1,-1));  //2
	mesh.geometry.add_vertex(Vec3f(1,-1,-1)); //3

	mesh.geometry.add_vertex(Vec3f(-1,-1,1)); //4
	mesh.geometry.add_vertex(Vec3f(-1,1,1));  //5
	mesh.geometry.add_vertex(Vec3f(1,1,1));   //6
	mesh.geometry.add_vertex(Vec3f(1,-1,1));  //7

	mesh.texcoords.add_vertex(Vec3f(0,0,0));
	mesh.texcoords.add_vertex(Vec3f(1,0,0));
	mesh.texcoords.add_vertex(Vec3f(1,1,0));
	mesh.texcoords.add_vertex(Vec3f(0,1,0));

	mesh.normals.add_vertex(Vec3f(1,0,0));
	mesh.normals.add_vertex(Vec3f(-1,0,0));
	mesh.normals.add_vertex(Vec3f(0,1,0));
	mesh.normals.add_vertex(Vec3f(0,-1,0));
	mesh.normals.add_vertex(Vec3f(0,0,1));
	mesh.normals.add_vertex(Vec3f(0,0,-1));
	
	//Bottom
	mesh.geometry.add_face(Vec3i(0,1,2));
	mesh.texcoords.add_face(Vec3i(0,1,2));
	mesh.geometry.add_face(Vec3i(2,3,0));
	mesh.texcoords.add_face(Vec3i(2,3,0));
	mesh.normals.add_face(Vec3i(5));
	mesh.normals.add_face(Vec3i(5));
	//Top
	mesh.geometry.add_face(Vec3i(5,4,6));
	mesh.texcoords.add_face(Vec3i(3,0,2));
	mesh.geometry.add_face(Vec3i(6,4,7));
	mesh.texcoords.add_face(Vec3i(2,0,1));
	mesh.normals.add_face(Vec3i(4));
	mesh.normals.add_face(Vec3i(4));
	//Y+
	mesh.geometry.add_face(Vec3i(1,5,2));
	mesh.texcoords.add_face(Vec3i(0,3,1));
	mesh.geometry.add_face(Vec3i(2,5,6));
	mesh.texcoords.add_face(Vec3i(1,3,2));
	mesh.normals.add_face(Vec3i(2));
	mesh.normals.add_face(Vec3i(2));
	//Y-
	mesh.geometry.add_face(Vec3i(0,3,4));
	mesh.texcoords.add_face(Vec3i(0,1,3));
	mesh.geometry.add_face(Vec3i(4,3,7));
	mesh.texcoords.add_face(Vec3i(3,1,2));
	mesh.normals.add_face(Vec3i(3));
	mesh.normals.add_face(Vec3i(3));
	//X+
	mesh.geometry.add_face(Vec3i(2,6,3));
	mesh.texcoords.add_face(Vec3i(1,2,0));
	mesh.geometry.add_face(Vec3i(3,6,7));
	mesh.texcoords.add_face(Vec3i(0,2,3));
	mesh.normals.add_face(Vec3i(0));
	mesh.normals.add_face(Vec3i(0));
	//X-
	mesh.geometry.add_face(Vec3i(0,5,1));
	mesh.texcoords.add_face(Vec3i(0,2,1));
	mesh.geometry.add_face(Vec3i(5,0,4));
	mesh.texcoords.add_face(Vec3i(2,0,3));
	mesh.normals.add_face(Vec3i(1));
	mesh.normals.add_face(Vec3i(1));
}
TriMesh::TriMesh(BasicShapeEnum shape){
	switch(shape){
		case 	CUBE:
			buildCube(mesh);
			this->ressourceName = "BasicShape/Cube";
		break;
		case SPHERE:
            buildSphere(mesh);
			this->ressourceName = "BasicShape/Sphere";
		break;
		case PLANE:
			buildPlane(mesh);
			this->ressourceName = "BasicShape/Plane";
		break;
		default:
			assert(false);
		break;
	}
    createVBO();
}


TriMesh::~TriMesh(){
	glDeleteBuffers(1,&VBOId);
	glDeleteBuffers(1,&iVBOId);
}

void TriMesh::load(const string& name){
	Ressource::load(name);

	this->loadOBJ(name);
	//this->mesh.compute_normals();

	createVBO();
}

void TriMesh::loadOBJ(const std::string& filename) {

	FILE *fp = fopen(filename.data(), "r");
	if (fp==0) {
		cerr << "File " << filename << " does not exist" << endl;
	}

	mesh.materials.resize(1);
	
	char buf[256];
	Vec3f v_geo;
	Vec3f v_normals;
	Vec3f v_texcoords;

	Vec3i f_geo;
	Vec3i f_normals;
	Vec3i f_texcoords;
	int current_material=0;
	int v,n,t;

	while(fscanf(fp, "%s", buf) != EOF) {
		switch(buf[0]) 
			{
			case '#': // A comment
				fgets(buf, sizeof(buf), fp);
				break;
			case 'm':
				fgets(buf, sizeof(buf), fp);
				sscanf(buf, "%s %s", buf, buf);
				//read_material_library(buf);
				break;
			case 'u':
				fgets(buf, sizeof(buf), fp);
				//sscanf(buf, "%s %s", buf, buf);
				//current_material = mesh.find_material(buf);
				break;
			case 'v': // v, vn, vt
				switch(buf[1]) 
					{
					case '\0': // vertex
						fscanf(fp, "%f %f %f", &v_geo[0], &v_geo[1], &v_geo[2]);
						mesh.geometry.add_vertex(v_geo);
						break;
					case 'n': // normal
						fscanf(fp, "%f %f %f", &v_normals[0], &v_normals[1], &v_normals[2]);
						mesh.normals.add_vertex(v_normals);
						break;
					case 't': // texcoord
						fscanf(fp, "%f %f", &v_texcoords[0], &v_texcoords[1]);
						v_texcoords[2]=1;
						mesh.texcoords.add_vertex(v_texcoords);
						break;
					}
				break;
			case 'f':
				v = n = t = 0;
				fscanf(fp, "%s", buf);
				// can be one of %d, %d//%d, %d/%d, %d/%d/%d 
				if(sscanf(buf, "%d/%d/%d", &v, &t, &n) == 3)
					{ // v/t/n
						
						f_geo[0]=get_vert(v); 
						f_texcoords[0]=get_texcoord(t);
						f_normals[0]=get_normal(n);

						fscanf(fp, "%d/%d/%d", &v, &t, &n); 
						f_geo[1]=get_vert(v); 
						f_texcoords[1]=get_texcoord(t);
						f_normals[1]=get_normal(n);

						fscanf(fp, "%d/%d/%d", &v, &t, &n); 
						f_geo[2]=get_vert(v); 
						f_texcoords[2]=get_texcoord(t);
						f_normals[2]=get_normal(n);

						int idx = mesh.geometry.add_face(f_geo);
						mesh.normals.add_face(f_normals, idx);
						mesh.texcoords.add_face(f_texcoords, idx);
						mesh.mat_idx.push_back(current_material);

						// Load a general polygon and convert to triangles
						while(fscanf(fp, "%d/%d/%d", &v, &t, &n)==3) 
							{
								f_geo[1]=f_geo[2];
								f_normals[1]=f_normals[2];
								f_texcoords[1]=f_texcoords[2];

								f_geo[2]=get_vert(v);
								f_normals[2]=get_normal(n);
								f_texcoords[2]=get_texcoord(t);

								int idx = mesh.geometry.add_face(f_geo);
								mesh.normals.add_face(f_normals, idx);
								mesh.texcoords.add_face(f_texcoords, idx);
								mesh.mat_idx.push_back(current_material);
							}
					} 
				else if (sscanf(buf, "%d//%d", &v, &n)==2)
					{// v//n 
						f_geo[0]=get_vert(v);
						f_normals[0]=get_normal(n);

						fscanf(fp, "%d//%d", &v, &n); 
						f_geo[1]=get_vert(v);
						f_normals[1]=get_normal(n);
						
						fscanf(fp, "%d//%d", &v, &n); 
						f_geo[2]=get_vert(v);
						f_normals[2]=get_normal(n);
						
						int idx = mesh.geometry.add_face(f_geo);
						mesh.normals.add_face(f_normals, idx);
						mesh.mat_idx.push_back(current_material);
						
						// Load a general polygon and convert to triangles
						while(fscanf(fp, "%d//%d", &v, &n)==2) 
							{
								f_geo[1]=f_geo[2];
								f_normals[1]=f_normals[2];
								f_geo[2]=get_vert(v);
								int idx = mesh.geometry.add_face(f_geo);
								mesh.normals.add_face(f_normals, idx);
								mesh.mat_idx.push_back(current_material);
							}
					} 
				else if (sscanf(buf, "%d/%d", &v, &t) == 2)
					{ // v/t 
						f_geo[0]=get_vert(v);
						f_texcoords[0]=get_texcoord(t);

						fscanf(fp, "%d/%d", &v, &t); 
						f_geo[1]=get_vert(v);
						f_texcoords[1]=get_texcoord(t);

						fscanf(fp, "%d/%d", &v, &t); 
						f_geo[2]=get_vert(v);
						f_texcoords[2]=get_texcoord(t);

						int idx = mesh.geometry.add_face(f_geo);
						mesh.texcoords.add_face(f_texcoords, idx);
						mesh.mat_idx.push_back(current_material);
				
						// Load a general polygon and convert to triangles
						while(fscanf(fp, "%d/%d", &v, &t)==2) 
							{
								f_geo[1]=f_geo[2];
								f_texcoords[1]=f_texcoords[2];
						
								f_geo[2]=get_vert(v);
								f_texcoords[2]=get_texcoord(t);

								int idx = mesh.geometry.add_face(f_geo);
								mesh.texcoords.add_face(f_texcoords, idx);
								mesh.mat_idx.push_back(current_material);
							}
					} 
				else if (sscanf(buf, "%d", &v)==1)
					{ // v 
						f_geo[0]=get_vert(v);
						
						fscanf(fp, "%d", &v);
						f_geo[1]=get_vert(v);
						
						fscanf(fp, "%d", &v);
						f_geo[2]=get_vert(v);
						
						mesh.geometry.add_face(f_geo);
						mesh.mat_idx.push_back(current_material);

						// Load a general polygon and convert to triangles
						while(fscanf(fp, "%d", &v)==1) 
							{
								f_geo[1]=f_geo[2];
								f_geo[2]=get_vert(v);
								mesh.geometry.add_face(f_geo);
								mesh.mat_idx.push_back(current_material);
							}
					}
				break;
			default:
				fgets(buf, sizeof(buf), fp);
				break;
			}
	}
	fclose(fp);
}

void TriMesh::read_material_library(const string& filename)
{
	string fn = filename;
	FILE* file = fopen(fn.data(), "r");
	if (!file) 
		{
			cerr << "Could not open " << filename << endl;
			return;
		}
		
	char  buf[128];
	unsigned int nummaterials=1;
		
	// count the number of materials in the file 
	while(fscanf(file, "%s", buf) != EOF) 
		{
			switch(buf[0]) 
				{
				case '#':				/* comment */
					/* eat up rest of line */
					fgets(buf, sizeof(buf), file);
					break;
				case 'n':				/* newmtl */
					fgets(buf, sizeof(buf), file);
					nummaterials++;
					sscanf(buf, "%s %s", buf, buf);
					break;
				default:
					/* eat up rest of line */
					fgets(buf, sizeof(buf), file);
					break;
				}
		}
	rewind(file);
	
	/* allocate memory for the materials */
	mesh.materials.resize(nummaterials);

	/* now, read in the data */
	nummaterials = 0;
	while(fscanf(file, "%s", buf) != EOF) {
		switch(buf[0]) {
		case '#':				/* comment */
			/* eat up rest of line */
			fgets(buf, sizeof(buf), file);
			break;
		case 'n':				/* newmtl */
			fgets(buf, sizeof(buf), file);
			sscanf(buf, "%s %s", buf, buf);
			nummaterials++;
			mesh.materials[nummaterials].name = buf;
			break;
		case 'N':
    switch(buf[1])
      {
      case 's':
			    fscanf(file, "%f", &mesh.materials[nummaterials].shininess);
			    /* wavefront shininess is from [0, 1000], so scale for OpenGL */
			    mesh.materials[nummaterials].shininess /= 1000.0;
			    mesh.materials[nummaterials].shininess *= 128.0;
        break;
      case 'i':
			    fscanf(file, "%f", &mesh.materials[nummaterials].ior_in);
        break;
				default:
					/* eat up rest of line */
					fgets(buf, sizeof(buf), file);
					break;
      }
			break;
		case 'K': 
			switch(buf[1]) 
				{
				case 'd':
					fscanf(file, "%f %f %f",
								 &mesh.materials[nummaterials].diffuse[0],
								 &mesh.materials[nummaterials].diffuse[1],
								 &mesh.materials[nummaterials].diffuse[2]);
					break;
				case 's':
					fscanf(file, "%f %f %f",
								 &mesh.materials[nummaterials].specular[0],
								 &mesh.materials[nummaterials].specular[1],
								 &mesh.materials[nummaterials].specular[2]);
					break;
				case 'a':
					fscanf(file, "%f %f %f",
								 &mesh.materials[nummaterials].ambient[0],
								 &mesh.materials[nummaterials].ambient[1],
								 &mesh.materials[nummaterials].ambient[2]);
					break;
				default:
					/* eat up rest of line */
					fgets(buf, sizeof(buf), file);
					break;
				}
			break;
  case 'T':
			fscanf(file, "%f %f %f",
           &mesh.materials[nummaterials].transmission[0],
           &mesh.materials[nummaterials].transmission[1],
           &mesh.materials[nummaterials].transmission[2]);
    break;
  case 'i':
			fscanf(file, "%d", &mesh.materials[nummaterials].illum);
    break;
		case 'm': // Map ... all maps are treated equally.
			{
				fscanf(file,"%s",buf);
				//mesh.materials[nummaterials].tex_path = pathname;
				mesh.materials[nummaterials].tex_name = string(buf);
			}
			break;
		default:
			/* eat up rest of line */
			fgets(buf, sizeof(buf), file);
			break;
		}
	}
    fclose(file);
}


void TriMesh::createVBO(){

	//CREAT AN indexed list of vertives (p,n,tc)
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	//FOR each face
	for(int i=0;i<mesh.geometry.no_faces();i++) {
		Vec3i n_face = mesh.normals.face(i);
		Vec3i g_face = mesh.geometry.face(i);
		Vec3i t_face = mesh.texcoords.face(i);

		//For each vertex of the face
		for(int j=0;j<3;j++) {
			//create the vertex
			Vec3f position = mesh.geometry.vertex(g_face[j]);
			Vec3f normal;
			Vec2f tc;

			if(n_face != NULL_FACE)	normal = mesh.normals.vertex(n_face[j]);
			else normal = Vec3f(0);
			if(t_face != NULL_FACE) tc = Vec2f(mesh.texcoords.vertex(t_face[j]));
			else tc = Vec2f(0);
			
			Vertex v = {position,normal,tc};

			//See if the vertex allready exists
			unsigned int index = -1;
			for(size_t k = 0; k < indices.size(); k++){
				if( equals(vertices[indices[k]], v) ){
					index = k;
					break;
				}
			}

			//add the vertex at the end of the vertex list and create a new index
			vertices.push_back(v);
			index = vertices.size()-1;
		
			indices.push_back(index);
		}
	}

	glGenBuffers(1,&VBOId);
	glBindBuffer(GL_ARRAY_BUFFER,VBOId);
	glBufferData(GL_ARRAY_BUFFER,
				vertices.size()*sizeof(Vertex),
				vertices[0].position.get(),
				GL_STATIC_DRAW);


	glGenBuffers(1,&iVBOId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,iVBOId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
				indices.size()*sizeof(unsigned int),
				&indices[0],
				GL_STATIC_DRAW);
}

void TriMesh::sendVertices()const{
	
	glBindBuffer(GL_ARRAY_BUFFER,VBOId);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(0));
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(12));
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(24));
	/*
	glEnableVertexAttribArray(0);    //We like submitting vertices on stream 0 for no special reason
	 glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(0));   //The starting point of the VBO, for the vertices
	 glEnableVertexAttribArray(1);    //We like submitting normals on stream 1 for no special reason
	 glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(12));     //The starting point of normals, 12 bytes away
	 glEnableVertexAttribArray(2);    //We like submitting texcoords on stream 2 for no special reason
	 glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(24));   //The starting point of texcoords, 24 bytes away
	 */
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iVBOId);
	glDrawElements(GL_TRIANGLES, 3*mesh.geometry.no_faces(), GL_UNSIGNED_INT, BUFFER_OFFSET(0));

	glDisableClientState(GL_VERTEX_ARRAY);  
	glDisableClientState(GL_NORMAL_ARRAY);  
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);  
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	/*
	//Drawing with vertex arrays	
	glEnableClientState(GL_VERTEX_ARRAY);			
	glVertexPointer(3, GL_FLOAT, 0, (float*)mesh.geometry.vertex(0).get());		
	glDrawElements(GL_TRIANGLES, 3*mesh.geometry.no_faces(), GL_UNSIGNED_INT, (unsigned int*)mesh.geometry.face(0).get());		
	glDisableClientState(GL_VERTEX_ARRAY);		
	*/

	/* MODEL FOR VBO DRAWING
		//Load vertices		
		glBindBuffer(GL_ARRAY_BUFFER, this->mesh->vbo_vertices);		
		glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));		
		glEnableClientState(GL_VERTEX_ARRAY);		
		//Load normals		
		glBindBuffer(GL_ARRAY_BUFFER, this->mesh->vbo_normals);		
		glNormalPointer(GL_FLOAT, 0, BUFFER_OFFSET(0));		
		glEnableClientState(GL_NORMAL_ARRAY);		
		//Load UVs		
		glBindBuffer(GL_ARRAY_BUFFER, this->mesh->vbo_uvs);		
		glTexCoordPointer(2, GL_FLOAT, 0, BUFFER_OFFSET(0));		
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);		

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mesh->vbo_index);		
		glDrawElements(GL_TRIANGLES, 3*this->mesh->numFaces, GL_UNSIGNED_INT, BUFFER_OFFSET(0));	

		glDisableClientState(GL_VERTEX_ARRAY);		
		glDisableClientState(GL_NORMAL_ARRAY);		
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		*/
		
	/*
	glBegin(GL_TRIANGLES);
	for(int i=0;i<mesh.geometry.no_faces();i++) {
		Vec3i n_face = mesh.normals.face(i);
		Vec3i g_face = mesh.geometry.face(i);
		Vec3i t_face = mesh.texcoords.face(i);
		for(int j=0;j<3;j++) {
			if(n_face != NULL_FACE){
				Vec3f norm = mesh.normals.vertex(n_face[j]);
				glNormal3fv(norm.get());
			}
			if(t_face != NULL_FACE){
				Vec3f texc = mesh.texcoords.vertex(t_face[j]);
				glTexCoord2fv(texc.get());
			}
			Vec3f vert = mesh.geometry.vertex(g_face[j]);
			glVertex3fv(vert.get());		
		}
	}
	glEnd();
	*/
}
