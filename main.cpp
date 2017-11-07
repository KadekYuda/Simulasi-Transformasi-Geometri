#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/freeglut.h>
#endif
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

GLfloat x,y;
int nVertex;
float** shownVertices;
float** originVertices;
std::string menu;
std::string param;
std::string axis;
float dx, dy, scale, a, b, c, d, deg;
bool run = true;
int n;

const int WIDTH = 1000;
const int HEIGHT = 1000;
const float PI = 3.141592;

void translateShape(float dx, float dy);
void dilateShape(float scl);
void rotateShape(float deg, float a, float b);
void reflectShape(string param);
void shearShape(string param, float sh);
void stretchShape(string param, float st);
void customShape(float a, float b, float c, float d);
void multipleShape(int n);
void resetShape();

void cartesiusGrid(){
    for (int i=-20;i<=20;i++){
        glBegin(GL_LINES);
            //Set warna bentuk pada gambar ini
            glColor3f(0.5,0.5,0.5);
            //Buat titik-titik
            glVertex2f(-HEIGHT,50*i);
            glVertex2f(HEIGHT,50*i);
        glEnd();

        glBegin(GL_LINES);
            //Set warna bentuk pada gambar ini
            glColor3f(0.5,0.5,0.5);
            //Buat titik-titik
            glVertex2f(50*i,-WIDTH);
            glVertex2f(50*i,WIDTH);
        glEnd();
    }

    //Membuat Kartesius
    glBegin(GL_LINES);
        //Set warna bentuk pada gambar ini
        glColor3f(1.0,1.0,1.0);
        //Buat titik-titik
        glVertex2f(-HEIGHT,0);
        glVertex2f(HEIGHT,0);
    glEnd();

    glBegin(GL_LINES);
        //Set warna bentuk pada gambar ini
        glColor3f(1.0,1.0,1.0);
        //Buat titik-titik
        glVertex2f(0,-WIDTH);
        glVertex2f(0,WIDTH);
    glEnd();
}

void display(){
    //Menggunakan settingan background
    glClear(GL_COLOR_BUFFER_BIT);

    cartesiusGrid();
    //GLfloat shownVertices[3][2] = {{0.0, 0.0}, {249.0, 499.0}, {499.0, 0.0}};
    glBegin(GL_TRIANGLE_FAN);
        //Set warna bentuk pada gambar ini
        glColor3f(1.0,0.0,0.0);
        //Buat titik-titik
        for(int i = 0; i<nVertex; i++){
            glVertex2f(shownVertices[i][0],shownVertices[i][1]);
        }
    glEnd();
    glFlush();
    glutSwapBuffers();
}

void initOpenGL(){
    //Set warna background dalam R,G,B,A
    glClearColor(0.0,0.0,0.0,1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-WIDTH/2, WIDTH/2, -HEIGHT/2, HEIGHT/2);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv){

    cin >> nVertex;

    shownVertices = new float* [nVertex];
    for (int i = 0; i<nVertex; i++){
        shownVertices[i] = new float[3];
    }

    originVertices = new float* [nVertex];
    for (int i = 0; i<nVertex; i++){
        originVertices[i] = new float[3];
    }

    for (int i = 0; i<nVertex; i++){
        cin >> x >> y;
        originVertices[i][0] = x;
        originVertices[i][1] = y;
        originVertices[i][2] = 1;
        shownVertices[i][0] = x;
        shownVertices[i][1] = y;
        shownVertices[i][2] = 1;
    }

    //Start up freeGLUT
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutInitWindowPosition(300,0);
    glutCreateWindow("freeGLUT");

    initOpenGL();

    glutDisplayFunc(display);
    glutIdleFunc(display);

    while(run){
        glutMainLoopEvent();
        cout << "Input : ";
        cin >> menu;
        if (menu.compare("exit")!=0){
            if (menu.compare("translate") == 0){
                cin >> dx >> dy;
                translateShape(dx, dy);
            }
            else if (menu.compare("dilate") == 0){
                cin >> scale;
                dilateShape(scale);
            }
            else if (menu.compare("rotate") == 0){
                cin >> deg >> x >> y;
                rotateShape(deg, x, y);
            }
            else if (menu.compare("reflect") == 0){
                cin >> param;
                reflectShape(param);
            }
            else if (menu.compare("shear") == 0){
                cin >> param >> scale;
                shearShape(param, scale);
            }
            else if (menu.compare("stretch") == 0){
                cin >> param >> scale;
                stretchShape(param, scale);
            }
            else if (menu.compare("custom") == 0){
                cin >> a >> b >> c >> d;
                customShape(a,b,c,d);
            }
            else if (menu.compare("reset") == 0){
                resetShape();
            }
            else if (menu.compare("multiple") == 0){
                cin >> n;
                multipleShape(n);
            }
        }else{
            run = false;
        }
        glutPostRedisplay();
    }

    return 0;
}

void translateShape(float dx, float dy){
    for(int i=0; i<nVertex; i++){
        shownVertices[i][0] += dx;
        shownVertices[i][1] += dy;
    }
}

void dilateShape(float scl){
    for(int i=0; i<nVertex; i++){
        shownVertices[i][0] *= scl;
        shownVertices[i][1] *= scl;
    }
}

void rotateShape(float deg, float a, float b){
    for(int i=0; i<nVertex; i++){
        float vx, vy;
        vx = shownVertices[i][0];
        vy = shownVertices[i][1];

        vx -= a;
        vy -= b;

        float vxn = vx * cos(deg*PI/180) - vy * sin(deg*PI/180);
        float vyn = vx * sin(deg*PI/180) + vy * cos(deg*PI/180);

        shownVertices[i][0] = vxn + a;
        shownVertices[i][1] = vyn + b;
    }
}

void reflectShape(string param){
    if (param.compare("x")==0){
        for (int i=0;i<nVertex;i++)
        {
            shownVertices[i][1] *= -1;
        }
    }
    else if (param.compare("y")==0){
        for (int i=0;i<nVertex;i++){
            shownVertices[i][0] *= -1;
        }
    } else if (param.compare("y=x")==0){
        for (int i=0;i<nVertex;i++){
            float temp = shownVertices[i][0];
            shownVertices[i][0] = shownVertices[i][1];
            shownVertices[i][1] = temp;
        }
    } else if (param.compare("y=-x")==0){
        for (int i=0;i<nVertex;i++){
            float temp = shownVertices[i][0];
            shownVertices[i][0] = -shownVertices[i][1];
            shownVertices[i][1] = -temp;
        }
    } else if (2 == std::sscanf(param.c_str(), "(%f,%f)", &x, &y)){
        for (int i=0;i<nVertex;i++){
            shownVertices[i][0] = 2*x - shownVertices[i][0];
            shownVertices[i][1] = 2*y - shownVertices[i][1];
        }
    }
}

void shearShape(string param, float k){
    if (param.compare("x")==0){
        for (int i = 0; i<nVertex; i++){
            shownVertices[i][0] += k*shownVertices[i][1];
        }
    }else if (param.compare("y")==0){
        for (int i = 0; i<nVertex; i++){
            shownVertices[i][1] += k*shownVertices[i][0];
        }
    }
}

void stretchShape(string param, float k){
    if (param.compare("x")==0){
        for (int i = 0; i<nVertex; i++){
            shownVertices[i][0] *=k;
        }
    }else if (param.compare("y")==0){
        for (int i = 0; i<nVertex; i++){
            shownVertices[i][1] *=k;
        }
    }
}

void customShape(float a, float b, float c, float d){
    float trans[3][3] = { {a, b, 0.0},{c, d, 0.0}, {0.0, 0.0, 1.0} };
    float tempVertices[nVertex][3];
    // HITUNG NILAI MATRIKS KE tempVertices
    for(int i=0; i<nVertex; i++){
        for(int j=0; j<3; j++){
            float sum = 0;
            for (int k=0; k<3; k++){
                sum = sum + trans[j][k]*shownVertices[i][k];
            }
            tempVertices[i][j] = sum;
        }
    }
    // PINDAHIN tempVertices KE shownVertices
    for(int i = 0; i<nVertex; i++){
        for (int j = 0; j<3; j++){
            shownVertices[i][j] = tempVertices[i][j];
        }
    }
}

void multipleShape(int n){
    for (int i = 0; i<n; i++){
        cin >> menu;
        if (menu.compare("translate") == 0){
            cin >> dx >> dy;
            translateShape(dx, dy);
        }
        else if (menu.compare("dilate") == 0){
            cin >> scale;
            dilateShape(scale);
        }
        else if (menu.compare("rotate") == 0){
            cin >> deg >> x >> y;
            rotateShape(deg, x, y);
        }
        else if (menu.compare("reflect") == 0){
            cin >> param;
            reflectShape(param);
        }
        else if (menu.compare("shear") == 0){
            cin >> param >> scale;
            shearShape(param, scale);
        }
        else if (menu.compare("stretch") == 0){
            cin >> param >> scale;
            stretchShape(param, scale);
        }
        else if (menu.compare("custom") == 0){
            cin >> a >> b >> c >> d;
            customShape(a,b,c,d);
        }
        else{
            cout << "Masukan menu tidak valid. Silakan coba lagi" << endl;
            i--;
        }
    }
}

void resetShape(){
    for(int i = 0; i<nVertex; i++){
        for (int j = 0; j<3; j++){
            shownVertices[i][j] = originVertices[i][j];
        }
    }
}
