#include "trackballcamera.h"
#include "Transform.h"

#include <Windows.h>
#include <WinGDI.h>
#include <gl/glu.h>
#include <cmath>
#include <iostream>

TrackBallCamera::TrackBallCamera(Transform* trans)
{
	transform = trans;
    _hold = false;
    _angleY = 0;
    _angleZ = 0;
    _distance = 2;
    _motionSensivity = 0.03;
    _scrollSensivity = 1;
}

void TrackBallCamera::OnMouseMotion(const SDL_MouseMotionEvent & event)
{
    if (_hold)
    {
        _angleZ += event.xrel*_motionSensivity;
        _angleY += event.yrel*_motionSensivity;

    }
}

void TrackBallCamera::OnMouseButton(const SDL_MouseButtonEvent & event)
{
	
    if (event.button == SDL_BUTTON_LEFT)
    {
        if ((_hold)&&(event.type == SDL_MOUSEBUTTONUP))
        {
            _hold = false;
        }
        else if ((!_hold)&&(event.type == SDL_MOUSEBUTTONDOWN))
        {
            _hold = true;
        }
    }
    else if ((event.button == SDL_BUTTON_WHEELUP)&&(event.type == SDL_MOUSEBUTTONDOWN))
    {
        _distance -= _scrollSensivity;
        if (_distance < 0.1)
            _distance = 0.1;
    }
    else if ((event.button == SDL_BUTTON_WHEELDOWN)&&(event.type == SDL_MOUSEBUTTONDOWN))
    {
            _distance += _scrollSensivity;
    }
}

void TrackBallCamera::OnKeyboard(const SDL_KeyboardEvent & event)
{
    if ((event.type == SDL_KEYDOWN)&&(event.keysym.sym == SDLK_HOME))
    {
        _angleY = 0;
        _angleZ = 0;
    }
}

void TrackBallCamera::setMotionSensivity(double sensivity)
{
    _motionSensivity = sensivity;
}

void TrackBallCamera::setScrollSensivity(double sensivity)
{
    _scrollSensivity = sensivity;
}

TrackBallCamera::~TrackBallCamera()
{
}

void TrackBallCamera::look(float elapsed_time)
{
	transform->setPosition(_distance*Vec3f(
					cosf(-_angleZ)*cosf(-_angleY),
					sinf(-_angleZ)*cosf(-_angleY),
					sinf(_angleY)
					));

    transform->lookAt(Vec3f(0,0,0));
}

