/**
 *
 *  You can modify and use this source freely
 *  only for the development of application related Live2D.
 *
 *  (c) Live2D Inc. All rights reserved.
 */
#pragma once


// ���
static const float VIEW_MAX_SCALE = 2.0f;
static const float VIEW_MIN_SCALE = 0.8f;

static const float VIEW_LOGICAL_LEFT = -1;
static const float VIEW_LOGICAL_RIGHT = 1;

static const float VIEW_LOGICAL_MAX_LEFT = -2;
static const float VIEW_LOGICAL_MAX_RIGHT = 2;
static const float VIEW_LOGICAL_MAX_BOTTOM = -2;
static const float VIEW_LOGICAL_MAX_TOP = 2;

// �O����`�t�@�C��(json)�ƍ��킹��
static const char MOTION_GROUP_IDLE [ ] = "idle";// �A�C�h�����O
static const char MOTION_GROUP_TAP_BODY [ ] = "tap_body";// �̂��^�b�v�����Ƃ�

// �O����`�t�@�C��(json)�ƍ��킹��
static const char HIT_AREA_NAME_HEAD [ ] = "head";
static const char HIT_AREA_NAME_BODY [ ] = "body";

// ���[�V�����̗D��x�萔
static const int PRIORITY_NONE = 0;
static const int PRIORITY_IDLE = 1;
static const int PRIORITY_NORMAL = 2;
static const int PRIORITY_FORCE = 3;


class LAppDefine {
public:
    static const bool DEBUG_LOG = true;// �f�o�b�O�p���O�̕\��
    static const bool DEBUG_TOUCH_LOG = false;
};
