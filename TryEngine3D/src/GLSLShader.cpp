#include "GLSLShader.h"
#include "Component.h"

const RTTI GLSLShader::TYPE("GLSLShader", &Component::TYPE);

GLSLShader::GLSLShader():vs_object(0),fs_object(0),ressourceName("None"){
} 
GLSLShader::GLSLShader(const string& path, const string& vertexShaderPath, const string& fragmentShaderPath)
	:ressourceName(vertexShaderPath){
	vs_object = 0;
	fs_object = 0;
	
	vs_object = create_glsl_shader(GL_VERTEX_SHADER, path, vertexShaderPath);
	fs_object = create_glsl_shader(GL_FRAGMENT_SHADER, path, fragmentShaderPath);
	prog_object = glCreateProgram();
	
	if(vs_object)glAttachShader(prog_object, vs_object);
	if(fs_object)glAttachShader(prog_object, fs_object);
	glLinkProgram(prog_object);
	
	print_glsl_program_log(prog_object);
}

GLSLShader::~GLSLShader(){
	glDeleteShader(vs_object);
	glDeleteShader(fs_object);
	glDeleteProgram(prog_object);
}

void GLSLShader::bindShader()const{
	glUseProgram(prog_object);
}


GLuint GLSLShader::getShaderProgramId()const{
	return prog_object;
}

//COPY OF GEL CODE TO BEBUG
  void print_glsl_program_log(GLuint program)
  {
    GLint infoLog_length = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLog_length);

    // Some drivers return 1 as infoLog_length when the infoLog is an empty string
    if(infoLog_length > 1) 
    {
      char* infoLog = new char[infoLog_length];
      glGetProgramInfoLog(program, infoLog_length, 0, infoLog);
      cerr << "InfoLog:" << endl << infoLog << endl << endl;
      delete [] infoLog;
    }
  }

  void print_glsl_shader_log(GLuint shader)
  {
    GLint infoLog_length = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLog_length);

    // Some drivers return 1 as infoLog_length when the infoLog is an empty string
    if(infoLog_length > 1)
    {
      char* infoLog = new char[infoLog_length];
      glGetShaderInfoLog(shader, infoLog_length, 0, infoLog);
      cerr << "InfoLog:" << endl << infoLog << endl << endl;
      delete [] infoLog;
    }
  }

  bool check_glsl_shader(GLuint shader)
  {
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    return status == GL_TRUE;
  }

  const std::string read_glsl_source(const std::string& path, const std::string& file)
  {
    string fullpath = path + "/" + file;
    ifstream is(fullpath.c_str(), ios::binary);
    string str, contents;
    while(getline(is,str)) 
    {
      contents += str;
      contents += "\n";
    }
    return contents;
  }

  GLuint create_glsl_shader(GLuint stype, const std::string& src, bool print_log)
  {
    GLuint S = glCreateShader(stype);
    const GLchar* src_cstr = src.c_str();

    glShaderSource(S, 1, &src_cstr, 0);
    glCompileShader(S);
    
    if(print_log && !check_glsl_shader(S))
    {
      print_glsl_shader_log(S);
      glDeleteShader(S);
      return 0;
    }
    return S;
  }

  GLuint create_glsl_shader(GLuint stype, const std::string& path, const std::string& file)
  {
	string str = read_glsl_source(path, file);
    if(!str.empty())
    {
      GLuint shader = create_glsl_shader(stype, str, false);
      if(!check_glsl_shader(shader))
      {
        cerr << path << file << endl;
        print_glsl_shader_log(shader);
        glDeleteShader(shader);
        return 0;
      }
      return shader;
    }
    return 0;
  }