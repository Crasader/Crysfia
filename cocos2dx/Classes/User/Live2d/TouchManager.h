/**
 *
 *  You can modify and use this source freely
 *  only for the development of application related Live2D.
 *
 *  (c) Live2D Inc. All rights reserved.
 */

#pragma once
#include "cocos2d.h"

class TouchManager 
{
private:
    float startY ;// �^�b�`���J�n�����ʒu
	float startX ;
    
	float lastX ;// �V���O���^�b�`����x�̒l
	float lastY ;// �V���O���^�b�`����y�̒l
	float lastX1 ;// �_�u���^�b�`���̈�ڂ�x�̒l
	float lastY1 ;// �_�u���^�b�`���̈�ڂ�y�̒l
	float lastX2 ;// �_�u���^�b�`���̓�ڂ�x�̒l
	float lastY2 ;// �_�u���^�b�`���̓�ڂ�y�̒l
    
	float lastTouchDist ;// 2�{�ȏ�Ń^�b�`�����Ƃ��̎w�̋���
    
	float deltaX;// �O��̒l���獡��̒l�ւ�x�̈ړ������B
	float deltaY;// �O��̒l���獡��̒l�ւ�y�̈ړ������B
    
	float scale;// ���̃t���[���Ŋ|�����킹��g�嗦�B�g�呀�쒆�ȊO��1�B
    
	bool touchSingle ;// �V���O���^�b�`����true
	bool flipAvailable ;// �t���b�v���L�����ǂ���
    
    
public:
    TouchManager();
    float getCenterX(){ return lastX ; }
    float getCenterY(){ return lastY ; }
    float getDeltaX() { return deltaX; }
    float getDeltaY() { return deltaY; }
    float getStartX() { return startX; }
    float getStartY() { return startY; }
    float getScale()  { return scale;  }
    float getX()  { return lastX; }
    float getY()  { return lastY; }
    float getX1() { return lastX1; }
    float getY1() { return lastY1; }
    float getX2() { return lastX2; }
    float getY2() { return lastY2; }
    bool isSingleTouch() { return touchSingle; }
    bool isFlickAvailable() { return flipAvailable; }
    void disableFlick() { flipAvailable=false; }


    void touchesBegan(float deviceX, float deviceY);
    void touchesBegan(float deviceX1, float deviceY1, float deviceX2, float deviceY2) ;
    void touchesMoved(cocos2d::Point touches[],int num);
    void touchesMoved(float deviceX, float deviceY);
    void touchesMoved(float deviceX1, float deviceY1, float deviceX2, float deviceY2);
    float getFlickDistance();
    
private:
    float distance(float x1, float y1, float x2, float y2);
    float calcShift( float v1 , float v2 );
    
};



