#ifndef DESC_CAM_ENUM_H
#define DESC_CAM_ENUM_H
namespace Descriptors {
  namespace Camera {
    enum m_enum {
      NoCamera = 0,
      OrthographicCamera,
      PerspectiveCamera
    };

    static const char *m_name  [] = {
      "NoCamera",
      "OrthographicCamera",
      "PerspectiveCamera"
    };
  }
}
#endif
