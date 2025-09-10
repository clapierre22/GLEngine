#include <stdio.h>
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
    // static GLclampf z = 0.0f;
    // glClearColor(z, z, z, z);
    // printf("%f\n", z);
    // glClear(GL_COLOR_BUFFER_BIT);
    // glutSwapBuffers();

    glClear(GL_COLOR_BUFFER_BIT);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_POINTS, 0, 1);

    glDisableVertexAttribArray(0);

    glutSwapBuffers();
}

static void CreateVertexBuffer()
{
    Vector3f Vertices[1];
    Vertices[0].x = 0.0f;
    Vertices[0].y = 0.0f;
    Vertices[0].z = 0.0f;

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

int main(int argc, char* argv[]) 
{
    printf("Good Build\n");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    
    int width = 1920;
    int height = 1080;
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

    glutDisplayFunc(RenderScene);
    
    glutMainLoop();

    return 0;
}