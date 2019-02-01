#pragma once

#include<windows.h>
#include<string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Text
{
public:
	static void Draw(std::wstring str = std::wstring(), float x = 0, float y = 0, glm::vec3 color = glm::vec3(0));
	static void Draw(std::string str = std::string(), float x = 0, float y = 0, glm::vec3 color = glm::vec3(0));

public:
	Text(std::wstring str = std::wstring(), float x = 0, float y = 0, glm::vec3 color = glm::vec3(0));
	Text(std::string str, float x = 0, float y = 0, glm::vec3 color = glm::vec3(0));
	~Text();

	void setText(std::wstring str);
	void setText(std::string str);
	void setColor(float r, float g, float b, float a = 1.0f);
	void show();

protected:
	std::wstring str;
	float x;
	float y;
	glm::vec3 color;

};

