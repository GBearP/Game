#pragma once
#ifndef LIGHT_H
#define LIGHT_H

struct dxLight
{
	int type;
	float posX, posY, posZ;
	float dirX, dirY, dirZ;
	float ambientR, ambientG, ambientB, ambientA;
	float diffuseR, diffuseG, diffuseB, diffuseA;
	float specularR, specularG, specularB, specularA;
	float range;//�����������
	float falloffRange;//����˥������
	float attenuation0;//��ǿ�����˥����ʽ
	float attenuation1;
	float attenuation2;
	float theta;//�۹����׶��Բ׶��
	float phi;//��׶��Բ׶��
	dxLight() {
		type = 0; 
		posX = 0; posY = 0; posZ = 0; 
		dirX = 0; dirY = 0; dirZ = 0;
		ambientR = ambientG = ambientB = ambientA = 1;
		diffuseR = diffuseG = diffuseB = diffuseA = 1;
		specularR = specularG = specularB = specularA = 0;
		range = 1000;
		falloffRange = 0;
		attenuation0 = 0;
		attenuation1 = 0;
		attenuation2 = 0;
		theta = 0;
		phi = 0;
	}
};
#endif // !LIGHT_H

