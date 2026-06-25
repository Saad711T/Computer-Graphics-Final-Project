//  Computer Graphics Group 3 Project - Taif University
//  Scene: CIT College Building


#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/glut.h>
#include <cmath>

bool  isDaytime = true;
bool  doorOpen = false;
bool  signGlow = false;
float personX = 50.0f;
float cloudX = 0.0f;
float t = 0.0f;

void col(float dr, float dg, float db, float nr, float ng, float nb) {
    if (isDaytime) glColor3f(dr, dg, db);
    else           glColor3f(nr, ng, nb);
}



void rect(float x1, float y1, float x2, float y2) {
    glBegin(GL_QUADS);
    glVertex2f(x1, y1); glVertex2f(x2, y1);
    glVertex2f(x2, y2); glVertex2f(x1, y2);
    glEnd();
}



void disc(float cx, float cy, float r, int seg = 36) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= seg; i++) {
        float a = 2.0f * 3.14159265f * i / seg;
        glVertex2f(cx + r * cosf(a), cy + r * sinf(a));
    }
    glEnd();
}



void strokeText(float x, float y, float s, const char* str, float w) {
    glLineWidth(w);
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(s, s, 1);
    for (const char* p = str; *p; ++p)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
    glPopMatrix();
    glLineWidth(1.0f);


}

void bitmapText(float x, float y, const char* str) {
    glRasterPos2f(x, y);

    for (const char* p = str; *p; ++p)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p);


}




void drawSky() {
    col(0.25f, 0.60f, 0.90f, 0.04f, 0.05f, 0.16f);
    rect(0, 0, 100, 100);

    if (isDaytime) {
        glColor3f(1.0f, 0.93f, 0.30f);
        disc(86, 90, 5);
    }


    else {
        glColor3f(0.95f, 0.95f, 0.85f);
        disc(86, 90, 4);
        glColor3f(0.04f, 0.05f, 0.16f);
        disc(88, 91.5f, 3.2f);

        glColor3f(1.0f, 1.0f, 0.90f);
        float sx[] = { 26, 34, 66, 74, 30, 70, 82, 18, 90, 58 };
        float sy[] = { 90, 95, 93, 96, 86, 88, 94, 90, 87, 97 };
        for (int i = 0; i < 10; i++) {
            float tw = 0.35f + 0.30f * sinf(t * 3 + i);
            disc(sx[i], sy[i], tw, 8);
        }

    }

}

void cloudBlob(float x, float y) {
    glColor3f(1, 1, 1);


    disc(x, y, 4);  disc(x + 4, y + 1.5f, 3); disc(x - 4, y + 1, 3);
    disc(x + 2, y - 1.5f, 3); disc(x - 2, y - 1.5f, 3);
}

void drawClouds() {
    if (!isDaytime) return;
    cloudBlob(cloudX + 10, 90);
    cloudBlob(cloudX + 45, 84);
    cloudBlob(cloudX + 78, 92);
}

void drawWalls() {
    col(0.82f, 0.77f, 0.67f, 0.30f, 0.28f, 0.23f);
    glBegin(GL_QUADS);
    glVertex2f(0, 92);  glVertex2f(22, 80);
    glVertex2f(22, 40); glVertex2f(0, 22);

    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(100, 92); glVertex2f(78, 80);
    glVertex2f(78, 40);  glVertex2f(100, 22);


    glEnd();

}




void drawFacade() {
    col(0.88f, 0.83f, 0.73f, 0.40f, 0.37f, 0.30f);
    rect(22, 40, 78, 80);
    col(0.78f, 0.72f, 0.60f, 0.33f, 0.30f, 0.24f);
    rect(22, 80, 78, 83);
}





void drawSign() {
    col(0.88f, 0.83f, 0.73f, 0.40f, 0.37f, 0.30f);
    rect(42, 83, 58, 93);
    col(0.78f, 0.72f, 0.60f, 0.33f, 0.30f, 0.24f);
    rect(42, 92, 58, 93.5f);
    col(0.74f, 0.36f, 0.24f, 0.74f, 0.36f, 0.24f);
    strokeText(43.5f, 86.0f, 0.045f, "CIT", 3.0f);
}


void drawWindow(float x, float y) {
    const float w = 4, h = 5;
    col(0.30f, 0.30f, 0.30f, 0.20f, 0.18f, 0.12f);
    rect(x - 0.4f, y - 0.4f, x + w + 0.4f, y + h + 0.4f);

    if (isDaytime) glColor3f(0.55f, 0.58f, 0.60f);
    else           glColor3f(1.00f, 0.92f, 0.45f);
    rect(x, y, x + w, y + h);

    col(0.30f, 0.30f, 0.30f, 0.55f, 0.45f, 0.20f);
    rect(x, y + h * 0.46f, x + w, y + h * 0.54f);
    rect(x + w * 0.44f, y, x + w * 0.56f, y + h);
}


void drawWindows() {
    float L[] = { 24, 30, 36 };
    float R[] = { 60, 66, 72 };
    float rows[] = { 52, 65 };


    for (int r = 0; r < 2; r++)
        for (int i = 0; i < 3; i++) {
            drawWindow(L[i], rows[r]);
            drawWindow(R[i], rows[r]);
        }
    drawWindow(34, 72);
    drawWindow(62, 72);
}

void drawEntrance() {
    col(0.80f, 0.74f, 0.62f, 0.36f, 0.33f, 0.27f);
    rect(40, 40, 60, 63);
    col(0.74f, 0.68f, 0.55f, 0.32f, 0.29f, 0.23f);
    rect(38, 60, 62, 64);

    const float dl = 44, dr = 56;
    if (doorOpen) {
        glColor3f(0.10f, 0.08f, 0.06f);
        rect(dl, 42, dr, 59);
        col(0.55f, 0.40f, 0.25f, 0.30f, 0.22f, 0.14f);
        rect(dl, 42, dl + 1.5f, 59);
        rect(dr - 1.5f, 42, dr, 59);
        if (isDaytime) glColor3f(0.45f, 0.38f, 0.30f);
        else           glColor3f(0.95f, 0.85f, 0.45f);
        rect(dl + 2, 43, dr - 2, 57);
    }
    else {
        glColor3f(0.16f, 0.12f, 0.09f);
        rect(dl, 42, dr, 59);
        col(0.45f, 0.32f, 0.20f, 0.25f, 0.18f, 0.11f);
        rect(dl + 1, 43, dr - 1, 58);
        glColor3f(0.10f, 0.08f, 0.06f);
        rect(49.7f, 43, 50.3f, 58);
        glColor3f(0.80f, 0.65f, 0.10f);
        disc(48.6f, 50, 0.5f, 12);
        disc(51.4f, 50, 0.5f, 12);

    }

    col(0.78f, 0.72f, 0.60f, 0.33f, 0.30f, 0.24f);
    rect(41, 40, 59, 42);
    col(0.72f, 0.66f, 0.54f, 0.30f, 0.27f, 0.21f);
    rect(39, 38.5f, 61, 40);



}

void drawFloor() {
    col(0.62f, 0.58f, 0.52f, 0.28f, 0.27f, 0.25f);
    glBegin(GL_POLYGON);
    glVertex2f(0, 22);  glVertex2f(22, 40); glVertex2f(78, 40);
    glVertex2f(100, 22); glVertex2f(100, 12); glVertex2f(0, 12);
    glEnd();

    col(0.45f, 0.43f, 0.28f, 0.18f, 0.18f, 0.13f);
    glBegin(GL_POLYGON);
    glVertex2f(0, 22);  glVertex2f(22, 40); glVertex2f(40, 40);
    glVertex2f(25, 12); glVertex2f(0, 12);
    glEnd();


    glBegin(GL_POLYGON);

    glVertex2f(100, 22); glVertex2f(78, 40); glVertex2f(60, 40);
    glVertex2f(75, 12);  glVertex2f(100, 12);
    glEnd();

}

void drawRoad() {
    col(0.55f, 0.55f, 0.55f, 0.22f, 0.22f, 0.22f);
    rect(0, 0, 100, 12);
    glColor3f(0, 0, 0);
    rect(0, 4, 100, 8.5f);
    glColor3f(0.95f, 0.95f, 0.95f);
    for (float x = 1; x < 100; x += 6) rect(x, 4, x + 3, 8.5f);
    col(0.40f, 0.40f, 0.40f, 0.15f, 0.15f, 0.15f);
    rect(0, 11.4f, 100, 12);

}

void drawBush(float x, float y, float w, float h) {
    col(0.12f, 0.30f, 0.12f, 0.06f, 0.16f, 0.06f);
    rect(x - 0.6f, y - 0.6f, x + w + 0.6f, y + h + 0.6f);
    col(0.20f, 0.46f, 0.20f, 0.10f, 0.26f, 0.10f);
    rect(x, y, x + w, y + h);
    col(0.16f, 0.38f, 0.16f, 0.08f, 0.20f, 0.08f);
    rect(x + 0.8f, y + 0.8f, x + w - 0.8f, y + h - 0.8f);
    glColor3f(0.85f, 0.15f, 0.15f);
    rect(x + w * 0.55f, y + h * 0.55f, x + w * 0.70f, y + h * 0.65f);
    disc(x + w * 0.30f, y + h * 0.30f, 0.5f, 10);

}

void drawBushes() {
    drawBush(10, 17, 9, 13);
    drawBush(64, 23, 8, 12);

}

void drawSignPost() {
    col(0.35f, 0.35f, 0.35f, 0.18f, 0.18f, 0.18f);
    rect(52.6f, 19, 53.4f, 30);
    float br = signGlow ? (0.25f + 0.20f * sinf(t * 5)) : 0.0f;
    glColor3f(0.25f, 0.62f + br, 0.28f);
    rect(51, 30, 55, 34);

}

void drawPerson(float x) {
    float y = 14 + 0.6f * sinf(t * 6);
    col(0.15f, 0.15f, 0.25f, 0.10f, 0.10f, 0.18f);
    rect(x - 1.2f, y - 3, x - 0.2f, y);
    rect(x + 0.2f, y - 3, x + 1.2f, y);
    col(0.20f, 0.45f, 0.75f, 0.15f, 0.30f, 0.50f);
    rect(x - 1.6f, y, x + 1.6f, y + 4.5f);
    col(0.90f, 0.75f, 0.60f, 0.55f, 0.45f, 0.38f);
    disc(x, y + 6, 1.6f, 16);

}

void drawInstructions() {
    if (isDaytime) glColor3f(0.10f, 0.10f, 0.10f);
    else           glColor3f(0.95f, 0.95f, 0.95f);
    bitmapText(1.5f, 98.0f, "Arrows Left/Right: Move person   Arrows Up/Down: Day/Night");
    bitmapText(1.5f, 95.0f, "SPACE: Door   Mouse Click: Highlight sign   (N / A / D also work)");
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawSky();
    drawClouds();
    drawWalls();
    drawFacade();
    drawWindows();
    drawEntrance();
    drawSign();
    drawFloor();
    drawRoad();
    drawBushes();
    drawSignPost();
    drawPerson(personX);
    drawInstructions();
    glutSwapBuffers();
}



void timer(int) {
    t += 0.05f;
    cloudX += 0.15f;
    if (cloudX > 100) cloudX = -30;
    glutPostRedisplay();
    glutTimerFunc(33, timer, 0);
}



void keyboard(unsigned char key, int, int) {
    switch (key) {
    case 'n': case 'N': isDaytime = !isDaytime; break;
    case ' ':           doorOpen = !doorOpen;  break;
    case 'a': case 'A': personX -= 2; if (personX < 8)  personX = 8;  break;
    case 'd': case 'D': personX += 2; if (personX > 92) personX = 92; break;
    }
    glutPostRedisplay();
}


void special(int key, int, int) {
    switch (key) {
    case GLUT_KEY_LEFT:  personX -= 2; if (personX < 8)  personX = 8;  break;
    case GLUT_KEY_RIGHT: personX += 2; if (personX > 92) personX = 92; break;
    case GLUT_KEY_UP:
    case GLUT_KEY_DOWN:  isDaytime = !isDaytime;                       break;
    }
    glutPostRedisplay();
}


void mouse(int button, int state, int, int) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        signGlow = !signGlow;
        glutPostRedisplay();
    }
}



void init() {
    glClearColor(0.25f, 0.60f, 0.90f, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 100, 0, 100);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(850, 850);
    glutCreateWindow("Taif University - CIT Building (Group 3)");
    init();
    glutDisplayFunc(display);

    glutKeyboardFunc(keyboard);

    glutSpecialFunc(special);
    glutMouseFunc(mouse);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}
