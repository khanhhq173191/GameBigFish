#include "stdafx.h"
#include "Object.h"
#include "Camera.h"
#include "Globals.h"
#include "Singleton.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include <time.h>

#define PI 3.141592653589

Objects::Objects()
{
}

Objects::~Objects()
{
}

void Objects::set_matrix(Matrix v) {

	set_world(0.75, 0, 0, 0, 0, -0.5, 0);
	//set_view(0, 0, 0, 0, 0, 0);
	//set_perspective();
	set_wvp(v);
}

void Objects::set_world(float s, float rx, float ry, float rz, float tx, float ty, float tz) {
	//sw = s; rxw = rx; ryw = ry; rzw = rz;
	//txw = tx; tyw = ty; tzw= tz;
	scaleMatrix.SetScale(sxw, syw, szw);
	Rx.SetRotationX(rxw * (PI / 180));
	Ry.SetRotationY(ryw * (PI / 180));
	Rz.SetRotationZ(rzw * (PI / 180));
	rotationMatrix = Rz * Rx * Ry;
	translationMatrix.SetTranslation(txw, tyw, tzw);
	wMatrix = scaleMatrix * rotationMatrix * translationMatrix;
}


void Objects::set_wvp(Matrix v) {
	wvpMatrix = wMatrix * v;
}

void Objects::draw()
{
	set_matrix(Singleton<Camera>::GetInstance()->camera_VP);
	glUseProgram(shaders.program);
	glUniformMatrix4fv(shaders.WVP, 1, GL_FALSE, &wvpMatrix.m[0][0]);

	glBindBuffer(GL_ARRAY_BUFFER, Singleton<ResourceManager>::GetInstance()->models[models].vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Singleton<ResourceManager>::GetInstance()->models[models].iboId);

	for (int j = 0; j < textureNum; j++) {
		glActiveTexture(GL_TEXTURE0 + j);
		glBindTexture(GL_TEXTURE_2D, Singleton<ResourceManager>::GetInstance()->TD_Textures[texture[j]].textureID);
		glUniform1i(glGetUniformLocation(shaders.program, "u_texture"), j);
	}

	/*glBindTexture(GL_TEXTURE_CUBE_MAP, Singleton<ResourceManager>::GetInstance()->cube_Textures[0].cubeTextureID);
	int cTextureLoc = glGetUniformLocation(shaders.program, "u_samplerCubeMap");
	glUniform1i(cTextureLoc, 0);*/

	if (shaders.positionAttribute != -1)
	{
		glEnableVertexAttribArray(shaders.positionAttribute);
		glVertexAttribPointer(shaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}
	if (shaders.uvAttribute != -1)
	{
		glEnableVertexAttribArray(shaders.uvAttribute);
		glVertexAttribPointer(shaders.uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizeof(Vector3)
			+ sizeof(Vector3) + sizeof(Vector3) + sizeof(Vector3));
	}

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDrawElements(GL_TRIANGLES, Singleton<ResourceManager>::GetInstance()->models[models].num_indice, GL_UNSIGNED_INT, 0);
	glDepthMask(GL_TRUE);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

int c = 0;
float a = -1.5;
float b = 0.1;
void Objects::update()
{	
	float x = ((rand() % (260 - 0 + 1) + 0) - 130) / 100.0000;//random vi tri bong bong'
	float y = ((rand() % (200 - 50 + 1) + 50)) / 100.0000;
	if (c == 1) {
		txw = x;
		tyw = -2.0;
		a = ((rand() % (200 - 50 + 1) + 50)) / 100.0000; //random độ cao bong bong'
		b = ((rand() % (200 - 150 + 1) + 150)) / 100000.0000;//random toc do bong bong'
		c = 0;
	}
	if (c == 0) {
		tyw += 0.002;
		if (tyw > a) {
			c = 1;
		}
	}
}

void Objects::update_world(float s, float x, float y, float z, float tx, float ty, float tz) {
	float sw;
	scaleMatrix.SetScale(sw);
	rxw += x*(PI / 180);
	ryw += y*(PI / 180);
	rzw += z*(PI / 180);
	Rx.SetRotationX(rxw * (PI / 180));
	Ry.SetRotationY(ryw * (PI / 180));
	Rz.SetRotationZ(rzw * (PI / 180));
	rotationMatrix = Rz * Rx * Ry;
	txw += tx;
	tyw += ty;
	tzw += tz;
	translationMatrix.SetTranslation(txw, tyw, tzw);
	wMatrix = scaleMatrix * rotationMatrix * translationMatrix;
	//set_wvp();
}

