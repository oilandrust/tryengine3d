#ifndef TRACKBALLCAMERAQT_H
#define TRACKBALLCAMERAQT_H

#include "TryEngine.h"
#include <QEvent>
#include <QMouseEvent>

enum EditorCameraModeEnum{
	MOVE,
	SELECT,
};

class TrackBallCameraQT
{
public:
    TrackBallCameraQT(Transform* trans, Scene* scen);

	void setCameraMode(EditorCameraModeEnum mode);
	EditorCameraModeEnum getCameraMode()const;

    virtual void OnMousePressQT(const QMouseEvent & Event);
    virtual void OnMouseReleaseQT(const QMouseEvent & Event);
    virtual void OnMouseMotionQT(const QMouseEvent & Event);
    virtual void OnKeyboardQT(const QEvent & Event);

    virtual void look(float elapsed_time);
    virtual void setMotionSensivity(float sensivity);
	virtual void setScrollSensivity(float sensivity);

	Transform* getTransform()const{return transform;}

    virtual ~TrackBallCameraQT();
protected:
	EditorCameraModeEnum mode;
	Transform * transform;
	Scene * scene;
    float _motionSensivity;
	float _scrollSensivity;
    

	//Zoom
	bool _hold_z;
    float _distance;
	//Rotation
	bool _hold_m;
    float _angleY;
    float _angleZ;
	//center
	bool _hold_t;
	Vec3f center;

	//Mouse coord
	float old_x;
	float old_y;


};

#endif //TRACKBALLCAMERA_H
