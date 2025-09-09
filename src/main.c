#include <stdio.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/glut.h>

static void RenderScene() 
{
    static GLclampf z = 0.0f;
    glClearColor(10.0f, z, z, 10.0f);
    printf("%f\n", z);
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

int main(int argc, char* argv[]) 
{
    printf("Hello World\n");

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
        return -1;
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    GLclampf Red = 0.0f, Green = 0.0f, Blue = 0.0f, Alpha = 0.0f;
    glClearColor(Red, Green, Blue, Alpha);

    glutDisplayFunc(RenderScene);
    
    glutMainLoop(); // This was missing!

    return 0;
}