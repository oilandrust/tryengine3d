#ifndef TRACKBALLCAMERA_H
#define TRACKBALLCAMERA_H

#include <SDL.h>

class Transform;

class TrackBallCamera
{
public:
    TrackBallCamera(Transform* trans);

    virtual void OnMouseMotion(const SDL_MouseMotionEvent & event);
    virtual void OnMouseButton(const SDL_MouseButtonEvent & event);
    virtual void OnKeyboard(const SDL_KeyboardEvent & event);

    virtual void look(float elapsed_time);
    virtual void setMotionSensivity(double sensivity);
	virtual void setScrollSensivity(double sensivity);

    virtual ~TrackBallCamera();
protected:
	Transform * transform;
    double _motionSensivity;
	double _scrollSensivity;
    bool _hold;
    double _distance;
    double _angleY;
    double _angleZ;
    SDL_Cursor * _hand1;
    SDL_Cursor * _hand2;
};

#endif //TRACKBALLCAMERA_H
