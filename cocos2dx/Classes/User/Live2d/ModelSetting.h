/**
 *
 *  You can modify and use this source freely
 *  only for the development of application related Live2D.
 *
 *  (c) Live2D Inc. All rights reserved.
 */
#pragma once

#include <string>

class ModelSetting
{
public:
    
	virtual ~ModelSetting(){}
	
	// ���f���f�[�^�ɂ���
	virtual std::string getModelName() =0 ;
	virtual std::string getModelFile() =0  ;
	
	// �e�N�X�`���ɂ���
	virtual int getTextureNum() =0 ;
	virtual std::string getTextureDir() =0 ;
	virtual std::string getTextureFile(int n) =0 ;
	
	// �����p�����[�^�ɂ���
	virtual int getInitParamNum() =0;
	virtual float getInitParamValue(int n) =0 ;
	virtual std::string getInitParamID(int n) =0 ;
	
	// �����p�[�c�\���ɂ���
	virtual int getInitPartsVisibleNum() =0 ;
	virtual float getInitPartsVisibleValue(int n) =0 ;
	virtual std::string getInitPartsVisibleID(int n) =0;
	
	// �����蔻��ɂ���
	virtual int getHitAreasNum() =0 ;
	virtual std::string getHitAreaID(int n) =0 ;
	virtual std::string getHitAreaName(int n) =0 ;
	
	// �������Z�A�p�[�c�؂�ւ��A�\��t�@�C���ɂ���
	virtual std::string getPhysicsFile() =0;
	virtual std::string getPoseFile() =0;
	
	virtual int getExpressionNum()=0;
	virtual std::string getExpressionName(int n) =0 ;
	virtual std::string getExpressionFile(int n) =0 ;
	
	// ���[�V�����ɂ���
	virtual int getMotionNum(std::string name)  =0;
	virtual int getMotionGroupNum() =0;
	virtual std::string getMotionGroupName(int n) =0;
	virtual std::string getMotionFile(std::string name,int n) =0   ;
	virtual std::string getMotionSound(std::string name,int n)  =0 ;
	virtual int getMotionFadeIn(std::string name,int n) =0 ;
	virtual int getMotionFadeOut(std::string name,int n) =0     ;
	
	virtual bool getLayout(std::map<std::string, float> & layout)=0;
	
};