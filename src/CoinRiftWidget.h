#ifndef COINRIFTWIDGET_H
#define COINRIFTWIDGET_H

#include <QGLWidget>


class CoinRiftWidget : public QGLWidget
{
    ovrHmd hmd;
    ovrHmdDesc hmdDesc;
    ovrEyeDesc eyes[2];
    ovrEyeRenderDesc eyeRenderDesc[2];
    ovrTexture eyeTexture[2];

#ifdef USE_FRAMEBUFFER
    GLuint frameBufferID[2], depthBufferID[2];
    // A SoSceneManager has a SoRenderManager to do the rendering -- should we not use SoRenderManager instead?
    // We are probably not that interested in events. SoSceneManager::setSceneGraph() searches for the camera
    // and sets it in SoRenderManager, but its is actually only used for built-in stereo rendering. We sould
    // probably eliminate that search...
    SoSceneManager *m_sceneManager;
#endif
#ifdef USE_SO_OFFSCREEN_RENDERER
    SoOffscreenRenderer *renderer;
#endif
    SoSeparator *rootScene[2];
    SoFrustumCamera *camera[2];
    SoNode *scene;

public:
    explicit CoinRiftWidget();
    ~CoinRiftWidget();
    void setSceneGraph(SoNode *sceneGraph);
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height) {
        int side = qMin(width, height);
        glViewport((width - side) / 2, (height - side) / 2, side, side);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-1.0, 1.0, -1.0, 1.0, 0.0, 1000.0);
        glMatrixMode(GL_MODELVIEW);
    }
};
#endif /* COINRIFTWIDGET_H */