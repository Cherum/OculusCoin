/**************************************************************************\
 * Copyright (c) Bastiaan Veelo (Bastiaan a_t Veelo d_o_t net)
 * All rights reserved. Contact me if the below is too restrictive for you.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
\**************************************************************************/

//#define USE_SO_OFFSCREEN_RENDERER
#define USE_FRAMEBUFFER

#ifdef USE_SO_OFFSCREEN_RENDERER
#  ifdef USE_FRAMEBUFFER
#    error "Mutually exclusive options defined."
#  endif
#endif

#include <QApplication>
#include <QGLWidget>
#include <QTimer>
#include <QDebug>
#include <Inventor/SoDB.h>
#include <Inventor/SoInput.h>
#ifdef USE_SO_OFFSCREEN_RENDERER
#  include <Inventor/SoOffscreenRenderer.h>
#endif
#ifdef USE_FRAMEBUFFER
#  include <Inventor/SoSceneManager.h>
#endif
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoFrustumCamera.h>
#include <Inventor/nodes/SoDirectionalLight.h>
//#include <OVR_CAPI_GL.h>
#include <../Src/OVR_CAPI_GL.h>
#include <../Src/CAPI/GL/CAPI_GL_Util.h>    // For framebuffer functions.

#include "CoinRiftWidget.h"


static void cleanup()
{
    SoDB::finish();
    ovr_Shutdown();
}


int main(int argc, char *argv[])
{
    SoDB::init();

    QApplication app(argc, argv);
    qAddPostRoutine(cleanup);

    // Moved here because of https://developer.oculusvr.com/forums/viewtopic.php?f=17&t=7915&p=108503#p108503
    // Init libovr.
    if (!ovr_Initialize()) {
        qDebug() << "Could not initialize Oculus SDK.";
        exit(1);
    }

    CoinRiftWidget window;
    window.show();

    // An example scene.
    static const char * inlineSceneGraph[] = {
        "#Inventor V2.1 ascii\n",
        "\n",
        "Separator {\n",
        "  Rotation { rotation 1 0 0  0.3 }\n",
        "  Cone { }\n",
        "  BaseColor { rgb 1 0 0 }\n",
        "  Scale { scaleFactor .7 .7 .7 }\n",
        "  Cube { }\n",
        "\n",
        "  DrawStyle { style LINES }\n",
        "  ShapeHints { vertexOrdering COUNTERCLOCKWISE }\n",
        "  Coordinate3 {\n",
        "    point [\n",
        "       -2 -2 1.1,  -2 -1 1.1,  -2  1 1.1,  -2  2 1.1,\n",
        "       -1 -2 1.1,  -1 -1 1.1,  -1  1 1.1,  -1  2 1.1\n",
        "        1 -2 1.1,   1 -1 1.1,   1  1 1.1,   1  2 1.1\n",
        "        2 -2 1.1,   2 -1 1.1,   2  1 1.1,   2  2 1.1\n",
        "      ]\n",
        "  }\n",
        "\n",
        "  Complexity { value 0.7 }\n",
        "  NurbsSurface {\n",
        "     numUControlPoints 4\n",
        "     numVControlPoints 4\n",
        "     uKnotVector [ 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0 ]\n",
        "     vKnotVector [ 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0 ]\n",
        "  }\n",
        "}\n",
        NULL
    };

    SoInput in;
    in.setStringArray(inlineSceneGraph);

    window.setSceneGraph(SoDB::readAll(&in));

    return app.exec();
}
