#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H

struct dxMaterial
{
	float ambientR, ambientG, ambientB, ambientA;
	float diffuseR, diffuseG, diffuseB, diffuseA;
	float specularR, specularG, specularB, specularA;
	float emissiveR, emissiveG, emissiveB, emissiveA;
	float power;//高亮区域
	dxMaterial() {
		float ambientR = ambientG = ambientB = ambientA = 1;
		float diffuseR = diffuseG = diffuseB = diffuseA = 1;
		float specularR = specularG = specularB = specularA = 0;
		float emissiveR = emissiveG = emissiveB = emissiveA = 0;
		float power=0;//高亮区域
	}
};
#endif // !MATERIAL_H

