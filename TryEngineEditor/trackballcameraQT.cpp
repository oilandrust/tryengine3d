#include "trackballcameraQT.h"

#include <cmath>
#include <iostream>

TrackBallCameraQT::TrackBallCameraQT(Transform* trans, Scene* scen)
{
	mode = MOVE;
	old_x = old_y = 0;
	scene = scen;
	transform = trans;
    _hold_m = _hold_z = false;
    _angleY = 0;
    _angleZ = 0;
    _distance = 2;
    _motionSensivity = 0.03f;
    _scrollSensivity = 1;
	center = Vec3f(0,0,0);
	_hold_t = false;

}

void TrackBallCameraQT::OnMouseMotionQT(const QMouseEvent& Event){
	int dx = Event.x() - old_x;
	int dy = Event.y() - old_y;


	old_x=Event.x();
	old_y=Event.y();

	if (_hold_m){
		_angleZ += dx*_motionSensivity;
		_angleY += dy*_motionSensivity;
	}
	if(_hold_t){
		center += 0.01*dx*transform->getRight() + 0.01*dy*transform->getUp();
	}

	if (_hold_z){
		_distance += dy*_motionSensivity;
	}

}

void TrackBallCameraQT::OnMousePressQT(const QMouseEvent& Event){

	if ( (Event.button() == Qt::LeftButton && mode != SELECT) || Event.button() == Qt::RightButton && mode == SELECT){
		if (!_hold_m){
			old_x=Event.x();old_y=Event.y();
			_hold_m = true;
			
		}
	}
	if ( Event.button() == Qt::RightButton && mode != SELECT){
		if (!_hold_t){
			old_x=Event.x();old_y=Event.y();
			_hold_t = true;
		}
	}
	else if (Event.button() == Qt::MidButton){
		if (!_hold_z){
			old_x=Event.x();old_y=Event.y();
			_hold_z = true;
		}
	}

}

void TrackBallCameraQT::OnMouseReleaseQT(const QMouseEvent& Event){

		if ( (Event.button() == Qt::LeftButton && mode != SELECT) || Event.button() == Qt::RightButton && mode == SELECT){
			if (_hold_m){
				_hold_m = false;
				old_x=old_y=0;
			}
		}
		if ( Event.button() == Qt::RightButton && mode != SELECT){
			if (_hold_t){
				old_x=0;old_y=0;
				_hold_t = false;
			}
		}
		else if (Event.button() == Qt::MidButton){
			if (_hold_z){
				_hold_z = false;
				old_x=old_y=0;
			}
		}


}

void TrackBallCameraQT::OnKeyboardQT(const QEvent & event)
{
	/*
    if ((event.type == SDL_KEYDOWN)&&(event.keysym.sym == SDLK_HOME))
    {
        _angleY = 0;
        _angleZ = 0;
    }
	*/
}

void TrackBallCameraQT::setMotionSensivity(float sensivity){
    _motionSensivity = sensivity;
}

void TrackBallCameraQT::setScrollSensivity(float sensivity){
    _scrollSensivity = sensivity;
}

TrackBallCameraQT::~TrackBallCameraQT()
{
}

void TrackBallCameraQT::look(float elapsed_time)
{
	transform->setPosition(center+_distance*Vec3f(
					cosf(-_angleZ)*cosf(-_angleY),
					sinf(-_angleZ)*cosf(-_angleY),
					sinf(_angleY)
					));

    transform->lookAt(center);
}

void TrackBallCameraQT::setCameraMode(EditorCameraModeEnum mod){
	mode = mod;
}
EditorCameraModeEnum TrackBallCameraQT::getCameraMode()const{
	return mode;
}

