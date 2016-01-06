#ifndef GLSLSHADER_H_INCLUDED
#define GLSLSHADER_H_INCLUDED

#include <string>
#include <iostream>
#include <fstream>

#include "includeGL.h"
#include "Component.h"

using namespace std;

/**
 *A class encaplulation (very quickly) a GLSL shader, typicaly attached to a Material.
 */
class GLSLShader:public Component{
	public :
		static const RTTI TYPE;
		virtual const RTTI& getType() const{ return TYPE; }

	protected:
		GLuint vs_object;
		GLuint fs_object;
		GLuint prog_object;
		std::string ressourceName;

	public:
		GLSLShader();
		GLSLShader(const string& path, const string& vertexShaderPath, const string& fragmentShaderPath);
		~GLSLShader();

		void bindShader()const;
		GLuint getShaderProgramId()const;
	private:
		//Serialization
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version){
			// serialize base class information
			ar & boost::serialization::base_object<Object>(*this);
			ar & ressourceName;
		}
};

 /// Print the info log for a program if the status is not OK.
  void print_glsl_program_log(GLuint program);

  /// Print the info log for a shader if the status is not OK.
  void print_glsl_shader_log(GLuint shader);
  
  /** The two arguments are concatenated to form the name with full path of a text file.
    This file is read and returned as a string. */
  const std::string read_glsl_source(const std::string& path, const std::string& file);
  
  /** Create a shader of type specified by the first argument from a source string given
    as second argument.  Return shader handle. If there is a problem, the infolog is 
    printed and 0 is returned (unless the third argument is false). */
  GLuint create_glsl_shader(GLuint stype, const std::string& src, bool print_log = true);
    
  /** Create a shader of type specified as first argument from the file indicated by the 
    supplied path and file name (second and third arguments) and return a shader handle. 
    This function is only a convenience function wrapping read_glsl_source and 
    create_glsl_shader */
  GLuint create_glsl_shader(GLuint stype, const std::string& path, const std::string& file);


#endif
