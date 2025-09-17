#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/glut.h>

GLuint VBO;

typedef struct Vector3f;

typedef struct 
{
    float x, y, z;
} Vector3f;

static void RenderScene() 
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(0);

    glutSwapBuffers();
}

static void CreateVertexBuffer()
{
    Vector3f Vertices[3];

    Vertices[0].x = -1.0f;
    Vertices[0].y = -1.0f;
    Vertices[0].z = 0.0f;

    Vertices[1].x = 1.0f;
    Vertices[1].y = -1.0f;
    Vertices[1].z = 0.0f;

    Vertices[2].x = 0.0f;
    Vertices[2].y = 1.0f;
    Vertices[2].z = 0.0f;

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

static void AddShader(GLuint ShaderProgram, const char* ShaderText, GLenum ShaderType)
{
    GLuint ShaderObj = glCreateShader(ShaderType);

    if (ShaderObj == 0)
    {
        fprintf(stderr, "Eroor creating shader type %d\n", ShaderType);
        exit(1);
    }

    const GLchar* p[1];
    p[0] = ShaderText;

    GLint Lengths[1];
    Lengths[0] = (GLint)strlen(ShaderText);

    glShaderSource(ShaderObj, 1, p, Lengths);

    glCompileShader(ShaderObj);

    GLint success;
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
        fprintf(stderr, "Error compiling shder type %d: %s\n", ShaderType, InfoLog);
        exit(1);
    }

    glAttachShader(ShaderProgram, ShaderObj);
}

// Global shader variables
const char* VSFilename = "shader.vs";
const char* FSFilename = "shader.fs";

static void CompileShaders()
{
    GLuint ShaderProgram = glCreateProgram();

    if (ShaderProgram == 0)
    {
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
    }

    char *vs = NULL, *fs = NULL;

    // Vertex Shader
    FILE* vsf = fopen(VSFilename, "r");
    
    if (vsf == NULL)
    {
        fprintf(stderr, "Error opening file %s\n", VSFilename);
        exit(1);
    }

    fseek(vsf, 0, SEEK_END);
    long vss = ftell(vsf); // VS size
    fseek(vsf, 0, SEEK_SET);

    vs = malloc(vss + 1);

    if (vs == NULL)
    {
        fclose(vsf);
        fprintf(stderr, "Error allocating memory\n");
        exit(1);
    }

    fread(vs, 1, vss, vsf);
    vs[vss] = '\0'; // Add endline character
    fclose(vsf);

    AddShader(ShaderProgram, vs, GL_VERTEX_SHADER);

    // Fragment Shader
    FILE* fsf = fopen(FSFilename, "r");

    if (fsf == NULL)
    {
        fprintf(stderr, "Error opening file %s", FSFilename);
        exit(1);
    }

    fseek(fsf, 0, SEEK_END);
    long fss = ftell(fsf); // FS size
    fseek(fsf, 0, SEEK_SET);

    fs = malloc(fss + 1);

    if (fs == NULL)
    {
        fprintf(stderr, "Error allocating memory\n");
        exit(1);
    }

    fread(fs, 1, fss, fsf);
    fs[fss] = '\0'; // Add endline character
    fclose(fsf);

    AddShader(ShaderProgram, fs, GL_FRAGMENT_SHADER);

    glLinkProgram(ShaderProgram);

    GLint success;
    GLchar ErrorLog[1024];

    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Error linking shader program: %s\n", ErrorLog);
        exit(1);
    }

    glValidateProgram(ShaderProgram); // If multiple shaders, states then call after every call to draw()
    glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Error linking shader program: %s\n", ErrorLog);
        exit(1);
    }

    glUseProgram(ShaderProgram);
}

int main(int argc, char* argv[]) 
{
    printf("Good Build\n");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    
    int width = 1360;
    int height = 768;
    glutInitWindowSize(width, height);

    int x = 100;
    int y = 100;
    glutInitWindowPosition(x, y);

    glutCreateWindow("Test Window");
    
    // Initialize GLEW after creating OpenGL context
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return 1;
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    GLclampf Red = 0.0f, Green = 0.0f, Blue = 0.0f, Alpha = 0.0f;
    glClearColor(Red, Green, Blue, Alpha);

    CreateVertexBuffer();

    CompileShaders();

    glutDisplayFunc(RenderScene);
    
    glutMainLoop();

    return 0;
}